/**
 The One Programming Language

 File: lexer.test.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "test.h"

#define TEST(source)	lexer_init(source); \
	 parser_init(); \
	 parser_scan();

bool lexer_test1()
{
	TEST("main{}");
	return false;
}

int main()
{
	printf("Hello to Lexer test!\n");
	return 0;
}
