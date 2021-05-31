/**
 The One Programming Language

 File: lexer.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _LEXER_H_
#define _LEXER_H_

typedef struct _token Token;
typedef struct _location Location;
typedef struct _errors ErrorsContainer;

typedef struct _lexer {
    Token **tokens;
    size_t token_count;

    char *filename; // filename (path)
    char *source; // source string
    Location location;
} Lexer;

Lexer *lexerInit(char *, char *, ErrorsContainer *);

int lexerCheck(Lexer *, ErrorsContainer *);

void lexerFree(Lexer *);

#endif
