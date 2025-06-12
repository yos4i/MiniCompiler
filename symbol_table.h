#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include "ast.h"

typedef enum {
    SYMBOL_FUNCTION,
    SYMBOL_VARIABLE
} symbol_type;

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_STRING,
    TYPE_BOOL,
    TYPE_VOID,
    TYPE_UNKNOWN
} data_type;

typedef struct param {
    char *name;
    data_type type;
    int has_default;
    node *default_value;
    struct param *next;
} param;

typedef struct symbol {
    char *name;
    symbol_type sym_type;
    data_type data_type;
    int scope_level;
    
    param *params;
    int param_count;
    int required_params;  
    data_type return_type;
    
    struct symbol *next;
} symbol;

typedef struct scope {
    int level;
    symbol *symbols;
    struct scope *parent;
} scope;

void init_symbol_table();
void enter_scope();
void exit_scope();
symbol* add_symbol(char *name, symbol_type type, data_type dtype);
symbol* lookup_symbol(char *name);
symbol* lookup_symbol_in_current_scope(char *name);
symbol* lookup_symbol_in_global_scope(char *name);
int function_exists_globally(char *name);

data_type string_to_type(char *type_str);
char* type_to_string(data_type type);
void add_function_param(symbol *func, char *name, data_type type, int has_default, node *default_val);
void free_symbol_table();

data_type get_expression_type(node *expr);
int types_compatible(data_type t1, data_type t2);

#endif