#ifndef _ONE_LEXER_LEXER_H_
#define _ONE_LEXER_LEXER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "../utility/file.h"
#include "../utility/array.h"

typedef enum {
    TOKEN_EOF,

    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_IDENTIFIER,

    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_SEMICOLON,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,

    TOKEN_FN,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_BREAK,
    TOKEN_CONTINUE,
    TOKEN_RET,

    TOKEN_ASSIGN,
    TOKEN_EQUAL,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_STAR,
    TOKEN_SLASH,
    TOKEN_PERCENT
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

    array* tokens;
} Lexer;

Lexer* lexer_new(char* file, char* data);

int lexer_run(Lexer* lexer);

void lexer_next(Lexer* lexer);

void lexer_free(Lexer* lexer);

Token* token_make(TokenType type);

Token* token_make_value(TokenType type, char* value);

bool lexer_eof(Lexer* lexer);

void lexer_identifier(Lexer* lexer);

void lexer_number(Lexer* lexer);

void lexer_debug(Lexer* lexer);

#endif