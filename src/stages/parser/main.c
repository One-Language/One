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
    if (lexer->errors->count > 0) {
        printf("Lexer errors: %d\n", lexer->errors->count);
        for (int i = 0; i < lexer->errors->count; i++) {
            Error* error = (Error*)lexer->errors->data[i];
            printf("Error: %s\n", error->message);
        }
        return 1;
    }
    sds xml = lexer_trace(lexer);
    printf("XML:\n%s\n", xml);
    sdsfree(xml);

    ////////////////////////////////////

    Parser* parser = parser_init(lexer);
    parser_parse(parser);
    if (parser->errors->count > 0) {
        printf("Parser errors: %d\n", parser->errors->count);
        for (int i = 0; i < parser->errors->count; i++) {
            Error* error = (Error*)parser->errors->data[i];
            printf("Error: %s\n", error->message);
        }
        return 1;
    }
    xml = parser_trace(parser);
    printf("XML:\n%s\n", xml);
    sdsfree(xml);

    parser_free(parser);

    return 0;
}