#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    // FILE* output = stdout;
    FILE* output = fopen("test.txt", "a");
    fprintf(output, "Hello World!\n");

    return 0;
}
