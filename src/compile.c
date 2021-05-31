/**
 The One Programming Language

 File: compile.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "arg.h"
#include "file.h"
#include "token.h"
#include "lexer.h"
#include "parser.h"
#include "error.h"
#include "compile.h"
#include "parser.h"

void link(Args *args, ErrorsContainer *errors) {
    // TODO, link all object file(s) and create final executable file!
}

int compileFileString(char *filename, char *input, ErrorsContainer *errors) {
    Lexer *lex = lexerInit(filename, input, errors);
    int res = lexerCheck(lex, errors);
    lexerFree(lex);

    if(res == EXIT_SUCCESS) {
        Parser* pars = parserInit(lex, errors);
        res = parserCheck(pars, errors);
        parserFree(pars);

        if(res == EXIT_SUCCESS) {
//            Ast* ast = astInit(pars, errors);
//            res = astCheck(ast, errors);
//            astFree(ast);
        }
    }

    return res;
}

int compileString(char *input, ErrorsContainer *errors) {
    return compileFileString(NULL, input, errors);
}

int compileFile(char *filename, ErrorsContainer *errors) {
    char *input = fileReads(filename, errors);
    return compileFileString(filename, input, errors);
}

int compile(Args *args, ErrorsContainer *errors) {
    if (args->input_file_count == 0)
        return EXIT_FAILURE;

    int res = EXIT_SUCCESS;
    for (int i = 0; i < args->input_file_count; i++) {
        printf("-->%s\n", args->input_files[i]);
        int res_now = compileFile(args->input_files[i], errors);

        if (res_now != EXIT_SUCCESS) {
            res = res_now;
            break; // TODO: stop to parse other files or no?
        }
    }

    link(args, errors);

    return EXIT_SUCCESS;
}
