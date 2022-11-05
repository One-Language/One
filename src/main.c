#include <stdio.h>
#include <stdlib.h>

#include "utility/file.h"
#include "utility/cli.h"

int main(int argc, char** argv) {
    return cli_parse(argc, argv);
}
