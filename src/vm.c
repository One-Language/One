/**
 The One Programming Language

 File: vm.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "vm.h"

void vmInit(AstRoot* root)
{
	root->functions = malloc(sizeof(Array));
	root->package = malloc(sizeof(char) * 1024);
	//	strcpy(root->package,"max");
	//	printf("-->%s\n", root->package);
}

char* vmStatementName(AstStatementType type)
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

void vmStatement(AstStatement* stmt)
{
	printf("[STMT] %s\n", vmStatementName(stmt->type));
}
void vmStatements(AstStatements* stmts)
{
	for (size_t i = 0; i < stmts->count; i++)
	{
		vmStatement(stmts->data[i]);
	}
}

void vmBlock(AstBlock* block)
{
	vmStatements(block->statements);
}

void vmFunction(AstFunction* func)
{
	printf("[FUNC] %s\n", func->name);
	vmBlock(func->block);
}

void vmLog(AstRoot* root)
{
	if (root->package == NULL || strlen(root->package) == 0 || strcmp(root->package, "") == 0)
	{
		root->package = "main";
	}
	printf("=============== AST ===============\n");

	printf("Package: %s\n", root->package);

	for (size_t i = 0; i < root->functions->count; i++)
	{
		vmFunction(root->functions->data[i]);
	}
}

void vmFree(AstRoot* root)
{
}
