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
    printf("[parser_except] %c\n", tt);
  #endif

  Token* t = lexer_getcurrent(lex);
  if(t == NULL)
    error("Sorry, cannot access to current token at %d!", lex->location.t);
  else if(t->type == tt) lexer_next(lex);
  else
    error("Except token %c but we get %c", tt, t->type);
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

  #ifdef DEBUG
    printf("[parser] last token: %s\n", token_name(lex->tokens[count-1]));
    // printf("[parser] last token: %d\n", lex->tokens[count-1]->type);
  #endif


  Token *t;
  for(int i=0;i<count;i++) {
    t = lexer_get(lex, i);
  
    #ifdef DEBUG
      printf("[parser]");
      token_log(t);
    #endif

    if(t->type == tok_identifier) {
      Token* t2 = lexer_get(lex, ++i);
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
