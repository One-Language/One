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

#include "array.h"

typedef Array AstArguments;
typedef Array AstStatements;

typedef struct _ast_statement
{
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

#endif //_AST_H_
