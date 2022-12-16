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
    ast->functions = array_init();
    return ast;
}

/**
 * @brief Initialize a function
 * 
 * @param void
 * 
 * @return ast_function_t* 
 */
ast_function_t* ast_function_init()
{
    ast_function_t* function = (ast_function_t*)malloc(sizeof(ast_function_t));
    return function;
}

/**
 * @brief Print AST
 * 
 * @param ast_t* ast
 * 
 * @return char*
 */
char* ast_print(ast_t* ast)
{
    string_t* str = string_init();

    string_append(str, "AST!\n");

    string_append_format(str, "Functions: %d\n", ast->functions->size);

    return str->value;
}

/**
 * @brief Print function in JSON format
 * 
 * @param ast_function_t* function
 * 
 * @return char*
 */
char* ast_print_json(ast_function_t* function)
{
    string_t* str = string_init();

    string_append(str, "{soon}");

    return str->value;
}
