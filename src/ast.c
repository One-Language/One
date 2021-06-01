/**
 The One Programming Language

 File: ast.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "ast.h"

AstBlock* astBlock(AstStatement** stmts)
{
	AstBlock* ast = malloc(sizeof(AstBlock));
}

AstFunction* astFunction(char* name, AstBlock* block)
{
}
