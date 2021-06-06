#include "unity.h"
#include "error.h"
#include "lexer.h"

char *filename;
char *input;
ErrorsContainer *errors;
Lexer *lex;

void setUp(void)
{
    //This is the initialization for the variables needed for the unit testing.
    //It can be updated
    filename = "tests/1-hello-world.et";
    input = "";
    ErrorsInit(errors);
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