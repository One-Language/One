/**
 File: token.c
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "one.h"
#include "lexer.h"
#include "token.h"

void token_init()
{

}

Token* token_next(Lexer* lex)
{
  token_nextchar(lex);
}

Token* token_prev(Lexer* lex)
{

}

char token_nextchar(Lexer* lex)
{
  *lex->s++;
}

char token_prevchar(Lexer* lex)
{
  *lex->s--;
}

bool token_end(Lexer* lex)
{
  #ifdef DEBUG
    printf("[token_end] %c\n", *lex->s);
  #endif
  if (*lex->s == '\0') return TRUE;
  return FALSE;
}
