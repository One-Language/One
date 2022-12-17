cmake_minimum_required(VERSION 3.23)

project(one C)

set(CMAKE_C_STANDARD 11)

add_executable(one src/array.c src/ast.c src/cli.c src/file.c src/generator.c src/lexer.c src/one.c src/parser.c src/string.c src/token.c)
