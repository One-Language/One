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

void tree_show(FILE* f, AstRoot* root)
{
	debug_tree("tree_show");

	print_tree(f, BOLDBLUE "- AST Tree of One Programming Language\n");
	tree_show_functions(f, root->functions);
}

void tree_show_functions(FILE* f, AstFunctions* fns)
{
	print_tree(f, BOLDBLUE "| Functions (%zu)\n", fns->count);
	for (size_t i = 0; i < fns->count; i++)
	{
		AstFunction* fn = (AstFunction*)fns->data[i];
		print_tree(f, BOLDBLUE "| Function %s\n", fn->name);
	}
}
