/**
 The One Programming Language
 File: cli.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#ifndef _CLI_H_
#define _CLI_H_

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#include <string.h> // strcmp

typedef enum {
    CLI_HELP,
    CLI_VERSION,
    CLI_COMPILE,
    CLI_LEX,
    CLI_PARSE,
    // CLI_RUN,
    // CLI_TEST,
    // CLI_FORMAT,
    // CLI_LINT,
    // CLI_DOC,
    // CLI_INSTALL,
    // CLI_UNINSTALL,
    // CLI_CONFIG,
    CLI_UNKNOWN
} cli_command_t;

typedef struct {
    cli_command_t command;
    char* file;
    char* output;
    char* error;
    // char* target;
    // char* arch;
    // char* os;
    // char* compiler;
    // char* linker;
    // char* flags;
    // char* libs;
    // char* libpath;
    // char* includepath;
    // char* defines;
    // char* run;
    // char* test;
    // char* format;
    // char* lint;
    // char* doc;
    // char* install;
    // char* uninstall;
    // char* config;
} cli_options_t;

typedef struct {
    int argc;
    char** argv;
    cli_options_t* options;
} cli_t;

/**
 * @brief Initialize the CLI object
 * 
 * @param int argc
 * @param char** argv
 * 
 * @return cli_t* 
 */
cli_t* cli_init(int argc, char** argv);


/**
 * @brief Initialize the CLI options object
 * 
 * @param void
 * 
 * @return cli_options_t* 
 */
cli_options_t* cli_options_init();

/**
 * @brief Run the CLI object
 * 
 * @param cli_t* cli
 * 
 * @return int 
 */
int cli_run(cli_t* cli);

/**
 * @brief Free the CLI object
 * 
 * @param cli_t* cli
 * 
 * @return void
 */
void cli_free(cli_t* cli);

#endif
