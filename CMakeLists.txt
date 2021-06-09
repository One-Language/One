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

        src/token.c
        src/token.h

        src/lexer.c
        src/lexer.h

        src/parser.c
        src/parser.h

        src/array.c
        src/array.h

        src/file.c
        src/file.h

        src/argument.c
        src/argument.h

        src/interpret.c
        src/interpret.h

        src/error.c
        src/error.h

        )
