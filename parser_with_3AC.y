%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"
#include "semantic_analyzer.h"
#include "3ac_generator.h"

extern int yylex();
extern int yylineno;
extern char* yytext;
void yyerror(const char *s);

// Global variables for 3AC generation
int temp_count = 0;
int label_count = 0;
char* current_function = NULL;
int param_count = 0;

// 3AC instruction list
typedef struct TAC_Instruction {
    char* op;
    char* arg1;
    char* arg2;
    char* result;
    struct TAC_Instruction* next;
} TAC_Instruction;

TAC_Instruction* tac_head = NULL;
TAC_Instruction* tac_tail = NULL;

// Helper functions for 3AC generation
char* new_temp() {
    char* temp = (char*)malloc(10);
    sprintf(temp, "t%d", temp_count++);
    return temp;
}

char* new_label() {
    char* label = (char*)malloc(10);
    sprintf(label, "L%d", label_count++);
    return label;
}

void emit(char* op, char* arg1, char* arg2, char* result) {
    TAC_Instruction* new_inst = (TAC_Instruction*)malloc(sizeof(TAC_Instruction));
    new_inst->op = strdup(op);
    new_inst->arg1 = arg1 ? strdup(arg1) : NULL;
    new_inst->arg2 = arg2 ? strdup(arg2) : NULL;
    new_inst->result = result ? strdup(result) : NULL;
    new_inst->next = NULL;
    
    if (tac_tail == NULL) {
        tac_head = tac_tail = new_inst;
    } else {
        tac_tail->next = new_inst;
        tac_tail = new_inst;
    }
}

void print_3ac() {
    TAC_Instruction* inst = tac_head;
    while (inst != NULL) {
        if (strcmp(inst->op, "BeginFunc") == 0 || strcmp(inst->op, "EndFunc") == 0) {
            printf("%s %s\n", inst->op, inst->arg1 ? inst->arg1 : "");
        } else if (inst->result && inst->result[0] == 'L' && inst->op[0] != 'i' && inst->op[0] != 'G') {
            printf("%s:\n", inst->result);
        } else if (strcmp(inst->op, "if") == 0) {
            printf("\tif %s %s %s Goto %s\n", inst->arg1, inst->arg2, inst->result, inst->arg2);
        } else if (strcmp(inst->op, "Goto") == 0) {
            printf("\tGoto %s\n", inst->arg1);
        } else if (strcmp(inst->op, "=") == 0) {
            printf("\t%s = %s\n", inst->result, inst->arg1);
        } else if (strcmp(inst->op, "+") == 0 || strcmp(inst->op, "-") == 0 || 
                   strcmp(inst->op, "*") == 0 || strcmp(inst->op, "/") == 0) {
            printf("\t%s = %s %s %s\n", inst->result, inst->arg1, inst->op, inst->arg2);
        } else if (strcmp(inst->op, "Return") == 0) {
            printf("\tReturn %s\n", inst->arg1);
        } else if (strcmp(inst->op, "PushParam") == 0) {
            printf("\tPushParam %s\n", inst->arg1);
        } else if (strcmp(inst->op, "LCall") == 0) {
            printf("\t%s = LCall %s\n", inst->result, inst->arg1);
        } else if (strcmp(inst->op, "PopParams") == 0) {
            printf("\tPopParams %s\n", inst->arg1);
        }
        inst = inst->next;
    }
}

%}

%union {
    int num;
    float fnum;
    char* str;
    struct {
        char* place;
        char* true_label;
        char* false_label;
        char* next_label;
    } expr;
    struct {
        char* next_label;
    } stmt;
}

%token <num> NUMBER
%token <fnum> FLOAT_NUMBER
%token <str> IDENTIFIER STRING
%token DEF RETURN IF ELSE WHILE
%token INT FLOAT STRING_TYPE VOID
%token ASSIGN EQ NE LT GT LE GE
%token AND OR NOT
%token ARROW COLON SEMICOLON COMMA
%token LPAREN RPAREN LBRACE RBRACE

%type <str> type return_type
%type <expr> expression logical_expression relational_expression additive_expression multiplicative_expression primary_expression
%type <stmt> statement if_statement while_statement statement_list

%left OR
%left AND
%left EQ NE
%left LT GT LE GE
%left '+' '-'
%left '*' '/'
%right NOT

%%

program:
    function_list
    ;

function_list:
    function_list function
    | function
    ;

function:
    DEF IDENTIFIER LPAREN parameter_list RPAREN return_type COLON LBRACE {
        current_function = $2;
        printf("%s:\n", $2);
        
        // Calculate space needed for local variables
        int local_space = count_local_variables() * 4;
        char space_str[20];
        sprintf(space_str, "%d", local_space);
        emit("BeginFunc", space_str, NULL, NULL);
        
        // Reset counters for new function
        temp_count = 0;
    }
    statement_list RBRACE {
        emit("EndFunc", NULL, NULL, NULL);
        print_3ac();
        // Clear 3AC list for next function
        tac_head = tac_tail = NULL;
    }
    ;

parameter_list:
    /* empty */
    | parameters
    ;

parameters:
    parameters COMMA parameter
    | parameter
    ;

parameter:
    type IDENTIFIER
    ;

return_type:
    ARROW type { $$ = $2; }
    | /* empty */ { $$ = "void"; }
    ;

type:
    INT { $$ = "int"; }
    | FLOAT { $$ = "float"; }
    | STRING_TYPE { $$ = "string"; }
    | VOID { $$ = "void"; }
    ;

statement_list:
    statement_list statement { $$.next_label = $2.next_label; }
    | statement { $$.next_label = $1.next_label; }
    ;

statement:
    variable_declaration SEMICOLON { $$.next_label = NULL; }
    | assignment_statement SEMICOLON { $$.next_label = NULL; }
    | if_statement { $$.next_label = $1.next_label; }
    | while_statement { $$.next_label = $1.next_label; }
    | return_statement SEMICOLON { $$.next_label = NULL; }
    | expression SEMICOLON { $$.next_label = NULL; }
    | LBRACE statement_list RBRACE { $$.next_label = $2.next_label; }
    ;

variable_declaration:
    type identifier_list
    ;

identifier_list:
    identifier_list COMMA IDENTIFIER
    | IDENTIFIER
    ;

assignment_statement:
    IDENTIFIER ASSIGN expression {
        emit("=", $3.place, NULL, $1);
    }
    ;

if_statement:
    IF expression COLON {
        char* true_label = new_label();
        char* false_label = new_label();
        char* next_label = new_label();
        
        // For simple comparisons
        if ($2.true_label == NULL) {
            emit("if", $2.place, "==", "1");
            emit("Goto", true_label, NULL, NULL);
            emit("Goto", false_label, NULL, NULL);
        }
        
        emit(NULL, NULL, NULL, true_label); // Label
        $<stmt>$.next_label = next_label;
    }
    statement {
        char* next_label = $<stmt>4.next_label;
        emit("Goto", next_label, NULL, NULL);
        
        char* false_label = new_label();
        emit(NULL, NULL, NULL, false_label); // Label
    }
    else_part {
        char* next_label = $<stmt>4.next_label;
        emit(NULL, NULL, NULL, next_label); // Label
        $$.next_label = next_label;
    }
    ;

else_part:
    ELSE COLON statement
    | /* empty */
    ;

while_statement:
    WHILE {
        char* loop_label = new_label();
        emit(NULL, NULL, NULL, loop_label); // Label
        $<str>$ = loop_label;
    }
    expression COLON {
        char* body_label = new_label();
        char* exit_label = new_label();
        
        // Check condition
        emit("if", $3.place, "<", "1");
        emit("Goto", exit_label, NULL, NULL);
        emit("Goto", body_label, NULL, NULL);
        
        emit(NULL, NULL, NULL, body_label); // Label
        
        $<stmt>$.next_label = exit_label;
    }
    LBRACE statement_list RBRACE {
        char* loop_label = $<str>2;
        char* exit_label = $<stmt>5.next_label;
        
        emit("Goto", loop_label, NULL, NULL);
        emit(NULL, NULL, NULL, exit_label); // Label
        
        $$.next_label = exit_label;
    }
    ;

return_statement:
    RETURN expression {
        emit("Return", $2.place, NULL, NULL);
    }
    | RETURN {
        emit("Return", NULL, NULL, NULL);
    }
    ;

expression:
    logical_expression { $$ = $1; }
    ;

logical_expression:
    logical_expression OR logical_expression {
        // Short-circuit evaluation for OR
        char* temp = new_temp();
        char* true_label = new_label();
        char* false_label = new_label();
        char* end_label = new_label();
        
        // If first expression is true, skip second
        emit("if", $1.place, "==", "1");
        emit("Goto", true_label, NULL, NULL);
        
        // Evaluate second expression
        emit("if", $3.place, "==", "1");
        emit("Goto", true_label, NULL, NULL);
        emit("Goto", false_label, NULL, NULL);
        
        emit(NULL, NULL, NULL, true_label);
        emit("=", "1", NULL, temp);
        emit("Goto", end_label, NULL, NULL);
        
        emit(NULL, NULL, NULL, false_label);
        emit("=", "0", NULL, temp);
        
        emit(NULL, NULL, NULL, end_label);
        $$.place = temp;
    }
    | logical_expression AND logical_expression {
        // Short-circuit evaluation for AND
        char* temp = new_temp();
        char* true_label = new_label();
        char* false_label = new_label();
        char* end_label = new_label();
        
        // If first expression is false, skip second
        emit("if", $1.place, "==", "0");
        emit("Goto", false_label, NULL, NULL);
        
        // Evaluate second expression
        emit("if", $3.place, "==", "0");
        emit("Goto", false_label, NULL, NULL);
        emit("Goto", true_label, NULL, NULL);
        
        emit(NULL, NULL, NULL, true_label);
        emit("=", "1", NULL, temp);
        emit("Goto", end_label, NULL, NULL);
        
        emit(NULL, NULL, NULL, false_label);
        emit("=", "0", NULL, temp);
        
        emit(NULL, NULL, NULL, end_label);
        $$.place = temp;
    }
    | relational_expression { $$ = $1; }
    ;

relational_expression:
    additive_expression EQ additive_expression {
        char* temp = new_temp();
        emit("==", $1.place, $3.place, temp);
        $$.place = temp;
    }
    | additive_expression NE additive_expression {
        char* temp = new_temp();
        emit("!=", $1.place, $3.place, temp);
        $$.place = temp;
    }
    | additive_expression LT additive_expression {
        char* temp = new_temp();
        emit("<", $1.place, $3.place, temp);
        $$.place = temp;
    }
    | additive_expression GT additive_expression {
        char* temp = new_temp();
        emit(">", $1.place, $3.place, temp);
        $$.place = temp;
    }
    | additive_expression LE additive_expression {
        char* temp = new_temp();
        emit("<=", $1.place, $3.place, temp);
        $$.place = temp;
    }
    | additive_expression GE additive_expression {
        char* temp = new_temp();
        emit(">=", $1.place, $3.place, temp);
        $$.place = temp;
    }
    | additive_expression { $$ = $1; }
    ;

additive_expression:
    additive_expression '+' multiplicative_expression {
        char* temp = new_temp();
        emit("+", $1.place, $3.place, temp);
        $$.place = temp;
    }
    | additive_expression '-' multiplicative_expression {
        char* temp = new_temp();
        emit("-", $1.place, $3.place, temp);
        $$.place = temp;
    }
    | multiplicative_expression { $$ = $1; }
    ;

multiplicative_expression:
    multiplicative_expression '*' primary_expression {
        char* temp = new_temp();
        emit("*", $1.place, $3.place, temp);
        $$.place = temp;
    }
    | multiplicative_expression '/' primary_expression {
        char* temp = new_temp();
        emit("/", $1.place, $3.place, temp);
        $$.place = temp;
    }
    | primary_expression { $$ = $1; }
    ;

primary_expression:
    NUMBER {
        char* temp = new_temp();
        char num_str[20];
        sprintf(num_str, "%d", $1);
        emit("=", num_str, NULL, temp);
        $$.place = temp;
    }
    | FLOAT_NUMBER {
        char* temp = new_temp();
        char num_str[20];
        sprintf(num_str, "%.2f", $1);
        emit("=", num_str, NULL, temp);
        $$.place = temp;
    }
    | IDENTIFIER {
        $$.place = $1;
    }
    | IDENTIFIER LPAREN argument_list RPAREN {
        // Function call
        char* temp = new_temp();
        emit("LCall", $1, NULL, temp);
        
        // Pop parameters
        char param_size[20];
        sprintf(param_size, "%d", param_count * 8);
        emit("PopParams", param_size, NULL, NULL);
        
        param_count = 0;
        $$.place = temp;
    }
    | LPAREN expression RPAREN {
        $$ = $2;
    }
    ;

argument_list:
    /* empty */
    | arguments
    ;

arguments:
    arguments COMMA expression {
        emit("PushParam", $3.place, NULL, NULL);
        param_count++;
    }
    | expression {
        emit("PushParam", $1.place, NULL, NULL);
        param_count = 1;
    }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error at line %d: %s\n", yylineno, s);
}

int count_local_variables() {
    // This function should count local variables in current scope
    // For now, return a default value
    return 6; // Adjust based on actual variable count
}