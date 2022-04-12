//
// Created by max on 4/12/22.
//

#ifndef ONE_TOKEN_H
#define ONE_TOKEN_H

typedef enum {
	#undef TOKEN_DEFINE
	#define TOKEN_DEFINE(ID, NAME, VALUE) ID VALUE,
	#include "token_type.h"
} TokenType;

typedef struct {
	char* start_ptr;
	char* end_ptr;
	TokenType type;
} Token;


Token* token_make(char* start_ptr, char* end_ptr, TokenType type);

#endif //ONE_TOKEN_H
