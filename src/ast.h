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
    token_t* name;
    token_t* type;
} ast_function_t;

typedef struct {
    ast_function_t** data;
    int size;
    int capacity;
} ast_list_function_t;

typedef struct {
    ast_list_function_t* functions;
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
