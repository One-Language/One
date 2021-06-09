cmake_minimum_required(VERSION 3.19)
project(One C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

# enable_testing()
# add_subdirectory(test)
include_directories(test)

set(PROJECT_HEADERS
        src/one.h

        src/repl.h

        src/token.h

        src/lexer.h

        src/parser.h

        src/array.h

        src/file.h

        src/argument.h

        src/interpret.h

        src/error.h
        )

set(PROJECT_SOURCES
        src/one.c

        src/repl.c

        src/token.c

        src/lexer.c

        src/parser.c

        src/array.c

        src/file.c

        src/argument.c

        src/interpret.c

        src/error.c)

add_executable(One ${PROJECT_SOURCES} ${PROJECT_HEADERS})
