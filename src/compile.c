/**
 The One Programming Language

 File: compile.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "arg.h"
#include "error.h"
#include "file.h"
#include "compile.h"
#include "token.h"
#include "lexer.h"
#include "parser.h"

void link(Args *args, ErrorsContainer *errors) {
    // TODO, link all object file(s) and create final executable file!
}

int compileString(char *filename) {
    lexerInit();
    lexerParse();
    lexerFree();
    return EXIT_SUCCESS;
}

int compileFile(char *filename) {
    char *input = fileReads(filename);
    compileString(input);
//     TODO: free
    return EXIT_SUCCESS;
}

int compile(Args *args, ErrorsContainer *errors) {
    if (args->input_file_count == 0) return EXIT_FAILURE;

    int res = EXIT_SUCCESS;
    for (int i = 0; i < args->input_file_count; i++) {
        printf("-->%s\n", args->input_files[i]);
        int res_now = compileFile(args->input_files[i]);

        if (res_now != EXIT_SUCCESS) {
            res = res_now;
            break; // TODO: stop to parse other files or no?
        }
    }

    link(args, errors);

    return EXIT_SUCCESS;
}
