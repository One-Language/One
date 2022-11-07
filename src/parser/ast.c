#include "ast.h"

Ast* ast_new() {
    Ast* ast = malloc(sizeof(Ast));
    // ast->root = NULL;
    return ast;
}
