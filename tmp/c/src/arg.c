/**
 File: arg.c
  _        _
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "arg.h"

const Args default_args = {
	 .help = false,
	 .version = false,
	 .debug = false,

	 .input_files = NULL,

	 .argc = 0,
	 .argv = NULL,
	 .env = NULL,
};

void parseArgs(int argc, char **argv, char **env, Args *args)
{
	args->argc = argc;
	args->argv = argv;
	args->env = env;

	*args = default_args;
	args->input_files = vector_create();

	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
			{
				args->help = true;
			}
			else if (strcmp(argv[i], "-v") == 0 ||
				 strcmp(argv[i], "--version") == 0)
			{
				args->version = true;
			}
			else if (strcmp(argv[i], "-g") == 0 ||
				 strcmp(argv[i], "--debug") == 0)
			{
				args->debug = true;
			}
		}
		else
		{
			vector_add(&args->input_files, argv[i]);
		}
	}
}
