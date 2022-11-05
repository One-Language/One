#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "../utility/file.h"

#define LEXER_CURRENT_CHAR(lexer) (lexer->input[lexer->index])
#define LEXER_NEXT_CHAR(lexer) (lexer->input[lexer->index + 1])

#define LEXER_INCREMENT_INDEX(lexer) (lexer->index++)
#define LEXER_DECREMENT_INDEX(lexer) (lexer->index--)

Lexer* lexer_new(char* file, char* data) {
    Lexer* lexer = malloc(sizeof(Lexer));

    lexer->file = file;
    lexer->file_dir = get_file_dir(file);

    lexer->buffer = data != NULL ? data : file_reads(file);
    lexer->length = strlen(lexer->buffer);

    lexer->tokens = malloc(sizeof(Token*));
    lexer->token_size = 0;

    return lexer;
}

int lexer_run(Lexer* lexer) {
    printf("Lexer: %s\n", lexer->file);
    printf("Input: %s\n", lexer->buffer);
    printf("Input Size: %d\n", lexer->length);

    if (lexer->length == 0) return 1;

    while (lexer->offset < lexer->length) {
        lexer_next(lexer);
    }
    return 0;
}

void lexer_next(Lexer* lexer) {

}

void lexer_free(Lexer* lexer) {
    // free input
    // free tokens
    // free lexer
}
