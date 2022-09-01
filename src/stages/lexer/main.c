#include "lexer.h"

int main(int argc, char** argv) {
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
    Token** tokens = lexer_lex(lexer);

    return 0;
}
