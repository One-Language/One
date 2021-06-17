/**
 File: parser.c
  _        _
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "parser.h"
#include "lexer.h"
#include "token.h"

void parser_except(Lexer *lex, char tt)
{
#ifdef DEBUG
	printf("[parser_except] %c %d\n", tt, tt);
#endif

	Token *t = lexer_getcurrent(lex);
	if (t == NULL)
		error("Sorry, cannot access to current token at %d!", lex->location.t);
	else if (t->type == tt)
		lexer_next(lex);
	else
		error("Except token %c but we get %c", tt, t->type);
}

void parser(Lexer *lex)
{
#ifdef DEBUG
	printf("[parser]\n");
#endif

	int count = vector_size(lex->tokens);
#ifdef DEBUG
	printf("[parser] token size: %d\n", count);
#endif

#ifdef DEBUG
	printf("[parser] last token: %s\n", token_name(lex->tokens[count - 1]));
	// printf("[parser] last token: %d\n", lex->tokens[count-1]->type);
#endif

	Token *t;
	while (true)
	{
		t = lexer_getcurrent(lex);
		if (t == NULL || t->type == tok_eof)
			break;

#ifdef DEBUG
		printf("[parser]");
		token_log(t);
#endif

		if (t->type == tok_identifier)
		{
			Token *t2 = lexer_getnext(lex);
			if (t2->type == '{' || t2->type == '(')
			{
#ifdef DEBUG
				printf("========= Define function %s\n", t->vstring);
#endif

				lexer_prev(lex); // back to identifier
				parser_function(lex);
			}
			else
			{
				lexer_next(lex);
				continue;
			}
		}
		else
		{
			lexer_next(lex);
			continue;
		}
	}
}

void parser_function(Lexer *lex)
{
	Token *t;

#ifdef DEBUG
	printf("[parser_function]\n");
#endif

	t = lexer_getcurrent(lex);
	parser_except(lex, tok_identifier);
	sds name = t->vstring;
#ifdef DEBUG
	printf("[parser_function] name: %s\n", name);
#endif

	t = lexer_getcurrent(lex);

	if (t->type == '{')
		parser_statements(lex);
	else if (t->type == '(')
	{
		parser_function_arguments(lex);
		parser_statements(lex);
	}
}

void parser_function_arguments(Lexer *lex)
{
#ifdef DEBUG
	printf("[parser_function_arguments]\n");
#endif

#ifdef DEBUG
	printf("[parser_function_arguments]");
#endif
	parser_except(lex, '('); // eat '('

	Token *t;
	while ((t = lexer_getcurrent(lex)) && t->type != ')')
	{
#ifdef DEBUG
		printf("[parser_function_arguments] %s\n", token_name(t));
#endif
		lexer_next(lex);
	}

#ifdef DEBUG
	printf("[parser_function_arguments]");
#endif
	parser_except(lex, ')'); // eat ')'
}

void parser_statement(Lexer *lex)
{
#ifdef DEBUG
	printf("[parser_statement]");
#endif
	token_next(lex);
}

int parser_operator_precedence(int type)
{
	// 1 is lowest precedence.
	switch (type)
	{
		case '<':
		case '>':
			return 10;
			break;

		case '+':
		case '-':
			return 10;
			break;

		case '*':
		case '/':
			return 40;
			break;
	}
	return -1;
}

/// GetTokPrecedence - Get the precedence of the pending binary operator token.
static int GetTokPrecedence(Lexer *lex)
{
	Token *t = lexer_getcurrent(lex);

	if (token_is_operator(t) == true)
	{
		// Install standard binary operators.
		return parser_operator_precedence(t->type);
	}

	return -1;
}
/// parent ::= '(' expression ')'
int parser_expression_parent(Lexer *lex)
{
	parser_except(lex, '(');
	int V = parser_expression(lex);

	parser_except(lex, ')');
	return V;
}

/// binoprhs
///   ::= ('+' unary)*
int parser_bin_op_rhs(Lexer *lex, int ExprPrec, int LHS)
{
	// If this is a binop, find its precedence.
	while (true)
	{
		int TokPrec = GetTokPrecedence(lex);

		// If this is a binop that binds at least as tightly as the current binop,
		// consume it, otherwise we are done.
		if (TokPrec < ExprPrec)
			return LHS;

		// Okay, we know this is a binop.
		Token *BinOp = lexer_getcurrent(lex);
		lexer_next(lex);

		// Parse the unary expression after the binary operator.
		int RHS = parser_unary(lex, 20);
		// if (!RHS)
		//   return nullptr;

		// If BinOp binds less tightly with RHS than the operator after RHS, let
		// the pending operator take RHS as its LHS.
		int NextPrec = GetTokPrecedence(lex);
		if (TokPrec < NextPrec)
		{
			RHS = parser_bin_op_rhs(lex, TokPrec + 1, RHS);
			// if (!RHS)
			//   return nullptr;
		}

		// Merge LHS/RHS.
		LHS = LHS * RHS; // * is BinOp
	}
}

int parser_expression_number(Lexer *lex)
{
	Token *t = lexer_getcurrent(lex);
	parser_except(lex, tok_number);
	return t->vint;
}

/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'
int parser_expression_identifier(Lexer *lex)
{
	Token *t = lexer_getcurrent(lex);
	parser_except(lex, tok_identifier);
	return 10;
}

int parser_primary(Lexer *lex)
{
	Token *t = lexer_getcurrent(lex);
	switch (t->type)
	{
		default:
			error("unknown token when expecting an expression");
			return -1;
		case tok_identifier:
			return parser_expression_identifier(lex);
		case tok_number:
			return parser_expression_number(lex);
		case '(':
			return parser_expression_parent(lex);
	}
}

/// unary
///   ::= primary
///   ::= '!' unary
///   ::= '-' unary
int parser_unary(Lexer *lex, int val)
{
	Token *t = lexer_getcurrent(lex);
	if (t->type != '-')
		return parser_primary(lex);

	return -val;
}

int parser_expression(Lexer *lex)
{
	int LHS = parser_unary(lex, 10);
	int res = parser_bin_op_rhs(lex, 0, LHS);
	printf("Expression Result: %d\n", res);
	return res;
}

void parser_statement_return(Lexer *lex)
{
#ifdef DEBUG
	printf("[parser_statement_return]\n");
#endif

	parser_except(lex, tok_ret); // eat `ret`

	parser_expression(lex);
}

void parser_statements(Lexer *lex)
{
#ifdef DEBUG
	printf("[parser_statements]\n");
#endif

	parser_except(lex, '{'); // eat '{'

	Token *t;
	while ((t = lexer_getcurrent(lex)) && t->type != '}')
	{
#ifdef DEBUG
		printf("[parser_statements] %s\n", token_name(t));
#endif

		if (t->type == tok_ret)
			parser_statement_return(lex);
		else
		{
			error("Error: This kind of statement still not supported!\n");
			printf("Bad token is: %s\n", token_name(t));
			lexer_next(lex);
		}
	}

	parser_except(lex, '}'); // eat '}'
}
