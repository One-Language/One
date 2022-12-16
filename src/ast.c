/**
 The One Programming Language
 File: ast.c
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#include "ast.h"

/**
 * @brief Initialize AST
 * 
 * @param void
 * 
 * @return ast_t* 
 */
ast_t* ast_init()
{
    ast_t* ast = (ast_t*)malloc(sizeof(ast_t));
    return ast;
}
