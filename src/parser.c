/**
 The One Programming Language
 File: parser.c
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#include "parser.h"

/**
 * @brief Initialize parser with tokens
 * 
 * @param token_list_t* tokens
 * 
 * @return parser_t*
 */
parser_t* parser_init(token_list_t* tokens)
{
    parser_t* parser = (parser_t*)malloc(sizeof(parser_t));
    parser->tokens = tokens;
    parser->current_token = 0;
    parser->ast = ast_init();
    return parser;
}

/**
 * @brief Parse tokens
 * 
 * @param parser_t* parser
 * 
 * @return void
 */
void parser_parse(parser_t* parser)
{
    while (parser->current_token < parser->tokens->size) {
        token_t* token = parser->tokens->data[parser->current_token];

        if (token->type == TOKEN_FUNC) parser_parse_function(parser);
        else {
            printf("Unexpected token: %s\n", token_name(token->type));
        }


        parser->current_token++;
    }
}

/**
 * @brief Parse function
 * 
 * @param parser_t* parser
 * 
 * @return void
 */
void parser_parse_function(parser_t* parser)
{
    token_t* token = parser->tokens->data[parser->current_token];
    if (token->type != TOKEN_FUNC) {
        printf("Unexpected token: %s\n", token_name(token->type));
        return;
    }

    ast_function_t* function = ast_function_init();
    function->name = token->value;

    parser->current_token++;
    token = parser->tokens->data[parser->current_token];
    if (token->type != TOKEN_LEFT_PAREN) {
        printf("Unexpected token: %s\n", token_name(token->type));
        return;
    }

    parser->current_token++;
    token = parser->tokens->data[parser->current_token];
    if (token->type != TOKEN_RIGHT_PAREN) {
        printf("Unexpected token: %s\n", token_name(token->type));
        return;
    }

    parser->current_token++;
    token = parser->tokens->data[parser->current_token];
    if (token->type != TOKEN_LEFT_BRACE) {
        printf("Unexpected token: %s\n", token_name(token->type));
        return;
    }

    parser->current_token++;
    token = parser->tokens->data[parser->current_token];
    if (token->type != TOKEN_RIGHT_BRACE) {
        printf("Unexpected token: %s\n", token_name(token->type));
        return;
    }

    array_append(parser->ast->functions, function);
}

/**
 * @brief Get AST from parser
 * 
 * @param parser_t* parser
 * 
 * @return ast_t*
 */
ast_t* parser_ast(parser_t* parser)
{
    return parser->ast;
}

/**
 * @brief Free parser
 * 
 * @param parser_t* parser
 */
void parser_free(parser_t* parser)
{
    free(parser);
}
