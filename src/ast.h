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
#include "array.h"

typedef struct {
    char* name;
} ast_function_t;

typedef struct {
    array_t* functions;
    // ast_list_error_t* errors;
} ast_t;

/**
 * @brief Initialize AST
 * 
 * @param void
 * 
 * @return ast_t* 
 */
ast_t* ast_init();

/**
 * @brief Initialize a function
 * 
 * @param void
 * 
 * @return ast_function_t* 
 */
ast_function_t* ast_function_init();

/**
 * @brief Print AST
 * 
 * @param ast_t* ast
 * 
 * @return char*
 */
char* ast_print(ast_t* ast);

/**
 * @brief Print function in JSON format
 * 
 * @param ast_function_t* function
 * 
 * @return char*
 */
char* ast_print_json(ast_function_t* function);

#endif
