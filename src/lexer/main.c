#include <stdio.h>
#include <stdlib.h>
#include "../builtins/file.h"
#include "lexer.h"

int main(int argc, char** argv)
{
    if (argc == 1) {
        printf("Please run ./one_lexer input output\n");
        return 1;
    } else if (argc == 2) {
        printf("Please run ./one_lexer %s output", argv[1]);
        return 1;
    }

    printf("INPUT: %s\n", argv[1]);
    printf("OUTPUT: %s\n", argv[2]);

    if (!file_exists(argv[1])) {
        printf("Error: unable to open a file!\n");
        return 1;
    }

    char* data = file_reads(argv[1]);
    if (data == NULL) {
        printf("Error: unable to read a file!\n");
        return 1;
    }

    printf("DATA: %s\n", data);

    lexer_t* lexer = lexer_init(data);
    lexer = lexer_scan_tokens(lexer);

    int tokens_count = array_count(lexer->tokens);
    printf("NUMBER OF TOKENS: %d\n", tokens_count);
    for (int i = 0; i < tokens_count; i++) {
        lexer_token_t* current_token = array_getat(lexer->tokens, i);
        if (current_token->value != NULL) printf("   [%d:%d]-[%d:%d] TOKEN: %s (%s)\n", current_token->location->start_line, current_token->location->start_column, current_token->location->end_line, current_token->location->end_column, token_type_name(current_token->type), current_token->value);
        else printf("   [%d:%d]-[%d:%d] TOKEN: %s\n", current_token->location->start_line, current_token->location->start_column, current_token->location->end_line, current_token->location->end_column, token_type_name(current_token->type));
    }

    return 0;
}
