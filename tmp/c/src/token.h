/**
 File: token.h
  _        _
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

typedef struct lexer Lexer;

#ifndef _TOKEN_H_
#define _TOKEN_H_

#include "one.h"

typedef enum tokenType {
  tok_eof = -1,

  tok_def = -2,
  tok_extern = -3,

  tok_identifier = -4,
  tok_number = -5,
  tok_string = -6,

  tok_define = -8,  // '=='
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

typedef struct token {
  TokenType type;
  size_t l; // line number: default is 1
  size_t c; // column number: default is 0

  int vint;
  sds vstring;
} Token;

void token_init(Lexer *);

bool token_is_space(char);
bool token_is_alpha(char);
bool token_is_number(char);
bool token_is_digit(char);
bool token_is_ident(char);
bool token_is_end(Lexer *);

char token_nextchar(Lexer *);
char token_prevchar(Lexer *);

// Token* token_get(Lexer*);
// Token* token_getnext(Lexer*);

Token *token_next(Lexer *);
Token *token_prev(Lexer *);

void token_free(Token *);
char *token_name(Token *);
void token_log(Token *);
Token *token_get(Lexer *);
bool token_is_operator(Token *);

#endif
