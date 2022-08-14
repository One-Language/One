/**
The One Programming Language

File: lexer/main.c
 _        _
/ \ |\ | |_    Max Base
\_/ | \| |_    Copyright 2022; One Language Contributors

**/

#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

int main(int argc, char** argv)
{
	Lexer* lexer;

	printf("%d\n", argc);
	if(argc == 2) {
		lexer = lexer_init("INPUT", "5+5\n3.14");
		lexer_execute(lexer);

		printf("Number of tokens: %d\n", lexer->tokens->count);
		for (int i = 0; i < lexer->tokens->count; i++) {
			// Token* token = lexer->tokens->data[i];
			printf("token\n");
		}
	}
	else {
		printf("Error: arguments are not correct!\n");
		printf("one_lexer input.one output\n");
		printf("one_lexer \"your input here as string\"\n");
	}
	return 0;
}
