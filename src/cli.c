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
    options->file = NULL;
    options->output = stdout;
    options->is_json = false;
    return options;
}

/**
 * @brief Print the version of the compiler
 * 
 * @param cli_t* cli
 * 
 * @return void
 */
void cli_print_version(cli_t* cli)
{
    printf("One Programming Language v0.0.1\n");
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
    printf("  -j, --json\t\tPrint the JSON of main command\n");
    printf("\n");
}

/**
 * @brief Parse the CLI arguments
 * 
 * @param cli_t* cli
 * 
 * @return cli_t*
 */
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
                printf("Opening file '%s' for writing\n", cli->argv[i + 1]);
                cli->options->output = fopen(cli->argv[i + 1], "w");
                if (cli->options->output == NULL) {
                    cli->options->command = CLI_UNKNOWN;
                    cli->options->error = malloc(sizeof(char) * 100);
                    sprintf_s(cli->options->error, 100, "Error: cannot open file '%s' for writing.\n", cli->argv[i + 1]);
                }
                fprintf(cli->options->output, "Hello, world1!\n");
                fprintf(cli->options->output, "Hello, world2!\n");
                fprintf(cli->options->output, "Hello, world3!\n");
                i++;
            } else {
                cli->options->command = CLI_UNKNOWN;
                cli->options->error = malloc(sizeof(char) * 100);
                sprintf_s(cli->options->error, 100, "Error: -o or --output option requires one argument.\n");
            }
        } else if (strcmp(cli->argv[i], "-h") == 0 || strcmp(cli->argv[i], "--help") == 0) {
            if (cli->options->command == CLI_UNKNOWN) continue;

            cli->options->command = CLI_HELP;
        } else if (strcmp(cli->argv[i], "-v") == 0 || strcmp(cli->argv[i], "--version") == 0) {
            if (cli->options->command == CLI_UNKNOWN) continue;

            cli->options->command = CLI_VERSION;
        } else if (strcmp(cli->argv[i], "-p") == 0 || strcmp(cli->argv[i], "--parse") == 0) {
            if (cli->options->command == CLI_UNKNOWN) continue;

            cli->options->command = CLI_PARSE;
        } else if (strcmp(cli->argv[i], "-l") == 0 || strcmp(cli->argv[i], "--lex") == 0) {
            if (cli->options->command == CLI_UNKNOWN) continue;

            cli->options->command = CLI_LEX;
        } else if (strcmp(cli->argv[i], "-j") == 0 || strcmp(cli->argv[i], "--json") == 0) {
            cli->options->is_json = true;
        } else {
            cli->options->file = file_init(cli->argv[i]);
            file_read(cli->options->file);

            if (file_exists(cli->options->file) == false) {
                cli->options->command = CLI_UNKNOWN;
                cli->options->error = malloc(sizeof(char) * 100);
                sprintf_s(cli->options->error, 100, "Error: File '%s' does not exist.\n", cli->options->file->path);
            }
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
    switch (cli->options->command) {
        case CLI_HELP:
            cli_print_help(cli);
            break;

        case CLI_VERSION:
            cli_print_version(cli);
            break;

        case CLI_LEX:
            lexer_t* lex = lexer_init(cli->options->file);
            lexer_lex(lex);

            token_list_t* tokens = lexer_tokens(lex);

            if (cli->options->is_json) fprintf(cli->options->output, token_list_print_json(tokens));
            else fprintf(cli->options->output, token_list_print(tokens));

            // write hello world to the file
            fprintf(cli->options->output, "Hello World!\n");

            lexer_free(lex);
            break;

        case CLI_PARSE:
            printf("Parsing the source code...\n");
            break;

        case CLI_UNKNOWN:
        default:
            printf(cli->options->error == NULL ? "Unknown command\n" : cli->options->error);
            break;
    }

    // if (cli->options->output != NULL && cli->options->output != stdout) fclose(cli->options->output);

    // Default return value
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
