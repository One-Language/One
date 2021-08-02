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

#define MY_TEST(source)    \
	tokens = tokenizer_string(source]);

void test_lexer_log()
{
	for (int i = 0; i < parser.tokens_count; i++)
	{
		printf("[%d] %s\n", i, token_name(parser.tokens[i]->type));
	}
}

bool test_lexer_item(LexerTest test)
{
	Token** tokens = MY_TEST(test.source);

	// test_lexer_log();

	while (tokens != NULL && *tokens != NULL)
	{
		Token* t = *tokens;
		Token* t_want = *(test.tokens);
		if (t == NULL)
		{
			return false;
		}
		else if (t_want->type == t->type)
		{
			continue;
		}
		else
		{
			return false;
		}
		tokens++;
		test.tokens++;
	}

	if (tokens != NULL)
	{ //  if `parser.tokens_count` is 0
		return false;
	}
	return true; // if loop finished without an error!
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
