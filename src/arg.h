/**
 File: arg.h
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "one.h"

#ifndef _ARG_H_
#define _ARG_H_

typedef struct {
	bool help;
	bool version;
	bool debug;

	char** input_files;

    int argc;
    char** argv;
    char** env;
} Args;

void parseArgs(int argc, char** argv, char** env, Args* args);

#endif
