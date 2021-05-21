/**
 File: lexer.c
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "one.h"
#include "lexer.h"
#include "token.h"

extern Token* tk;

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
  #ifdef DEBUG
    printf("[lexer_statement]");
    tok_log(tk);
  #endif
  token_getnext(lex);
}

void lexer_except(Lexer* lex, char tt)
{
  Token* t = token_get(lex);
  if(t->type == tt) token_getnext(lex);
  else
    error("Except token %c but we get %c", tt, t->type);
}

void lexer_statements(Lexer* lex)
{
  #ifdef DEBUG
    printf("[lexer_statements]\n");
  #endif
  lexer_except(lex, '{');
  while(tk->type != '}') {
    lexer_statement(lex);
  }

  #ifdef DEBUG
    printf("\n");
  #endif
}

void lexer_parse(Lexer* lex)
{
  token_init(lex);

  #ifdef DEBUG
    printf("Source = %s\n", lex->f);
    // printf("-->%s\n", lex->s);
  #endif

  Token *t1;
  while(token_is_end(lex) == FALSE) {
    t1 = token_getnext(lex);

    printf("[lexer_parse]");
    tok_log(t1);

    if(t1->type == tok_identifier) {
      Token* t2 = token_getnext(lex);
      if(t2->type == '{') {
        #ifdef DEBUG
        printf("\nDefine function %s\n", t1->vstring);
        #endif
        lexer_statements(lex);
      }
      else continue;
    }
  }
}
