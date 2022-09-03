cmake_minimum_required(VERSION 3.23)
project(one_lexer C)

set(CMAKE_C_STANDARD 11)

include_directories(./)
include_directories(../../utilities)

add_executable(one_lexer
        lexer.c
        lexer.h
        main.c
        token.c
        token.h
        ../../utilities/io.c
        ../../utilities/io.h)
