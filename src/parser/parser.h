/**
 The One Programming Language

 File: parser/parser.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef _ONE_PARSER_PARSER_H_
#define _ONE_PARSER_PARSER_H_

#include "../lexer/lexer.h"

// typedef struct _token Token;

typedef struct
{
	const char* package;
	const char* path;

	Token** tokens;
} Parser;

/*
 * @function: parser_init
 * @description: Set default value for the global `parser` variable
 * @arguments: char* input, Token** tokens
 * @return: void; nothing
 */
void parser_init(char* input, Token** tokens);

/*
 * @function: parser_free
 * @description: Free allocated memory for the parser stage! TODO
 * @arguments: nothing
 * @return: nothing, void
 */
void parser_free();

#endif // _ONE_PARSER_PARSER_H_
