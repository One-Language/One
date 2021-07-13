/**
 The One Programming Language

 File: argument.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "one.h"
#include "array.h"
#include "error.h"
#include "interpret.h"

#include "argument.h"

void argument_init(Arguments *args)
{
	debug("argument_init");
}

ArgumentType argument_type(char *value)
{
	debug("argument_type");

	if (value[0] == '-')
	{
		if (strcmp(value, "-h") == 0 || strcmp(value, "--help") == 0 ||
			 strcmp(value, "help") == 0)
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
	debug("argument_parse");

	debug("argument_parse: argc is %d", argc);

	args->argv = argv;

	Array files;
	array_init(&files);

	ArgumentType type;
	for (int i = 1; i < argc; i++)
	{
		type = argument_type(argv[i]);
		debug("argument_parse: argv[%d] is %s and type is %s", i, argv[i], argument_type_name(type));

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
			error_panic("Could not detect \"%s\" argument.", argv[i]);
			exit(64);
			// Todo: Error
		}
		else if (type == ARGUMENT_FILE)
		{
			array_push(&files, (void *)argv[i]);
		}
	}

	args->input_files = (char **)files.data;
	args->input_files_count = files.count;

	//	array_free(&files);
}

void argument_free(Arguments *args)
{
	debug("argument_free");

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
	debug("argument_help");

	fprintf(file, "Usage: %s [options] file...\n", args->argv[0]);
	fprintf(file, "\nOptions:\n");
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
	debug("argument_version");

	fprintf(file, "  _        _ \n");
	fprintf(file, " / \\ |\\ | |_    Max Base\n");
	fprintf(file, " \\_/ | \\| |_    Copyright 2021; One Language Contributors\n");
	fprintf(file, "\n Version: ");
	fprintf(file, ONE_VERSION);
	fprintf(file, "\n");
	fprintf(file, "\n");
}

int argument_run_files(Arguments *args)
{
	debug("argument_run_files");

	debug("argument_run_files: input_files_count is %d", args->input_files_count);

	int ret;
	for (int i = 0; i < args->input_files_count; i++)
	{
		debug("argument_run_files: Run input_files[%d]", i);
		debug("argument_run_files: input_files[%d] is %s", i, args->input_files[i]);

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
	debug("argument_run");

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

char *argument_type_name(ArgumentType type)
{
	debug("argument_type_name");

	switch (type)
	{
		case ARGUMENT_HELP:
			return "HELP";
		case ARGUMENT_DEBUG:
			return "DEBUG";
		case ARGUMENT_ERROR:
			return "ERROR";
		case ARGUMENT_FILE:
			return "FILE";
		case ARGUMENT_VERSION:
			return "VERSION";
		default:
			return "UNKNOWN";
	}
}
