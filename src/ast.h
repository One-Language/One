/**
 The One Programming Language
 File: ast.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#ifndef _ONE_AST_H_
#define _ONE_AST_H_

#include "token.h"

typedef struct {
    int test;
} ast_t;

/**
 * @brief Initialize AST
 * 
 * @param void
 * 
 * @return ast_t* 
 */
ast_t* ast_init();

#endif
