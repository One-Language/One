/**
 The One Programming Language

 File: ast.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _AST_H_
#define _AST_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "array.h"

typedef Array AstArguments;
typedef Array AstStatements;
typedef Array AstFunctions;
typedef Array AstExpressions;

typedef struct _ast_expression AstExpression;

typedef enum
{
	AST_TYPE_I8,
	AST_TYPE_I16,
	AST_TYPE_I32,
	AST_TYPE_I64,

	AST_TYPE_U8,
	AST_TYPE_U16,
	AST_TYPE_U32,
	AST_TYPE_U64,
} AstValueType;

typedef enum
{
	AST_STATEMENT_PRINT,
	AST_STATEMENT_PRINTNL,
	AST_STATEMENT_PRINTDB,
	AST_STATEMENT_PRINTDBNL,

	AST_STATEMENT_RETURN,
} AstStatementType;

typedef enum
{
	AST_OPERATOR_DIRECT, // without an operator!

	AST_OPERATOR_PLUS,
	AST_OPERATOR_MINUS,
	AST_OPERATOR_MUL,
	AST_OPERATOR_DIV,
	AST_OPERATOR_POW,
	// TODO: adding more operators!
} AstOperatorType;

typedef struct _ast_statement
{
	AstStatementType type;
	AstExpressions* expressions;
	AstExpression* expression;
} AstStatement;

typedef struct _ast_block
{
	AstStatements* statements;
} AstBlock;

typedef struct _ast_type
{
	int type;
	bool hasArray;
} AstType;

typedef struct _ast_expression
{
	AstOperatorType operator;

	int vint;
	float vfloat;
	char* vstring;
	bool vbool;

	AstExpression* left;
	AstExpression* right;
} AstExpression;

typedef struct _ast_argument
{
	char* name;
	AstType* type;
} AstArgument;

typedef struct _ast_function
{
	char* name;
	AstArguments* arguments;
	AstBlock* block;
} AstFunction;

typedef struct _ast_root
{
	char* package;
	AstFunctions* functions;
} AstRoot;

AstType* astType(int, bool);

AstBlock* astBlock(AstStatements*);

AstArgument* astArgument(char*, AstType*);

AstFunction* astFunction(char*, AstArguments*, AstBlock*);

AstRoot* astRoot(char*, AstFunctions*);

AstStatement* astStatement(AstStatementType);

char* astOperatorName(AstOperatorType);

char* astStatementName(AstStatementType);

AstExpression* astExpression(AstOperatorType, int, float, char*, bool, AstExpression*, AstExpression*);

#endif //_AST_H_
