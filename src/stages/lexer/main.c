//
// Created by Max on 9/4/2022.
//

#include "lexer.h"

int main()
{
    char *source = file_reads("../../input.one");

    printf("Source: %s\n", source);

    Lexer* lexer = lexer_init(source);
    lexer_tokenizer(lexer);

    str* xml = lexer_trace(lexer);
    printf("XML: %s\n", xml->value);

    return 0;
}