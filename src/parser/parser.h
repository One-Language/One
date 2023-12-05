#ifndef _ONE_PARSER_PARSER_H_
#define _ONE_PARSER_PARSER_H_

#include <stdio.h>
#include <stdlib.h>

#include "../lexer/lexer.h"
#include "ast.h"

typedef struct {
    lexer_t* lexer;
    ast_t* ast;
} parser_t;

parser_t* parser_init(lexer_t* lexer);

ast_t* parpser_scan(parser_t* parser);

parser_t* parser_run(lexer_t* lexer);

void parser_free(parser_t* parser);

#endif