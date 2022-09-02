cmake_minimum_required(VERSION 3.23)
project(one_lexer C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

#file(GLOB source_files CONFIGURE_DEPENDS
#        "*.h"
#        "*/*.h"
#        "*/*/*.h"
#        )

#include_directories(./stages
#        ./stages/lexer
#        ./utilities
#        )

add_executable(one_lexer
#        lexer.h
#        ../../utilities/io.h
        lexer.c
        ../../utilities/io.c
        main.c token.c token.h)
