/**
 The One Programming Language
 File: stages/lexer/token.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2020-2022; One Language Contributors
 **/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    TOKEN_IDENTIFIER,

    TOKEN_KEYWORD_IF,
    TOKEN_KEYWORD_ELSE,
    TOKEN_KEYWORD_WHILE,
    TOKEN_KEYWORD_RETURN,
    TOKEN_KEYWORD_FOR,
    TOKEN_KEYWORD_FN,

    TOKEN_OPERATOR_PAREN_LEFT,
    TOKEN_OPERATOR_PAREN_RIGHT,
    TOKEN_OPERATOR_BRACE_LEFT,
    TOKEN_OPERATOR_BRACE_RIGHT,

    TOKEN_OPERATOR_SEMICOLON,
    TOKEN_OPERATOR_COMMA,

    TOKEN_EOF
} TokenType;

typedef struct {
    int line;
    int column;
    int offset;
} Location;

typedef struct {
    TokenType type;
    char* value;

    Location start;
    Location end;
} Token;

bool is_whitespace(char ch);

bool is_identifier(char ch);

bool is_digit(char ch);

bool is_alpha(char ch);

char* get_token_name(Token* t);

Token* token_make(TokenType type, char* value, Location start, Location end);
