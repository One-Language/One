/**
 File: parser.c
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "token.h"
#include "lexer.h"
#include "parser.h"

// extern Token* tk;

void parser_except(Lexer* lex, char tt)
{
  #ifdef DEBUG
    printf("[lexer_except] %c\n", tt);
  #endif

  // Token* t = token_get(lex);
  // if(t->type == tt) token_get(lex);
  // else
  //   error("Except token %c but we get %c", tt, t->type);
}

void parser(Lexer* lex)
{
  #ifdef DEBUG
    printf("[parser]\n");
  #endif

  int count = vector_size(lex->tokens); 
  #ifdef DEBUG
    printf("[parser] token size: %d\n", count);
  #endif

  Token *t;
  for(int i=0;i<count;i++) {
    t = lex->tokens[i];
  
    #ifdef DEBUG
      printf("[parser]");
      tok_log(t);
    #endif

    if(t->type == tok_identifier) {
      Token* t2 = lex->tokens[++i];
      if(t2->type == '{') {

        #ifdef DEBUG
          printf("\nDefine function %s\n", t->vstring);
        #endif

        parser_statements(lex);
      }
      else continue;
    }

  }
}

void parser_statement(Lexer* lex)
{
  #ifdef DEBUG
    printf("[parser_statement]");
  #endif
  token_next(lex);
}

void parser_statements(Lexer* lex)
{
  #ifdef DEBUG
    printf("[parser_statements]\n");
  #endif

  parser_except(lex, '{');
  // while(tk->type != '}') {
  //   parser_statement(lex);
  // }

  #ifdef DEBUG
    printf("\n");
  #endif
}
