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

bool test_lexer()
{
	for (unsigned i = 0; i < lexer_tests_count; i++)
	{
		printf("==>%d\n", i);
	}
	TEST("main{}");
	test_lexer_log();

	return false;
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
