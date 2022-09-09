cmake_minimum_required(VERSION 3.23)
project(one_generator C)

set(CMAKE_C_STANDARD 11)

include_directories(../../builtins)
include_directories(./)

add_executable(one_generator
        ../../builtins/io.c
        ../../builtins/io.h

        ../../builtins/array.c
        ../../builtins/array.h

        ../../builtins/error.c
        ../../builtins/error.h

        ../../builtins/str.c
        ../../builtins/str.h

        ../lexer/lexer.c
        ../lexer/lexer.h

        ../parser/parser.c
        ../parser/parser.h

        ./generator.c
        ./generator.h

        ./main.c)
