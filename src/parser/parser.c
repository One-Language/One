#include "parser.h"

parser_t* parser_init(lexer_t* lexer)
{
    parser_t* parser = malloc(sizeof(parser_t));
    if (parser == NULL) {
        printf("Error: Not enough memory to create a parser.");
        exit(74);
    }

    parser->lexer = lexer;
    parser->ast = ast_init();

    return parser;
}

void parser_error(parser_t* parser, char* error_format, ...)
{
    // TODO: Adding n args into error_format...
    printf("Parser error: %s\n", error_format);
}

lexer_token_t* parser_prev(parser_t* parser)
{
    parser->lexer->tokens--;
    lexer_token_t* prev_token = (lexer_token_t*) *parser->lexer->tokens;
    parser->lexer->tokens++;

    return prev_token;
}

lexer_token_t* parser_prev_prev(parser_t* parser)
{
    parser->lexer->tokens--;
    parser->lexer->tokens--;
    lexer_token_t* prev_prev_token = (lexer_token_t*) *parser->lexer->tokens;
    parser->lexer->tokens++;
    parser->lexer->tokens++;

    return prev_prev_token;
}

lexer_token_t* parser_next(parser_t* parser)
{
    parser->lexer->tokens++;
    lexer_token_t* next_token = (lexer_token_t*) *parser->lexer->tokens;
    parser->lexer->tokens--;

    return next_token;
}

lexer_token_t* parser_next_next(parser_t* parser)
{
    parser->lexer->tokens++;
    parser->lexer->tokens++;
    lexer_token_t* next_next_token = (lexer_token_t*) *parser->lexer->tokens;
    parser->lexer->tokens--;
    parser->lexer->tokens--;

    return next_next_token;
}

bool parser_has(parser_t* parser, lexer_token_type_t type)
{
    lexer_token_t* current_token = (lexer_token_t*) *parser->lexer->tokens;

    if (current_token->type != type) return false;
    else return true;
}

bool parser_expect(parser_t* parser, lexer_token_type_t type)
{
    lexer_token_t* current_token = (lexer_token_t*) *parser->lexer->tokens;

    if (current_token->type != type) {
        parser_error(parser, "expecting %s but fouding %s\n", lexer_token_type_name(type), lexer_token_type_name(current_token->type));
        return false;
    }

    return true;
}

ast_t* parpser_scan(parser_t* parser)
{
    return parser->ast;    
}

parser_t* parser_run(lexer_t* lexer)
{
    parser_t* parser = parser_init(lexer);
    parser->ast = parpser_scan(parser);


    return parser;
}

void parser_free(parser_t* parser)
{
    lexer_free(parser->lexer);
    free(parser->lexer);
}
