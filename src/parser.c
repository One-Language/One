//
// Created by max on 6/9/21.
//

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "lexer.h"
#include "token.h"
#include "array.h"

#include "parser.h"

// Global variable(s)
Parser parser;
Array tokens;

// macro
#define PARSER_HAS(want_type) ((*parser.tokens)->type == want_type)

#define PARSER_CURRENT (*parser.tokens)

void parser_init()
{
	debug("parser_init");

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
	debug("parser_scan");

	Token* t;
	for (;;)
	{
		t = lexer_scan();
		parser_push(t);
		debug("parser_scan: print_token %s", token_name(t->type));
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
	debug("parser_start");

	parser.tokens = (Token**)tokens.data;
	parser.tokens_count = tokens.count;

	parser_check();
}

void parser_check()
{
	debug("parser_check");

	Token* t;

	while ((*parser.tokens)->type != TOKEN_EOF)
	{
		t = *parser.tokens;
		debug("parser_check: print_token %d <-> %s", t->type, token_name(t->type));
		if (t->type == TOKEN_ERROR)
		{
			debug("parser_check: print_token_error %s", t->value);
			error_token(t->value);
			break;
		}

		parser_parse();

		//		parser.tokens++;
	}
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

void parser_parse()
{
	if (PARSER_CURRENT->type == TOKEN_PACKAGE)
	{
		parser_parse_package();
	}
}

void parser_parse_package()
{
	if (parser.tokens_index == 0)
	{
		parser_expect(TOKEN_PACKAGE);
		if(PARSER_HAS(TOKEN_VALUE_IDENTIFIER)) {
			parser_expect(TOKEN_VALUE_IDENTIFIER);
		}
		else if(PARSER_HAS(TOKEN_VALUE_STRING)) {
			parser_expect(TOKEN_VALUE_STRING);
		}
		else {
			error_parser("You cannot set package name as %s token, you have to write this in two general forms:\n\t1- Identifier: `package yourname`\n\t2- String: `package \"your-name\"`", token_name(PARSER_CURRENT->type));
		}
	}
	else
	{
		error_parser("You are unable to define package name at middle or end of the file and you have to set package name at top!");
	}
}

bool parser_expect(TokenType expected)
{
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
	if (PARSER_CURRENT->type == expected)
	{
		return true;
	}
	return false;
}

void parser_package()
{
}

void parser_free()
{
	// TODO
}