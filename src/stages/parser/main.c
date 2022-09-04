//
// Created by Max on 9/4/2022.
//

#include "parser.h"
#include "../lexer/lexer.h"

int main()
{
    char *source = file_reads("../../input.one");

    printf("Source: %s\n", source);

    Lexer* lexer = lexer_init(source);
    lexer_tokenizer(lexer);

    sds xml = lexer_trace(lexer);
    printf("XML:\n%s\n", xml);
    sdsfree(xml);
    ////////////////////////////////////
    Parser* parser = parser_init(lexer);
    parser_parse(parser);

    xml = parser_trace(parser);
    printf("XML:\n%s\n", xml);
    sdsfree(xml);

    return 0;
}