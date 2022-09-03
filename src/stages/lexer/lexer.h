/**
 The One Programming Language
 File: stages/lexer/lexer.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2020-2022; One Language Contributors
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "token.h"
#include "../../utilities/io.h"

typedef struct {
    FILE* file;

    Token** tokens;
    int token_count;

    char* source;
    int offset;
    Location location;
} Lexer;

void lexer_go_next_char(Lexer* lexer);

void lexer_go_prev_char(Lexer* lexer);

char lexer_get_next_char(Lexer* lexer);

char lexer_get_prev_char(Lexer* lexer);

bool lexer_is_eof(Lexer* lexer);

void lexer_skip_whitespace(Lexer* lexer);

Token* lexer_read_identifier(Lexer* lexer);

Token* lexer_next_token(Lexer* lexer);

Token** lexer_lex(Lexer* lexer);
