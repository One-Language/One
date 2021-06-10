//
// Created by max on 6/10/21.
//

#include <stdio.h>
#include <stdlib.h>

#include "array.h"
#include "lexer.h"
#include "token.h"

#include "ast.h"
#include "parser.h"
#include "error.h"

#include "tree.h"

#define print_tree fprintf

int ident = 0;

//#define TREE_PREFIX "|── "

#define TREE_PREFIX "└──"

void tree_show_ident()
{
	for (int i = 0; i < ident; i++)
	{
		printf("    ");
	}
}
void tree_show(FILE* f, AstRoot* root) // Question: why at here I have to put **  and cannot use *? If i wrote * value will be wrong!
{
	debug_tree("tree_show");

	AstFunctions fns = root->functions;
	print_tree(f, BOLDBLUE "| AST Tree of One Programming Language\n" RESET);
	tree_show_functions(f, fns);
}

void tree_show_functions(FILE* f, AstFunctions fns)
{
	debug_tree("tree_show_functions");

	print_tree(f, BOLDBLUE TREE_PREFIX "Functions (%d)\n", fns.count);
	ident++;
	for (int i = 0; i < fns.count; i++)
	{
		AstFunction* fn = (AstFunction*)fns.data[i];
		tree_show_function(f, fn);
	}
	ident--;
}

void tree_show_function(FILE* f, AstFunction* fn)
{
	tree_show_ident();
	print_tree(f, BOLDBLUE TREE_PREFIX "Function %s\n" RESET, fn->name);
	ident++;

	tree_show_arguments(f, fn->arguments);

	ident--;
}

void tree_show_arguments(FILE* f, AstArguments args)
{
	tree_show_ident();
	print_tree(f, BOLDBLUE TREE_PREFIX "Arguments (%d)\n" RESET, args.count);
}
