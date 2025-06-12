#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol_table.h"

static scope *current_scope = NULL;
static scope *global_scope = NULL;

void init_symbol_table() {
    global_scope = (scope*)malloc(sizeof(scope));
    global_scope->level = 0;
    global_scope->symbols = NULL;
    global_scope->parent = NULL;
    current_scope = global_scope;
}

void enter_scope() {
    scope *new_scope = (scope*)malloc(sizeof(scope));
    new_scope->level = current_scope->level + 1;
    new_scope->symbols = NULL;
    new_scope->parent = current_scope;
    current_scope = new_scope;
}

void exit_scope() {
    if (current_scope->parent != NULL) {
        scope *temp = current_scope;
        current_scope = current_scope->parent;
        
        symbol *sym = temp->symbols;
        while (sym) {
            symbol *next = sym->next;
            free(sym->name);
            
            if (sym->sym_type == SYMBOL_FUNCTION) {
                param *p = sym->params;
                while (p) {
                    param *next_p = p->next;
                    free(p->name);
                    free(p);
                    p = next_p;
                }
            }
            
            free(sym);
            sym = next;
        }
        
        free(temp);
    }
}

symbol* add_symbol(char *name, symbol_type type, data_type dtype) {
    symbol *new_sym = (symbol*)malloc(sizeof(symbol));
    new_sym->name = strdup(name);
    new_sym->sym_type = type;
    new_sym->data_type = dtype;
    new_sym->scope_level = current_scope->level;
    new_sym->params = NULL;
    new_sym->param_count = 0;
    new_sym->required_params = 0;
    new_sym->return_type = TYPE_VOID;
    
    new_sym->next = current_scope->symbols;
    current_scope->symbols = new_sym;
    
    return new_sym;
}

symbol* lookup_symbol(char *name) {
    scope *s = current_scope;
    while (s != NULL) {
        symbol *sym = s->symbols;
        while (sym != NULL) {
            if (strcmp(sym->name, name) == 0) {
                return sym;
            }
            sym = sym->next;
        }
        s = s->parent;
    }
    return NULL;
}

symbol* lookup_symbol_in_current_scope(char *name) {
    symbol *sym = current_scope->symbols;
    while (sym != NULL) {
        if (strcmp(sym->name, name) == 0) {
            return sym;
        }
        sym = sym->next;
    }
    return NULL;
}

data_type string_to_type(char *type_str) {
    if (strcmp(type_str, "int") == 0) return TYPE_INT;
    if (strcmp(type_str, "float") == 0) return TYPE_FLOAT;
    if (strcmp(type_str, "string") == 0) return TYPE_STRING;
    if (strcmp(type_str, "bool") == 0) return TYPE_BOOL;
    if (strcmp(type_str, "void") == 0) return TYPE_VOID;
    return TYPE_UNKNOWN;
}

char* type_to_string(data_type type) {
    switch (type) {
        case TYPE_INT: return "int";
        case TYPE_FLOAT: return "float";
        case TYPE_STRING: return "string";
        case TYPE_BOOL: return "bool";
        case TYPE_VOID: return "void";
        default: return "unknown";
    }
}

void add_function_param(symbol *func, char *name, data_type type, int has_default, node *default_val) {
    if (func->sym_type != SYMBOL_FUNCTION) return;
    
    param *new_param = (param*)malloc(sizeof(param));
    new_param->name = strdup(name);
    new_param->type = type;
    new_param->has_default = has_default;
    new_param->default_value = default_val;
    new_param->next = NULL;
    
    if (func->params == NULL) {
        func->params = new_param;
    } else {
        param *p = func->params;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = new_param;
    }
    
    func->param_count++;
    if (!has_default) {
        func->required_params++;
    }
}

void free_symbol_table() {
    while (current_scope != NULL) {
        exit_scope();
    }
}

data_type get_literal_type(node *literal) {
    if (!literal) return TYPE_UNKNOWN;
    
    char *token = literal->token;
    
    if (strcmp(token, "True") == 0 || strcmp(token, "False") == 0) {
        return TYPE_BOOL;
    }
    
    if (token[0] == '"' || token[0] == '\'') {
        return TYPE_STRING;
    }
    
    if (strchr(token, '.') != NULL) {
        return TYPE_FLOAT;
    }
    
    if (strlen(token) > 2 && token[0] == '0' && (token[1] == 'x' || token[1] == 'X')) {
        return TYPE_INT;
    }
    
    return TYPE_INT;
}

data_type get_expression_type(node *expr) {
    if (!expr) return TYPE_UNKNOWN;
    
    if (strcmp(expr->token, "True") == 0 || strcmp(expr->token, "False") == 0) {
        return TYPE_BOOL;
    }
    
    if (expr->token[0] == '"' || expr->token[0] == '\'') {
        return TYPE_STRING;
    }
    
    if (strchr(expr->token, '.') != NULL) {
        char *endptr;
        strtod(expr->token, &endptr);
        if (*endptr == '\0') {
            return TYPE_FLOAT;
        }
    }
    
    if ((expr->token[0] >= '0' && expr->token[0] <= '9') ||
        (expr->token[0] == '-' && expr->token[1] >= '0' && expr->token[1] <= '9')) {
        return get_literal_type(expr);
    }
    
    symbol *sym = lookup_symbol(expr->token);
    if (sym) {
        if (sym->sym_type == SYMBOL_VARIABLE) {
            return sym->data_type;
        } else if (sym->sym_type == SYMBOL_FUNCTION) {
            return TYPE_UNKNOWN;
        }
    }
    
    if (strcmp(expr->token, "CALL") == 0 && expr->left) {
        symbol *func = lookup_symbol(expr->left->token);
        if (func && func->sym_type == SYMBOL_FUNCTION) {
            return func->return_type;
        }
    }
    
    if (strcmp(expr->token, "+") == 0 || strcmp(expr->token, "-") == 0 ||
        strcmp(expr->token, "*") == 0 || strcmp(expr->token, "/") == 0 ||
        strcmp(expr->token, "**") == 0) {
        data_type left_type = get_expression_type(expr->left);
        data_type right_type = get_expression_type(expr->right);
        
        if (left_type == TYPE_FLOAT || right_type == TYPE_FLOAT) {
            return TYPE_FLOAT;
        }
        if (left_type == TYPE_INT && right_type == TYPE_INT) {
            return TYPE_INT;
        }
        return TYPE_UNKNOWN;
    }
    
    if (strcmp(expr->token, "<") == 0 || strcmp(expr->token, ">") == 0 ||
        strcmp(expr->token, "<=") == 0 || strcmp(expr->token, ">=") == 0 ||
        strcmp(expr->token, "==") == 0 || strcmp(expr->token, "!=") == 0) {
        return TYPE_BOOL;
    }
    
    if (strcmp(expr->token, "AND") == 0 || strcmp(expr->token, "OR") == 0) {
        return TYPE_BOOL;
    }
    
    if (strcmp(expr->token, "NOT") == 0) {
        return TYPE_BOOL;
    }
    
    if (strcmp(expr->token, "NEG") == 0) {
        return get_expression_type(expr->left);
    }
    
    if (strcmp(expr->token, "INDEX") == 0) {
        data_type base_type = get_expression_type(expr->left);
        if (base_type == TYPE_STRING) {
            return TYPE_STRING;
        }
        return TYPE_UNKNOWN;
    }
    
    if (strcmp(expr->token, "SLICE") == 0) {
        data_type base_type = get_expression_type(expr->left);
        if (base_type == TYPE_STRING) {
            return TYPE_STRING;
        }
        return TYPE_UNKNOWN;
    }
    
    return TYPE_UNKNOWN;
}

int function_exists_globally(char *name) {
    symbol *sym = global_scope->symbols;
    while (sym) {
        if (sym->sym_type == SYMBOL_FUNCTION && strcmp(sym->name, name) == 0) {
            return 1;
        }
        sym = sym->next;
    }
    return 0;
}

symbol* lookup_symbol_in_global_scope(char *name) {
    symbol *sym = global_scope->symbols;
    while (sym != NULL) {
        if (strcmp(sym->name, name) == 0) {
            return sym;
        }
        sym = sym->next;
    }
    return NULL;
}


int types_compatible(data_type t1, data_type t2) {
    if (t1 == t2) return 1;
    
    if ((t1 == TYPE_INT && t2 == TYPE_FLOAT) || 
        (t1 == TYPE_FLOAT && t2 == TYPE_INT)) {
        return 1;
    }
    
    return 0;
}