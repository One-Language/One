#include <stdio.h>
#include <stdlib.h>
#include "../built-in/file.h"

int main(int argc, char** argv)
{
    if (argc == 1) {
        printf("Please run ./one_lexer input output\n");
        return 1;
    }
    else if (argc == 2) {
        printf("Please run ./one_lexer %s output", argv[1]);
        return 1;
    }

    printf("INPUT: %s\n", argv[1]);
    printf("OUTPUT: %s\n", argv[2]);

    if (!file_exists(argv[1])) {
        printf("Error: unable to open a file!\n");
        return 1;
    }

    char* data = file_reads(argv[1]);
    if (data == NULL) {
        printf("Error: unable to read a file!\n");
        return 1;
    }

    printf("DATA: %s\n", data);

    return 0;
}
