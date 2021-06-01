/**
 The One Programming Language

 File: parser.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _PARSER_H_
#define _PARSER_H_

typedef struct _token Token;
typedef struct _location Location;
typedef struct _errors ErrorsContainer;
typedef struct _lexer Lexer;

typedef struct _parser
{
	Lexer *lex;
} Parser;

Parser *parserInit(Lexer *, ErrorsContainer *);

int parserCheck(Parser *, ErrorsContainer *);

void parserFree(Parser *);

bool tokenIsUserType(Parser *, ErrorsContainer *);
bool tokenIsPrimaryType(Parser *, ErrorsContainer *);

int exceptGo(Parser *, TokenType, ErrorsContainer *);

int except(Parser *, TokenType, ErrorsContainer *);

#endif
