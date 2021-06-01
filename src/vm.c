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

void vmFunction(AstFunction* func)
{
	printf("[FUNC] %s\n", func->name);
}

void vmLog(AstRoot* root)
{
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
