#include "utility/file.h"
#include "utility/cli.h"

int main(int argc, char** argv) {
    cli_args* arguments = malloc(sizeof(cli_args));
    arguments->argc = argc;
    arguments->argv = argv;

    return cli_parse(arguments);
}
