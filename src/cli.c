#include "cli.h"

/**
 * @brief Initialize the CLI object
 * 
 * @param argc 
 * @param argv 
 * 
 * @return cli_t* 
 */
cli_t* cli_init(int argc, char** argv)
{
    cli_t* cli = (cli_t*)malloc(sizeof(CLI));
    cli->argc = argc;
    cli->argv = argv;
}

/**
 * @brief Run the CLI object
 * 
 * @param cli 
 * 
 * @return int 
 */
int cli_run(cli_t* cli)
{
    return 0;
}

/**
 * @brief Free the CLI object
 * 
 * @param cli 
 */
void cli_free(cli_t* cli)
{
    free(cli);
}
