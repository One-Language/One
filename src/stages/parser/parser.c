//
// Created by Max on 9/4/2022.
//

#include "parser.h"

Parser* parser_init(Lexer* lexer)
{
    printf("parser_init\n");
}

void parser_parse(Parser* parser)
{
    printf("parser_parse\n");
}

char* parser_trace(Parser* parser)
{
    printf("parser_trace\n");
    sds temp = sdsnew("<Parser>\n");

    temp = sdscat(temp, "</Parser>");

    return temp;
}
