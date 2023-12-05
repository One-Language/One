#include <stdio.h>
#include <stdlib.h>
#include "../lexer/lexer.h"

typedef struct {
    lexer_t* lexer;
} parser_t;

parser_t* parser_init(lexer_t* lexer);

void parser_free(parser_t* parser);
