/**
 The One Programming Language
 File: generator.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#ifndef _ONE_GENERATOR_H_
#define _ONE_GENERATOR_H_

#include <stdio.h> // FILE
#include <stdlib.h> // malloc, free

#include "ast.h" // ast_t
#include "string.h" // string_t, string_init, string_append

typedef struct {
    ast_t* ast;
    string_t* code;

    int ident;
} generator_t;

/**
 * @brief Initialize the generator object
 *
 * @param ast_t* ast
 *
 * @return generator_t*
 */
generator_t* generator_init(ast_t* ast);

/**
 * @brief Generate the code of a expression from AST
 *
 * @param ast_generator_t* generator
 * @param ast_block_t* block
 * @param ast_expr_t* expression
 *
 * @return
 */
char* generator_generate_expression(generator_t* generator, ast_block_t* block, ast_expr_t* expression);

/**
 * @brief Generate the code of a IF statement from AST
 *
 * @param generator_t* generator
 * @param block_t* block
 * @param ast_if_t* if_stmt
 * @param bool is_else
 *
 * @return char*
 */
char* generator_generate_if(generator_t* generator, ast_block_t* block, ast_if_t* if_stmt, bool is_else);

/**
 * @brief Generate the code of a RET statement from AST
 *
 * @param generator_t* generator
 * @param block_t* block
 * @param ast_ret_t* ret_statement
 *
 * @return char*
 */
char* generator_generate_ret(generator_t* generator, ast_block_t* block, ast_ret_t * ret_statement);

/**
 * @brief Generate the code of a statement from AST
 *
 * @param generator_t* generator
 * @param block_t* block
 * @param ast_statement_t* statement
 *
 * @return char*
 */
char* generator_generate_statement(generator_t* generator, ast_block_t* block, ast_statement_t* statement);

/**
 * @brief Generate the code of a block from AST
 *
 * @param generator_t* generator
 * @param block_t* block
 * @param bool need_ident
 *
 * @return char*
 */
char* generator_generate_block(generator_t* generator, void* parent, ast_block_t* block, bool need_ident);

/**
 * @brief Generate the code of a function from AST
 *
 * @param generator_t* generator
 * @param ast_function_t* function
 *
 * @return char*
 */
char* generator_generate_function(generator_t* generator, ast_function_t* function);

/**
 * @brief Generate the code from AST
 *
 * @param generator_t* generator
 *
 * @return void
 */
void generator_generate(generator_t* generator);

/**
 * @brief Get the code from generator
 *
 * @param generator_t* generator
 *
 * @return char*
 */
char* generator_code(generator_t* generator);

/**
 * @brief Free the generator object
 *
 * @param generator_t* generator
 *
 * @return void
 */
void generator_free(generator_t* generator);

#endif
