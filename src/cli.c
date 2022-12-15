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
    cli->options = cli_options_init();
    return cli;
}

/**
 * @brief Initialize the CLI options object
 * 
 * @param void
 * 
 * @return cli_options_t* 
 */
cli_options_t* cli_options_init()
{
    cli_options_t* options = (cli_options_t*)malloc(sizeof(cli_options_t));
    options->output = NULL;
    options->file = NULL;
    options->output = NULL;
    return options;
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

cli_t* cli_parse(cli_t* cli)
{
    // If no argummets are passed
    if (cli->argc == 1) {
        cli->options->command = CLI_HELP;
        return cli;
    }

    for (int i = 1; i < cli->argc; i++) {
        if (strcmp(cli->argv[i], "-o") == 0 || strcmp(cli->argv[i], "--output") == 0) {
            if (i + 1 < cli->argc) {
                cli->options->output = cli->argv[i + 1];
                i++;
            } else {
                cli->options->command = CLI_UNKNOWN;
                cli->options->error = malloc(sizeof(char) * 100);
                sprintf_s(cli->options->error, 100, "Error: -o or --output option requires one argument.\n");
            }
        } else if (strcmp(cli->argv[i], "-p") == 0 || strcmp(cli->argv[i], "--parse") == 0) {
            if (cli->options->command == CLI_UNKNOWN) continue;

            cli->options->command = CLI_PARSE;
        } else if (strcmp(cli->argv[i], "-l") == 0 || strcmp(cli->argv[i], "--lex") == 0) {
            if (cli->options->command == CLI_UNKNOWN) continue;

            cli->options->command = CLI_LEX;
        } else {
            cli->options->file = cli->argv[i];
        }
    }

    return cli;
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
    // if (cli->)
    if (cli->argc <= 1) {
        cli_print_help(cli);
        return 0;
    } else {
        for (int i = 1; i < cli->argc; i++) {
            if (strcmp(cli->argv[i], "-h") == 0 || strcmp(cli->argv[i], "--help") == 0) {
                cli_print_help(cli);
                return 0;
            } else if (strcmp(cli->argv[i], "-v") == 0 || strcmp(cli->argv[i], "--version") == 0) {
                printf("One Programming Language v0.0.1\n");
                return 0;
            } else if (strcmp(cli->argv[i], "-o") == 0 || strcmp(cli->argv[i], "--output") == 0) {
                if (i + 1 < cli->argc) {
                    i++;
                    printf("Output file: %s\n", cli->argv[i]);
                } else {
                    printf("Error: No output file specified\n");
                    return 1;
                }
            } else if (strcmp(cli->argv[i], "-p") == 0 || strcmp(cli->argv[i], "--parse") == 0) {
                if (i + 1 < cli->argc) {
                    i++;
                    printf("Parse file: %s\n", cli->argv[i]);
                } else {
                    printf("Error: No parse file specified\n");
                    return 1;
                }
            } else if (strcmp(cli->argv[i], "-l") == 0 || strcmp(cli->argv[i], "--lex") == 0) {
                if (i + 1 < cli->argc) {
                    i++;
                    printf("Lex file: %s\n", cli->argv[i]);
                } else {
                    printf("Error: No lex file specified\n");
                    return 1;
                }
            } else {
                printf("Error: Unknown option: %s\n", cli->argv[i]);
                return 1;
            }
        }
    }

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
