#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "cli.h"
#include "file.h"
#include "../lexer/lexer.h"

void cli_help(cli_args* arguments) {
    printf("Usage: %s [options] [file]\n", arguments->argv[0]);
    printf("\nOptions:\n");
    printf("  -h, --help\t\tPrint this help message\n");
    printf("  -v, --version\t\tPrint version information\n");
    printf("  -o, --output\t\tSpecify output file\n");
    printf("  -i, --input\t\tSpecify input file\n");
    printf("  -d, --debug\t\tEnable debug mode\n");
    printf("\n");
}

int cli_run_file(cli_options* options) {
    Lexer* lexer;
    if (options->is_raw_input) {
        lexer = lexer_new(NULL, options->input);
    } else {
        char* data = file_reads(options->input);
        if (data == NULL) {
            printf("Error: Could not read file: %s\n", options->input);
            return 1;
        }
        lexer = lexer_new(options->input, data);
    }

    int result = lexer_run(lexer);

    // Parser* parser = parser_new(lexer);
    // parser_run(parser);

    // parser_free(parser);

    lexer_free(lexer);
    return result;
}

int cli_parse(cli_args* arguments) {
    cli_options* options = malloc(sizeof(cli_options));
    options->input = NULL;
    options->input_dir = NULL;
    options->output = NULL;
    options->output_dir = NULL;
    options->is_debug = false;
    options->is_raw_input = false;

    if (arguments->argc == 1) {
        cli_help(arguments);
        return 0;
    } else if (arguments->argc == 2) {
        if (strcmp(arguments->argv[1], "-h") == 0 || strcmp(arguments->argv[1], "--help") == 0) {
            cli_help(arguments);
            return 0;
        } else if (strcmp(arguments->argv[1], "-v") == 0 || strcmp(arguments->argv[1], "--version") == 0) {
            printf("Version 1.0.0\n");
            return 0;
        } else {
            options->input = arguments->argv[1];
            return cli_run_file(options);
        }
    } else {
        for (int i = 1; i < arguments->argc; i++) {
            if (strcmp(arguments->argv[i], "-r") == 0 || strcmp(arguments->argv[i], "--run") == 0) {
                options->input = arguments->argv[i + 1];
                options->is_raw_input = true;
                return cli_run_file(options);
            } else if (strcmp(arguments->argv[i], "-d") == 0 || strcmp(arguments->argv[i], "--debug") == 0) {
                options->is_debug = true;
            } else if (strcmp(arguments->argv[i], "-i") == 0 || strcmp(arguments->argv[i], "--input") == 0) {
                options->input = arguments->argv[i + 1];
                i++;
            } else if (strcmp(arguments->argv[i], "-o") == 0 || strcmp(arguments->argv[i], "--output") == 0) {
                options->output = arguments->argv[i + 1];
                i++;
            } else {
                options->input = arguments->argv[i];
            }
        }
        return cli_run_file(options);
    }
}
