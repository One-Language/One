#ifndef _ONE_PARSER_PARSER_H_
#define _ONE_PARSER_PARSER_H_

#include <stdio.h>
#include <stdlib.h>

#include "../lexer/lexer.h"

typedef struct {
    lexer_t* lexer;
} parser_t;

parser_t* parser_init(lexer_t* lexer);

void parser_free(parser_t* parser);

#endif