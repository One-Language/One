//
// Created by Max on 9/4/2022.
//

#ifndef SRC_LEXER_H
#define SRC_LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <str.h>

#include "../../builtins/io.h"
#include "../../builtins/array.h"
#include "../../builtins/str.h"
#include "../../builtins/error.h"

typedef struct {
    int offset;
    int line;
    int column;
} Location;

typedef struct {
    char* source;
    Location position;
    Array* tokens;
} Lexer;

typedef enum {
    TOKEN_EOF,
    TOKEN_ERROR,

    TOKEN_IDENTIFIER,
    TOKEN_FN,

    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
} TokenType;

typedef struct {
    TokenType type;
    char* value;

    Location start;
    Location end;
} Token;

Lexer* lexer_init(char* source);

void lexer_tokenizer(Lexer* lexer);

sds lexer_trace(Lexer* lexer);

#endif //SRC_LEXER_H
