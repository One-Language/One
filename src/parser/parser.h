#ifndef _ONE_PARSER_PARSER_H_
#define _ONE_PARSER_PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// #include "../lexer/token.h"
#include "../lexer/lexer.h"
#include "ast.h"

typedef struct {
    lexer_t* lexer;
    ast_t* ast;
} parser_t;

parser_t* parser_init(lexer_t* lexer);

void parser_error(parser_t* parser, char* error_format, ...);

lexer_token_t* parser_prev(parser_t* parser);

lexer_token_t* parser_prev_prev(parser_t* parser);

lexer_token_t* parser_next(parser_t* parser);

lexer_token_t* parser_next_next(parser_t* parser);

bool parser_has(parser_t* parser, lexer_token_type_t type);

bool parser_expect(parser_t* parser, lexer_token_type_t type);

ast_t* parpser_scan(parser_t* parser);

parser_t* parser_run(lexer_t* lexer);

void parser_free(parser_t* parser);

#endif