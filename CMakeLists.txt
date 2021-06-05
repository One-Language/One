cmake_minimum_required(VERSION 3.19)
project(One C)

set(CMAKE_C_STANDARD 11)

include_directories(src)
include_directories(unit-tests)
include_directories(unit-tests/unity)

add_executable(One
        src/arg.c
        src/arg.h

        src/array.c
        src/array.h

        src/compile.c
        src/compile.h

        src/error.c
        src/error.h

        src/lexer.c
        src/lexer.h

        src/one.c
        src/one.h

        src/ast.c
        src/ast.h

        src/parser.c
        src/parser.h

        src/tree.c
        src/tree.h

        src/token.c
        src/token.h

        src/compile.c
        src/compile.h

        src/vm.c
        src/vm.h

        src/file.c
        src/file.h

        unit-tests/unity/unity.c
        unit-tests/unity/unity.h
        unit-tests/unity/unity_internals.h

        unit-tests/arg-tests.c
        )
