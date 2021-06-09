//
// Created by max on 6/9/21.
//

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
		ret = interpret_source(line);
	}

	return ret;
}