/**
 The One Programming Language

 File: parser/lexer/lexer.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef _ONE_LEXER_LEXER_H_
#define _ONE_LEXER_LEXER_H_

#include "token.h"

// typedef struct _token Token;
// typedef enum _token_type TokenType;
// typedef struct _location Location;

typedef struct
{
	Location pos;
	Location pos_end;

	const char* start;
	const char* current;

	int temp_column;
} Lexer;

extern Lexer lexer;

/*
 * @function: lexer_init
 * @description: Set default value for the global `lexer` variable
 * @arguments: char*; input of One source-code program
 * @return: void; nothing
 */
void lexer_init(char* source);

/*
	Move to the next token
*/
void advance();

/*
	Check if the current token is of type t
*/
bool peekFor(TokenType);

/*
 * @function: lexer_free
 * @description: Free allocated memory for the lexer stage! TODO
 				 Only we have to check it's a user-defined variable or a registered Keyword refer to `keywords` variable
 * @arguments: nothing
 * @return: nothing, void
 */
void lexer_free();

#endif // _ONE_LEXER_LEXER_H_
