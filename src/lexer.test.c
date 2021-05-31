
struct TestFunction {
    const char *name;

    int (*function)(void);
};

struct TestFunction lexer_functions[] = {
        {"test1",  lexer_test1},
        {"test2",  lexer_test2},
        {"test3",  lexer_test3},
        {"test4",  lexer_test4},
        {"test5",  lexer_test4},
        {"test6",  lexer_test4},
        {"test7",  lexer_test4},
        {"test8",  lexer_test4},
        {"test9",  lexer_test9},
        {"test10", lexer_test10},
};
enum {
    LEXER_TEST_COUNT = sizeof(functions) / sizeof(functions[0])
};


void run_tests() {
    int res[LEXER_TEST_COUNT];
    for (size_t i = 0; i < LEXER_TEST_COUNT; i++) {
        res[i] = lexer_functions[i]();
        if(res[i] == 1) {
            printf("Test Success.\n");
        } else {
            printf("Test Failed!\n");
        }
    }
}

int main() {
    run_tests();
    return 0;
}
