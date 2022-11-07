#ifndef _ONE_UTILITY_CLI_H_
#define _ONE_UTILITY_CLI_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "file.h"
#include "../lexer/lexer.h"

typedef struct {
    int argc;
    char** argv;
} cli_args;

typedef struct {
    char* data;

    char* input;
    char* input_dir;

    char* output;
    char* output_dir;

    bool is_debug;
    bool is_raw_input;
} cli_options;

void cli_help(cli_args* arguments);

int cli_run_file(cli_options* options);

int cli_parse(cli_args* arguments);

#endif
