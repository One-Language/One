/**
 The One Programming Language

 File: parser.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "token.h"
#include "lexer.h"
#include "parser.h"

Parser *parserInit(Lexer *lex, ErrorsContainer *errors)
{
	Parser *pars = malloc(sizeof(Parser));
	pars->lex = lex;
	return pars;
}

int parserCheck(Parser *pars, ErrorsContainer *errors)
{
	printf("=============== Parser ===============\n");

	Token *t;
	for (size_t i = 0; i < pars->lex->token_count; i++)
	{
		t = pars->lex->tokens[i];
		printf("-->%s\n", tokenName(t->type));
	}
	return EXIT_SUCCESS;
}

void parserFree(Parser *pars)
{
}
