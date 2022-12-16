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
 * @brief Parse tokens
 * 
 * @param parser_t* parser
 * 
 * @return void
 */
void parser_parse(parser_t* parser);

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
 * @brief Parse function
 * 
 * @param parser_t* parser
 * 
 * @return void
 */
void parser_parse_function(parser_t* parser);

#endif
