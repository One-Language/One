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
#include <stdbool.h>

typedef struct _lexer Lexer;

typedef struct _location {
    size_t line; // line number: default is 1
    size_t column; // column number: default is 0
} Location;

typedef enum {
    tok_eof = -1,

    tok_def = -2,
    tok_extern = -3,

    tok_identifier = -4,
    tok_number = -5,
    tok_string = -6,

    tok_define = -8, // '=='
    tok_div_int = -9, // '//'

    tok_type_i8 = -10,
    tok_type_i16 = -11,
    tok_type_i32 = -12,
    tok_type_i64 = -13,

    tok_type_u8 = -14,
    tok_type_u16 = -15,
    tok_type_u32 = -16,
    tok_type_u64 = -17,

    tok_type_f32 = -18,
    tok_type_f64 = -19,

    tok_type_bool = -20,
    tok_type_char = -21,
    tok_type_string = -22,

    tok_ret = -23,

} TokenType;

typedef struct _token {
    TokenType type;
    Location location;

    int vint;
    char *vstring;
} Token;

void token_init();

bool token_is_space(char);

bool token_is_alpha(char);

bool token_is_number(char);

bool token_is_digit(char);

bool token_is_ident(char);


bool token_is_eof(char c);

bool tokenEOF(Lexer *lex);

void tokenNextChar(Lexer *lex);

#endif
