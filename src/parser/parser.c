#include "parser.h"

Parser* parser_new(Lexer* lexer) {
    Parser* parser = malloc(sizeof(Parser));
    parser->lexer = lexer;
    parser->ast = ast_new();
    return parser;
}

void parser_run(Parser* parser) {
    printf("Parser: %d tokens\n", parser->lexer->tokens->size);
}

void parser_free(Parser* parser) {
    free(parser);
}
