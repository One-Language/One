cmake_minimum_required(VERSION 3.23)
project(one C)

set(CMAKE_C_STANDARD 11)

add_executable(one src/array.c ast.c cli.c file.c generator.c lexer.c one.c parser.c string.c token.c)
