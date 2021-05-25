/**
 The One Programming Language

 File: one.c
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

int main(int argc, char** argv, char** env)
{
  int ret = EXIT_SUCCESS;

  ErrorsContainer errors;
  ErrorsInit(&errors);

  Args args;
  ArgsInit(&args);
  ArgsParse(&args);


  return ret;
}
