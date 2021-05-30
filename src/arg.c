/**
 The One Programming Language

 File: arg.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "token.h"
#include "lexer.h"
#include "array.h"
#include "error.h"
#include "one.h"

#include "arg.h"

void ArgsInit(Args *args) {
}

void ArgsParse(int argc, char **argv, char **env, Args *args, ErrorsContainer *errors) {
    args->argv = argv;

    Array files;
    arrayInit(&files);

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0 ||
                strcmp(argv[i], "help")) {
                args->help = true;
            } else if (strcmp(argv[i], "-g") == 0 ||
                       strcmp(argv[i], "--debug") == 0) {
                args->debug = true;
            } else if (strcmp(argv[i], "-v") == 0 ||
                       strcmp(argv[i], "--version") == 0) {
                args->version = true;
            }
        } else {
            arrayPush(&files, (void *) argv[i]);
        }
    }

    args->input_file_count = files.count;
    args->input_files = (char **) files.data;
}

void ArgsFree(Args *args) {
    //     free argc
    for (int i = 0; i < args->argc; i++)
        free(args->argv[i]);

    //     free input_files
    //     TODO
    //    for (int i = 0; i < args->input_file_count; i++) {
    //        printf("free %d\n", i);
    //        free(args->input_files[i]);
    //    }

    //     free env
    //     TODO
}

void ArgsHelp(FILE *file, Args *args) {
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

void ArgsVersion(FILE *file, Args *args) {
    fprintf(file, "  _        _ \n");
    fprintf(file, " / \\ |\\ | |_    Max Base\n");
    fprintf(file, " \\_/ | \\| |_    Copyright 2021\n");
    fprintf(file, "\n");
    fprintf(file, ONE_VERSION);
}
