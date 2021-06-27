/**
 The One Programming Language

 File: lexer.test.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "test.h"

#define TEST(source)    \
	lexer_init(source); \
	parser_init();      \
	parser_scan();

bool test_lexer1()
{
	TEST("main{}");
	return false;
}

bool test_lexer()
{
	return test_lexer1();
	return false;
}
int main()
{
	printf("Hello to Lexer test!\n");
	bool res = test_lexer();
	if(res == true) {
		printf("All tests passed.\n");
		return 0;
	}
	printf("Test(s) failed!\n");
	return 1;
}
