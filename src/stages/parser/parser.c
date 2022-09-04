//
// Created by Max on 9/4/2022.
//

#include "parser.h"
#include "../lexer/lexer.h"

Parser* parser_init(Lexer* lexer)
{
    Parser* parser = (Parser*)malloc(sizeof(Parser));
    parser->lexer = lexer;
    parser->ast = (AstProgram*)malloc(sizeof(AstProgram));
    parser->ast->statements = malloc(sizeof(Array));
    array_init(parser->ast->statements);

    return parser;
}

AstStatement* statement_make(char* name)
{
    AstStatement* statement = (AstStatement*)malloc(sizeof(AstStatement));
    statement->name = name;

    return statement;
}

void parser_parse(Parser* parser)
{
    printf("parser_parse\n");

    Token* token = parser->lexer->tokens->data[0];
    printf("Parser Token: %s\n", token_type_name(token->type));

    AstStatement* stmt = statement_make(token->value);
    array_push(parser->ast->statements, stmt);
}

char* parser_trace(Parser* parser)
{
    printf("parser_trace\n");
    sds temp = sdsnew("<Parser>\n");

    for (int i = 0; i < parser->ast->statements->count; i++)
    {
        AstStatement* stmt = parser->ast->statements->data[i];
        temp = sdscatprintf(temp, "\t<Statement name=\"%s\" />\n", stmt->name);
    }

    temp = sdscat(temp, "</Parser>");

    return temp;
}
