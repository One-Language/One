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
 * @brief Parser go to next token
 * 
 * @param parser_t* parser
 * 
 * @return void
 */
void parser_next(parser_t* parser)
{
    if (parser->current_token < parser->tokens->size) parser->current_token++;
}

/**
 * @brief Parser go to previous token
 * 
 * @param parser_t* parser
 * 
 * @return void
 */
void parser_previous(parser_t* parser)
{
    if (parser->current_token > 0) parser->current_token--;
}

/**
 * @brief Parser peek a token
 * 
 * @param parser_t* parser
 * 
 * @return token_t*
 */
token_t* parser_peek(parser_t* parser)
{
    return parser->tokens->data[parser->current_token];
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
        printf("Unexpected token %s while expecting %s\n", token_name(token->type), token_name(type));
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

        if (token->type == TOKEN_EOF) break;
        else if (token->type == TOKEN_FUNC) {
            ast_function_t* function = parser_parse_function(parser);
            if (function != NULL) array_push(parser->ast->functions, function);
        }
        else {
            printf("Unexpected token in parser: %s\n", token_name(token->type));
            parser->current_token++;
        }
    }
}

ast_expr_t* parser_parse_expression(parser_t* parser)
{
    ast_expr_t* expr = ast_expression_init();

    token_t* token = parser_eat(parser);
    expr->value = token;

    return expr;
}

/**
 * @brief Parser parse an if statement
 * 
 * @param parser_t* parser
 * 
 * @return ast_if_t*
 */
ast_if_t* parser_parse_if(parser_t* parser)
{
    ast_if_t* stmt_if = ast_statement_if_init();

    if(!parser_expect(parser, TOKEN_IF)) return NULL;

    stmt_if->condition = parser_parse_expression(parser);

    stmt_if->then = parser_parse_block(parser);

    if (parser_skip(parser, TOKEN_ELSE)) {
        if (parser_has(parser, TOKEN_IF)) {
            stmt_if->else_ = parser_parse_if(parser);
        }
        else if (parser_has(parser, TOKEN_LEFT_BRACE)) stmt_if->else_ = parser_parse_block(parser);
        else {
            printf("Unexpected token %s after else\n", token_name(parser_peek(parser)->type));
            return NULL;
        }
    }

    return stmt_if;
}

/**
 * @brief Parser parse a ret statement
 * 
 * @param parser_t* parser
 * 
 * @return ast_ret_t*
 */
ast_ret_t* parser_parse_ret(parser_t* parser)
{
    ast_ret_t* stmt_ret = ast_statement_ret_init();

    if(!parser_expect(parser, TOKEN_RET)) return NULL;

    stmt_ret->expression = parser_parse_expression(parser);

    return stmt_ret;
}

/**
 * @brief Parser parse a statement
 * 
 * @param parser_t* parser
 * 
 * @return ast_statement_t* 
 */
ast_statement_t* parser_parse_statement(parser_t* parser)
{
    ast_statement_t* statement = ast_statement_init();

    token_t* token = parser_peek(parser);
    switch (token->type) {
        case TOKEN_IF: {
            statement->type = AST_STATEMENT_IF;
            statement->stmt_if = parser_parse_if(parser);
            if (statement->stmt_if == NULL) return NULL;
            break;
        }

        case TOKEN_RET: {
            statement->type = AST_STATEMENT_RET;
            statement->stmt_ret = parser_parse_ret(parser);
            if (statement->stmt_ret == NULL) return NULL;
            break;
        }

        default: {
            printf("Unexpected token in statement: %s\n", token_name(token->type));
            parser_next(parser);
            return NULL;
        }
    }

    return statement;
}

/**
 * @brief Parser parse statements
 * 
 * @param parser_t* parser
 * 
 * @return array_t* (array of ast_statement_t*)
 */
array_t* parser_parse_statements(parser_t* parser)
{
    array_t* statements = array_init();

    while (!parser_has(parser, TOKEN_RIGHT_BRACE) && !parser_has(parser, TOKEN_EOF)) {
        ast_statement_t* statement = parser_parse_statement(parser);
        if (statement != NULL) array_push(statements, statement);
    }

    return statements;
}

/**
 * @brief Parse statements
 * 
 * @param parser_t* parser
 * 
 * @return ast_block_t*
 */
ast_block_t* parser_parse_block(parser_t* parser)
{
    ast_block_t* block = ast_block_init();

    if(!parser_expect(parser, TOKEN_LEFT_BRACE)) return NULL;

    block->statements = parser_parse_statements(parser);
    if (block->statements == NULL) return NULL;

    if(!parser_expect(parser, TOKEN_RIGHT_BRACE)) return NULL;

    return block;
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

    if (!parser_expect(parser, TOKEN_FUNC)) return NULL;
    token_t* name = parser_expect(parser, TOKEN_IDENTIFIER);

    if (!parser_expect(parser, TOKEN_LEFT_PAREN)) return NULL;
    if (!parser_expect(parser, TOKEN_RIGHT_PAREN)) return NULL;

    function->name = name->value;
    function->block = parser_parse_block(parser);
    if (!function->block) return NULL;

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
