/**
 The One Programming Language

 File: lexer/lexer.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef _ONE_LEXER_LEXER_H_
#define _ONE_LEXER_LEXER_H_

typedef struct
{
	const char* start;
	const char* current;
	Location loc;
} Lexer;

#endif // _ONE_LEXER_LEXER_H_
