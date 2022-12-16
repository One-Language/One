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
 * @return array_t* (array of ast_statement_t*)
 */
array_t* parser_parse_block(parser_t* parser);

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

#endif
