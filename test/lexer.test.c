/**
 The One Programming Language

 File: lexer.test.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "test.h"

LexerTest lexer_tests[1024];
unsigned int lexer_tests_count = 0;

void test_lexer_log(const char* source, Token** tokens)
{
	lexer_trace(stdout, source, tokens);
}

bool test_lexer_item(LexerTest test)
{
	Token** tokens = tokenizer_string(test.source);

#ifndef _ONE_TEST_
	test_lexer_log((const char*)test.source, tokens);
#endif

	if (tokens == NULL && test.token_count == 0)
	{
		return true;
	}

	for (size_t i = 0; i < test.token_count; i++)
	{
		if (tokens[i] == NULL)
		{
			return false;
		}
		else if (test.tokens[i]->type == tokens[i]->type)
		{
			continue;
		}
		else
		{
			return false;
		}
	}

	return true; // if loop finished without an error!
}

bool test_lexer()
{
	bool res_final = true;
	for (unsigned i = 0; i < lexer_tests_count; i++)
	{
		printf("Test case %d", i + 1);
		bool res = test_lexer_item(lexer_tests[i]);
		if (res == false)
		{
			printf(": Failed!");
			res_final = false;
		}
		printf("\n");
	}

	return res_final;
}

int main()
{
	printf("Hello to Lexer test!\n");

	lexer_tests[lexer_tests_count++] = (LexerTest){"", {token_make(TOKEN_EOF)}, 1};
	lexer_tests[lexer_tests_count++] = (LexerTest){"    ", {token_make(TOKEN_SKIP_WHITESPACE), token_make(TOKEN_EOF)}, 2};
	lexer_tests[lexer_tests_count++] = (LexerTest){"\r\n", {token_make(TOKEN_SKIP_WHITESPACE_LINE), token_make(TOKEN_EOF)}, 2};
	lexer_tests[lexer_tests_count++] = (LexerTest){"   \r\n", {token_make(TOKEN_SKIP_WHITESPACE_LINE), token_make(TOKEN_EOF)}, 2};
	lexer_tests[lexer_tests_count++] = (LexerTest){"\r\n    ", {token_make(TOKEN_SKIP_WHITESPACE_LINE), token_make(TOKEN_EOF)}, 2};
	lexer_tests[lexer_tests_count++] = (LexerTest){"1\r\n    ", {token_make(TOKEN_VALUE_NUMBER), token_make(TOKEN_SKIP_WHITESPACE_LINE), token_make(TOKEN_EOF)}, 3};
	lexer_tests[lexer_tests_count++] = (LexerTest){"1\r\n    2", {token_make(TOKEN_VALUE_NUMBER), token_make(TOKEN_SKIP_WHITESPACE_LINE), token_make(TOKEN_VALUE_NUMBER), token_make(TOKEN_EOF)}, 4};
	lexer_tests[lexer_tests_count++] = (LexerTest){"1\r\n    2\n3\n4", {token_make(TOKEN_VALUE_NUMBER), token_make(TOKEN_SKIP_WHITESPACE_LINE), token_make(TOKEN_VALUE_NUMBER), token_make(TOKEN_SKIP_WHITESPACE_LINE), token_make(TOKEN_VALUE_NUMBER), token_make(TOKEN_SKIP_WHITESPACE_LINE), token_make(TOKEN_VALUE_NUMBER), token_make(TOKEN_EOF)}, 7};
	lexer_tests[lexer_tests_count++] = (LexerTest){"main{}", {token_make(TOKEN_VALUE_IDENTIFIER), token_make(TOKEN_OPERATOR_BRACKET_CURLY_LEFT), token_make(TOKEN_OPERATOR_BRACKET_CURLY_RIGHT), token_make(TOKEN_EOF)}, 4};
	lexer_tests[lexer_tests_count++] = (LexerTest){"import math", {token_make(TOKEN_IMPORT), token_make(TOKEN_SKIP_WHITESPACE), token_make(TOKEN_VALUE_IDENTIFIER), token_make(TOKEN_EOF)}, 4};

	bool res = test_lexer();
	if (lexer_tests_count == 0)
	{
		printf("No tests.\n");
		return 0;
	}
	else if (res == true)
	{
		printf("All tests passed.\n");
		return 0;
	}
	printf("Test(s) failed!\n");
	return 1;
}
