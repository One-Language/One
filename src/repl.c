/**
 The One Programming Language

 File: repl.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include <stdio.h>
#include <stdlib.h>

#include "interpret.h"

#include "repl.h"

static int repl()
{
	int ret;
	char line[2048];

	for (;;)
	{
		printf("> ");
		if (!fgets(line, sizeof line, stdin))
		{
			printf("\n");
			break;
		}
		ret = interpret_source(line, NULL);
	}

	return ret;
}
