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

char* ast_statement_name(AstStatementType type)
{
	switch (type)
	{
		case AST_GLOBAL_STATEMENT_FN:
			return "FN";
		case AST_GLOBAL_STATEMENT_VAR:
			return "VAR";
		case AST_GLOBAL_STATEMENT_ENUM:
			return "ENUM";
		case AST_GLOBAL_STATEMENT_STRUCT:
			return "STRUCT";
		case AST_GLOBAL_STATEMENT_TYPE:
			return "TYPE";

		case AST_STATEMENT_RET:
			return "RET";
		case AST_STATEMENT_PRINT:
			return "PRINT";
		case AST_STATEMENT_PRINTNL:
			return "PRINTNL";
		case AST_STATEMENT_PRINTDB:
			return "PRINTDB";
		case AST_STATEMENT_PRINTDBNL:
			return "PRINTDBNL";

		case AST_STATEMENT_WHILE:
			return "WHILE";
		case AST_STATEMENT_FOR:
			return "FOR";
		case AST_STATEMENT_DO:
			return "DO";
		case AST_STATEMENT_MATCH:
			return "MATCH";

		case AST_STATEMENT_EXPRESSION:
			return "EXPRESSIONS";

		case AST_STATEMENT_IF:
			return "IF";

		case AST_STATEMENT_VARIABLE:
			return "VARIABLE";

		default:
			return "UNKNOWN";
	}
}

char* ast_value_name(AstValueType type)
{
	switch (type)
	{
		case AST_TYPE_I8:
			return "i8";
		case AST_TYPE_I16:
			return "i16";
		case AST_TYPE_I32:
			return "i32";
		case AST_TYPE_I64:
			return "i64";
		case AST_TYPE_I128:
			return "i128";

		case AST_TYPE_U8:
			return "u8";
		case AST_TYPE_U16:
			return "u16";
		case AST_TYPE_U32:
			return "u32";
		case AST_TYPE_U64:
			return "u64";
		case AST_TYPE_U128:
			return "u128";

		case AST_TYPE_F32:
			return "f32";
		case AST_TYPE_F64:
			return "f64";

		case AST_TYPE_STRING:
			return "string";
		case AST_TYPE_CHAR:
			return "char";
		case AST_TYPE_BOOL:
			return "bool";

		default:
			return "UNKNOWN";
	}
}

AstType* ast_make_type(int type, bool hasArray)
{
	AstType* ast = malloc(sizeof(AstType));
	ast->type = type;
	ast->hasArray = hasArray;
	return ast;
}

AstBlock* ast_make_block(AstStatements stmts)
{
	AstBlock* ast = malloc(sizeof(AstBlock));
	ast->statements = stmts;
	return ast;
}

AstExpression* ast_make_expression_3(TokenType op, int value, AstExpression* left, AstExpression* right, AstExpression* third)
{
	AstExpression* ast = malloc(sizeof(AstExpression));
	ast->operator= op;

	ast->vint = value;
	//	ast->vfloat = vf;
	ast->vstring = NULL;
	//	ast->vbool = vb;

	ast->left = left;
	ast->right = right;
	ast->third = third;

	return ast;
}
AstExpression* ast_make_expression_2(TokenType op, int value, AstExpression* left, AstExpression* right)
{
	AstExpression* ast = malloc(sizeof(AstExpression));
	ast->operator= op;

	ast->vint = value;
	ast->vstring = NULL;

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

AstFunction* ast_make_function(char* name, AstArguments args, AstBlock* block)
{
	AstFunction* ast = malloc(sizeof(AstFunction));
	ast->name = name;
	ast->arguments = args;
	ast->block = block;
	return ast;
}

AstRoot* ast_make_root(char* package, AstFunctions funcs)
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

void ast_free(AstRoot** root)
{
	//	free(root); // TODO
}
