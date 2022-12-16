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

typedef enum {
    AST_STATEMENT_IF,
    AST_STATEMENT_WHILE,
    AST_STATEMENT_FOR,
    AST_STATEMENT_REPEAT,
    AST_STATEMENT_RET,
    AST_STATEMENT_EXPRESSION,
} ast_statement_type_t;

typedef struct {
    array_t* statements;
} ast_block_t;

typedef struct {
    char* name;
    array_t* arguments;
    ast_block_t* block;
} ast_function_t;

typedef struct {
    token_t* value;
} ast_expr_t;

typedef struct ast_if_t {
    ast_expr_t* condition;
    ast_block_t* then;
    struct ast_if_t* else_;
} ast_if_t;

typedef struct {
    ast_expr_t* expression;
} ast_ret_t;

typedef struct {
    token_t* token;
    // ast_list_error_t* errors;
    ast_statement_type_t type;
    union {
        ast_function_t* stmt_function;
        ast_if_t* stmt_if;
        ast_ret_t* stmt_ret;
        // ast_while_t* while;
        // ast_for_t* for;
        // ast_repeat_t* repeat;
        // ast_ret_t* ret;
        // ast_expression_t* expression;
    };
    
} ast_statement_t;

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
 * @brief Initialize a statement
 * 
 * @return ast_statement_t* 
 */
ast_statement_t* ast_statement_init();

/**
 * @brief Initialize an expression
 * 
 * @param void
 * 
 * @return ast_expr_t* 
 */
ast_expr_t* ast_expression_init();

/**
 * @brief Initialize a block
 * 
 * @param void
 * 
 * @return ast_block_t* 
 */
ast_block_t* ast_block_init();

/**
 * @brief Print AST of a function
 * 
 * @param ast_function_t* function
 * 
 * @return char*
 */
char* ast_print_function(ast_function_t* function);

/**
 * @brief Print AST
 * 
 * @param ast_t* ast
 * 
 * @return char*
 */
char* ast_print(ast_t* ast);

/**
 * @brief Print AST in JSON format
 * 
 * @param ast_t* ast
 * 
 * @return char*
 */
char* ast_print_json(ast_t* ast);

/**
 * @brief Initialize an if statement
 * 
 * @param void
 * 
 * @return ast_if_t* 
 */
ast_if_t* ast_statement_if_init();

/**
 * @brief Initialize a ret statement
 * 
 * @param void
 * 
 * @return ast_ret_t* 
 */
ast_ret_t* ast_statement_ret_init();

#endif
