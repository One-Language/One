//
// Created by max on 6/9/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "one.h"
#include "array.h"
#include "interpret.h"

#include "argument.h"

void argument_init(Arguments *args)
{
}

ArgumentType argument_type(char *value)
{
	if (value[0] == '-')
	{
		if (strcmp(value, "-h") == 0 || strcmp(value, "--help") == 0 ||
			 strcmp(value, "help"))
			return ARGUMENT_HELP;
		else if (strcmp(value, "-g") == 0 ||
			 strcmp(value, "--debug") == 0)
			return ARGUMENT_DEBUG;
		else if (strcmp(value, "-v") == 0 ||
			 strcmp(value, "--version") == 0)
			return ARGUMENT_VERSION;
		else
			return ARGUMENT_ERROR;
	}
	else
		return ARGUMENT_FILE;
}

void argument_parse(int argc, char **argv, char **env, Arguments *args)
{
	args->argv = argv;

	Array files;
	array_init(&files);

	ArgumentType type;
	for (int i = 1; i < argc; i++)
	{
		type = argument_type(argv[i]);
		if (type == ARGUMENT_HELP)
		{
			args->help = true;
		}
		else if (type == ARGUMENT_DEBUG)
		{
			args->debug = true;
		}
		else if (type == ARGUMENT_VERSION)
		{
			args->version = true;
		}
		else if (type == ARGUMENT_ERROR)
		{
			// Todo: Error
		}
		else if (type == ARGUMENT_FILE)
		{
			array_push(&files, (void *)argv[i]);
		}
	}

	args->input_files = (char **)files.data;
	args->input_files_count = files.count;

	array_free(&files);
}

void argument_free(Arguments *args)
{
	//     free argc
	for (int i = 0; i < args->argc; i++)
		free(args->argv[i]);

	//     free input_files
	//     TODO
	//    for (int i = 0; i < args->input_files_count; i++) {
	//        printf("free %d\n", i);
	//        free(args->input_files[i]);
	//    }

	//     free env
	//     TODO
}

void argument_help(FILE *file, Arguments *args)
{
	fprintf(file, "Usage: %s [options] file...\n", args->argv[0]);
	fprintf(file, "Options:\n");
	fprintf(file, "    -h, --help                Print out this help text.\n");
	fprintf(file, "    -g, --debug               Include debug information in "
				  "the build.\n");
	fprintf(
		 file,
		 "    -o, --output FILE         Output the result to the given file.\n");
	fprintf(file,
		 "    -v, --version             Print out the compiler version\n");
	fprintf(file, "\n");
}

void argument_version(FILE *file, Arguments *args)
{
	fprintf(file, "  _        _ \n");
	fprintf(file, " / \\ |\\ | |_    Max Base\n");
	fprintf(file, " \\_/ | \\| |_    Copyright 2021\n");
	fprintf(file, "\n");
	fprintf(file, ONE_VERSION);
}

int argument_run_files(Arguments *args)
{
	int ret;
	for (int i = 0; i < args->input_files_count; i++)
	{
		ret = interpret_file(args->input_files[i]);
		if (ret != EXIT_SUCCESS)
		{
			break;
		}
	}
	return ret;
}

int argument_run(Arguments *args)
{
	int ret = EXIT_SUCCESS;

	if (args->help)
	{
		argument_help(stderr, args);
	}
	else if (args->version)
	{
		argument_version(stderr, args);
	}
	else if (args->input_files_count > 0)
	{
		argument_run_files(args);
	}
	else
	{
		argument_help(stderr, args);
	}

	return ret;
}