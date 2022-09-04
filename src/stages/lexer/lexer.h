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

Lexer* lexer_make(FILE* file);

bool lexer_is_eof(Lexer* lexer);

Token* lexer_lex(Lexer* lexer);

void lexer_debug(Lexer* lexer);

Token** lexer_tokenizer(Lexer* lexer);
