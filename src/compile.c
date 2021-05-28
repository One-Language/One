/**
 The One Programming Language

 File: compile.c
  _        _
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "error.h"
#include "arg.h"
#include "compile.h"

void link(Args* args, ErrorsContainer* errors)
{
    // TODO, link all object file(s) and create final executable file!
}

int compileString(char* filename)
{
    return EXIT_SUCCESS;
}

int compile(Args* args, ErrorsContainer* errors)
{
    if(args->input_file_count == 0) return EXIT_FAILURE;

    int res = EXIT_SUCCESS;
    for(int i=0;i<args->input_file_count;i++) {
        int res_now = compileString(args->input_files[i]);

        if (res_now != EXIT_SUCCESS) {
            res = res_now;
        }
        printf("-->%s\n", args->input_files[i]);
    }

    link(args, errors);

    return EXIT_SUCCESS;
}
