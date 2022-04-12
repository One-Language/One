/**
The One Programming Language

File: lexer/lexer.c
 _        _
/ \ |\ | |_    Max Base
\_/ | \| |_    Copyright 2022; One Language Contributors

**/

#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

Lexer* lexer_init(char* file_path, char* input)
{
	printf("lexer_init\n");

	Lexer* lexer = (Lexer*) malloc(sizeof(Lexer));

	lexer->path = file_path;
	lexer->input = input;
	array_init(lexer->tokens);

	return lexer;
}

Token* lexer_next(Lexer* lexer)
{
	printf("lexer_next\n");

	Token* token = (Token*) malloc(sizeof(Token));

	if(*(lexer->current_pos) == '\0')
		token = token_make(lexer->current_pos, lexer->current_pos+1, TokenTypeEndOfFile);
	else
		token = token_make(lexer->current_pos, lexer->current_pos+1, TokenTypeNumber);
	lexer->current_pos += 1;

	return token;
}

void lexer_execute(Lexer* lexer)
{
	printf("lexer_execute\n");

	Token* token;

	do {
		token = lexer_next(lexer);
		array_push(lexer->tokens, token);
	} while(token->type != TokenTypeEndOfFile);
}
