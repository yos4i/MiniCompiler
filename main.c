#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "semantic.h"
#include "3ac_generator.h"

int syntax_errors = 0;
int semantic_errors = 0;

extern int yyparse();
extern FILE* yyin;
extern int yylineno;
extern int syntax_errors;
extern int semantic_errors;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    
    FILE* input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
        return 1;
    }
    
    yyin = input_file;
    
    // Initialize symbol table
    init_symbol_table();
    
    // Parse the input
    int parse_result = yyparse();
    
    fclose(input_file);
    
    // Check for errors
    if (parse_result != 0 || syntax_errors > 0) {
        fprintf(stderr, "Compilation failed: %d syntax error(s)\n", syntax_errors);
        free_symbol_table();
        return 1;
    }
    
    if (semantic_errors > 0) {
        fprintf(stderr, "Compilation failed: %d semantic error(s)\n", semantic_errors);
        free_symbol_table();
        return 1;
    }
    
    // If no errors, print the 3AC output
    printf("Compilation successful!\n");
    printf("Generated 3AC:\n");
    printf("================\n");
    print_tac_list();
    
    // Clean up
    free_symbol_table();
    cleanup_tac();
    
    return 0;
}