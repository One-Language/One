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

void lexer_statement(Lexer* lex)
{

}

void lexer_except(Lexer* lex, char tt)
{
  Token* tk = token_get(lex);
  if(tk->type == tt) token_getnext(lex);
  else
    error("Except token %c but we get %c", tt, tk->type);
}

void lexer_statements(Lexer* lex)
{
  lexer_except(lex, '{');
  token_getnext(lex);
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
    t = token_getnext(lex);
    if(t->type == tok_identifier) {
      Token* t2 = token_getnext(lex);
      if(t2->type == '{') {
        lexer_statements(lex);
      }
      else continue;
    }
    tok_log(t);
  }
}
