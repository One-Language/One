/**
 File: lexer.c
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "one.h"
#include "lexer.h"
#include "token.h"

Lexer* lexer_init(char *filename, char *input)
{
  Lexer* lex = malloc(sizeof(Lexer));
  lex->f = filename;
  lex->s = input;
  // #ifdef DEBUG
  //   printf("-->%s\n", lex->f);
  //   printf("-->%s\n", lex->s);
  // #endif
  return lex;
}

void lexer_parse(Lexer* lex)
{
  token_init(lex);

  #ifdef DEBUG
    printf("-->%s\n", lex->f);
    // printf("-->%s\n", lex->s);
  #endif

  Token *t;
  while(token_is_end(lex) == FALSE) {
    t = token_next(lex);
    tok_log(t);
  }
}
