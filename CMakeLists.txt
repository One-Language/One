############################################################
# The One Programming Language                             #
#                                                          #
# File: CMakeLists.txt                                     #
#  _        _                                              #
# / \ |\ | |_    Max Base                                  #
# \_/ | \| |_    Copyright 2021; One Language Contributors #
#                                                          #
############################################################

# Project setup
cmake_minimum_required(VERSION 3.19)
set(CMAKE_C_STANDARD 11)
project(One VERSION 0.1.0)

# Setup Shell Variables
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

# Setup CPack, CTest, and enable testing
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include(CTest)
enable_testing()

# Setup LLVM
find_package(LLVM)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(/usr/include)
link_directories(/usr/lib)
llvm_map_components_to_libnames(core)
add_definitions(
        -D_GNU_SOURCE
        -D__STDC_CONSTANT_MACROS
        -D__STDC_FORMAT_MACROS
        -D__STDC_LIMIT_MACROS
)

# Set builtins source and headers
set(BUILTINS_SOURCE
        tmp/c-new3/builtins/array.c

        tmp/c-new3/builtins/error.c

        tmp/c-new3/builtins/file.c

        tmp/c-new3/builtins/string.c
)

set(BUILTINS_HEADERS
        tmp/c-new3/builtins/array.h

        tmp/c-new3/builtins/error.h

        tmp/c-new3/builtins/file.h

        tmp/c-new3/builtins/string.h
)

# Set lexer source and headers
set(LEXER_SOURCE
        src/lexer/tokenizer/token.c

        src/lexer/tokenizer/tokenizer.c

        src/lexer/lexer.c
)

set(LEXER_HEADERS
        src/lexer/tokenizer/token.h

        src/lexer/tokenizer/tokenizer.h

        src/lexer/lexer.h
)

# Set AST source and headers
set(AST_SOURCE
        tmp/c-new3/ast/ast.c
)

set(AST_HEADERS
        tmp/c-new3/ast/ast.h
)

# Set parser source and headers
set(PARSER_SOURCE
        tmp/c-new3/parser/parser_token.c

        tmp/c-new3/parser/parser.c
)

set(PARSER_HEADERS
        tmp/c-new3/parser/parser_token.h

        tmp/c-new3/parser/parser.h
)

# Set Main executables for lexer, ast, and parser
set(LEXER_MAIN
        src/lexer/main.c
)

set(AST_MAIN
        tmp/c-new3/ast/main.c
)

set(PARSER_MAIN
        tmp/c-new3/parser/main.c
)

# Set Tests
set(TESTS_HEADERS
        test/test.h
)

set(LEXER_TEST
        test/lexer.test.c
)

set(PARSER_TEST
        test/parser.test.c
)

set(ARGUMENT_TEST
        test/argument.test.c
)

# Create Executables for lexer, ast, and parser
add_executable(lexer ${LEXER_MAIN} ${LEXER_SOURCE} ${LEXER_HEADERS} ${BUILTINS_SOURCE} ${BUILTINS_HEADERS} ${CFLAGS} ${LIBS})
add_executable(ast  ${AST_MAIN} ${AST_SOURCE} ${AST_HEADERS} ${LEXER_SOURCE} ${LEXER_HEADERS} ${BUILTINS_SOURCE} ${BUILTINS_HEADERS} ${PARSER_SOURCE} ${PARSER_HEADERS} ${CFLAGS} ${LIBS})
add_executable(parser  ${PARSER_MAIN} ${PARSER_SOURCE} ${PARSER_HEADERS} ${LEXER_SOURCE} ${LEXER_HEADERS} ${AST_SOURCE} ${AST_HEADERS} ${BUILTINS_SOURCE} ${BUILTINS_HEADERS}  ${CFLAGS} ${LIBS})

# Create Executables for lexer test
add_executable(lexer_test ${LEXER_TEST} ${TEST_HEADERS} ${PARSER_SOURCE} ${PARSER_HEADERS} ${LEXER_SOURCE} ${LEXER_HEADERS} ${AST_SOURCE} ${AST_HEADERS} ${BUILTINS_SOURCE} ${BUILTINS_HEADERS} ${CFLAGS} ${LIBS})
target_compile_options(lexer_test PUBLIC "-D_ONE_TEST_")
add_test(lexer_test lexer_test)

# Create Executables for parser test
add_executable(parser_test  ${PARSER_TEST} ${TEST_HEADERS})
add_test(NAME parser_test WORKING_DIRECTORY ../test COMMAND parser_test)

# Create Executables for argument test
add_executable(argument_test  ${ARGUMENT_TEST} ${TEST_HEADERS})
add_test(NAME argument_test WORKING_DIRECTORY ../test COMMAND argument_test)
