%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "semantic.h"
#include "3ac_generator.h"

node* ast_root = NULL;
int syntax_error_occurred = 0; 
int yylex(void);
void yyerror(const char *msg);
void printtree(node *tree, int level);
int syntax_error_count = 0;
node* append_node(node* list, node* new_node);
char* current_function = NULL;
char currentLineText[1024] = "";
int currentPos = 0;
int param_count = 0;
int func_counter = 1;

char* generate_expr_code(node* expr);
void generate_stmt_code(node* stmt);
void generate_func_code(node* func);

%}

%union {
    struct node *n;
}

%debug
%token <n> BOOL_LIT REL_OP DEF TOKEN_TYPE POW INT_LIT HEX_LIT FLOAT_LIT STRING_LIT ID MAIN_ID
%token <n> IF ELIF ELSE WHILE RETURN TOKEN_PASS AND OR NOT IS ARROW PRINT

%type <n> CODE FUNC FUNC_LIST FUNC_CALL PARAMS TYPE_GROUP BODY
%type <n> RET_TYPE BLOCK STMT STMT_LIST EXPR RETURN_STMT ASSIGNMENT IF_STMT ARGS
%type <n> BARE_PARAM_LIST DEFAULT_PARAM_LIST PARAM_WITH_DEFAULT LITERAL DECLARATION
%type <n> DECL_LIST DECL_ITEM PASS LHS LHS_LIST EXPR_LIST ARG_LIST FUNC_CALL_STMT
%type <n> ELIF_LIST ELIF_BLOCK WHILE_STMT SUITE PRINT_STMT

%right '='
%left OR
%left AND
%right NOT
%left REL_OP IS
%left '+' '-'
%left '*' '/'
%right POW
%right UMINUS
%left '[' ']'
%left '(' ')'


%%

CODE: FUNC_LIST { 
    $$ = mknode("CODE", $1, NULL); 
    ast_root = $$; 
};

FUNC_LIST: FUNC_LIST FUNC { $$ = mknode("FUNC_LIST", $1, $2); }
         | FUNC           { $$ = $1; };

FUNC: DEF ID '(' ARGS ')' RET_TYPE ':' SUITE {
    $$ = mknode("FUNC", $2, mknode("ARGS", $4, mknode($6->token, $6->left, $8)));
}
| DEF MAIN_ID '(' ')' ':' SUITE {
    $$ = mknode("FUNC", $2, mknode("ARGS", mknode("NONE", NULL, NULL), mknode("RETURN VOID", NULL, $6)));
};

ARGS: PARAMS { $$ = $1; }
    |         { $$ = mknode("NONE", NULL, NULL); };

RET_TYPE: ARROW TOKEN_TYPE { $$ = mknode("RET", $2, NULL); }
        |                  { $$ = mknode("RETURN VOID", NULL, NULL); };

PARAMS: TYPE_GROUP              { $$ = $1; }
      | PARAMS ';' TYPE_GROUP   { $$ = mknode("PARAMS", $1, $3); };

TYPE_GROUP: TOKEN_TYPE BARE_PARAM_LIST              { $$ = mknode($1->token, $2, NULL); }
          | TOKEN_TYPE BARE_PARAM_LIST ',' DEFAULT_PARAM_LIST { $$ = mknode($1->token, mknode("BARE", $2, $4), NULL); }
          | TOKEN_TYPE DEFAULT_PARAM_LIST           { $$ = mknode($1->token, $2, NULL); };

BARE_PARAM_LIST: ID                          { $$ = $1; }  
               | BARE_PARAM_LIST ',' ID      { $$ = append_node($1, $3); };

DEFAULT_PARAM_LIST: PARAM_WITH_DEFAULT        { $$ = $1; }
                  | DEFAULT_PARAM_LIST ',' PARAM_WITH_DEFAULT { $$ = mknode($1->token, $1, $3); };

PARAM_WITH_DEFAULT: ID ':' LITERAL            { $$ = mknode("DEFAULT", $1, $3); };

LITERAL: INT_LIT      { $$ = $1; }
       | HEX_LIT      { $$ = $1; }
       | FLOAT_LIT    { $$ = $1; }
       | STRING_LIT   { $$ = $1; }
       | BOOL_LIT     { $$ = $1; };

SUITE: STMT  { $$ = $1; }
     | BLOCK { $$ = $1; };

BLOCK: '{' BODY '}' { $$ = $2; };

BODY: STMT_LIST { $$ = mknode("BODY", $1, NULL); }
    |           { $$ = mknode("BODY", NULL, NULL); };

STMT_LIST: STMT_LIST STMT { $$ = mknode("STMT_LIST", $1, $2); }
         | STMT { $$ = $1; };

DECLARATION: TOKEN_TYPE DECL_LIST ';' { $$ = mknode($1->token, $2, NULL); };

DECL_LIST: DECL_ITEM                 { $$ = $1; }
         | DECL_ITEM ',' DECL_LIST   { $$ = mknode("DECL_LIST", $1, $3); };

DECL_ITEM: ID                        { $$ = $1; }
         | ID '=' EXPR               { $$ = mknode("ASSIGN", $1, $3); };

STMT:
      FUNC_CALL_STMT { $$ = $1; }
    | ASSIGNMENT     { $$ = $1; }
    | DECLARATION    { $$ = $1; }
    | RETURN_STMT    { $$ = $1; }
    | IF_STMT        { $$ = $1; }
    | WHILE_STMT     { $$ = $1; }
    | PRINT_STMT     { $$ = $1; }
    | PASS           { $$ = $1; }
    | error ';'      { yyerror("Error in statement"); yyerrok; };

PASS: TOKEN_PASS ';' { $$ = mknode("PASS", $1, NULL); };

PRINT_STMT: PRINT '(' EXPR ')' ';' { $$ = mknode("PRINT", $3, NULL); };

LHS: ID                     { $$ = $1; }
   | ID '[' EXPR ']'       { $$ = mknode("INDEX", $1, $3); };

LHS_LIST: LHS                     { $$ = $1; }
        | LHS_LIST ',' LHS       { $$ = mknode("LHS_LIST", $1, $3); };

ASSIGNMENT: LHS_LIST '=' EXPR ';' { $$ = mknode("ASS", $1, $3); };

RETURN_STMT: RETURN EXPR ';' { $$ = mknode("RET", $2, NULL); }
           | RETURN ';'      { $$ = mknode("RET", NULL, NULL); };

FUNC_CALL: ID '(' ARG_LIST ')' { $$ = mknode("CALL", $1, $3); };

ARG_LIST: EXPR_LIST { $$ = mknode("ARGS", $1, NULL); }
        |           { $$ = mknode("ARGS", mknode("NONE", NULL, NULL), NULL); };

EXPR_LIST: EXPR                  { $$ = $1; }
         | EXPR_LIST ',' EXPR   { $$ = mknode("EXPR_LIST", $1, $3); };

FUNC_CALL_STMT: FUNC_CALL ';' { $$ = $1; };

IF_STMT:
    IF EXPR ':' SUITE ELSE ':' SUITE         { $$ = mknode("IF-ELSE", $2, mknode("BLOCK", $4, $7)); }
  | IF EXPR ':' SUITE ELIF_LIST ELSE ':' SUITE { $$ = mknode("IF-ELIF-ELSE", $2, mknode("CHAIN", $4, mknode("ELIFS", $5, $8))); }
  | IF EXPR ':' SUITE ELIF_LIST              { $$ = mknode("IF-ELIF", $2, mknode("CHAIN", $4, $5)); }
  | IF EXPR ':' SUITE                         { $$ = mknode("IF", $2, $4); };

ELIF_LIST:
    ELIF_BLOCK                                { $$ = $1; }
  | ELIF_LIST ELIF_BLOCK                      { $$ = mknode("ELIF_LIST", $1, $2); };

ELIF_BLOCK:
    ELIF EXPR ':' SUITE                       { $$ = mknode("ELIF", $2, $4); };

WHILE_STMT: WHILE EXPR ':' SUITE { $$ = mknode("WHILE", $2, $4); };

EXPR:  EXPR '+' EXPR            { $$ = mknode("+", $1, $3); }
    | EXPR '-' EXPR             { $$ = mknode("-", $1, $3); }
    | EXPR '*' EXPR             { $$ = mknode("*", $1, $3); }
    | EXPR '/' EXPR             { $$ = mknode("/", $1, $3); }
    | EXPR POW EXPR             { $$ = mknode("**", $1, $3); }
    | EXPR REL_OP EXPR          { $$ = mknode($2->token, $1, $3); }
    | EXPR AND EXPR             { $$ = mknode("AND", $1, $3); }
    | EXPR OR EXPR              { $$ = mknode("OR", $1, $3); }
    | NOT EXPR                  { $$ = mknode("NOT", $2, NULL); }
    | '-' EXPR %prec UMINUS     { $$ = mknode("NEG", $2, NULL); }
    | '(' EXPR ')'              { $$ = $2; }
    | ID                        { $$ = $1; }
    | INT_LIT                   { $$ = $1; }
    | STRING_LIT                { $$ = $1; }
    | BOOL_LIT                  { $$ = $1; }
    | FLOAT_LIT                 { $$ = $1; }
    | HEX_LIT                   { $$ = $1; }
    | FUNC_CALL                 { $$ = $1; }
    | EXPR '[' EXPR ']'                     { $$ = mknode("INDEX", $1, $3); }
    | EXPR '[' EXPR ':' EXPR ']'            { $$ = mknode("SLICE", $1, mknode("RANGE", $3, $5)); }
    | EXPR '[' ':' EXPR ']'                 { $$ = mknode("SLICE", $1, mknode("RANGE", mknode("START", NULL, NULL), $4)); }
    | EXPR '[' EXPR ':' ']'                 { $$ = mknode("SLICE", $1, mknode("RANGE", $3, mknode("END", NULL, NULL))); }
    | EXPR '[' ':' ']'                      { $$ = mknode("SLICE", $1, mknode("RANGE", mknode("START", NULL, NULL), mknode("END", NULL, NULL))); }
    | EXPR '[' EXPR ':' EXPR ':' EXPR ']'   { $$ = mknode("SLICE", $1, mknode("RANGE", $3, mknode("STEP", $5, $7))); }
    | EXPR '[' ':' ':' EXPR ']'             { $$ = mknode("SLICE", $1, mknode("RANGE", mknode("START", NULL, NULL), mknode("STEP", mknode("END", NULL, NULL), $5))); };

%%

node* append_node(node* list, node* new_node) {
    if (!list) return new_node;
    
    if (strcmp(list->token, "PARAM_LIST") != 0) {
        return mknode("PARAM_LIST", list, new_node);
    }
    
    node* current = list;
    while (current && strcmp(current->token, "PARAM_LIST") == 0 && current->right) {
        current = current->right;
    }
    
    if (strcmp(current->token, "PARAM_LIST") != 0) {
        node* new_list = mknode("PARAM_LIST", current, new_node);
        return list == current ? new_list : list;
    }
    
    current->right = new_node;
    return list;
}

void printtree(node *tree, int level) {
    if (!tree) return;
    for (int i = 0; i < level; i++) printf("  ");
    printf("(%s", tree->token);
    if (tree->left || tree->right) {
        printf("\n");
        printtree(tree->left, level + 1);
        printtree(tree->right, level + 1);
        for (int i = 0; i < level; i++) printf("  ");
    }
    printf(")\n");
}

void yyerror(const char *msg) {
    extern int yylineno;
    extern char currentLineText[];
    extern int currentPos;

    syntax_error_occurred = 1;  
    
    fprintf(stderr, "\nSyntax error at line %d!\n", yylineno);
    fprintf(stderr, "%s\n", currentLineText);
    if (currentPos > 0) {
        for (int i = 0; i < currentPos; i++) fprintf(stderr, " ");
        fprintf(stderr, "^\n");
    }
}


char* generate_expr_code(node* expr) {
    if (!expr) return NULL;
    int temp_counter = 0;

    if (!expr->left && !expr->right) {
        if (expr->token[0] >= '0' && expr->token[0] <= '9') {
            char* temp = new_temp();
            printf("\t%s = %s\n", temp, expr->token);
            return temp;
        }
        if (strstr(expr->token, ".") != NULL) {
            char* temp = new_temp();
            printf("\t%s = %s\n", temp, expr->token);
            return temp;
        }
        return expr->token;
    }

    
    
    if (strcmp(expr->token, "+") == 0 || strcmp(expr->token, "-") == 0 ||
        strcmp(expr->token, "*") == 0 || strcmp(expr->token, "/") == 0) {
        char* left_temp = generate_expr_code(expr->left);
        char* right_temp = generate_expr_code(expr->right);
        char* result_temp = new_temp();
        printf("\t%s = %s %s %s\n", result_temp, left_temp, expr->token, right_temp);
        return result_temp;
    }
    
    if (strcmp(expr->token, "==") == 0 || strcmp(expr->token, "!=") == 0 ||
        strcmp(expr->token, "<") == 0 || strcmp(expr->token, ">") == 0 ||
        strcmp(expr->token, "<=") == 0 || strcmp(expr->token, ">=") == 0) {
        return NULL; 
    }
    
    if (strcmp(expr->token, "CALL") == 0) {
        param_count = 0;
        node* args = expr->right;
        if (args && args->left && strcmp(args->left->token, "NONE") != 0) {
            node* arg = args->left;
            while (arg) {
                if (strcmp(arg->token, "EXPR_LIST") == 0) {
                    char* temp = generate_expr_code(arg->left);
                    printf("\tPushParam %s\n", temp);
                    param_count++;
                    arg = arg->right;
                } else {
                    char* temp = generate_expr_code(arg);
                    printf("\tPushParam %s\n", temp);
                    param_count++;
                    break;
                }
            }
        }
        
        char* result_temp = new_temp();
        printf("\t%s = LCall %s\n", result_temp, expr->left->token);
        printf("\tPopParams %d\n", param_count * 8);
        
        return result_temp;
    }
    
    return expr->token;
}


void generate_stmt_code(node* stmt) {
    if (!stmt) return;
    
    if (strcmp(stmt->token, "STMT_LIST") == 0) {
        generate_stmt_code(stmt->left);
        generate_stmt_code(stmt->right);
        return;
    }
    
    if (strcmp(stmt->token, "BODY") == 0) {
        generate_stmt_code(stmt->left);
        return;
    }
    
    if (strcmp(stmt->token, "int") == 0 || strcmp(stmt->token, "float") == 0) {
        node* decl = stmt->left;
        while (decl) {
            if (strcmp(decl->token, "ASSIGN") == 0) {
                char* expr_result = generate_expr_code(decl->right);
                if (expr_result && decl->left) {
                    printf("\t%s = %s\n", decl->left->token, expr_result);
                }
            }
            if (strcmp(decl->token, "DECL_LIST") == 0) {
                decl = decl->right;
            } else {
                break;
            }
        }
        return;
    }
    
    if (strcmp(stmt->token, "ASS") == 0) {
        char* expr_result = generate_expr_code(stmt->right);
        if (expr_result && stmt->left) {
            printf("\t%s = %s\n", stmt->left->token, expr_result);
        }
        return;
    }
    
    if (strcmp(stmt->token, "IF") == 0 || 
        strcmp(stmt->token, "IF-ELSE") == 0 ||
        strcmp(stmt->token, "IF-ELIF") == 0 ||
        strcmp(stmt->token, "IF-ELIF-ELSE") == 0) {
        
        char* end_label = new_label();
        
        char* true_label = new_label();
        char* false_label = new_label();
        
        if (stmt->left && stmt->left->token) {
            char* op = stmt->left->token;
            char* left = generate_expr_code(stmt->left->left);
            char* right = generate_expr_code(stmt->left->right);
            printf("\tif %s %s %s Goto %s\n", left, op, right, true_label);
            printf("\tGoto %s\n", false_label);
        }
        
        printf("%s:\n", true_label);
        if (strcmp(stmt->token, "IF") == 0) {
            generate_stmt_code(stmt->right);
        } else {
            if (stmt->right && stmt->right->left) {
                generate_stmt_code(stmt->right->left);
            }
        }
        printf("\tGoto %s\n", end_label);
        
        printf("%s:\n", false_label);
        
        if (strcmp(stmt->token, "IF-ELSE") == 0) {
            if (stmt->right && stmt->right->right) {
                generate_stmt_code(stmt->right->right);
            }
        } else if (strcmp(stmt->token, "IF-ELIF") == 0 || 
                   strcmp(stmt->token, "IF-ELIF-ELSE") == 0) {
            node* elif_chain = NULL;
            if (strcmp(stmt->token, "IF-ELIF") == 0) {
                elif_chain = stmt->right->right;
            } else {
                if (stmt->right && stmt->right->right && stmt->right->right->left) {
                    elif_chain = stmt->right->right->left;
                }
            }
            
            while (elif_chain) {
                if (strcmp(elif_chain->token, "ELIF") == 0) {
                    char* elif_true = new_label();
                    char* elif_false = new_label();
                    
                    if (elif_chain->left && elif_chain->left->token) {
                        char* op = elif_chain->left->token;
                        char* left = generate_expr_code(elif_chain->left->left);
                        char* right = generate_expr_code(elif_chain->left->right);
                        printf("\tif %s %s %s Goto %s\n", left, op, right, elif_true);
                        printf("\tGoto %s\n", elif_false);
                    }
                    
                    printf("%s:\n", elif_true);
                    generate_stmt_code(elif_chain->right);
                    printf("\tGoto %s\n", end_label);
                    
                    printf("%s:\n", elif_false);
                    break;
                } else if (strcmp(elif_chain->token, "ELIF_LIST") == 0) {
                    node* current_elif = elif_chain->left;
                    if (current_elif && strcmp(current_elif->token, "ELIF") == 0) {
                        char* elif_true = new_label();
                        char* elif_false = new_label();
                        
                        if (current_elif->left && current_elif->left->token) {
                            char* op = current_elif->left->token;
                            char* left = generate_expr_code(current_elif->left->left);
                            char* right = generate_expr_code(current_elif->left->right);
                            printf("\tif %s %s %s Goto %s\n", left, op, right, elif_true);
                            printf("\tGoto %s\n", elif_false);
                        }
                        
                        printf("%s:\n", elif_true);
                        generate_stmt_code(current_elif->right);
                        printf("\tGoto %s\n", end_label);
                        
                        printf("%s:\n", elif_false);
                    }
                    elif_chain = elif_chain->right;
                } else {
                    break;
                }
            }
            
            if (strcmp(stmt->token, "IF-ELIF-ELSE") == 0) {
                if (stmt->right && stmt->right->right && stmt->right->right->right) {
                    generate_stmt_code(stmt->right->right->right);
                }
            }
        }
        
        printf("%s:\n", end_label);
        return;
    }
    
    if (strcmp(stmt->token, "WHILE") == 0) {
        char* loop_label = new_label();
        char* body_label = new_label();
        char* exit_label = new_label();
        
        printf("%s:\n", loop_label);
        
        if (stmt->left && stmt->left->token) {
            char* op = stmt->left->token;
            char* left = generate_expr_code(stmt->left->left);
            char* right = generate_expr_code(stmt->left->right);
            printf("\tif %s %s %s Goto %s\n", left, op, right, body_label);
            printf("\tGoto %s\n", exit_label);
        }
        
        printf("%s:\n", body_label);
        if (stmt->right) {
            generate_stmt_code(stmt->right);
        }
        printf("\tGoto %s\n", loop_label);
        
        printf("%s:\n", exit_label);
        return;
    }
    
    if (strcmp(stmt->token, "RET") == 0) {
        if (stmt->left) {
            char* ret_value = generate_expr_code(stmt->left);
            printf("\tReturn %s\n", ret_value);
        } else {
            printf("\tReturn\n");
        }
        return;
    }
    
    if (strcmp(stmt->token, "BLOCK") == 0) {
        generate_stmt_code(stmt->left);
        generate_stmt_code(stmt->right);
        return;
    }
    
    if (strcmp(stmt->token, "CALL") == 0) {
        generate_expr_code(stmt);
        return;
    }
}



void generate_func_code(node* func) {
    if (!func) return;
    
    if (strcmp(func->token, "FUNC") == 0) {
        char* func_name = func->left->token;
        printf("%s:\n", func_name);
        
        printf("\tBeginFunc %d\n", func_counter++);

        
        
        node* args_node = func->right;
        if (args_node && args_node->right) {
            node* ret_type_node = args_node->right;
            if (ret_type_node && ret_type_node->right) {
                generate_stmt_code(ret_type_node->right);
            }
        }
        
        printf("\tEndFunc\n");

    }
}

void generate_funcs_from_list(node* func_list) {
    if (!func_list) return;

    if (strcmp(func_list->token, "FUNC_LIST") == 0) {
        generate_funcs_from_list(func_list->left);
        generate_func_code(func_list->right);
    } else {
        generate_func_code(func_list);
    }
}

void generate_3ac_from_ast(node* root) {
    if (!root) return;

    if (strcmp(root->token, "CODE") == 0) {
        generate_funcs_from_list(root->left);
    }
}


int main() {
    extern int yydebug;
    yydebug = 0;
    
    int result = yyparse();
    
    if (result == 0 && syntax_error_occurred == 0 && ast_root != NULL) {
        int errors = analyze_tree(ast_root);
        
        if (errors > 0) {
            printf("Semantic errors found. Compilation failed.\n");
            exit(1);
        }
        
        generate_3ac_from_ast(ast_root);
        
        return 0;
    } else {
        printf("Parsing failed due to syntax errors\n");
        return 1;
    }
}