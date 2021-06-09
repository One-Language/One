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

Token lexer_scan();

#endif //ONE_LEXER_H
