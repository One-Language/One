//
// Created by max on 6/9/21.
//

#ifndef ONE_LEXER_H
#define ONE_LEXER_H

typedef struct _token Token;

typedef struct _location
{
	int line;
	int column;
} Location;

typedef struct
{
	const char* start;
	const char* current;
	Location loc;
} Lexer;

void lexer_init(char* source);

void lexer_skip_whitespace();

Token* lexer_number();

Token* lexer_char();

Token* lexer_string();

Token* lexer_scan();

void lexer_free();

#endif //ONE_LEXER_H
