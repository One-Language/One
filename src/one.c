/**
 The One Programming Language

 File: one.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "repl.h"
#include "interpret.h"
#include "argument.h"

#include "one.h"

int main(int argc, char **argv, char **env)
{
	Arguments args;

	argument_init(&args);
	argument_parse(argc, argv, env, &args);
	int ret = argument_run(&args);
	argument_free(&args);

	return ret;
}
