//
// Created by max on 6/9/21.
//

#ifndef ONE_ARG_H
#define ONE_ARG_H

#include <stdbool.h>

typedef struct
{
	bool help;
	bool version;
	bool debug;

	char **input_files;
	int input_files_count;

	int argc;
	char **argv;
	char **env;
} Arguments;

typedef enum
{
	ARGUMENT_HELP,
	ARGUMENT_VERSION,
	ARGUMENT_DEBUG,
	ARGUMENT_FILE,
	ARGUMENT_ERROR,
} ArgumentType;

void argument_init(Arguments *args);

ArgumentType argument_type(char *value);

void argument_parse(int argc, char **argv, char **env, Arguments *args);

void argument_free(Arguments *args);

void argument_help(FILE *file, Arguments *args);

void argument_version(FILE *file, Arguments *args);

int argument_run_files(Arguments* args);

int argument_run(Arguments *args);

#endif //ONE_ARG_H
