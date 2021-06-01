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

void parserNextToken(Parser *pars, ErrorsContainer *errors)
{
	pars->lex->tokens++; // go back to the prev token
}

void parserPrevToken(Parser *pars, ErrorsContainer *errors)
{
	pars->lex->tokens--; // go back to the prev token
}

bool tokenIsPrimaryType(Parser *pars, ErrorsContainer *errors)
{
	Token *t = *pars->lex->tokens;

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

bool tokenIsUserType(Parser *pars, ErrorsContainer *errors)
{
	Token *t = *pars->lex->tokens;

	if (t->type == TOKEN_VALUE_IDENTIFIER)
	{
		if (strcmp(t->vstring, "point") == 0)
			return true;

		// TODO: Need to check from a vector-like!
		return false;
	}
	return false;
}

bool parseDatatype(Parser *pars, ErrorsContainer *errors)
{
	if (tokenIsPrimaryType(pars, errors) == true || tokenIsUserType(pars, errors) == true)
	{ // if current token is a primitive data-type
		// TODO: check data-type array. e;g `i32 []`

		parserNextToken(pars, errors); // go to next token

		printf("---------- parseDatatype\n");
		return true; // yes it's a data-type token series!
	}
	return false; // is not!
}

bool parseArguments(Parser *pars, ErrorsContainer *errors)
{
	if ((*pars->lex->tokens)->type == TOKEN_BRACKET_OPEN)
	{
		parserNextToken(pars, errors); // go to next token
		while ((*pars->lex->tokens)->type != TOKEN_BRACKET_CLOSE)
		{ // loop iterate before see a `)` token.
			if (parseDatatype(pars, errors) == true)
			{
				parserExceptToken(pars, TOKEN_VALUE_IDENTIFIER, errors);
				parserNextToken(pars, errors); // go to next token
				return true;
			}
			else
			{
				// TODO: ErrorAppend(...)
				return false;
			}
		}
	}
	return false; // it's optional
}

bool parserHasToken(Parser *pars, TokenType want, ErrorsContainer *errors)
{
	Token *t = *pars->lex->tokens;
	if (t->type == want)
		return true;
	return false;
}

bool parserExceptToken(Parser *pars, TokenType want, ErrorsContainer *errors)
{
	Token *t = *pars->lex->tokens;
	if (t->type != want)
	{
		// TODO: ErrorAppend(...)
		printf("Error: we except %s, but we see %s\n", tokenName(want), tokenName(t->type));
		return false; // not valid
	}
	return true; // valid
}

bool parserExceptTokenGo(Parser *pars, TokenType want, ErrorsContainer *errors)
{
	int res = parserExceptToken(pars, want, errors); // call except function
	if (res == 1)
		pars->lex->tokens++;
	// Why we not have and need a `else`, because we already handled errors at parent function.
	return res;
}

void parseExpression(Parser *pars, ErrorsContainer *errors)
{
	printf("---------- parseExpression\n");
	//	printf("==>%s\n", tokenName((*pars->lex->tokens)->type));

	if (parserHasToken(pars, TOKEN_VALUE_IDENTIFIER, errors) == true)
		parserNextToken(pars, errors);
	else if (parserHasToken(pars, TOKEN_VALUE_STRING, errors) == true)
		parserNextToken(pars, errors);
	else if (parserHasToken(pars, TOKEN_VALUE_NUMBER, errors) == true)
		parserNextToken(pars, errors);
	else if (parserHasToken(pars, TOKEN_VALUE_BOOL, errors) == true)
		parserNextToken(pars, errors);
	else
	{
		// TODO: ErrorAppend(...)
		printf("Error: bad value as expression!\n");
		parserNextToken(pars, errors);
		exit(1);
	}
}

void parseExpressions(Parser *pars, ErrorsContainer *errors)
{
	printf("---------- parseExpressions\n");

	parseExpression(pars, errors);
	while (parserHasToken(pars, TOKEN_OPERATOR_VIRGOOL, errors) == true)
	{
		parserExceptTokenGo(pars, TOKEN_OPERATOR_VIRGOOL, errors);
		parseExpression(pars, errors);
	}
}

void parseStatementPrint(Parser *pars, ErrorsContainer *errors)
{
	printf("---------- parseStatementPrint\n");

	parserExceptTokenGo(pars, TOKEN_PRINT, errors);
	parseExpressions(pars, errors);
}

void parseStatementPrintNl(Parser *pars, ErrorsContainer *errors)
{
	printf("---------- parseStatementPrintNl\n");

	parserExceptTokenGo(pars, TOKEN_PRINTNL, errors);
	parseExpressions(pars, errors);
}

void parseStatementPrintErr(Parser *pars, ErrorsContainer *errors)
{
	printf("---------- parseStatementPrintErr\n");

	parserExceptTokenGo(pars, TOKEN_PRINTDB, errors);
	parseExpressions(pars, errors);
}

void parseStatementPrintErrNl(Parser *pars, ErrorsContainer *errors)
{
	printf("---------- parseStatementPrintErrNl\n");

	parserExceptTokenGo(pars, TOKEN_PRINTNLDB, errors);
	parseExpressions(pars, errors);
}

void parseStatement(Parser *pars, ErrorsContainer *errors)
{
	if ((*pars->lex->tokens)->type == TOKEN_PRINT)
	{
		parseStatementPrint(pars, errors);
	}
	else if ((*pars->lex->tokens)->type == TOKEN_PRINTNL)
	{
		parseStatementPrintNl(pars, errors);
	}
	else if ((*pars->lex->tokens)->type == TOKEN_PRINTDB)
	{
		parseStatementPrintErr(pars, errors);
	}
	else if ((*pars->lex->tokens)->type == TOKEN_PRINTNLDB)
	{
		parseStatementPrintErrNl(pars, errors);
	}
	else
	{
		// TODO: ErrorAppend(...)
		printf("Error: bad stmt!\n");
		//		exit(1);
		parserNextToken(pars, errors);
	}
}

void parseBlock(Parser *pars, ErrorsContainer *errors)
{
	parserExceptTokenGo(pars, TOKEN_SECTION_OPEN, errors);
	printf("==== start stmt loop\n");
	while ((*pars->lex->tokens)->type != TOKEN_SECTION_CLOSE)
	{
		parseStatement(pars, errors);
		printf("==== end current stmt\n");
	}
	printf("==== end stmt loop\n");
	parserExceptTokenGo(pars, TOKEN_SECTION_CLOSE, errors);
}

void parseFunction(Parser *pars, ErrorsContainer *errors)
{
	printf("---------- parseFunction\n");

	if (parseDatatype(pars, errors) == true)
	{
		parserExceptTokenGo(pars, TOKEN_VALUE_IDENTIFIER, errors); // check if current token is a user identifier

		//		printf("==>%s\n", tokenName((*pars->lex->tokens)->type));
		parseArguments(pars, errors);
		printf("==== end args\n");
		parseBlock(pars, errors);
		printf("==== end block\n");
	}
	else
	{
		// TODO: ErrorAppend(...)
	}
}

void check(Parser *pars)
{
	//	printf("==>%s\n", tokenName((*pars->lex->tokens)->type));
	pars->lex->tokens++;
	//	printf("==>%s\n", tokenName((*pars->lex->tokens)->type));
}

int parserCheck(Parser *pars, ErrorsContainer *errors)
{
	printf("=============== Parser ===============\n");

	Token *t;
	while (*pars->lex->tokens != NULL)
	{
		t = *pars->lex->tokens;
		printf("[TOKEN] %s\n", tokenName(t->type));
		if (t->type == TOKEN_EOF || t->type == TOKEN_UNKNOWM) break;

		if (parseDatatype(pars, errors) == true) // if current token is a primitive data-type
		{
			if ((*pars->lex->tokens)->type == TOKEN_VALUE_IDENTIFIER)
			{ // check if current token is a user identifier
				parserNextToken(pars, errors); // go to next token
				if ((*pars->lex->tokens)->type == TOKEN_BRACKET_OPEN || (*pars->lex->tokens)->type == TOKEN_SECTION_OPEN)
				{
					parserPrevToken(pars, errors); // go back to user-identifier name (function name)
					parserPrevToken(pars, errors); // go back to data-type
					parseFunction(pars, errors);
					printf("==== end func\n");
				}
			}
		}
		//		break;

		//	pars->lex->tokens++;
	}
	return EXIT_SUCCESS;
}

void parserFree(Parser *pars)
{
}
