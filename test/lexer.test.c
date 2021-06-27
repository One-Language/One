/**
 The One Programming Language

 File: lexer.test.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "test.h"

typedef struct
{
	char* source;
	Token* tokens[1024];
} LexerTest;

LexerTest lexer_tests[1024];
unsigned int lexer_tests_count = 0;

#define TEST(source)    \
	lexer_init(source); \
	parser_init();      \
	parser_scan();      \
	parser_preapre();

void test_lexer_log()
{
	for (int i = 0; i < parser.tokens_count; i++)
	{
		printf("[%d] %s\n", i, token_name(parser.tokens[i]->type));
	}
}

bool test_lexer_item(LexerTest test)
{
	TEST(test.source);

	// test_lexer_log();

	for (int i = 0; i < parser.tokens_count; i++)
	{
		if (test.tokens[i] == NULL)
		{
			// printf("11111\n");
			return false;
		}
		else if (test.tokens[i]->type == parser.tokens[i]->type)
		{
			// printf("2222\n");
			continue;
		}
		else
		{
			// printf("3333\n");
			return false;
		}
	}

	return true; // for example if `parser.tokens_count` is 0 or loop finished without an error!
}

bool test_lexer()
{
	bool res_final = true;
	for (unsigned i = 0; i < lexer_tests_count; i++)
	{
		printf("Test case %d\n", i + 1);
		bool res = test_lexer_item(lexer_tests[i]);
		if (res == false)
		{
			res_final = false;
		}
	}

	return res_final;
}

int main()
{
	printf("Hello to Lexer test!\n");

	lexer_tests[lexer_tests_count++] = (LexerTest){"main{}", {
																  token_make(TOKEN_VALUE_IDENTIFIER),
																  token_make(TOKEN_OPERATOR_BRACKET_CURLY_LEFT),
																  token_make(TOKEN_OPERATOR_BRACKET_CURLY_RIGHT),
																  token_make(TOKEN_EOF),
															 }};
	bool res = test_lexer();
	if (lexer_tests_count == 0 || res == true)
	{
		printf("All tests passed.\n");
		return 0;
	}
	printf("Test(s) failed!\n");
	return 1;
}
