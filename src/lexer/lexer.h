#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

typedef struct {
} Token;

typedef struct {
    char* file;
    char* file_dir;

    char* buffer;
    uint32_t                    offset;         // current buffer offset (in bytes)
    // uint32_t                    position;       // current buffer position (in characters)
    uint32_t                    length;         // buffer length (in bytes)
    uint32_t                    lineno;         // line counter
    uint32_t                    colno;          // column counter

    Token** tokens;
    int token_size;
} Lexer;

Lexer* lexer_new(char* file, char* data);

int lexer_run(Lexer* lexer);

void lexer_next(Lexer* lexer);

void lexer_free(Lexer* lexer);
