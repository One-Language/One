#include "parser.h"

parser_t* parser_init(lexer_t* lexer)
{
    parser_t* parser = malloc(sizeof(parser_t));
    if (parser == NULL) {
        printf("Error: Not enough memory to create a parser.");
        exit(74);
    }

    parser->lexer = lexer;
    // parser->ast = ast_init();

    return parser;
}

void parser_free(parser_t* parser)
{
    lexer_free(parser->lexer);
    free(parser->lexer);
}
