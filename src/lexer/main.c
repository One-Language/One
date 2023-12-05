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

        printf("   [%d:%d]-[%d:%d] TOKEN: %s", current_token->location->start_line, current_token->location->start_column, current_token->location->end_line, current_token->location->end_column, token_type_name(current_token->type));

        if (current_token->value != NULL) printf("(%s)\n", current_token->value);
        else if (current_token->ch != '\0') printf("(%c)\n", current_token->ch);
        else if (current_token->op ) printf("(%c)\n", op_type_name(current_token->op));
        else printf("\n");
    }

    return 0;
}
