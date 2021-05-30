/**
 The One Programming Language

 File: lexer.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _LEXER_H_
#define _LEXER_H_

#include "error.h"
#include "token.h"

typedef struct {
    Token **tokens;

    char *filename; // filename (path)
    char *source; // source string
    Location location;
} Lexer;

Lexer* lexerInit(char *, char *, ErrorsContainer *);

int lexerParse(Lexer *, ErrorsContainer *);

void lexerFree(Lexer *);

#endif
