/**
 The One Programming Language

 File: tree.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

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
	//	print_tree(f, BOLDBLUE TREE_PREFIX "Function: %s\n" RESET, fn->name);
	print_tree(f, BOLDGREEN TREE_PREFIX "Function: %s\n" RESET, fn->name);

	ident++;
	tree_show_arguments(f, fn->arguments);

	tree_show_block(f, fn->block);
	ident--;
}

void tree_show_statement_prints(FILE* f, AstStatement* stmt)
{
	if (stmt->type == AST_STATEMENT_PRINT)
	{
		tree_show_statement_print(f, stmt);
	}
	else if (stmt->type == AST_STATEMENT_PRINTNL)
	{
		tree_show_statement_printnl(f, stmt);
	}
	else if (stmt->type == AST_STATEMENT_PRINTDB)
	{
		tree_show_statement_printdb(f, stmt);
	}
	else if (stmt->type == AST_STATEMENT_PRINTDBNL)
	{
		tree_show_statement_printdbnl(f, stmt);
	}
	else
	{
		error_tree("Cannot show tree of a unknown '%s' statement at prints_tree!", ast_statement_name(stmt->type));
	}
}

void tree_show_statement_print(FILE* f, AstStatement* stmt)
{
	//	tree_show_ident();
	//	print_tree(f, BOLDGREEN TREE_PREFIX "Statement Print\n" RESET);
	tree_show_expressions(f, stmt->expressions);
}

void tree_show_statement_printnl(FILE* f, AstStatement* stmt)
{
	//	tree_show_ident();
	//	print_tree(f, BOLDGREEN TREE_PREFIX "Statement PrintNL\n" RESET);
	tree_show_expressions(f, stmt->expressions);
}

void tree_show_statement_printdb(FILE* f, AstStatement* stmt)
{
	//	tree_show_ident();
	//	print_tree(f, BOLDGREEN TREE_PREFIX "Statement PrintDb\n" RESET);
	tree_show_expressions(f, stmt->expressions);
}

void tree_show_statement_printdbnl(FILE* f, AstStatement* stmt)
{
	//	tree_show_ident();
	//	print_tree(f, BOLDGREEN TREE_PREFIX "Statement PrintDbNL\n" RESET);
	tree_show_expressions(f, stmt->expressions);
}

void tree_show_statement_while(FILE* f, AstStatement* stmt)
{
	//	tree_show_ident();
	//	print_tree(f, BOLDBLUE TREE_PREFIX "Statement While\n" RESET);
}

void tree_show_statement_do(FILE* f, AstStatement* stmt)
{
	//	tree_show_ident();
	//	print_tree(f, BOLDBLUE TREE_PREFIX "Statement Do\n" RESET);
}

void tree_show_statement_for(FILE* f, AstStatement* stmt)
{
	//	tree_show_ident();
	//	print_tree(f, BOLDBLUE TREE_PREFIX "Statement For\n" RESET);
}

void tree_show_statement_ret(FILE* f, AstStatement* stmt)
{
	//	tree_show_ident();
	//	print_tree(f, BOLDBLUE TREE_PREFIX "Statement Ret\n" RESET);
	tree_show_expressions(f, stmt->expressions);
}

void tree_show_statement_variable(FILE* f, AstStatement* stmt)
{
	//	tree_show_ident();
	//	print_tree(f, BOLDBLUE TREE_PREFIX "Statement Variable\n" RESET);
}

void tree_show_statement_expression(FILE* f, AstStatement* stmt)
{
	//	tree_show_ident();
	//	print_tree(f, BOLDBLUE TREE_PREFIX "Statement Expression\n" RESET);
}

void tree_show_expression(FILE* f, AstExpression* expr)
{
	if (expr->operator== TOKEN_OPERATOR_NONE)
	{
		tree_show_ident();
		print_tree(f, BOLDBLUE TREE_PREFIX "Expression Direct: %s\n" RESET, expr->vstring == NULL ? "" : expr->vstring);
		//		tree_show_ident();
		//		print_tree(f, BOLDBLUE TREE_PREFIX "Expression Direct: %d\n" RESET, expr->vint);
	}
	else
	{
		tree_show_ident();
		print_tree(f, BOLDBLUE TREE_PREFIX "Expression %s\n" RESET, token_name(expr->operator));

		ident++;
		if (expr->left != NULL)
		{
			tree_show_ident();
			print_tree(f, BOLDBLUE TREE_PREFIX "Expression Left\n" RESET);
			ident++;
			tree_show_expression(f, expr->left);
			ident--;
		}
		if (expr->right != NULL)
		{
			tree_show_ident();
			print_tree(f, BOLDBLUE TREE_PREFIX "Expression Right\n" RESET);
			ident++;
			tree_show_expression(f, expr->right);
			ident--;
		}
		ident--;
	}
}

void tree_show_expressions(FILE* f, AstExpressions exprs)
{
	AstExpression* expr;

	tree_show_ident();
	print_tree(f, BOLDBLUE TREE_PREFIX "Expressions (%d)\n" RESET, exprs.count);

	ident++;
	for (int i = 0; i < exprs.count; i++)
	{
		expr = exprs.data[i];
		tree_show_expression(f, expr);
	}
	ident--;
}

void tree_show_statement(FILE* f, AstStatement* stmt)
{
	tree_show_ident();
	print_tree(f, BOLDGREEN TREE_PREFIX "Statement: %s\n" RESET, ast_statement_name(stmt->type));

	ident++;
	if (stmt->type == AST_STATEMENT_PRINT || stmt->type == AST_STATEMENT_PRINTNL || stmt->type == AST_STATEMENT_PRINTDB || stmt->type == AST_STATEMENT_PRINTDBNL)
	{
		tree_show_statement_prints(f, stmt);
	}
	else if (stmt->type == AST_STATEMENT_WHILE)
	{
		tree_show_statement_while(f, stmt);
	}
	else if (stmt->type == AST_STATEMENT_DO)
	{
		tree_show_statement_do(f, stmt);
	}
	else if (stmt->type == AST_STATEMENT_FOR)
	{
		tree_show_statement_for(f, stmt);
	}
	else if (stmt->type == AST_STATEMENT_RET)
	{
		tree_show_statement_ret(f, stmt);
	}
	else if (stmt->type == AST_STATEMENT_VARIABLE)
	{
		tree_show_statement_variable(f, stmt);
	}
	else
	{
		error_tree("Cannot show tree of a unknown '%s' statement!", ast_statement_name(stmt->type));
	}

	ident--;
}

void tree_show_statements(FILE* f, AstStatements stmts)
{
	AstStatement* stmt;
	tree_show_ident();
	print_tree(f, BOLDBLUE TREE_PREFIX "Block (%d)\n" RESET, stmts.count);
	ident++;
	for (int i = 0; i < stmts.count; i++)
	{
		stmt = stmts.data[i];
		tree_show_statement(f, stmt);
	}
	ident--;
}

void tree_show_block(FILE* f, AstBlock* block)
{
	tree_show_statements(f, block->statements);
}

void tree_show_arguments(FILE* f, AstArguments args)
{
	tree_show_ident();
	print_tree(f, BOLDBLUE TREE_PREFIX "Arguments (%d)\n" RESET, args.count);

	ident++;
	for (int i = 0; i < args.count; i++)
	{
		tree_show_ident();
		print_tree(f, BOLDBLUE TREE_PREFIX "Argument [%d]\n" RESET, args.count);
	}
	ident--;
}
