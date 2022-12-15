/**
 The One Programming Language
 File: cli.c
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#include "cli.h"

/**
 * @brief Initialize the CLI object
 * 
 * @param int argc
 * @param char** argv
 * 
 * @return cli_t* 
 */
cli_t* cli_init(int argc, char** argv)
{
    cli_t* cli = (cli_t*)malloc(sizeof(cli_t));
    cli->argc = argc;
    cli->argv = argv;
}

/**
 * @brief Print the help message
 * 
 * @param cli_t* cli
 * 
 * @return void
 */
void cli_print_help(cli_t* cli)
{
    printf("Usage: one [options] [file]\n");
    printf("Options:\n");
    printf("  -h, --help\t\tPrint this help message\n");
    printf("  -v, --version\t\tPrint the version of the compiler\n");
    printf("  -o, --output\t\tSpecify the output file\n");
    // printf("  -c, --compile\t\tCompile the source code to binary\n");
    // printf("  -r, --run\t\tRun the source code\n");
    // printf("  -d, --debug\t\tDebug the source code\n");
    // printf("  -t, --test\t\tTest the source code\n");
    // printf("  -l, --lint\t\tLint the source code\n");
    // printf("  -f, --format\t\tFormat the source code\n");
    // printf("  -s, --syntax\t\tSyntax the source code\n");
    printf("  -p, --lex\t\tLex the source code\n");
    printf("  -p, --parse\t\tParse the source code\n");
    // printf("  -a, --ast\t\tPrint the AST of the source code\n");
    // printf("  -i, --ir\t\tPrint the IR of the source code\n");
    // printf("  -b, --bytecode\t\tPrint the Bytecode of the source code\n");
    // printf("  -e, --execute\t\tExecute the source code\n");
    // printf("  -g, --generate\t\tGenerate the source code\n");
    // printf("  -w, --watch\t\tWatch the source code\n");
    // printf("  -x, --execute\t\tExecute the source code\n");
    // printf("  -y, --yaml\t\tPrint the YAML of the source code\n");
    // printf("  -j, --json\t\tPrint the JSON of the source code\n");
    printf("\n");
}

/**
 * @brief Run the CLI object
 * 
 * @param cli_t* cli
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
 * @param cli_t* cli
 * 
 * @return void
 */
void cli_free(cli_t* cli)
{
    free(cli);
}
