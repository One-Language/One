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
    printf("[parser_except] %c %d\n", tt, tt);
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
  while(true) {
    t = lexer_getcurrent(lex);
    if(t == NULL || t->type == tok_eof) break;
  
    #ifdef DEBUG
      printf("[parser]");
      token_log(t);
    #endif

    if(t->type == tok_identifier) {
      Token* t2 = lexer_getnext(lex);
      if(t2->type == '{') {
        #ifdef DEBUG
          printf("========= Define function %s\n", t->vstring);
        #endif

        lexer_prev(lex); // back to identifier
        parser_function(lex);
      }
      else {
        lexer_next(lex);
        continue;
      }
    }
    else {
      lexer_next(lex);
      continue;
    }


  }
}

void parser_function(Lexer* lex)
{
  Token* t;

  #ifdef DEBUG
    printf("[parser_function]\n");
  #endif

  t = lexer_getcurrent(lex);
  #ifdef DEBUG
    printf("[parser_function] current token: %s\n", token_name(t));
  #endif
  parser_except(lex, tok_identifier);
  sds name = t->vstring;
  #ifdef DEBUG
    printf("[parser_function] name: %s\n", name);
  #endif


  t = lexer_getcurrent(lex);
  #ifdef DEBUG
    printf("[parser_function] current token: %s\n", token_name(lexer_getcurrent(lex)));
  #endif

  if(t->type == '{')
    parser_statements(lex);
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

  Token* t;
  while((t = lexer_getnext(lex)) && t->type != '}') {
    #ifdef DEBUG
      printf("[parser_statements] %s\n", token_name(t));
    #endif
  }

  parser_except(lex, '}');
}
