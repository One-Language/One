#include <stdio.h>
#include <stdlib.h>

#include "lexer.h"

Lexer* lexer_new(char* file) {
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->input = NULL;
    lexer->input_size = 0;
    lexer->file = file;
    lexer->file_dir = NULL;
    lexer->tokens = NULL;
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
