/**
 File: lexer.c
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "lexer.h"
#include "token.h"
#include "parser.h"
#include "scanner.h"

Lexer* lexer_init(char *filename, char *input)
{
  #ifdef DEBUG
    printf("[lexer_init]\n");
  #endif

  Lexer* lex = malloc(sizeof(Lexer));
  lex->f = filename;
  lex->s = input;
  lex->tokens = vector_create();

  #ifdef DEBUG
    printf("-->%s\n", lex->s);
    printf("-->%s\n", lex->f);
    printf("\n");
  #endif

  return lex;
}

void lexer_get(Lexer* lex)
{
  #ifdef DEBUG
    printf("[lexer_get]\n");
  #endif

  token_init(lex);

  Token *t;
  while(token_is_end(lex) != true) {
    // printf("===>\n");
    t = token_next(lex);
    vector_add(&lex->tokens, t);

    #ifdef DEBUG
      printf("[lexer_get]");
      tok_log(t);
    #endif
  }
}

void lexer_start(Lexer* lex)
{
  #ifdef DEBUG
    printf("[lexer_start]\n");
  #endif

  lexer_get(lex);
  parser(lex);
}
