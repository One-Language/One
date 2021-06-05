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
#include "ast.h"
#include "vm.h"
#include "tree.h"

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

AstStatements *parseArguments(Parser *pars, ErrorsContainer *errors)
{
	AstType *type;
	AstArgument *arg;
	Array *args = malloc(sizeof(Array));

	arrayInit(args);

	if ((*pars->lex->tokens)->type == TOKEN_BRACKET_OPEN)
	{
		parserNextToken(pars, errors); // go to next token
		while ((*pars->lex->tokens)->type != TOKEN_BRACKET_CLOSE)
		{ // loop iterate before see a `)` token.
			if (parseDatatype(pars, errors) == true)
			{
				char *name = (*pars->lex->tokens)->vstring; // get value of current IDENTIFIER token.
				parserExceptToken(pars, TOKEN_VALUE_IDENTIFIER, errors);
				parserNextToken(pars, errors); // go to next token

				bool hasArray = false;
				type = astType(AST_TYPE_I8, hasArray);

				arg = astArgument(name, type);
				arrayPush(args, arg);
			}
			else
			{
				// TODO: ErrorAppend(...)
				return NULL;
			}
		}
		parserExceptTokenGo(pars, TOKEN_BRACKET_CLOSE, errors);
	}
	return args; // it's optional, so we return a empty array list!
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

AstExpression *parseExpressionPrimitive(Parser *pars, ErrorsContainer *errors)
{
	AstExpression *expr;
	printf("---------- parseExpressionPrimitive\n");
	switch ((*pars->lex->tokens)->type)
	{
		case TOKEN_VALUE_IDENTIFIER:
		case TOKEN_VALUE_STRING:
		case TOKEN_VALUE_NUMBER:
		case TOKEN_VALUE_BOOL:
			parserNextToken(pars, errors);
			Token* t = (*pars->lex->tokens);
			expr = astExpression(AST_OPERATOR_DIRECT, t->vint, 0, "", false, NULL, NULL);
			return expr;
			break;
		default:
			// TODO: ErrorAppend(...)
			printf("Error: bad value as expression!\n");
			parserNextToken(pars, errors);
			exit(1);
			break;
	}

	//	if (parserHasToken(pars, TOKEN_VALUE_IDENTIFIER, errors) == true)
	//		parserNextToken(pars, errors);
	//	else if (parserHasToken(pars, TOKEN_VALUE_STRING, errors) == true)
	//		parserNextToken(pars, errors);
	//	else if (parserHasToken(pars, TOKEN_VALUE_NUMBER, errors) == true)
	//		parserNextToken(pars, errors);
	//	else if (parserHasToken(pars, TOKEN_VALUE_BOOL, errors) == true)
	//		parserNextToken(pars, errors);
	//	else
	//	{
	//		// TODO: ErrorAppend(...)
	//		printf("Error: bad value as expression!\n");
	//		parserNextToken(pars, errors);
	//		exit(1);
	//	}
}

AstExpression *parseTerm(Parser *pars, ErrorsContainer *errors)
{
	return parseExpressionPrimitive(pars, errors);
}

AstExpression *parseExpression(Parser *pars, ErrorsContainer *errors)
{
	printf("---------- parseExpression\n");
	printf("[TEST]==>%s\n", tokenName((*pars->lex->tokens)->type));
	AstExpression *expr = parseTerm(pars, errors);

	printf("[TEST]==>%s\n", tokenName((*pars->lex->tokens)->type));
	if (parserHasToken(pars, TOKEN_OPERATOR_PLUS, errors) == true)
	{
		parserNextToken(pars, errors);
		expr = astExpression(AST_OPERATOR_PLUS, 10, 0, "", false, expr, parseExpression(pars, errors));
	}
	else if (parserHasToken(pars, TOKEN_OPERATOR_MINUS, errors) == true)
	{
		parserNextToken(pars, errors);
		expr = astExpression(AST_OPERATOR_MINUS, 10, 0, "", false, expr, parseExpression(pars, errors));
	}
	return expr;
}

AstExpressions *parseExpressions(Parser *pars, ErrorsContainer *errors)
{
	AstExpression *expr;
	Array *exprs = malloc(sizeof(Array));
	arrayInit(exprs);

	printf("---------- parseExpressions\n");

	expr = parseExpression(pars, errors);
	arrayPush(exprs, expr);

	while (parserHasToken(pars, TOKEN_OPERATOR_VIRGOOL, errors) == true)
	{
		parserExceptTokenGo(pars, TOKEN_OPERATOR_VIRGOOL, errors); // skip virgool and go to next token!
		expr = parseExpression(pars, errors);
		arrayPush(exprs, expr);
	}
	return exprs;
}

AstStatement *parseStatementPrint(Parser *pars, ErrorsContainer *errors)
{
	AstStatement *stmt = astStatement(AST_STATEMENT_PRINT);
	printf("---------- parseStatementPrint\n");

	parserExceptTokenGo(pars, TOKEN_PRINT, errors);
	stmt->expressions = parseExpressions(pars, errors);
	return stmt;
}

AstStatement *parseStatementPrintNl(Parser *pars, ErrorsContainer *errors)
{
	AstStatement *stmt = astStatement(AST_STATEMENT_PRINTNL);
	printf("---------- parseStatementPrintNl\n");

	parserExceptTokenGo(pars, TOKEN_PRINTNL, errors);
	stmt->expressions = parseExpressions(pars, errors);
	return stmt;
}

AstStatement *parseStatementPrintErr(Parser *pars, ErrorsContainer *errors)
{
	AstStatement *stmt = astStatement(AST_STATEMENT_PRINTDB);
	printf("---------- parseStatementPrintErr\n");

	parserExceptTokenGo(pars, TOKEN_PRINTDB, errors);
	stmt->expressions = parseExpressions(pars, errors);
	return stmt;
}

AstStatement *parseStatementPrintErrNl(Parser *pars, ErrorsContainer *errors)
{
	AstStatement *stmt = astStatement(AST_STATEMENT_PRINTDBNL);
	printf("---------- parseStatementPrintErrNl\n");

	parserExceptTokenGo(pars, TOKEN_PRINTNLDB, errors);
	stmt->expressions = parseExpressions(pars, errors);
	return stmt;
}

AstStatement *parseStatementReturn(Parser *pars, ErrorsContainer *errors)
{
	AstStatement *stmt = astStatement(AST_STATEMENT_RETURN);
	printf("---------- parseStatementReturn\n");

	parserExceptTokenGo(pars, TOKEN_RETURN, errors);
	stmt->expressions = parseExpressions(pars, errors);
	return stmt;
}

AstStatement *parseStatement(Parser *pars, ErrorsContainer *errors)
{
	if ((*pars->lex->tokens)->type == TOKEN_PRINT)
	{
		return parseStatementPrint(pars, errors);
	}
	else if ((*pars->lex->tokens)->type == TOKEN_PRINTNL)
	{
		return parseStatementPrintNl(pars, errors);
	}
	else if ((*pars->lex->tokens)->type == TOKEN_PRINTDB)
	{
		return parseStatementPrintErr(pars, errors);
	}
	else if ((*pars->lex->tokens)->type == TOKEN_PRINTNLDB)
	{
		return parseStatementPrintErrNl(pars, errors);
	}
	else if ((*pars->lex->tokens)->type == TOKEN_RETURN)
	{
		return parseStatementReturn(pars, errors);
	}
	else
	{
		// TODO: ErrorAppend(...)
		printf("Error: bad stmt!\n");
		printf("==>%s\n", tokenName((*pars->lex->tokens)->type));
		//		exit(1);
		return NULL;
		parserNextToken(pars, errors);
	}
}

AstBlock *parseBlock(Parser *pars, ErrorsContainer *errors)
{
	AstBlock *block;
	Array *stmts = malloc(sizeof(Array));
	arrayInit(stmts);

	parserExceptTokenGo(pars, TOKEN_SECTION_OPEN, errors);
	printf("==== start stmt loop\n");

	AstStatement *stmt;
	while ((*pars->lex->tokens)->type != TOKEN_SECTION_CLOSE)
	{
		stmt = parseStatement(pars, errors);
		printf("==== end current stmt\n");
		arrayPush(stmts, stmt);
	}
	printf("==== end stmt loop\n");
	parserExceptTokenGo(pars, TOKEN_SECTION_CLOSE, errors);

	block = astBlock(stmts);
	return block;
}

AstFunction *parseFunction(Parser *pars, ErrorsContainer *errors)
{
	printf("---------- parseFunction\n");

	if (parseDatatype(pars, errors) == true)
	{
		char *name = (*pars->lex->tokens)->vstring; // get value of current IDENTIFIER token
		parserExceptTokenGo(pars, TOKEN_VALUE_IDENTIFIER, errors); // check if current token is a user identifier

		//		printf("==>%s\n", tokenName((*pars->lex->tokens)->type));
		AstArguments *args = parseArguments(pars, errors);
		printf("==== end args\n");
		AstBlock *block = parseBlock(pars, errors);
		printf("==== end block\n");

		AstFunction *func = astFunction(name, args, block);
		return func;
	}
	else
	{
		// TODO: ErrorAppend(...)
		return NULL;
	}
}

void check(Parser *pars)
{
	//	printf("==>%s\n", tokenName((*pars->lex->tokens)->type));
	pars->lex->tokens++;
	//	printf("==>%s\n", tokenName((*pars->lex->tokens)->type));
}

void parsePackage(Parser *pars, char **package, ErrorsContainer *errors)
{
	printf("---------- parsePackage\n");

	parserExceptTokenGo(pars, TOKEN_PACKAGE, errors);

	if (parserHasToken(pars, TOKEN_VALUE_IDENTIFIER, errors) == true)
	{
		*package = (*pars->lex->tokens)->vstring;
		printf("==>%s\n", *package);
		parserNextToken(pars, errors);
	}
	else if (parserHasToken(pars, TOKEN_VALUE_STRING, errors) == true)
	{
		*package = (*pars->lex->tokens)->vstring;
		printf("==>%s\n", *package);
		parserNextToken(pars, errors);
	}
	else
	{
		printf("Error: bad value for package name!\n");
		// TODO: AppendError(...)
		exit(1);
	}
}

int parserCheck(Parser *pars, ErrorsContainer *errors)
{
	bool hasPackageName = false;
	AstFunction *func;
	AstRoot *root = malloc(sizeof(AstRoot));
	vmInit(root);
	arrayInit(root->functions);

	printf("=============== Parser ===============\n");

	Token *t;
	while (*pars->lex->tokens != NULL)
	{
		t = *pars->lex->tokens;
		printf("[TOKEN] %s\n", tokenName(t->type));
		if (t->type == TOKEN_EOF)
			break;
		else if (t->type == TOKEN_UNKNOWM)
		{
			printf("Break...............\n");
			break;
		}

		if (parserHasToken(pars, TOKEN_PACKAGE, errors) == true)
		{
			if (hasPackageName == true)
			{
				// TODO: AppendError(...), It's not allowerd to define package name twice at a source file!
				printf("Error: cannot twice define package name in a single file!");
				exit(1);
				// parserNextToken(pars, errors);
			}
			else
			{
				hasPackageName = true;
				parsePackage(pars, &root->package, errors);
				printf("==>%s\n", root->package);
			}
		}
		else if (parseDatatype(pars, errors) == true) // if current token is a primitive data-type
		{
			if ((*pars->lex->tokens)->type == TOKEN_VALUE_IDENTIFIER)
			{ // check if current token is a user identifier
				parserNextToken(pars, errors); // go to next token
				if ((*pars->lex->tokens)->type == TOKEN_BRACKET_OPEN || (*pars->lex->tokens)->type == TOKEN_SECTION_OPEN)
				{
					parserPrevToken(pars, errors); // go back to user-identifier name (function name)
					parserPrevToken(pars, errors); // go back to data-type
					func = parseFunction(pars, errors);
					printf("==== end func\n");
					arrayPush(root->functions, func);
				}
			}
		}
		else
		{
			printf("Error: bad token in the parser stage!\n");
			// TODO: ErrorAPpend(...)
			exit(1);
		}
	}

	treeLog(root);

	vmLog(root);
	vmFree(root);
	return EXIT_SUCCESS;
}

void parserFree(Parser *pars)
{
}
