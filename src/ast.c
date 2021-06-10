/**
 The One Programming Language

 File: ast.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lexer.h"
#include "token.h"
#include "array.h"

#include "ast.h"

char* ast_name(AstStatementType type)
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

AstType* ast_make_type(int type, bool hasArray)
{
	AstType* ast = malloc(sizeof(AstType));
	ast->type = type;
	ast->hasArray = hasArray;
	return ast;
}

AstBlock* ast_make_block(AstStatements* stmts)
{
	AstBlock* ast = malloc(sizeof(AstBlock));
	ast->statements = stmts;
	return ast;
}

AstExpression* ast_make_expression_3(TokenType op, int vi, float vf, char* vs, bool vb, AstExpression* left, AstExpression* right, AstExpression* third)
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
AstExpression* ast_make_expression_2(TokenType op, int vi, float vf, char* vs, bool vb, AstExpression* left, AstExpression* right)
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

AstArgument* ast_make_argument(char* name, AstType* type)
{
	AstArgument* ast = malloc(sizeof(AstArgument));
	ast->name = name;
	ast->type = type;
	return ast;
}

AstFunction* ast_make_function(char* name, AstArguments* args, AstBlock* block)
{
	AstFunction* ast = malloc(sizeof(AstFunction));
	ast->name = name;
	ast->arguments = args;
	ast->block = block;
	return ast;
}

AstRoot* ast_make_root(char* package, AstFunctions* funcs)
{
	AstRoot* ast = malloc(sizeof(AstRoot));
	ast->package = package;
	ast->functions = funcs;
	return ast;
}

AstStatement* ast_make_statement(AstStatementType type)
{
	AstStatement* ast = malloc(sizeof(AstStatement));
	ast->type = type;
	return ast;
}
