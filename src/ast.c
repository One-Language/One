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
    ast->functions = ast_list_function_init();
    return ast;
}

/**
 * @brief Initialize list of functions
 * 
 * @param void
 * 
 * @return ast_list_function_t* 
 */
ast_list_function_t* ast_list_function_init()
{
    ast_list_function_t* list = (ast_list_function_t*)malloc(sizeof(ast_list_function_t));
    list->data = (ast_function_t**)malloc(sizeof(ast_function_t*) * 0);
    list->size = 0;
    list->capacity = 5;
    return list;
}

/**
 * @brief Add function to list of functions
 * 
 * @param ast_list_function_t* list
 * @param ast_function_t* function
 * 
 * @return ast_list_function_t* 
 */
ast_list_function_t* ast_list_function_append(ast_list_function_t* list, ast_function_t* function)
{
    if (list->size == list->capacity) {
        list->capacity += 8;
        list->data = (ast_function_t**)realloc(list->data, sizeof(ast_function_t*) * list->capacity);
    }
    list->data[list->size++] = function;
    return list;
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
