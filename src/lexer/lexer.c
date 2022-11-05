#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "../utility/file.h"

Lexer* lexer_new(char* file, char* data) {
    Lexer* lexer = malloc(sizeof(Lexer));

    lexer->file = file;
    lexer->file_dir = get_file_dir(file);

    lexer->input = data != NULL ? data : file_reads(file);
    lexer->input_size = strlen(lexer->input);

    lexer->tokens = malloc(sizeof(Token*));
    lexer->token_size = 0;

    return lexer;
}

int lexer_run(Lexer* lexer) {
    return 0;
}

void lexer_free(Lexer* lexer) {
    // free input
    // free tokens
    // free lexer
}
