#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct TestFunction
{
	const char *name;

	int (*function)(void);
};

int lexer_test1()
{
	return 0;
}
int lexer_test2()
{
	return 1;
}
int lexer_test3()
{
	return 1;
}
int lexer_test4()
{
	return 1;
}
int lexer_test5()
{
	return 1;
}
int lexer_test6()
{
	return 1;
}
int lexer_test7()
{
	return 1;
}
int lexer_test8()
{
	return 0;
}
int lexer_test9()
{
	return 0;
}
int lexer_test10()
{
	return 1;
}

struct TestFunction lexer_functions[] = {
	 {"test1", lexer_test1},
	 {"test2", lexer_test2},
	 {"test3", lexer_test3},
	 {"test4", lexer_test4},
	 {"test5", lexer_test5},
	 {"test6", lexer_test6},
	 {"test7", lexer_test7},
	 {"test8", lexer_test8},
	 {"test9", lexer_test9},
	 {"test10", lexer_test10},
};
enum
{
	LEXER_TEST_COUNT = sizeof(lexer_functions) / sizeof(lexer_functions[0])
};

void run_tests()
{
	int res[LEXER_TEST_COUNT];
	for (size_t i = 0; i < LEXER_TEST_COUNT; i++)
	{
		printf("[Test %d] ", i);
		res[i] = lexer_functions[i].function();
		printf("%s: ", lexer_functions[i].name);
		if (res[i] == 1)
		{
			printf("Test Success.\n");
		}
		else
		{
			printf("Test Failed!\n");
		}
	}
}

int main()
{
	run_tests();
	return 0;
}
