#include "ast.h"

ast_t* ast_init()
{
    ast_t* ast = malloc(sizeof(ast_t));

    return ast;
}

void ast_free(ast_t* ast)
{
    free(ast);
}
