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

bool tokenIsUserType(Token *t)
{
	if (t->type == TOKEN_VALUE_IDENTIFIER)
	{
		if (strcmp(t->vstring, "point") == 0)
			return true;
		// TODO: Need to check from a vector-like!
		return false;
	}
	return false;
}

int parseDatatype(Token **tokens)
{
	if (tokenIsPrimaryType(*tokens) == true || tokenIsUserType(*tokens) == true)
	{ // if current token is a primitive data-type
		// TOOD: check data-type array. e;g `i32 []`
		return 1; // yes it's a data-type token series!
	}
	return -1; // is not!
}

int parseArguments(Token **tokens)
{
	if ((*tokens)->type == TOKEN_BRACKET_OPEN)
	{
		tokens++; // go to next token
		while ((*tokens)->type != TOKEN_BRACKET_CLOSE)
		{ // loop iterate before see a `)` token.
			tokens++; // go to next token
		}
		return 1;
	}
	else
	{
		return 0; // it's optional
	}
}

int except(Token **tokens, TokenType want, ErrorsContainer* errors)
{
	Token *t = *tokens;
	if (t->type != TOKEN_SECTION_OPEN)
	{
		// TODO: ErrorAppend(...)
		printf("Error: we except %s, but we see %s\n", tokenName(want), tokenName(t->type));
		return 0; // not valid
	}
	return 1; // valid
}

int exceptGo(Token **tokens, TokenType want, ErrorsContainer* errors)
{
	int res = except(tokens, want, errors); // call except function
	if (res == 1)
		tokens++;
	// Why we not have and need a `else`, because we already handled errors at parent function.
	return res;
}

void parseBlock(Token **tokens)
{
	if ((*tokens)->type == TOKEN_SECTION_OPEN)
	{
	}
}

void parseFunction(Token **tokens)
{
	if (parseDatatype(tokens) == 1)
	{
		tokens++; // go to next token
		if ((*tokens)->type == TOKEN_VALUE_IDENTIFIER)
		{ // check if current token is a user identifier
			tokens++; // go to next token
			parseArguments(tokens);
			parseBlock(tokens);
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

		if (tokenIsPrimaryType(*pars->lex->tokens) == true || tokenIsUserType(*pars->lex->tokens) == true) // if current token is a primitive data-type
		{
			Token *datatype = *pars->lex->tokens; // store data-type to a variable
			pars->lex->tokens++; // go to next token
			if ((*pars->lex->tokens)->type == TOKEN_VALUE_IDENTIFIER)
			{ // check if current token is a user identifier
				pars->lex->tokens++; // go to next token
				if ((*pars->lex->tokens)->type == TOKEN_BRACKET_OPEN || (*pars->lex->tokens)->type == TOKEN_SECTION_OPEN)
				{
					pars->lex->tokens--; // go back to user-identifier name (function name)
					pars->lex->tokens--; // go back to data-type
					parseFunction(pars->lex->tokens);
				}
			}
		}

		//	pars->lex->tokens++;
	}
	return EXIT_SUCCESS;
}

void parserFree(Parser *pars)
{
}
