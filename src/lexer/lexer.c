#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lexer.h"
#include "../utility/file.h"

// #define LEXER_CURRENT_CHAR(lexer) (lexer->buffer[lexer->offset])
// #define LEXER_NEXT_CHAR(lexer) (lexer->buffer[lexer->offset + 1])

// #define LEXER_INCREMENT_INDEX(lexer) (lexer->offset++)
// #define LEXER_DECREMENT_INDEX(lexer) (lexer->offset--)

Lexer* lexer_new(char* file, char* data) {
    Lexer* lexer = malloc(sizeof(Lexer));

    lexer->file = file;
    lexer->file_dir = get_file_dir(file);

    lexer->buffer = data != NULL ? data : file_reads(file);
    lexer->length = strlen(lexer->buffer);
    lexer->offset = 0;

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
    char c = lexer->buffer[lexer->offset];
    printf("Current: %c\n", c);

    switch (c) {
        case ' ':
        case '\t':
        case '\r':
        case '\n':
            lexer->offset++;
            break;
        case '+':
            lexer->offset++;
            break;
        case '-':
            lexer->offset++;
            break;
        case '*':
            lexer->offset++;
            break;
        case '/':
            lexer->offset++;
            break;
        case '%':
            lexer->offset++;
            break;
        case '^':
            lexer->offset++;
            break;
        case '=':
            lexer->offset++;
            break;
        case '!':
            lexer->offset++;
            break;
        case '<':
            lexer->offset++;
            break;
        case '>':
            lexer->offset++;
            break;
        case '&':
            lexer->offset++;
            break;
        case '|':
            lexer->offset++;
            break;
        case '~':
            lexer->offset++;
            break;
        case '(':
            lexer->offset++;
            break;
        case ')':
            lexer->offset++;
            break;
        case '[':
            lexer->offset++;
            break;
        case ']':
            lexer->offset++;
            break;
        case '{':
            lexer->offset++;
            break;
        case '}':
            lexer->offset++;
            break;
        case ',':
            lexer->offset++;
            break;
        case '.':
            lexer->offset++;
            break;
        case ':':
            lexer->offset++;
            break;
        case ';':
            lexer->offset++;
            break;
        case '?':
            lexer->offset++;
            break;
        case '#':
            lexer->offset++;
            break;
        case '\'':
            lexer->offset++;
            break;
        case '"':
            lexer->offset++;
            break;
        default:
            printf("Warning: Unknown character '%c' at %d", c, lexer->offset);
            lexer->offset++;
            break;
    }
    lexer->offset++;
}

void lexer_free(Lexer* lexer) {
    // free input
    // free tokens
    // free lexer
}
