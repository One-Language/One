#include "unity.h"
#include "error.h"
#include "lexer.h"

char *filename;
char *input;
ErrorsContainer *errors;
Lexer *lex;

void setUp(void)
{
	lex = lexerInit(filename, input, errors);
}

void tearDown(void)
{
	lexerFree(lex);
}

void test_function_should_check_lex(void)
{
	TEST_ASSERT_EQUAL_INT(EXIT_SUCCESS, lexerCheck(lex, errors));
}

int main(void)
{
	UNITY_BEGIN();
	RUN_TEST(test_function_should_check_lex);
	return UNITY_END();
}