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
 * @brief Initialize a statement
 * 
 * @return ast_statement_t* 
 */
ast_statement_t* ast_statement_init()
{
    ast_statement_t* statement = (ast_statement_t*)malloc(sizeof(ast_statement_t));
    return statement;
}

/**
 * @brief Initialize an expression
 * 
 * @param void
 * 
 * @return ast_expr_t* 
 */
ast_expr_t* ast_expression_init()
{
    ast_expr_t* expr = (ast_expr_t*)malloc(sizeof(ast_expr_t));
    return expr;
}

/**
 * @brief Initialize a block
 * 
 * @param void
 * 
 * @return ast_block_t* 
 */
ast_block_t* ast_block_init()
{
    ast_block_t* block = (ast_block_t*)malloc(sizeof(ast_block_t));
    return block;
}

/**
 * @brief Print AST of a function
 * 
 * @param ast_function_t* function
 * 
 * @return char*
 */
char* ast_print_function(ast_function_t* function)
{
    string_t* str = string_init();

    string_append_format(str, "\tFunction %s (%d statements)\n", function->name, function->statements->size);

    return str->value;
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

    if (ast->functions->size == 0) string_append(str, "There are no functions!\n");
    else {
        string_append_format(str, "Functions(%zu):\n", ast->functions->size);
        for (int i = 0; i < ast->functions->size; i++) {
            ast_function_t* function = ast->functions->data[i];
            string_append(str, ast_print_function(function));
        }
    }

    return str->value;
}

/**
 * @brief Initialize an if statement
 * 
 * @param void
 * 
 * @return ast_if_t* 
 */
ast_if_t* ast_statement_if_init()
{
    ast_if_t* st = (ast_if_t*)malloc(sizeof(ast_if_t));
    return st;
}

/**
 * @brief Initialize a ret statement
 * 
 * @param void
 * 
 * @return ast_ret_t* 
 */
ast_ret_t* ast_statement_ret_init()
{
    ast_ret_t* st = (ast_ret_t*)malloc(sizeof(ast_ret_t));
    return st;
}

/**
 * @brief Print AST in JSON format
 * 
 * @param ast_t* ast
 * 
 * @return char*
 */
char* ast_print_json(ast_t* ast)
{
    string_t* str = string_init();

    string_append(str, "{soon}");

    return str->value;
}
