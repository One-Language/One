/**
 File: token.h
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

typedef struct token {
  unsigned int type;
  size_t    l;    // line number: default is 1
  size_t    c;    // column number: default is 0
} Token;

void token_init();
bool token_end(Lexer*);
char token_nextchar(Lexer*);
char token_prevchar(Lexer*);
Token* token_next(Lexer*);
Token* token_prev(Lexer*);
