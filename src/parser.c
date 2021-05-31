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

bool tokenIsPrimaryType(Token *t)
{
	if (t->type == TOKEN_TYPE_I8)
		return true;
	else if (t->type == TOKEN_TYPE_I16)
		return true;
	else if (t->type == TOKEN_TYPE_I32)
		return true;
	else if (t->type == TOKEN_TYPE_I64)
		return true;
	else if (t->type == TOKEN_TYPE_I128)
		return true;

	else if (t->type == TOKEN_TYPE_U8)
		return true;
	else if (t->type == TOKEN_TYPE_U16)
		return true;
	else if (t->type == TOKEN_TYPE_U32)
		return true;
	else if (t->type == TOKEN_TYPE_U64)
		return true;
	else if (t->type == TOKEN_TYPE_U128)
		return true;

	else if (t->type == TOKEN_TYPE_CHAR)
		return true;
	else if (t->type == TOKEN_TYPE_STRING)
		return true;
	else if (t->type == TOKEN_TYPE_BOOL)
		return true;

	else if (t->type == TOKEN_TYPE_ANY)
		return true;

	return false;
}

void parseFunction(Token **tokens)
{
}

int parseDataType(Token **tokens)
{
	if (tokenIsPrimaryType(*tokens)) // if current token is a primitive data-type
	{
		Token *datatype = *tokens; // store data-type to a variable
		tokens++; // go to next token
		if ((*tokens)->type == TOKEN_VALUE_IDENTIFIER)
		{ // check if current token is a user identifier
			tokens++; // go to next token
			if ((*tokens)->type == TOKEN_BRACKET_OPEN || (*tokens)->type == TOKEN_SECTION_OPEN)
			{
				tokens--; // go back to user-identifier name (function name)
				tokens--; // go back to data-type
				parseFunction(tokens);
			}
		}
	}
}

int parserCheck(Parser *pars, ErrorsContainer *errors)
{
	printf("=============== Parser ===============\n");

	Token *t;
	while (*pars->lex->tokens != NULL)
	{
		t = *pars->lex->tokens;
		printf("-->%s\n", tokenName(t->type));
		pars->lex->tokens++;
	}
	return EXIT_SUCCESS;
}

void parserFree(Parser *pars)
{
}
