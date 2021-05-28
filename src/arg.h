/**
 The One Programming Language

 File: arg.h
  _        _
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _ARG_H_
#define _ARG_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool help;
  bool version;
  bool debug;

  char **input_files;
  unsigned int input_file_count;

  int argc;
  char **argv;
  char **env;
} Args;

void ArgsInit(Args *);
void ArgsParse(int, char **, char **, Args *, ErrorsContainer *);
void ArgsFree(Args *);
void ArgsHelp(FILE *, Args *);
void ArgsVersion(FILE *, Args *);

#endif
