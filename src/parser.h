//
// Created by max on 6/9/21.
//

#ifndef ONE_PARSER_H
#define ONE_PARSER_H

typedef struct _token Token;

typedef struct
{
	Token** tokens;
	size_t tokens_count;
} Parser;

void parser_init();

void parser_scan();

void parser_start();

void parser_check();

void parser_free();

#endif //ONE_PARSER_H
