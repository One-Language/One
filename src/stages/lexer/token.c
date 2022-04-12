//
// Created by max on 4/12/22.
//

#include <stdio.h>
#include <stdlib.h>

#include "token.h"

Token* token_make(char* start_ptr, char* end_ptr, TokenType type)
{
	printf("token_make\n");

	Token* token = malloc(sizeof(Token));

	token->start_ptr = start_ptr;
	token->end_ptr = end_ptr;
	token->type = type;

	return token;
}