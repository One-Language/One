#include "parser.h"

Parser* parser_new(Lexer* lexer) {
    Parser* parser = malloc(sizeof(Parser));
    parser->lexer = lexer;
    parser->ast = ast_new();
    return parser;
}

int parser_run(Parser* parser) {
    if (parser->lexer->tokens->size == 0) return 1;

    // TODO

    return 0; 
}

void parser_debug(Parser* parser) {
    printf("================= Parser (%d tokens) =================\n", parser->lexer->tokens->size);
}

void parser_free(Parser* parser) {
    free(parser);
}
