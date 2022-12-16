/**
 The One Programming Language
 File: parser.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#ifndef _ONE_PARSER_H_
#define _ONE_PARSER_H_

#include <stdlib.h> // malloc, free

#include "ast.h"
#include "lexer.h"

typedef struct {
    token_list_t* tokens;
    int current_token;
    ast_t* ast;
} parser_t;

struct binding_power {
    int left_power;
    int right_power;
};

/**
 * @brief Initialize parser with tokens
 * 
 * @param token_list_t* tokens
 * 
 * @return parser_t*
 */
parser_t* parser_init(token_list_t* tokens);

/**
 * @brief Parser eat a token
 * 
 * @param parser_t* parser
 * 
 * @return token_t*
 */
token_t* parser_eat(parser_t* parser);

/**
 * @brief Parser peek a token
 * 
 * @param parser_t* parser
 * 
 * @return token_t*
 */
token_t* parser_peek(parser_t* parser);

/**
 * @brief Parser check if has a token type
 * 
 * @param parser_t* parser
 * @param token_type_t type
 * 
 * @return bool
 */
bool parser_has(parser_t* parser, token_type_t type);

/**
 * @brief Parser skip a token type
 * 
 * @param parser_t* parser
 * @param token_type_t type
 * 
 * @return bool
 */
bool parser_skip(parser_t* parser, token_type_t type);

/**
 * @brief Parser expect a token type
 * 
 * @param parser_t* parser
 * @param token_type_t type
 * 
 * @return token_t*
 */
token_t* parser_expect(parser_t* parser, token_type_t type);

/**
 * @brief Parse tokens
 * 
 * @param parser_t* parser
 * 
 * @return void
 */
void parser_parse(parser_t* parser);

/**
 * @brief Parser parse a statement
 * 
 * @param parser_t* parser
 * 
 * @return ast_statement_t* 
 */
ast_statement_t* parser_parse_statement(parser_t* parser);

/**
 * @brief Parser parse statements
 * 
 * @param parser_t* parser
 * 
 * @return array_t* (array of ast_statement_t*)
 */
array_t* parser_parse_statements(parser_t* parser);

/**
 * @brief Parse statements
 * 
 * @param parser_t* parser
 * 
 * @return ast_block_t*
 */
ast_block_t* parser_parse_block(parser_t* parser);

/**
 * @brief Parse function
 * 
 * @param parser_t* parser
 * 
 * @return ast_function_t*
 */
ast_function_t* parser_parse_function(parser_t* parser);

/**
 * @brief Get AST from parser
 * 
 * @param parser_t* parser
 * 
 * @return ast_t*
 */
ast_t* parser_ast(parser_t* parser);

/**
 * @brief Free parser
 * 
 * @param parser_t* parser
 */
void parser_free(parser_t* parser);

/**
 * @brief Parser parse an if statement
 * 
 * @param parser_t* parser
 * 
 * @return ast_if_t*
 */
ast_if_t* parser_parse_if(parser_t* parser);

/**
 * @brief Parser parse a ret statement
 * 
 * @param parser_t* parser
 * 
 * @return ast_ret_t*
 */
ast_ret_t* parser_parse_ret(parser_t* parser);

/**
 * @brief Parser go to next token
 * 
 * @param parser_t* parser
 * 
 * @return void
 */
void parser_next(parser_t* parser);

/**
 * @brief Parser go to previous token
 * 
 * @param parser_t* parser
 * 
 * @return void
 */
void parser_previous(parser_t* parser);

// TODO: expression parser

ast_expr_t* parser_parse_expression_literal(parser_t* parser, ast_block_t* block);

ast_expr_t* parser_parse_expression_sub(parser_t* parser, ast_block_t* block);

ast_expr_t* parser_parse_expression_binary(parser_t* parser, ast_block_t* block, ast_expr_t* lhs, int min_bp);

ast_expr_t* parser_parse_expression_prefix(parser_t* parser, ast_block_t* block, int min_bp);

int parser_prefix_bp_lookup(token_type_t whichOperator);

array_t* parser_parse_expressions(parser_t* parser, ast_block_t* block);

ast_expr_t* parser_ternary_expression(parser_t* parser, ast_block_t* block, ast_expr_t* clause);

struct binding_power RightAssociative(int priority);

struct binding_power LeftAssociative(int priority);

struct binding_power parser_bp_lookup(token_type_t whichOperator);

ast_expr_t* parser_parse_expression_postfix(parser_t* parser, ast_block_t* block, ast_expr_t* lhs);

ast_expr_t* parser_parse_expression(parser_t* parser, ast_block_t* block, int binding_power_to_my_right);

#endif
