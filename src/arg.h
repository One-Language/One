/**
 File: arg.h
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "one.h"

typedef struct {
	bool help;
	bool version;
	bool debug;

	char** input_files;

    int argc;
    const char* const* argv;
    const char* const* env;
} Args;

void parseArgs(int argc, const char* const* argv, const char* const* env, Args* args);
