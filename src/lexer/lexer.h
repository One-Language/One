#ifndef _ONE_LEXER_LEXER_H_
#define _ONE_LEXER_LEXER_H_

#include <stdio.h>
#include <stdlib.h>

#include "../builtins/file.h"
#include "../builtins/array.h"

#include "token.h"

typedef struct {
    char* source;
    char* current;
    char* original_source;

    int line;
    int column;

    array_token_t* tokens;
} lexer_t;

lexer_t* lexer_init(char* source);

lexer_t* lexer_run(char* source);

char* lexer_log(lexer_t* lexer);

bool lexer_is_at_end(lexer_t* lexer);

void lexer_scan_token(lexer_t* lexer);

lexer_t* lexer_scan_tokens(lexer_t* lexer);

void lexer_free(lexer_t* lexer);

void lexer_add_token(lexer_t* lexer, lexer_token_t* token);

#endif