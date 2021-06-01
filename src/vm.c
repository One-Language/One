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
}

void vmFunction(AstFunction* func)
{
	printf("[FUNC] %s\n", func->name);
}

void vmLog(AstRoot* root)
{
	for(size_t i = 0; i <root->functions->count;i++) {
		vmFunction(root->functions->data[i]);
	}
}

void vmFree(AstRoot* root)
{
}
