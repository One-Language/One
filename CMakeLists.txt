cmake_minimum_required(VERSION 3.19)
set(CMAKE_C_STANDARD 11)
project(One C CXX)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

#enable_language(C++)


#find_package(LLVM REQUIRED CONFIG)
find_package(LLVM)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(src)

include_directories(test)
# enable_testing()
# add_subdirectory(test)

#include_directories(${LLVM_INCLUDE_DIRS})
include_directories(/usr/include)
link_directories(/usr/lib)

#add_definitions(${LLVM_DEFINITIONS})

#llvm_map_components_to_libnames(llvm_libs support core irreader)
llvm_map_components_to_libnames(core)

#set(LLVMCONF
#        llvm-config)

#set(RFLAGS
#        -O3)

add_definitions(
        -D_GNU_SOURCE
        -D__STDC_CONSTANT_MACROS
        -D__STDC_FORMAT_MACROS
        -D__STDC_LIMIT_MACROS
)


#set(CFLAGS
#        #        `${LLVMCONF} --cflags` -Wall ${RFLAGS})
#    -I/usr/include  -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS -Wall -O3)


#set(LIBS
##        `${LLVMCONF} --ldflags --libs --system-libs`)
#        -L/usr/lib  -lLLVM-11)

set(PROJECT_HEADERS
        src/one.h

        src/repl.h

        src/ast.h

        src/tree.h

        src/token.h

        src/lexer.h

        src/parser.h

        src/array.h

        src/file.h

        src/argument.h

        src/interpret.h

        src/value.h

        src/generator.h

        src/error.h
        )

set(PROJECT_SOURCES
        src/one.c

        src/repl.c

        src/ast.c

        src/tree.c

        src/token.c

        src/lexer.c

        src/parser.c

        src/array.c

        src/file.c

        src/argument.c

        src/interpret.c

        src/value.c

        src/generator.c

        src/error.c)

#add_executable(One ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${CFLAGS} ${LIBS})
add_executable(One ${PROJECT_SOURCES} ${PROJECT_HEADERS})

target_link_libraries(One ${llvm_libs})

target_link_libraries(One
        LLVM-11
        )
