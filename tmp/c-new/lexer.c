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
  lex->location.t = 0;
  lex->location.i = 0;
  lex->location.l = 0;
  lex->location.c = 0;

  #ifdef DEBUG
    printf("-->%s\n", lex->s);
    printf("-->%s\n", lex->f);
    printf("\n");
  #endif

  return lex;
}

void lexer_prepare(Lexer* lex)
{
  #ifdef DEBUG
    printf("[lexer_prepare]\n");
  #endif

  token_init(lex);

  Token *t;
  while(token_is_end(lex) != true) {
    // printf("===>\n");
    t = token_next(lex);
    vector_add(&lex->tokens, t);

    #ifdef DEBUG
      printf("[lexer_prepare]");
      token_log(t);
    #endif
  }

  // Adding tok_eof at end of tokens vector
  t = token_next(lex);
  if(token_is_end(lex) == true)
    vector_add(&lex->tokens, t);

  // exit(1);

  #ifdef DEBUG
    printf("[lexer_prepare] End\n\n");
  #endif
}

void lexer_start(Lexer* lex)
{
  #ifdef DEBUG
    printf("[lexer_start]\n");
  #endif

  lexer_prepare(lex);
  parser(lex);
}

void lexer_next(Lexer* lex)
{
  lex->location.t++;
}

Token* lexer_getnext(Lexer* lex)
{
  lexer_next(lex);
  return lex->tokens[lex->location.t];
}

void lexer_prev(Lexer* lex)
{
  lex->location.t--;
}

Token* lexer_getprev(Lexer* lex)
{
  lexer_prev(lex);
  return lex->tokens[lex->location.t];
}

Token* lexer_getcurrent(Lexer* lex)
{
  return lex->tokens[lex->location.t];
}

Token* lexer_get(Lexer* lex, size_t index)
{
  return lex->tokens[index];
}
