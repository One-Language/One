#include "parser.h"
#include "../lexer/lexer.h"

int main(int argc, char** argv)
{
    char* data = "if else";
    lexer_t* lexer = lexer_run(data)
    printf("%s", lexer_log(lexer));

    printf("=======================\n");

    parser_t* parser = parser_init(lexer);

    parser_free(parser);

    return 0;
}
