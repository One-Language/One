#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
} Token;

typedef struct {
    char* input;
    int input_size;

    char* file;
    char* file_dir;

    Token** tokens;
    int token_size;
} Lexer;

Lexer* lexer_new(char* file, char* data);

int lexer_run(Lexer* lexer);

void lexer_free(Lexer* lexer);
