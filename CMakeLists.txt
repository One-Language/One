cmake_minimum_required(VERSION 3.19)
project(One C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

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
        src/lexer.test.c
        src/one.c
        src/one.h
        src/parser.c
        src/parser.h
        src/parser.test.c src/compile.c src/compile.h)
