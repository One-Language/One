#include <stdio.h>
#include <stdlib.h>

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
    
    return 0;
}
