/**
 The One Programming Language

 File: token.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
#include <stdbool.h>

typedef struct _lexer Lexer;

typedef struct _location {
    size_t line; // line number: default is 1
    size_t column; // column number: default is 0
} Location;

typedef enum {
    tok_eof = -1,
    tok_unknowm,
    // ================= keywords
    tok_def,
    tok_extern,
    tok_ret,
    tok_if,
    tok_else,
    tok_do,
    tok_while,
    tok_for,
    tok_switch,
    // ================= values
    tok_identifier,
    tok_number,
    tok_string,

    tok_define,
    tok_div_int,
    // ================= types
    tok_type_i8,
    tok_type_i16,
    tok_type_i32,
    tok_type_i64,

    tok_type_u8,
    tok_type_u16,
    tok_type_u32,
    tok_type_u64,

    tok_type_f32,
    tok_type_f64,

    tok_type_bool,
    tok_type_char,
    tok_type_string,
    // ================= operators
    tok_op_plus, // +
    tok_op_minus, // -
    tok_op_mul, // *
    tok_op_div, // /
} TokenType;

typedef struct _token {
    TokenType type;
    Location location;

    int vint;
    char *vstring;
} Token;

void token_init();

bool token_is_space(char);

bool token_is_line(char);

bool token_is_freespace(char);

bool token_is_freeline(char);

bool token_is_free(char);

bool token_is_alphaasci(char);

bool token_is_alpha(char);

bool token_is_number(char);

bool token_is_digit(char);

bool token_is_ident(char);


bool token_is_eof(char);

bool tokenEOF(Lexer *);

void tokenNextChar(Lexer *);

void tokenPrevChar(Lexer *);

Token *tokenNext(Lexer *);

char *tokenName(TokenType );

#endif
