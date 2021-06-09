cmake_minimum_required(VERSION 3.19)
project(One C)

set(CMAKE_C_STANDARD 11)

include_directories(src)
include_directories(test)

add_executable(One
        src/one.c
        src/one.h

        src/repl.c
        src/repl.h

        src/lexer.c
        src/lexer.h

        src/utils/array.c
        src/utils/array.h

        src/argument.c
        src/argument.h

        src/interpret.c
        src/interpret.h

        #        src/arg.c
        #        src/arg.h
        #
        #        src/array.c
        #        src/array.h
        #
        #        src/compile.c
        #        src/compile.h
        #
        #        src/error.c
        #        src/error.h
        #
        #        src/lexer.c
        #        src/lexer.h
        #
        #        src/one.c
        #        src/one.h
        #
        #        src/ast.c
        #        src/ast.h
        #
        #        src/parser.c
        #        src/parser.h
        #
        #        src/tree.c
        #        src/tree.h
        #
        #        src/token.c
        #        src/token.h
        #
        #        src/compile.c
        #        src/compile.h
        #
        #        src/vm.c
        #        src/vm.h
        #
        #        src/file.c
        #        src/file.h
        #
        )
