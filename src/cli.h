/**
 The One Programming Language
 File: cli.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#ifndef _CLI_H_
#define _CLI_H_

typedef struct {
    int argc;
    char** argv;
} cli_t;

/**
 * @brief Initialize the CLI object
 * 
 * @param argc 
 * @param argv 
 * 
 * @return cli_t* 
 */
cli_t* cli_init(int argc, char** argv);

/**
 * @brief Run the CLI object
 * 
 * @param cli 
 * 
 * @return int 
 */
int cli_run(cli_t* cli);

/**
 * @brief Free the CLI object
 * 
 * @param cli 
 */
void cli_free(cli_t* cli);

#endif
