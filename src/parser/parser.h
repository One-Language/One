#ifndef _ONE_PARSER_PARSER_H_
#define _ONE_PARSER_PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ast.h"
#include "../lexer/lexer.h"

typedef struct {
    Lexer* lexer;
    Ast* ast;
} Parser;

Parser* parser_new(Lexer* lexer);

void parser_run(Parser* parser);

void parser_free(Parser* parser);

#endif
