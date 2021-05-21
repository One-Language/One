/**
 File: lexer.h
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

typedef struct token Token;

#ifndef _LEXER_H_
#define _LEXER_H_

#include "one.h"

typedef struct _location {
  size_t    i;    // file source index' character
  size_t    l;    // line number: default is 1
  size_t    c;    // column number: default is 0
} Location;

typedef struct lexer {
  // Assembly *assembly;
  Token**   tokens;

  char *    f;    // filename (path)
  char *    s;    // source string
  Location location;
} Lexer;

#include "scanner.h"

Lexer* lexer_init(char*, char*);
void lexer_get(Lexer*);
void lexer_start(Lexer*);

#endif
