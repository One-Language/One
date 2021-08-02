cmake_minimum_required(VERSION 3.19)
set(CMAKE_C_STANDARD 11)
project(One VERSION 0.1.0)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
include(CTest)
enable_testing()

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

set(LEXER_SOURCE
        src/lexer/tokenizer/token.c

        src/lexer/tokenizer/tokenizer.c

        src/lexer/lexer.c

        src/lexer/main.c
)

set(LEXER_HEADERS
        src/lexer/tokenizer/token.h

        src/lexer/tokenizer/tokenizer.h

        src/lexer/lexer.h
)

set(AST_SOURCE
        src/ast/ast.c

        src/ast/main.c
)

set(BUILTINS_SOURCE
        src/builtins/array.c

        src/builtins/error.c

        src/builtins/file.c

        src/builtins/string.c
)

set(PARSER_SOURCE
        src/parser/parser_token.c

        src/parser/parser.c

        src/parser/main.c
)

set(AST_HEADERS
        src/ast/ast.h
)

set(BUILTINS_HEADERS
        src/builtins/array.h

        src/builtins/error.h

        src/builtins/file.h

        src/builtins/string.h
)

set(PARSER_HEADERS
        src/parser/parser_token.h

        src/parser/parser.h
)

# set(TEST_HEADERS
#         test/test.h
# )

# set(TESTS
#         test/argument.test.c

#         test/lexer.test.c

#         test/parser.test.c
# )

add_executable(lexer ${LEXER_SOURCE} ${LEXER_HEADERS} ${BUILTINS_SOURCE} ${BUILTINS_HEADERS} ${CFLAGS} ${LIBS})
# add_executable(ast ${AST_SOURCE} ${AST_HEADERS} ${LEXER_SOURCE} ${LEXER_HEADERS} ${BUILTINS_SOURCE} ${BUILTINS_HEADERS} ${CFLAGS} ${LIBS})
# add_executable(parser ${PARSER_SOURCE} ${PARSER_HEADERS} ${LEXER_SOURCE} ${LEXER_HEADERS} ${AST_SOURCE} ${AST_HEADERS} ${BUILTINS_SOURCE} ${BUILTINS_HEADERS}  ${CFLAGS} ${LIBS})
add_test(lexer_test lexer ../src/input.one log)