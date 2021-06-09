//
// Created by max on 6/9/21.
//

#ifndef ONE_LEXER_H
#define ONE_LEXER_H

typedef struct
{
	const char* start;
	const char* current;
	Location loc;
} Lexer;

static void lexer_init(char* source);

#endif //ONE_LEXER_H
