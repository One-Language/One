#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utility/file.h"

typedef enum {
    TOKEN_EOF,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT,
    TOKEN_CARET,
    TOKEN_AMPERSAND,
    TOKEN_PIPE,
    TOKEN_TILDE,
    TOKEN_EXCLAMATION,
    TOKEN_QUESTION,
    TOKEN_COLON,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_EQUAL,
    TOKEN_LESS,
    TOKEN_GREATER,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_IDENTIFIER,
    TOKEN_STRING,
    TOKEN_INTEGER,
    TOKEN_FLOAT
} TokenType;

typedef struct {
    TokenType type;
    char* value;
} Token;

typedef struct {
    char* file;
    char* file_dir;

    char* buffer;
    uint32_t                    offset;         // current buffer offset (in bytes)
    // uint32_t                    position;       // current buffer position (in characters)
    uint32_t                    length;         // buffer length (in bytes)
    uint32_t                    line;         // line counter
    uint32_t                    column;          // column counter

    Token** tokens;
    int token_size;
} Lexer;

Lexer* lexer_new(char* file, char* data);

int lexer_run(Lexer* lexer);

void lexer_next(Lexer* lexer);

void lexer_free(Lexer* lexer);

Token* token_make(TokenType type);

Token* token_make_value(TokenType type, char* value);
