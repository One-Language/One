#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../../utilities/io.h"

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

typedef struct {
    FILE* file;

    Token** tokens;
    int token_count;

    char* source;
    int offset;
    Location location;
} Lexer;

Lexer* lexer_make(FILE* file);
Token** lexer_lex(Lexer* lexer);
