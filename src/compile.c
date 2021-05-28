/**
 The One Programming Language

 File: compile.c
  _        _
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "compile.h"
#include "arg.h"
#include "error.h"

int compile(Args *arg, ErrorsContainer *errors) {
  for (int i = 0; i < arg->input_file_count; i++) {
    printf("-->%s\n", arg->input_files[i]);
  }
  return EXIT_SUCCESS;
}
