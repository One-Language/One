/**
 The One Programming Language

 File: vm.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "token.h"
#include "vm.h"

void vmInit(AstRoot* root)
{
	root->functions = malloc(sizeof(Array));
	root->package = malloc(sizeof(char) * 1024);
	//	strcpy(root->package,"max");
	//	printf("-->%s\n", root->package);
}

void vmStatement(AstStatement* stmt)
{
	printf("[STMT] %s\n", astStatementName(stmt->type));
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
	printf("=============== VM ===============\n");

	printf("Package: %s\n", root->package);

	for (size_t i = 0; i < root->functions->count; i++)
	{
		vmFunction(root->functions->data[i]);
	}
}

void vmFree(AstRoot* root)
{
}
