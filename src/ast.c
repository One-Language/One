/**
 The One Programming Language

 File: ast.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "token.h"
#include "ast.h"

char* astStatementName(AstStatementType type)
{
	switch (type)
	{
		case AST_STATEMENT_RETURN:
			return "RET";
		case AST_STATEMENT_PRINT:
			return "PRINT";
		case AST_STATEMENT_PRINTNL:
			return "PRINTNL";
		case AST_STATEMENT_PRINTDB:
			return "PRINTDB";
		case AST_STATEMENT_PRINTDBNL:
			return "PRINTDBNL";
		default:
			return "UNKNOWM";
	}
}

char* astOperatorName(TokenType type)
{
	switch (type)
	{
		case TOKEN_OPERATOR_PLUS:
			return "+";
		case TOKEN_OPERATOR_MINUS:
			return "-";
		case TOKEN_OPERATOR_MUL:
			return "*";
		case TOKEN_OPERATOR_DIV:
			return "/";
		case TOKEN_OPERATOR_POW:
			return "**";
		case TOKEN_OPERATOR_DIRECT:
			return "VALUE";
		case TOKEN_OPERATOR_IF:
			return "?:";
		case TOKEN_OPERATOR_IFIF:
			return "??";

		case TOKEN_OPERATOR_G:
			return ">";
		case TOKEN_OPERATOR_GE:
			return ">=";
		case TOKEN_OPERATOR_L:
			return "<";
		case TOKEN_OPERATOR_LE:
			return "<=";

		case TOKEN_OPERATOR_EQUAL:
			return "=";
		case TOKEN_OPERATOR_EQUALEQUAL:
			return "==";
		case TOKEN_OPERATOR_EQUALEQUALEQUAL:
			return "===";

		case TOKEN_OPERATOR_NOT:
			return "!";
		case TOKEN_OPERATOR_NOTEQUAL:
			return "!=";
		case TOKEN_OPERATOR_NOTEQUALEQUAL:
			return "!==";


		case TOKEN_OPERATOR_AND:
			return "&&";
		case TOKEN_OPERATOR_BIT_AND:
			return "&";
		case TOKEN_OPERATOR_OR:
			return "||";
		case TOKEN_OPERATOR_BIT_OR:
			return "|";
		case TOKEN_OPERATOR_BIT_XOR:
			return "^";

		case TOKEN_OPERATOR_SHIFT_LEFT:
			return ">>";
		case TOKEN_OPERATOR_SHIFT_RIGHT:
			return "<<";

		default:
			return "UNKNOWM";
	}
}

AstType* astType(int type, bool hasArray)
{
	AstType* ast = malloc(sizeof(AstType));
	ast->type = type;
	ast->hasArray = hasArray;
	return ast;
}

AstBlock* astBlock(AstStatements* stmts)
{
	AstBlock* ast = malloc(sizeof(AstBlock));
	ast->statements = stmts;
	return ast;
}

AstExpression* astExpression3(TokenType op, int vi, float vf, char* vs, bool vb, AstExpression* left, AstExpression* right, AstExpression* third)
{
	AstExpression* ast = malloc(sizeof(AstExpression));
	ast->operator= op;

	ast->vint = vi;
	ast->vfloat = vf;
	ast->vstring = vs;
	ast->vbool = vb;

	ast->left = left;
	ast->right = right;
	ast->third = third;

	return ast;
}
AstExpression* astExpression(TokenType op, int vi, float vf, char* vs, bool vb, AstExpression* left, AstExpression* right)
{
	AstExpression* ast = malloc(sizeof(AstExpression));
	ast->operator= op;

	ast->vint = vi;
	ast->vfloat = vf;
	ast->vstring = vs;
	ast->vbool = vb;

	ast->left = left;
	ast->right = right;

	return ast;
}

AstArgument* astArgument(char* name, AstType* type)
{
	AstArgument* ast = malloc(sizeof(AstArgument));
	ast->name = name;
	ast->type = type;
	return ast;
}

AstFunction* astFunction(char* name, AstArguments* args, AstBlock* block)
{
	AstFunction* ast = malloc(sizeof(AstFunction));
	ast->name = name;
	ast->arguments = args;
	ast->block = block;
	return ast;
}

AstRoot* astRoot(char* package, AstFunctions* funcs)
{
	/*
	if(package == NULL || strcmp(package, "") == 0) {
		package = "main"; // TODO: I not sure it's memory safe or no!
	}
	 */

	AstRoot* ast = malloc(sizeof(AstRoot));
	ast->package = package;
	ast->functions = funcs;
	return ast;
}

AstStatement* astStatement(AstStatementType type)
{
	AstStatement* ast = malloc(sizeof(AstStatement));
	ast->type = type;
	return ast;
}
