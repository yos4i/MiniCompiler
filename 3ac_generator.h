#ifndef TAC_GENERATOR_H
#define TAC_GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Three Address Code structure
typedef struct TAC {
    char* op;
    char* arg1;
    char* arg2;
    char* result;
    struct TAC* next;
} TAC;

// Expression attributes for semantic actions
typedef struct {
    char* place;
    char* code;
    char* true_label;
    char* false_label;
    char* next_label;
} ExprAttributes;

// Global variables
extern int temp_counter;
extern int label_counter;
extern TAC* tac_list_head;
extern TAC* tac_list_tail;

// Function prototypes
char* new_temp();
char* new_label();
void emit_tac(char* op, char* arg1, char* arg2, char* result);
void emit_label(char* label);
void emit_jump(char* label);
void emit_conditional_jump(char* condition, char* true_label, char* false_label);
void print_tac_list();
void optimize_tac();
void cleanup_tac();

// Short-circuit evaluation functions
void handle_logical_or(ExprAttributes* result, ExprAttributes* left, ExprAttributes* right);
void handle_logical_and(ExprAttributes* result, ExprAttributes* left, ExprAttributes* right);
void handle_relational_op(ExprAttributes* result, ExprAttributes* left, char* op, ExprAttributes* right);

// Function handling
void emit_function_begin(char* name, int space);
void emit_function_end();
void emit_function_call(char* result, char* func_name, int param_count);
void emit_push_param(char* param);
void emit_pop_params(int size);
void emit_return(char* value);

#endif // TAC_GENERATOR_H