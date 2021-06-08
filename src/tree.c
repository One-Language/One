/**
 The One Programming Language

 File: tree.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "token.h"
#include "tree.h"
#include "vm.h"

size_t ident = 0;

void print_tabs(size_t n)
{
	for (size_t i = 0; i < n; i++)
	{
		printf("   ");
	}
}

void treeExpression(AstExpression* expr)
{
	print_tabs(ident);
	printf("[EXPR] %s ", astOperatorName(expr->operator));
	if (expr->operator== TOKEN_OPERATOR_DIRECT)
	{
		//		printf("%d", expr->vint);
		printf("%s", expr->vstring);
	}
	else
	{
		printf("\n");
		ident++;
		print_tabs(ident);

		printf("Left:\n");
		ident++;
		treeExpression(expr->left);
		ident--;

		if(expr->right != NULL) {
			print_tabs(ident);
			printf("Right:\n");
			ident++;
			treeExpression(expr->right);
			ident--;
		}

		ident--;
	}
	printf("\n");
}

void treeExpressions(AstExpressions* expressions)
{
	ident++;
	print_tabs(ident);
	printf("[EXPRESSIONS] %d expression(s)\n", expressions->count);
	ident++;
	for (size_t i = 0; i < expressions->count; i++)
	{
		treeExpression(expressions->data[i]);
	}
	ident--;
	ident--;
}

void treeStatement(AstStatement* stmt)
{
	printf("[STMT] %s\n", astStatementName(stmt->type));
	if (stmt->type == AST_STATEMENT_PRINT || stmt->type == AST_STATEMENT_PRINTNL || stmt->type == AST_STATEMENT_PRINTDB || stmt->type == AST_STATEMENT_PRINTDBNL || stmt->type == AST_STATEMENT_RETURN)
		treeExpressions(stmt->expressions);
}

void treeStatements(AstStatements* stmts)
{
	ident++;
	for (size_t i = 0; i < stmts->count; i++)
	{
		print_tabs(ident);
		treeStatement(stmts->data[i]);
	}
	ident--;
}

void treeBlock(AstBlock* block)
{
	treeStatements(block->statements);
}

void treeFunction(AstFunction* func)
{
	printf("\n");
	print_tabs(ident);
	printf("[FUNC] %s\n", func->name);

	treeBlock(func->block);
}

void treeLog(AstRoot* root)
{
	if (root->package == NULL || strlen(root->package) == 0 || strcmp(root->package, "") == 0)
	{
		root->package = "main";
	}
	printf("=============== TREE ===============\n");

	printf("Package: %s\n", root->package);

	for (size_t i = 0; i < root->functions->count; i++)
	{
		treeFunction(root->functions->data[i]);
	}
}
