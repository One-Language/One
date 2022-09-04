/**
 The One Programming Language
 File: stages/lexer/main.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2020-2022; One Language Contributors
 **/

#include "lexer.h"

int main(int argc, char** argv)
{
    if (argc == 1) {
        printf("Usage: %s <filename>", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Could not open file %s", argv[1]);
        return 1;
    }

    Lexer* lexer = lexer_make(file);
    Token** tokens = lexer_tokenizer(lexer);
    if (tokens == NULL) {
        printf("Could not read source");
        return 1;
    }

    lexer_debug(lexer);

    printf("Done\n");
    return 0;
}
