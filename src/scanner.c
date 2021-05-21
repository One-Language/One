/**
 File: scanner.c
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "scanner.h"

void scanner_parse(Lexer* lex)
{
  #ifdef DEBUG
    printf("[lexer_parse]\n");
  #endif

  int count = vector_size(lex->tokens); 
  Token *t;
  for(int i=0;i<count;i++) {
    t = lex->tokens[i];
  
    #ifdef DEBUG
      printf("[lexer_parse]");
      tok_log(t);
    #endif

    // if(t->type == tok_identifier) {
    //   Token* t2 = token_getnext(lex);
    //   if(t2->type == '{') {
    //     #ifdef DEBUG
    //     printf("\nDefine function %s\n", t->vstring);
    //     #endif
    //     lexer_statements(lex);
    //   }
    //   else continue;
    // }

  }
}
