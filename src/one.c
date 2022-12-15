/**
 The One Programming Language
 File: one.c
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#include "one.h"
#include "cli.h"

/**
 * @brief Main entry point of the program
 * 
 * @param argc 
 * @param argv 
 * 
 * @return int 
 */
int main(int argc, char** argv)
{
    cli_t* cli = cli_init(argc, argv);
    cli_parse(cli);
    int res = cli_run(cli);
    cli_free(cli);

    return res;
}
