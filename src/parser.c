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
 * @brief Parser eat a token
 * 
 * @param parser_t* parser
 * 
 * @return token_t*
 */
token_t* parser_eat(parser_t* parser)
{
    token_t* token = parser->tokens->data[parser->current_token];
    parser->current_token++;
    return token;
}

/**
 * @brief Parser check if has a token type
 * 
 * @param parser_t* parser
 * @param token_type_t type
 * 
 * @return bool
 */
bool parser_has(parser_t* parser, token_type_t type)
{
    token_t* token = parser->tokens->data[parser->current_token];
    return token->type == type;
}

/**
 * @brief Parser skip a token type
 * 
 * @param parser_t* parser
 * @param token_type_t type
 * 
 * @return bool
 */
bool parser_skip(parser_t* parser, token_type_t type)
{
    if (parser_has(parser, type)) {
        parser->current_token++;
        return true;
    }
    return false;
}

/**
 * @brief Parser expect a token type
 * 
 * @param parser_t* parser
 * @param token_type_t type
 * 
 * @return token_t*
 */
token_t* parser_expect(parser_t* parser, token_type_t type)
{
    token_t* token = parser->tokens->data[parser->current_token];
    if (token->type != type) {
        printf("Unexpected token: %s\n", token_name(token->type));
        return NULL;
    }
    parser->current_token++;
    return token;
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

        if (token->type == TOKEN_FUNC) {
            ast_function_t* function = parser_parse_function(parser);
            if (function != NULL) array_push(parser->ast->functions, function);
        }
        else {
            printf("Unexpected token: %s\n", token_name(token->type));
            parser->current_token++;
        }
    }
}

/**
 * @brief Parse statements
 * 
 * @param parser_t* parser
 * 
 * @return array_t* (array of ast_statement_t*)
 */
array_t* parser_parse_statements(parser_t* parser)
{
    array_t* statements = array_init();

    while (!parser_skip(parser, TOKEN_RIGHT_BRACE)) {
        token_t* token = parser_eat(parser);
        array_push(statements, token);
    }

    return statements;
}

/**
 * @brief Parse function
 * 
 * @param parser_t* parser
 * 
 * @return ast_function_t*
 */
ast_function_t* parser_parse_function(parser_t* parser)
{
    ast_function_t* function = ast_function_init();

    parser_expect(parser, TOKEN_FUNC);
    token_t* name = parser_expect(parser, TOKEN_IDENTIFIER);
    parser_expect(parser, TOKEN_LEFT_PAREN);
    parser_expect(parser, TOKEN_RIGHT_PAREN);

    function->name = name->value;
    function->statements = parser_parse_statements(parser);

    return function;
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
