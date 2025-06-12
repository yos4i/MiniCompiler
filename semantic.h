#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "ast.h"

// Semantic analysis function
int analyze_tree(node *tree);

// Error reporting
void semantic_error(const char *msg);

#endif