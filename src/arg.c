/**
 The One Programming Language

 File: arg.c
  _        _
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "error.h"
#include "arg.h"
#include "one.h"

void ArgsInit(Args* args)
{

}

void ArgsParse(int argc, char** argv, char** env, Args* args, ErrorsContainer* errors)
{
  args->argv = argv;
}

void ArgsFree(Args* args)
{

}

void ArgsHelp(FILE* file, Args* args)
{
  fprintf(file, "Usage: %s [options] file...\n", args->argv[0]);
  fprintf(file, "Options:\n");
  fprintf(file, "    -h, --help                Print out this help text.\n");
  fprintf(file, "    -g, --debug               Include debug information in the build.\n");
  fprintf(file, "    -o, --output FILE         Output the result to the given file.\n");
  fprintf(file, "    -v, --version             Print out the compiler version\n");
}

void ArgsVersion(FILE* file, Args* args)
{
  fprintf(file, "  _        _ \n");
  fprintf(file, " / \\ |\\ | |_    Author: Max Base\n");
  fprintf(file, " \\_/ | \\| |_    Copyright 2021\n");
  fprintf(file, "\n");
  fprintf(file, ONE_VERSION);

}
