//
// Created by max on 6/9/21.
//

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "lexer.h"
#include "token.h"
#include "array.h"
#include "one.h"
#include "ast.h"

#include "parser.h"

// Global variable(s)
Parser parser;
Array tokens;

// macro
#define PARSER_HAS(want_type) ((*parser.tokens)->type == want_type)

#define PARSER_CURRENT (*parser.tokens)

#define PARSER_CURRENT_LOG                              \
	debug_parser(                                       \
		 "Current Token is %s (%d)%s%s",                \
		 token_name((*parser.tokens)->type),            \
		 (*parser.tokens)->type,                        \
		 ((*parser.tokens)->value != NULL) ? ": " : "", \
		 ((*parser.tokens)->value != NULL) ? (*parser.tokens)->value : "");

void parser_init()
{
	debug_parser("parser_init");

	parser.package = NULL;
	parser.tokens = NULL;
	parser.tokens_count = 0;
	array_init(&tokens);
}

void parser_push(Token* t)
{
	array_push(&tokens, t);
}

void parser_scan()
{
	debug_parser("parser_scan");

	Token* t;
	for (;;)
	{
		t = lexer_scan();
		parser_push(t);
		debug_parser("parser_scan: print_token %s", token_name(t->type));
		if (t->type == TOKEN_ERROR)
		{
			printf("Error: %s\n", t->value);
			break;
		}
		else if (t->type == TOKEN_EOF)
			break;
	}
}

void parser_start()
{
	debug_parser("parser_start");

	parser.tokens = (Token**)tokens.data;
	parser.tokens_count = tokens.count;

	parser_check();
}

AstRoot* parser_check()
{
	debug_parser("parser_check");

	AstRoot* root;
	Token* t;

	while ((*parser.tokens)->type != TOKEN_EOF)
	{
		t = *parser.tokens;
		debug_parser("parser_check: print_token %d <-> %s", t->type, token_name(t->type));
		if (t->type == TOKEN_ERROR)
		{
			debug_parser("parser_check: print_token_error %s", t->value);
			error_token(t->value);
			break;
		}

		parser_parse();
		// parser.tokens++;
	}

	root->package = parser.package;
	root->functions;
	return root;
}

void parser_next()
{
	parser.tokens_index++;
	parser.tokens++;
}

void parser_prev()
{
	parser.tokens_index--;
	parser.tokens--;
}

Ast parser_parse()
{
	debug_parser("parser_parse");

	size_t i = parser.tokens_index;

	if (parser.tokens_index == 0 && PARSER_CURRENT->type != TOKEN_PACKAGE && parser.package == NULL)
	{
		info_parser("User not defined a package name, so we set it to '%s' as default.", ONE_PACKAGE_DEFAULT);
		parser.package = ONE_PACKAGE_DEFAULT;
	}

	if (PARSER_CURRENT->type == TOKEN_PACKAGE)
	{
		return parser_parse_package();
	}
	else if (PARSER_CURRENT->type == TOKEN_FN)
	{
		return parser_parse_fn();
	}

	if (PARSER_CURRENT->type == TOKEN_EOF)
		return;
	else if (parser.tokens_index == i)
	{
		error_parser("Cannot parse this kind of statement, we face to %s token!", token_name(PARSER_CURRENT->type));
	}
}

AstFunction* parser_parse_fn()
{
	debug_parser("parser_parse_fn");

	AstFunction* fn;
	AstBlock* block;
	Token* ident;
	AstArguments args;

	parser_expect(TOKEN_FN);
	ident = PARSER_CURRENT;
	parser_expect(TOKEN_VALUE_IDENTIFIER);

	info_parser("Define function = %s", ident->value);
	block = parser_parse_block();

	array_init(&args);

	fn->arguments = &args;
	//	array_free(&args);
	fn->name = ident->value;
	fn->block = block;
	return fn;
}

AstBlock* parser_parse_block()
{
	debug_parser("parser_parse_block");

	parser_expect(TOKEN_OPERATOR_BRACKET_CURLY_LEFT);
	AstBlock* block = parser_parse_statements();
	parser_expect(TOKEN_OPERATOR_BRACKET_CURLY_RIGHT);
	return block;
}

AstBlock* parser_parse_statements()
{
	debug_parser("parser_parse_statements");

	AstStatement* stmt;
	AstStatements stmts;
	array_init(&stmts);

	while (PARSER_CURRENT->type != TOKEN_OPERATOR_BRACKET_CURLY_RIGHT)
	{
		stmt = parser_parse_statement();
		array_push(&stmts, (void*)stmt);
	}

	AstBlock* block = ast_make_block(&stmts);
	//	array_free(&stmts); // TODO

	return block;
}

AstStatement* parser_parse_statement()
{
	AstStatement* stmt;

	debug_parser("parser_parse_statement");

	info_parser("statement type = %s", token_name(PARSER_CURRENT->type));

	if (PARSER_CURRENT->type == TOKEN_PRINT || PARSER_CURRENT->type == TOKEN_PRINTNL || PARSER_CURRENT->type == TOKEN_PRINTDB || PARSER_CURRENT->type == TOKEN_PRINTDBNL)
	{
		stmt = parser_parse_statement_prints();
	}
	else
	{
		error_parser("We face to %s as a unknown type of token at print statement!", token_name(PARSER_CURRENT->type));
	}
	return stmt;
}

AstStatement* parser_parse_statement_prints()
{
	debug_parser("parser_parse_statement_prints");

	if (PARSER_CURRENT->type == TOKEN_PRINT)
	{
		return parser_parse_statement_print();
	}
	else if (PARSER_CURRENT->type == TOKEN_PRINTNL)
	{
		return parser_parse_statement_printnl();
	}
	else if (PARSER_CURRENT->type == TOKEN_PRINTDB)
	{
		return parser_parse_statement_printdb();
	}
	else if (PARSER_CURRENT->type == TOKEN_PRINTDBNL)
	{
		return parser_parse_statement_printdbnl();
	}
	else
	{
		error_parser("We expect a print statement but we face to a %s token!", token_name(PARSER_CURRENT->type));
		return NULL;
	}
}

AstStatement* parser_parse_statement_print()
{
	debug_parser("parser_parse_statement_print");

	AstStatement* stmt = ast_make_statement(AST_STATEMENT_PRINT);

	parser_expect(TOKEN_PRINT);
	parser_parse_expressions();

	return stmt;
}

AstStatement* parser_parse_statement_printnl()
{
	debug_parser("parser_parse_statement_printnl");

	AstStatement* stmt = ast_make_statement(AST_STATEMENT_PRINTNL);

	parser_expect(TOKEN_PRINTNL);
	parser_parse_expressions();

	return stmt;
}

AstStatement* parser_parse_statement_printdb()
{
	debug_parser("parser_parse_statement_printdb");

	AstStatement* stmt = ast_make_statement(AST_STATEMENT_PRINTDB);

	parser_expect(TOKEN_PRINTDB);
	parser_parse_expressions();

	return stmt;
}

AstStatement* parser_parse_statement_printdbnl()
{
	debug_parser("parser_parse_statement_printdbnl");

	AstStatement* stmt = ast_make_statement(AST_STATEMENT_PRINTDBNL);

	parser_expect(TOKEN_PRINTDBNL);
	parser_parse_expressions();

	return stmt;
}

void parser_parse_expressions()
{
	debug_parser("parser_parse_expressions");

	bool is_multi = false;

	for (;;)
	{
		parser_parse_expression();

		if (parser_has(TOKEN_OPERATOR_COMMA))
		{
			parser_expect(TOKEN_OPERATOR_COMMA);
		}
		else
		{
			break;
		}
	}
}

void parser_parse_expression()
{
	debug_parser("parser_parse_expression");
	if (PARSER_CURRENT->type == TOKEN_VALUE_STRING)
	{
		parser_next();
	}
	else if (PARSER_CURRENT->type == TOKEN_VALUE_NUMBER)
	{
		parser_next();
	}
	else
	{
		error_parser("Bad token as expression, we face to a %s token!", token_name(PARSER_CURRENT->type));
	}
}

void parser_parse_package()
{
	debug_parser("parser_parse_package");

	Token* t;
	if (parser.tokens_index == 0)
	{
		parser_expect(TOKEN_PACKAGE);
		if (PARSER_HAS(TOKEN_VALUE_IDENTIFIER))
		{
			PARSER_CURRENT_LOG
			t = PARSER_CURRENT;
			parser_expect(TOKEN_VALUE_IDENTIFIER);
		}
		else if (PARSER_HAS(TOKEN_VALUE_STRING))
		{
			PARSER_CURRENT_LOG
			t = PARSER_CURRENT;
			parser_expect(TOKEN_VALUE_STRING);
		}
		else
		{
			error_parser("You cannot set package name as %s token, you have to write this in two general forms:\n\t1- Identifier: `package yourname`\n\t2- String: `package \"your-name\"`", token_name(PARSER_CURRENT->type));
			return;
		}
	}
	else
	{
		error_parser("You are unable to define package name at middle or end of the file and you have to set package name at top!");
		return;
	}

	info_parser("SET PACKAGE = \"%s\"", t->value);
	parser.package = (const char*)t->value;
}

bool parser_expect(TokenType expected)
{
	debug_parser("parser_expect");

	if (PARSER_CURRENT->type == expected)
	{
		parser.tokens++;
		return true;
	}
	else
	{
		error_parser("We expected %s but we find %s", token_name(expected), token_name(PARSER_CURRENT->type));
	}
	return false;
}

bool parser_has(TokenType expected)
{
	debug_parser("parser_has");

	if (PARSER_CURRENT->type == expected)
	{
		return true;
	}
	return false;
}

void parser_free()
{
	debug_parser("parser_free");

	// TODO
}
