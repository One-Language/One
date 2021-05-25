/**
 The One Programming Language

 File: one.c
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "error.h"

int main(int argc, char** argv, char** env)
{
  int ret = EXIT_SUCCESS;

  ErrorsContainer errors;
  ErrorsInit(&errors);

  Args args;
  ArgsInit(&args);
  ArgsParse(&args);

  if(args.help) {
    ArgsHelp(stderr, &args);
  } else if(args.version) {

  } else if(args.input_file_count > 0) {
    ret = compile(&args, &erors);
  }

  ErrorsPrint(stderr, &erors);

  ArgsFree(&args);
  ErrorsFree(&errors);

  return ret;
}
