#include <stdlib.h>
#include <string.h>
#include "ast.h"

node *mknode(char *token, node *left, node *right) {
    node *newnode = (node *)malloc(sizeof(node));
    char *newstr = (char *)malloc(strlen(token) + 1);
    strcpy(newstr, token);
    newnode->token = newstr;
    newnode->left = left;
    newnode->right = right;
    return newnode;
}