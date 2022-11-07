#include "utility/file.h"
#include "utility/cli.h"

int main(int argc, char** argv) {
    cli_args* arguments = malloc(sizeof(cli_args));
    arguments->argc = argc;
    arguments->argv = argv;
<<<<<<< HEAD

=======
>>>>>>> 4bba61f59a96590c2d3c6ec13246954197f7e842
    return cli_parse(arguments);
}
