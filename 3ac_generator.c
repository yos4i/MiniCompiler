#include "3ac_generator.h"

int temp_counter = 0;
int label_counter = 0;
TAC* tac_list_head = NULL;
TAC* tac_list_tail = NULL;

char* new_temp() {
    char* temp = (char*)malloc(10);
    sprintf(temp, "t%d", temp_counter++);
    return temp;
}

char* new_label() {
    char* label = (char*)malloc(10);
    sprintf(label, "L%d", label_counter++);
    return label;
}

void emit_tac(char* op, char* arg1, char* arg2, char* result) {
    TAC* new_tac = (TAC*)malloc(sizeof(TAC));
    new_tac->op = op ? strdup(op) : NULL;
    new_tac->arg1 = arg1 ? strdup(arg1) : NULL;
    new_tac->arg2 = arg2 ? strdup(arg2) : NULL;
    new_tac->result = result ? strdup(result) : NULL;
    new_tac->next = NULL;
    
    if (tac_list_tail == NULL) {
        tac_list_head = tac_list_tail = new_tac;
    } else {
        tac_list_tail->next = new_tac;
        tac_list_tail = new_tac;
    }
}

void emit_label(char* label) {
    emit_tac("LABEL", label, NULL, NULL);
}

void emit_jump(char* label) {
    emit_tac("GOTO", label, NULL, NULL);
}

void emit_conditional_jump(char* condition, char* true_label, char* false_label) {
    emit_tac("IF", condition, true_label, false_label);
}

void print_tac_list() {
    TAC* current = tac_list_head;
    while (current != NULL) {
        if (strcmp(current->op, "LABEL") == 0) {
            printf("%s:\n", current->arg1);
        } else if (strcmp(current->op, "GOTO") == 0) {
            printf("\tGoto %s\n", current->arg1);
        } else if (strcmp(current->op, "IF") == 0) {
        } else if (strcmp(current->op, "BeginFunc") == 0) {
            printf("\tBeginFunc %s\n", current->arg1);
        } else if (strcmp(current->op, "EndFunc") == 0) {
            printf("\tEndFunc\n");
        } else if (strcmp(current->op, "=") == 0) {
            printf("\t%s = %s\n", current->result, current->arg1);
        } else if (strcmp(current->op, "+") == 0 || strcmp(current->op, "-") == 0 ||
                   strcmp(current->op, "*") == 0 || strcmp(current->op, "/") == 0 ||
                   strcmp(current->op, "%") == 0) {
            printf("\t%s = %s %s %s\n", current->result, current->arg1, current->op, current->arg2);
        } else if (strcmp(current->op, "==") == 0 || strcmp(current->op, "!=") == 0 ||
                   strcmp(current->op, "<") == 0 || strcmp(current->op, ">") == 0 ||
                   strcmp(current->op, "<=") == 0 || strcmp(current->op, ">=") == 0) {
        } else if (strcmp(current->op, "RETURN") == 0) {
            if (current->arg1) {
                printf("\tReturn %s\n", current->arg1);
            } else {
                printf("\tReturn\n");
            }
        } else if (strcmp(current->op, "PUSH") == 0) {
            printf("\tPushParam %s\n", current->arg1);
        } else if (strcmp(current->op, "CALL") == 0) {
            printf("\t%s = LCall %s\n", current->result, current->arg1);
        } else if (strcmp(current->op, "POP") == 0) {
            printf("\tPopParams %s\n", current->arg1);
        }
        current = current->next;
    }
}

void handle_logical_or(ExprAttributes* result, ExprAttributes* left, ExprAttributes* right) {
    char* true_label = new_label();
    char* false_label = new_label();
    char* end_label = new_label();
    char* temp = new_temp();
    
    emit_tac("IF_TRUE", left->place, true_label, NULL);
    
    emit_tac("IF_TRUE", right->place, true_label, false_label);
    
    emit_label(true_label);
    emit_tac("=", "1", NULL, temp);
    emit_jump(end_label);
    
    emit_label(false_label);
    emit_tac("=", "0", NULL, temp);
    
    emit_label(end_label);
    result->place = temp;
}

void handle_logical_and(ExprAttributes* result, ExprAttributes* left, ExprAttributes* right) {
    char* true_label = new_label();
    char* false_label = new_label();
    char* end_label = new_label();
    char* temp = new_temp();
    
    emit_tac("IF_FALSE", left->place, false_label, NULL);
    
    emit_tac("IF_FALSE", right->place, false_label, true_label);
    
    emit_label(true_label);
    emit_tac("=", "1", NULL, temp);
    emit_jump(end_label);
    
    emit_label(false_label);
    emit_tac("=", "0", NULL, temp);
    
    emit_label(end_label);
    result->place = temp;
}

void handle_relational_op(ExprAttributes* result, ExprAttributes* left, char* op, ExprAttributes* right) {
    char* temp = new_temp();
    char* true_label = new_label();
    char* false_label = new_label();
    char* end_label = new_label();
    
    emit_tac(op, left->place, right->place, true_label);
    emit_jump(false_label);
    
    emit_label(true_label);
    emit_tac("=", "1", NULL, temp);
    emit_jump(end_label);
    
    emit_label(false_label);
    emit_tac("=", "0", NULL, temp);
    
    emit_label(end_label);
    result->place = temp;
}

void emit_function_begin(char* name, int space) {
    char space_str[20];
    sprintf(space_str, "%d", space);
    emit_tac("BeginFunc", space_str, NULL, NULL);
}

void emit_function_end() {
    emit_tac("EndFunc", NULL, NULL, NULL);
}

void emit_function_call(char* result, char* func_name, int param_count) {
    emit_tac("CALL", func_name, NULL, result);
}

void emit_push_param(char* param) {
    emit_tac("PUSH", param, NULL, NULL);
}

void emit_pop_params(int size) {
    char size_str[20];
    sprintf(size_str, "%d", size);
    emit_tac("POP", size_str, NULL, NULL);
}

void emit_return(char* value) {
    emit_tac("RETURN", value, NULL, NULL);
}

void cleanup_tac() {
    TAC* current = tac_list_head;
    while (current != NULL) {
        TAC* next = current->next;
        if (current->op) free(current->op);
        if (current->arg1) free(current->arg1);
        if (current->arg2) free(current->arg2);
        if (current->result) free(current->result);
        free(current);
        current = next;
    }
    tac_list_head = tac_list_tail = NULL;
    temp_counter = 0;
    label_counter = 0;
}

void optimize_tac() {

}