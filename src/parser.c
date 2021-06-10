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

void parser_init()
{
	debug("parser_init");

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
			printf("Error: %s\n", t->start);
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
	for (size_t i = 0; i < parser.tokens_count; i++)
	{
		t = parser.tokens[i];
		debug("parser_check: print_token %d <-> %s", t->type, token_name(t->type));
	}
}

void parser_free()
{
}