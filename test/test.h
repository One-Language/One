/**
 The One Programming Language

 File: test.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef ONE_TEST_H
#define ONE_TEST_H

// You have to define a macro at CLANG or C compiler: #define _ONE_TEST_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../src/builtins/array.h"
#include "../src/builtins/error.h"

#include "../src/builtins/file.h"

#include "../src/parser/lexer/lexer.h"
#include "../src/parser/parser.h"

typedef struct
{
	char* source;
	Token* tokens[1024];
	size_t token_count;
} LexerTest;

// Argument(s)

// Lexer
void test_lexer_log(const char* source, Token** tokens);
bool test_lexer_item(LexerTest test);
bool test_lexer();

// Parser

// Ast

#endif //ONE_TEST_H
