//
// Created by max on 6/9/21.
//

#include <stdio.h>

#include "interpret.h"

#include "repl.h"

static void repl()
{
	char line[2048];
	for (;;)
	{
		printf("> ");
		if (!fgets(line, sizeof line, stdin))
		{
			printf("\n");
			break;
		}
		interpret(line);
	}
}