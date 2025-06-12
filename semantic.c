#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "symbol_table.h"

static int semantic_errors = 0;
static int has_main = 0;
static int current_function_return_type = TYPE_VOID;
static int has_return_in_current_function = 0;
void count_params(node *params, symbol *func_sym);
void semantic_error(const char *msg) {
    fprintf(stderr, "Semantic error: %s\n", msg);
    semantic_errors++;
}
int count_arguments(node *args);
void check_argument_types(node *args, param *expected_param, char *func_name, int arg_index);
int analyze_node(node *n);
int register_function(node *func);
int analyze_function_body(node *func);
int analyze_params(node *params, symbol *func_sym);
int analyze_body(node *body);
int analyze_statement(node *stmt);
int analyze_expression(node *expr);
int analyze_declaration(node *decl);
int analyze_assignment(node *assign);
int analyze_function_call(node *call);
int check_return_statements(node *body, data_type expected_type);
int check_all_paths_return(node *body);

int analyze_tree(node *tree) {
    if (!tree) return 0;
    
    init_symbol_table();
    semantic_errors = 0;
    has_main = 0;
    
    if (strcmp(tree->token, "CODE") == 0) {
        node *func_list = tree->left;
        while (func_list) {
            if (strcmp(func_list->token, "FUNC_LIST") == 0) {
                if (func_list->right) {
                    register_function(func_list->right);
                }
                func_list = func_list->left;
            } else if (strcmp(func_list->token, "FUNC") == 0) {
                register_function(func_list);
                break;
            } else {
                break;
            }
        }
        
        if (tree->right && strcmp(tree->right->token, "FUNC") == 0) {
            register_function(tree->right);
        }
        
        func_list = tree->left;
        while (func_list) {
            if (strcmp(func_list->token, "FUNC_LIST") == 0) {
                if (func_list->right) {
                    analyze_function_body(func_list->right);
                }
                func_list = func_list->left;
            } else if (strcmp(func_list->token, "FUNC") == 0) {
                analyze_function_body(func_list);
                break;
            } else {
                break;
            }
        }
        
        if (tree->right && strcmp(tree->right->token, "FUNC") == 0) {
            analyze_function_body(tree->right);
        }
    }
    
    if (!has_main) {
        semantic_error("No __main__ function found");
    }

    fflush(stdout);
    return semantic_errors;
}

void count_params(node *params, symbol *func_sym) {
    if (!params) return;
    
    
    while (params && strcmp(params->token, "ARGS") == 0) {
        params = params->left;
    }
    
    if (!params || strcmp(params->token, "NONE") == 0) {
        return;
    }
    
    if (strcmp(params->token, "PARAMS") == 0) {
        count_params(params->left, func_sym);
        count_params(params->right, func_sym);
        return;
    }
    
    if (strncmp(params->token, "int", 3) == 0 || 
        strncmp(params->token, "float", 5) == 0 ||
        strncmp(params->token, "string", 6) == 0 ||
        strncmp(params->token, "bool", 4) == 0) {
        
        node *param_list = params->left;
        
        if (!param_list) {
            return;
        }
        
        
        int count = 0;
        
        if (strcmp(param_list->token, "PARAM_LIST") == 0) {
        }
        else if ((param_list->token[0] >= 'a' && param_list->token[0] <= 'z') ||
                 (param_list->token[0] >= 'A' && param_list->token[0] <= 'Z') ||
                 param_list->token[0] == '_') {
            count = 1;  
        }
        
        func_sym->param_count += count;
        func_sym->required_params += count;

    }
}

int register_function(node *func) {
    if (!func || strcmp(func->token, "FUNC") != 0) return 0;

    node *name_node = func->left;
    char *func_name = name_node->token;
    
    if (strcmp(func_name, "__main__") == 0) {
        if (has_main) {
            semantic_error("Multiple __main__ functions defined");
            return 0;
        }
        has_main = 1;
        
        node *args_node = func->right;
        if (args_node && args_node->left) {
            node *params = args_node->left;
            if (params && params->left && strcmp(params->left->token, "NONE") != 0) {
                semantic_error("__main__ function cannot have parameters");
            }
        }
        
        if (args_node && args_node->right) {
            node *ret_node = args_node->right;
            if (strcmp(ret_node->token, "RETURN VOID") != 0) {
                semantic_error("__main__ function must return void");
            }
        }
    }
    
    if (function_exists_globally(func_name)) {
        char msg[256];
        sprintf(msg, "Function '%s' already defined", func_name);
        semantic_error(msg);
        return 0;
    }
    
    symbol *func_sym = add_symbol(func_name, SYMBOL_FUNCTION, TYPE_VOID);
    
    func_sym->param_count = 0;
    func_sym->required_params = 0;
    
    node *args_node = func->right;
    if (args_node && args_node->right) {
        node *ret_node = args_node->right;
        if (ret_node->left && strcmp(ret_node->token, "RET") == 0) {
            func_sym->return_type = string_to_type(ret_node->left->token);
        } else if (strcmp(ret_node->token, "RETURN VOID") == 0) {
            func_sym->return_type = TYPE_VOID;
        }
    }
    
    if (args_node && args_node->left) {
        count_params(args_node->left, func_sym);
    }
    
    return 1;  
}

int analyze_function_body(node *func) {
    if (!func || strcmp(func->token, "FUNC") != 0) return 0;

    node *name_node = func->left;
    char *func_name = name_node->token;
    
    symbol *func_sym = lookup_symbol(func_name);
    if (!func_sym) return 0;
    
    current_function_return_type = func_sym->return_type;
    has_return_in_current_function = 0;
    
    enter_scope();

    node *args_node = func->right;
    
    if (args_node && args_node->left) {
        analyze_params(args_node->left, func_sym);
    }
    
    if (args_node && args_node->right && args_node->right->right) {
        node *body = args_node->right->right;
        analyze_body(body);
        
        if (func_sym->return_type != TYPE_VOID && !has_return_in_current_function) {
            char msg[256];
            sprintf(msg, "Function '%s' must return a value of type %s", 
                    func_name, type_to_string(func_sym->return_type));
            semantic_error(msg);
        }
    }
    
    exit_scope();
    
    return 1;
}


int analyze_params(node *params, symbol *func_sym) {
    if (!params) return 0;
    
    while (params && strcmp(params->token, "ARGS") == 0) {
        params = params->left;
    }
    
    if (!params || strcmp(params->token, "NONE") == 0) {
        return 0;
    }
    
    if (strcmp(params->token, "PARAMS") == 0) {
        analyze_params(params->left, func_sym);
        analyze_params(params->right, func_sym);
        return 1;
    }
    
    int seen_default = 0;
    
    if (strncmp(params->token, "int", 3) == 0 || 
        strncmp(params->token, "float", 5) == 0 ||
        strncmp(params->token, "string", 6) == 0 ||
        strncmp(params->token, "bool", 4) == 0) {
        
        data_type param_type = string_to_type(params->token);
        node *param_list = params->left;
        
        if (!param_list) return 0;
        
        if ((param_list->token[0] >= 'a' && param_list->token[0] <= 'z') ||
            (param_list->token[0] >= 'A' && param_list->token[0] <= 'Z') ||
            param_list->token[0] == '_') {
            
            char *param_name = param_list->token;
            
            if (lookup_symbol_in_current_scope(param_name) != NULL) {
                char msg[256];
                sprintf(msg, "Parameter '%s' already defined", param_name);
                semantic_error(msg);
            } else {

                add_symbol(param_name, SYMBOL_VARIABLE, param_type);
            }
            return 1;
        }
        
        if (strcmp(param_list->token, "BARE") == 0) {
            node *bare_params = param_list->left;
            
            if (bare_params) {
                if (strcmp(bare_params->token, "PARAM_LIST") == 0) {
                    node *temp = bare_params;
                    while (temp) {
                        if (strcmp(temp->token, "PARAM_LIST") == 0) {
                            if (temp->left) {
                                char *param_name = temp->left->token;
                                if (lookup_symbol_in_current_scope(param_name) != NULL) {
                                    char msg[256];
                                    sprintf(msg, "Parameter '%s' already defined", param_name);
                                    semantic_error(msg);
                                } else {
                                    add_symbol(param_name, SYMBOL_VARIABLE, param_type);
                                }
                            }
                            temp = temp->right;
                        } else {
                            char *param_name = temp->token;
                            if (lookup_symbol_in_current_scope(param_name) != NULL) {
                                char msg[256];
                                sprintf(msg, "Parameter '%s' already defined", param_name);
                                semantic_error(msg);
                            } else {
                                add_symbol(param_name, SYMBOL_VARIABLE, param_type);
                            }
                            break;
                        }
                    }
                } else {
                    char *param_name = bare_params->token;
                    
                    if (seen_default) {
                        semantic_error("Non-default parameter cannot follow default parameter");
                    }
                    
                    if (lookup_symbol_in_current_scope(param_name) != NULL) {
                        char msg[256];
                        sprintf(msg, "Parameter '%s' already defined", param_name);
                        semantic_error(msg);
                    } else {
                        add_symbol(param_name, SYMBOL_VARIABLE, param_type);
                    }
                }
            }
            
            node *default_params = param_list->right;
            while (default_params) {
                if (strcmp(default_params->token, "DEFAULT") == 0) {
                    seen_default = 1;
                    char *param_name = default_params->left->token;
                    node *default_val = default_params->right;
                    
                    data_type default_type = get_expression_type(default_val);
                    if (!types_compatible(param_type, default_type)) {
                        char msg[256];
                        sprintf(msg, "Default value for parameter '%s' has wrong type", param_name);
                        semantic_error(msg);
                    }
                    
                    if (lookup_symbol_in_current_scope(param_name) != NULL) {
                        char msg[256];
                        sprintf(msg, "Parameter '%s' already defined", param_name);
                        semantic_error(msg);
                    } else {
                        add_symbol(param_name, SYMBOL_VARIABLE, param_type);
                    }
                }
                default_params = default_params->right;
            }
        }
        else if (strcmp(param_list->token, "PARAM_LIST") == 0) {
            node *temp = param_list;
            while (temp) {
                if (strcmp(temp->token, "PARAM_LIST") == 0) {
                    if (temp->left) {
                        char *param_name = temp->left->token;
                        if (seen_default) {
                            semantic_error("Non-default parameter cannot follow default parameter");
                        }
                        if (lookup_symbol_in_current_scope(param_name) != NULL) {
                            char msg[256];
                            sprintf(msg, "Parameter '%s' already defined", param_name);
                            semantic_error(msg);
                        } else {
                            add_symbol(param_name, SYMBOL_VARIABLE, param_type);
                        }
                    }
                    temp = temp->right;
                } else {
                    char *param_name = temp->token;
                    if (seen_default) {
                        semantic_error("Non-default parameter cannot follow default parameter");
                    }
                    if (lookup_symbol_in_current_scope(param_name) != NULL) {
                        char msg[256];
                        sprintf(msg, "Parameter '%s' already defined", param_name);
                        semantic_error(msg);
                    } else {
                        add_symbol(param_name, SYMBOL_VARIABLE, param_type);
                    }
                    break;
                }
            }
        }
        else if (strcmp(param_list->token, "DEFAULT") == 0) {
            seen_default = 1;
            char *param_name = param_list->left->token;
            node *default_val = param_list->right;
            
            data_type default_type = get_expression_type(default_val);
            if (!types_compatible(param_type, default_type)) {
                char msg[256];
                sprintf(msg, "Default value for parameter '%s' has wrong type", param_name);
                semantic_error(msg);
            }
            
            if (lookup_symbol_in_current_scope(param_name) != NULL) {
                char msg[256];
                sprintf(msg, "Parameter '%s' already defined", param_name);
                semantic_error(msg);
            } else {
                add_symbol(param_name, SYMBOL_VARIABLE, param_type);
            }
        }
    }
    
    return 1;
}

int analyze_body(node *body) {
    if (!body) return 0;
    
    
    if (strcmp(body->token, "BODY") == 0) {
        body = body->left;
    }
    
    node *current = body;
    while (current) {
        if (strcmp(current->token, "STMT_LIST") == 0) {
            analyze_statement(current->left);
            current = current->right;
        } else {
            analyze_statement(current);
            break;
        }
    }
    
    return 1;
}

int analyze_statement(node *stmt) {
    if (!stmt) return 0;
    
    
    if (strcmp(stmt->token, "STMT_LIST") == 0) {
        return analyze_body(stmt);
    }
    
    if (strncmp(stmt->token, "int", 3) == 0 || 
        strncmp(stmt->token, "float", 5) == 0 ||
        strncmp(stmt->token, "string", 6) == 0 ||
        strncmp(stmt->token, "bool", 4) == 0) {
        return analyze_declaration(stmt);
    } else if (strcmp(stmt->token, "ASS") == 0) {
        return analyze_assignment(stmt);
    } else if (strcmp(stmt->token, "CALL") == 0) {
        return analyze_function_call(stmt);
    } else if (strcmp(stmt->token, "RET") == 0) {
        has_return_in_current_function = 1;
        
        if (stmt->left) {
            analyze_expression(stmt->left);
            data_type ret_type = get_expression_type(stmt->left);
            if (!types_compatible(current_function_return_type, ret_type)) {
                char msg[256];
                sprintf(msg, "Return type mismatch: expected %s but got %s",
                        type_to_string(current_function_return_type), 
                        type_to_string(ret_type));
                semantic_error(msg);
            }
        } else {
            if (current_function_return_type != TYPE_VOID) {
                semantic_error("Return statement must return a value");
            }
        }
        return 1;
    } else if (strcmp(stmt->token, "IF") == 0 || strcmp(stmt->token, "IF-ELSE") == 0) {
        analyze_expression(stmt->left);
        data_type cond_type = get_expression_type(stmt->left);
        if (cond_type != TYPE_BOOL) {
            semantic_error("IF condition must be of type bool");
        }
        
        enter_scope();
        if (strcmp(stmt->token, "IF") == 0) {
            analyze_body(stmt->right);
        } else {
            analyze_body(stmt->right->left);
        }
        exit_scope();
        
        if (strcmp(stmt->token, "IF-ELSE") == 0 && stmt->right && 
            strcmp(stmt->right->token, "BLOCK") == 0 && stmt->right->right) {
            enter_scope();
            analyze_body(stmt->right->right);
            exit_scope();
        }
        return 1;
    } else if (strcmp(stmt->token, "CHAIN") == 0 || 
               strcmp(stmt->token, "IF-ELIF") == 0 || 
               strcmp(stmt->token, "IF-ELIF-ELSE") == 0) {
        node *current_node = stmt;
        
        if (strcmp(stmt->token, "CHAIN") == 0 && stmt->left && 
            strcmp(stmt->left->token, "IF-ELIF") == 0) {
            analyze_expression(stmt->left->left);
            data_type cond_type = get_expression_type(stmt->left->left);
            if (cond_type != TYPE_BOOL) {
                semantic_error("IF condition must be of type bool");
            }
            
            enter_scope();
            analyze_body(stmt->left->right);
            exit_scope();
            
            current_node = stmt->right;
        } else if (strcmp(stmt->token, "IF-ELIF") == 0 || 
                   strcmp(stmt->token, "IF-ELIF-ELSE") == 0) {
            analyze_expression(stmt->left);
            data_type cond_type = get_expression_type(stmt->left);
            if (cond_type != TYPE_BOOL) {
                semantic_error("IF condition must be of type bool");
            }
            
            enter_scope();
            if (stmt->right && strcmp(stmt->right->token, "CHAIN") == 0) {
                analyze_body(stmt->right->left);
            } else {
                analyze_body(stmt->right);
            }
            exit_scope();
            
            if (stmt->right && strcmp(stmt->right->token, "CHAIN") == 0) {
                current_node = stmt->right->right;
            } else {
                current_node = NULL;
            }
        }
        
        while (current_node) {
            if (strcmp(current_node->token, "ELIF") == 0) {
                analyze_expression(current_node->left);
                data_type elif_cond_type = get_expression_type(current_node->left);
                if (elif_cond_type != TYPE_BOOL) {
                    semantic_error("ELIF condition must be of type bool");
                }
                
                enter_scope();
                analyze_body(current_node->right);
                exit_scope();
                break;
            } else if (strcmp(current_node->token, "ELIF_LIST") == 0) {
                if (current_node->left && strcmp(current_node->left->token, "ELIF") == 0) {
                    analyze_expression(current_node->left->left);
                    data_type elif_cond_type = get_expression_type(current_node->left->left);
                    if (elif_cond_type != TYPE_BOOL) {
                        semantic_error("ELIF condition must be of type bool");
                    }
                    
                    enter_scope();
                    analyze_body(current_node->left->right);
                    exit_scope();
                }
                current_node = current_node->right;
            } else if (strcmp(current_node->token, "ELIFS") == 0) {
                if (current_node->left) {
                    node *elif_node = current_node->left;
                    while (elif_node) {
                        if (strcmp(elif_node->token, "ELIF") == 0) {
                            analyze_expression(elif_node->left);
                            data_type elif_cond_type = get_expression_type(elif_node->left);
                            if (elif_cond_type != TYPE_BOOL) {
                                semantic_error("ELIF condition must be of type bool");
                            }
                            
                            enter_scope();
                            analyze_body(elif_node->right);
                            exit_scope();
                            break;
                        } else if (strcmp(elif_node->token, "ELIF_LIST") == 0) {
                            if (elif_node->left && strcmp(elif_node->left->token, "ELIF") == 0) {
                                analyze_expression(elif_node->left->left);
                                data_type elif_cond_type = get_expression_type(elif_node->left->left);
                                if (elif_cond_type != TYPE_BOOL) {
                                    semantic_error("ELIF condition must be of type bool");
                                }
                                
                                enter_scope();
                                analyze_body(elif_node->left->right);
                                exit_scope();
                            }
                            elif_node = elif_node->right;
                        } else {
                            break;
                        }
                    }
                }
                
                if (current_node->right) {
                    enter_scope();
                    analyze_body(current_node->right);
                    exit_scope();
                }
                break;
            } else {
                enter_scope();
                analyze_body(current_node);
                exit_scope();
                break;
            }
        }
        return 1;
    } else if (strcmp(stmt->token, "WHILE") == 0) {
        analyze_expression(stmt->left);
        data_type cond_type = get_expression_type(stmt->left);
        if (cond_type != TYPE_BOOL) {
            semantic_error("WHILE condition must be of type bool");
        }
        
        enter_scope();
        analyze_body(stmt->right);
        exit_scope();
        return 1;
    } else if (strcmp(stmt->token, "PRINT") == 0) {
        analyze_expression(stmt->left);
        return 1;
    } else if (strcmp(stmt->token, "PASS") == 0) {
        return 1;
    } else if (strcmp(stmt->token, "BODY") == 0) {
        return analyze_body(stmt);
    }
    
    return 0;
}

int analyze_declaration(node *decl) {
    if (!decl) return 0;
    
    
    data_type var_type = string_to_type(decl->token);
    node *decl_list = decl->left;

    
    while (decl_list) {
        node *item = decl_list;
        
        
        if (strcmp(decl_list->token, "DECL_LIST") == 0) {
            item = decl_list->left;
            decl_list = decl_list->right;
        } else {
            decl_list = NULL;
        }
        
        
        
        if (strcmp(item->token, "ASSIGN") == 0) {
            char *var_name = item->left->token;
            
            
            if (lookup_symbol_in_current_scope(var_name) != NULL) {
                char msg[256];
                sprintf(msg, "Variable '%s' already defined in this scope", var_name);
                semantic_error(msg);
            } else {
                add_symbol(var_name, SYMBOL_VARIABLE, var_type);
                
                analyze_expression(item->right);
                data_type init_type = get_expression_type(item->right);
                if (!types_compatible(var_type, init_type)) {
                    char msg[256];
                    sprintf(msg, "Type mismatch in initialization of '%s'", var_name);
                    semantic_error(msg);
                }
            }
        } else {
            char *var_name = item->token;
            
            if (lookup_symbol_in_current_scope(var_name) != NULL) {
                char msg[256];
                sprintf(msg, "Variable '%s' already defined in this scope", var_name);
                semantic_error(msg);
            } else {
                add_symbol(var_name, SYMBOL_VARIABLE, var_type);
            }
        }
    }
    
    return 1;
}

int analyze_assignment(node *assign) {
    if (!assign || strcmp(assign->token, "ASS") != 0) return 0;
    
    node *lhs = assign->left;
    node *rhs = assign->right;
    
    analyze_expression(rhs);
    data_type rhs_type = get_expression_type(rhs);
    
    while (lhs) {
        node *var = lhs;
        if (strcmp(lhs->token, "LHS_LIST") == 0) {
            var = lhs->left;
            lhs = lhs->right;
        } else {
            lhs = NULL;
        }
        
        if (strcmp(var->token, "INDEX") == 0) {
            symbol *sym = lookup_symbol(var->left->token);
            if (!sym) {
                char msg[256];
                sprintf(msg, "Undefined variable '%s'", var->left->token);
                semantic_error(msg);
            } else if (sym->data_type != TYPE_STRING) {
                semantic_error("Indexing operator [] can only be used on strings");
            }
            
            analyze_expression(var->right);
            data_type index_type = get_expression_type(var->right);
            if (index_type != TYPE_INT) {
                semantic_error("String index must be of type int");
            }
            
            if (!types_compatible(TYPE_STRING, rhs_type)) {
                semantic_error("Type mismatch in assignment to string element");
            }
        } else {
            symbol *sym = lookup_symbol(var->token);
            if (!sym) {
                char msg[256];
                sprintf(msg, "Undefined variable '%s'", var->token);
                semantic_error(msg);
            } else {
                if (!types_compatible(sym->data_type, rhs_type)) {
                    char msg[256];
                    sprintf(msg, "Type mismatch in assignment to '%s'", var->token);
                    semantic_error(msg);
                }
            }
        }
    }
    
    return 1;
}

int analyze_function_call(node *call) {
    if (!call || strcmp(call->token, "CALL") != 0) return 0;
    
    char *func_name = call->left->token;

    symbol *func_sym = lookup_symbol(func_name);
    
    if (!func_sym) {
        char msg[256];
        sprintf(msg, "Undefined function '%s'", func_name);
        semantic_error(msg);
        return 0;
    }

    if (func_sym->sym_type != SYMBOL_FUNCTION) {
        char msg[256];
        sprintf(msg, "'%s' is not a function", func_name);
        semantic_error(msg);
        return 0;
    }
    
    node *args = call->right;
    if (args && strcmp(args->token, "ARGS") == 0) {
        args = args->left;
    }
    
    int arg_count = 0;
    
    if (!args || strcmp(args->token, "NONE") == 0) {
        if (func_sym->required_params > 0) {
            char msg[256];
            sprintf(msg, "Function '%s' requires at least %d arguments, but 0 provided", 
                    func_name, func_sym->required_params);
            semantic_error(msg);
        }
    } else {
        arg_count = count_arguments(args);
        
        param *expected_param = func_sym->params;
        check_argument_types(args, expected_param, func_name, 1);
    }
    
    if (arg_count < func_sym->required_params) {
        char msg[256];
        sprintf(msg, "Function '%s' requires at least %d arguments, but %d provided", 
                func_name, func_sym->required_params, arg_count);
        semantic_error(msg);
    } else if (arg_count > func_sym->param_count) {
        char msg[256];
        sprintf(msg, "Function '%s' expects at most %d arguments, but %d provided", 
                func_name, func_sym->param_count, arg_count);
        semantic_error(msg);
    }
    
    return 1;
}

int count_arguments(node *args) {
    if (!args) return 0;
    
    if (strcmp(args->token, "EXPR_LIST") == 0) {
        int left_count = (args->left && strcmp(args->left->token, "EXPR_LIST") == 0) 
                         ? count_arguments(args->left) : 1;
        int right_count = args->right ? count_arguments(args->right) : 0;
        return left_count + right_count;
    } else {
        return 1;
    }
}

void check_argument_types(node *args, param *expected_param, char *func_name, int arg_index) {
    if (!args || !expected_param) return;
    
    if (strcmp(args->token, "EXPR_LIST") == 0) {
        if (args->left && strcmp(args->left->token, "EXPR_LIST") == 0) {
            check_argument_types(args->left, expected_param, func_name, arg_index);
            
            int left_count = count_arguments(args->left);
            for (int i = 0; i < left_count && expected_param; i++) {
                expected_param = expected_param->next;
                arg_index++;
            }
        } else if (args->left) {
            analyze_expression(args->left);
            data_type arg_type = get_expression_type(args->left);
            
            if (!types_compatible(expected_param->type, arg_type)) {
                char msg[256];
                sprintf(msg, "Type mismatch in argument %d of function '%s'", 
                        arg_index, func_name);
                semantic_error(msg);
            }
            expected_param = expected_param->next;
            arg_index++;
        }
        
        if (args->right) {
            check_argument_types(args->right, expected_param, func_name, arg_index);
        }
    } else {
        analyze_expression(args);
        data_type arg_type = get_expression_type(args);
        
        if (!types_compatible(expected_param->type, arg_type)) {
            char msg[256];
            sprintf(msg, "Type mismatch in argument %d of function '%s'", 
                    arg_index, func_name);
            semantic_error(msg);
        }
    }
}

int analyze_expression(node *expr) {
    if (!expr) return 0;
    
    if (strcmp(expr->token, "EXPR_LIST") == 0) {
        return 1;
    }
    if (strcmp(expr->token, "+") == 0 || strcmp(expr->token, "-") == 0 ||
        strcmp(expr->token, "*") == 0 || strcmp(expr->token, "/") == 0 ||
        strcmp(expr->token, "**") == 0) {
        analyze_expression(expr->left);
        analyze_expression(expr->right);
        
        data_type left_type = get_expression_type(expr->left);
        data_type right_type = get_expression_type(expr->right);
        
        if (left_type != TYPE_INT && left_type != TYPE_FLOAT) {
            semantic_error("Left operand of arithmetic operator must be int or float");
        }
        if (right_type != TYPE_INT && right_type != TYPE_FLOAT) {
            semantic_error("Right operand of arithmetic operator must be int or float");
        }
    } else if (strcmp(expr->token, "<") == 0 || strcmp(expr->token, ">") == 0 ||
               strcmp(expr->token, "<=") == 0 || strcmp(expr->token, ">=") == 0) {
        analyze_expression(expr->left);
        analyze_expression(expr->right);
        
        data_type left_type = get_expression_type(expr->left);
        data_type right_type = get_expression_type(expr->right);
        
        if ((left_type != TYPE_INT && left_type != TYPE_FLOAT) ||
            (right_type != TYPE_INT && right_type != TYPE_FLOAT)) {
            semantic_error("Comparison operators require numeric operands");
        }
    } else if (strcmp(expr->token, "==") == 0 || strcmp(expr->token, "!=") == 0) {
        analyze_expression(expr->left);
        analyze_expression(expr->right);
        
        data_type left_type = get_expression_type(expr->left);
        data_type right_type = get_expression_type(expr->right);
        
        if (left_type != right_type && 
            !((left_type == TYPE_INT && right_type == TYPE_FLOAT) ||
              (left_type == TYPE_FLOAT && right_type == TYPE_INT))) {
            semantic_error("Equality operators require operands of the same type");
        }
    } else if (strcmp(expr->token, "AND") == 0 || strcmp(expr->token, "OR") == 0) {
        analyze_expression(expr->left);
        analyze_expression(expr->right);
        
        data_type left_type = get_expression_type(expr->left);
        data_type right_type = get_expression_type(expr->right);
        
        if (left_type != TYPE_BOOL) {
            semantic_error("Left operand of logical operator must be bool");
        }
        if (right_type != TYPE_BOOL) {
            semantic_error("Right operand of logical operator must be bool");
        }
    } else if (strcmp(expr->token, "NOT") == 0) {
        analyze_expression(expr->left);
        
        data_type operand_type = get_expression_type(expr->left);
        if (operand_type != TYPE_BOOL) {
            semantic_error("Operand of NOT must be bool");
        }
    } else if (strcmp(expr->token, "NEG") == 0) {
        analyze_expression(expr->left);
        
        data_type operand_type = get_expression_type(expr->left);
        if (operand_type != TYPE_INT && operand_type != TYPE_FLOAT) {
            semantic_error("Operand of unary minus must be numeric");
        }
    } else if (strcmp(expr->token, "INDEX") == 0) {
        analyze_expression(expr->left);
        analyze_expression(expr->right);
        
        data_type base_type = get_expression_type(expr->left);
        data_type index_type = get_expression_type(expr->right);
        
        if (base_type != TYPE_STRING) {
            semantic_error("Indexing operator [] can only be used on strings");
        }
        if (index_type != TYPE_INT) {
            semantic_error("Index must be of type int");
        }
    } else if (strcmp(expr->token, "CALL") == 0) {
        analyze_function_call(expr);
    } else {
    if ((expr->token[0] >= 'a' && expr->token[0] <= 'z') ||
        (expr->token[0] >= 'A' && expr->token[0] <= 'Z') ||
        expr->token[0] == '_') {
        
        if (strcmp(expr->token, "True") != 0 && 
            strcmp(expr->token, "False") != 0) {
            
            symbol *sym = lookup_symbol(expr->token);
            if (!sym) {
                char msg[256];
                sprintf(msg, "Undefined identifier '%s'", expr->token);
                semantic_error(msg);
            }
        }
    }
    }
    
    return 1;  
}



int check_return_statements(node *body, data_type expected_type) {
    if (!body) return 0;
    
    if (strcmp(body->token, "BODY") == 0) {
        body = body->left;
    }
    
    node *current = body;
    while (current) {
        node *stmt = current;
        
        if (strcmp(current->token, "STMT_LIST") == 0) {
            stmt = current->left;
            current = current->right;
        } else {
            current = NULL;
        }
        
        if (stmt && strcmp(stmt->token, "RET") == 0) {
            if (stmt->left) {
                data_type ret_type = get_expression_type(stmt->left);
                if (!types_compatible(expected_type, ret_type)) {
                    char msg[256];
                    sprintf(msg, "Return type mismatch: expected %s but got %s",
                            type_to_string(expected_type), type_to_string(ret_type));
                    semantic_error(msg);
                }
            } else if (expected_type != TYPE_VOID) {
                semantic_error("Return statement must return a value");
            }
            return 1;
        } else if (stmt && (strcmp(stmt->token, "IF") == 0 || 
                           strcmp(stmt->token, "IF-ELSE") == 0 ||
                           strcmp(stmt->token, "WHILE") == 0)) {
            if (stmt->right) {
                if (check_return_statements(stmt->right, expected_type)) {
                    return 1;
                }
            }
        }
    }
    
    return 0;
}