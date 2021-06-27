/**
 The One Programming Language

 File: test.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef ONE_TEST_H
#define ONE_TEST_H

// You have to define a macro at CLANG or c compiler: #define _ONE_TEST_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "../src/array.h"
#include "../src/lexer.h"
#include "../src/token.h"
#include "../src/ast.h"
#include "../src/parser.h"
#include "../src/error.h"
#include "../src/generator.h"

extern Parser parser;
extern Array tokens;

#endif //ONE_TEST_H
