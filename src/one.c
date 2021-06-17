/**
 The One Programming Language

 File: one.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "repl.h"
#include "interpret.h"
#include "argument.h"
#include "error.h"

#include "one.h"

int main(int argc, char **argv, char **env)
{
	debug("main");

	Arguments args;

	argument_init(&args);
	argument_parse(argc, argv, env, &args);
	int ret = argument_run(&args);
	argument_free(&args);

	debug("main: return %d", ret);
	debug("main: end");

	return ret;
}
