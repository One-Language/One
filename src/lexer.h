/**
 File: lexer.h
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include <stdio.h>
#include <stdlib.h>
#include "vec.h"
#include "token.h"

typedef struct lexer {
  // Assembly *assembly;
  Token**   tokens;

  char *    f;    // filename (path)
  char *    s;    // source string

  size_t    l;    // line number: default is 1
  size_t    c;    // column number: default is 0
} Lexer;

Lexer* lexer_init(char*, char*);
void lexer_parse(Lexer*);
void lexer_statement(Lexer*);
void lexer_statements(Lexer*);
