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

<<<<<<< HEAD
=======
void cli_help(cli_args* arguments);

int cli_run_file(cli_options* options);

>>>>>>> 4bba61f59a96590c2d3c6ec13246954197f7e842
int cli_parse(cli_args* arguments);
