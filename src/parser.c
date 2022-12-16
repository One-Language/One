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
        else if (token->type == TOKEN_VAR) parser_parse_variable(parser);
        else if (token->type == TOKEN_IF) parser_parse_if(parser);
        else if (token->type == TOKEN_WHILE) parser_parse_while(parser);
        else if (token->type == TOKEN_FOR) parser_parse_for(parser);
        else if (token->type == TOKEN_RETURN) parser_parse_return(parser);
        else if (token->type == TOKEN_BREAK) parser_parse_break(parser);
        else if (token->type == TOKEN_CONTINUE) parser_parse_continue(parser);
        else if (token->type == TOKEN_IMPORT) parser_parse_import(parser);
        else if (token->type == TOKEN_USE) parser_parse_use(parser);
        else if (token->type == TOKEN_CLASS) parser_parse_class(parser);
        else if (token->type == TOKEN_ENUM) parser_parse_enum(parser);
        else if (token->type == TOKEN_STRUCT) parser_parse_struct(parser);
        else if (token->type == TOKEN_INTERFACE) parser_parse_interface(parser);
        else if (token->type == TOKEN_NAMESPACE) parser_parse_namespace(parser);
        else if (token->type == TOKEN_SWITCH) parser_parse_switch(parser);
        else if (token->type == TOKEN_TRY) parser_parse_try(parser);
        else if (token->type == TOKEN_CATCH) parser_parse_catch(parser);
        else if (token->type == TOKEN_THROW) parser_parse_throw(parser);
        else if (token->type == TOKEN_PUBLIC) parser_parse_public(parser);
        else if (token->type == TOKEN_PRIVATE) parser_parse_private(parser);
        else if (token->type == TOKEN_PROTECTED) parser_parse_protected(parser);
        else if (token->type == TOKEN_STATIC) parser_parse_static(parser);
        else if (token->type == TOKEN_CONST) parser_parse_const(parser);
        else if (token->type == TOKEN_EXTERN) parser_parse_extern(parser);
        else if (token->type == TOKEN_VIRTUAL) parser_parse_virtual(parser);
        else if (token->type == TOKEN_ABSTRACT) parser_parse_abstract(parser);
        else if (token->type == TOKEN_OVERRIDE) parser_parse_override(parser);
        else if (token->type == TOKEN_FINAL) parser_parse_final(parser);
        else if (token->type == TOKEN_NEW) parser_parse_new(parser);
        else if (token->type == TOKEN_DELETE) parser_parse_delete(parser);
        else if (token->type == TOKEN_OPERATOR) parser

        parser->current_token++;
    }
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
