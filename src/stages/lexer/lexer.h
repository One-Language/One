//
// Created by Max on 9/4/2022.
//

#ifndef SRC_LEXER_H
#define SRC_LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../builtins/io.h"
#include "../../builtins/array.h"
#include "../../builtins/str.h"
#include "../../builtins/error.h"

typedef struct {
    char* main_source;
    char* source;
    Location position;
    Array* tokens;
    Array* errors;
} Lexer;

typedef enum {
    TOKEN_EOF,
    TOKEN_ERROR,

    TOKEN_IDENTIFIER,
    TOKEN_FN,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_WHILE,
    TOKEN_FOR,
    TOKEN_RET,

    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,

    TOKEN_LBRACKET,
    TOKEN_RBRACKET,

    TOKEN_GT,
    TOKEN_LT,
    TOKEN_GTE,
    TOKEN_LTE,
    TOKEN_NEQ,
    TOKEN_EQ,
    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_MOD,
    TOKEN_POW,
    TOKEN_NOT,
    TOKEN_AND,
    TOKEN_OR,
    TOKEN_ANDAND,
    TOKEN_OROR,
    TOKEN_INC,
    TOKEN_DEC,
    TOKEN_ASSIGN,
    TOKEN_ADD_ASSIGN,
    TOKEN_SUB_ASSIGN,
    TOKEN_MUL_ASSIGN,
    TOKEN_DIV_ASSIGN,
    TOKEN_MOD_ASSIGN,

    TOKEN_DOT,
    TOKEN_DOTDOT,
    TOKEN_ELLIPSIS,
    TOKEN_SEMICOLON,
    TOKEN_COMMA,
    TOKEN_COLON,
    TOKEN_TILDE,
} TokenType;

typedef struct {
    TokenType type;
    char* value;

    Location start;
    Location end;
} Token;

Lexer* lexer_init(char* source);

Token* lexer_lex(Lexer* lexer);

void lexer_tokenizer(Lexer* lexer);

sds lexer_trace(Lexer* lexer);

char* token_type_name(TokenType type);

void lexer_free(Lexer* lexer);

#endif //SRC_LEXER_H
