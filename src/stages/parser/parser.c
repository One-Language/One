//
// Created by Max on 9/4/2022.
//

#include "parser.h"
#include "../lexer/lexer.h"

Parser* parser_init(Lexer* lexer)
{
    Parser* parser = (Parser*)malloc(sizeof(Parser));
    parser->lexer = lexer;

    parser->tokens = lexer->tokens->data;
    parser->token_count = lexer->tokens->count;

    parser->ast = (AstProgram*)malloc(sizeof(AstProgram));
    parser->ast->statements = malloc(sizeof(Array));
    array_init(parser->ast->statements);
    parser->ast->errors = malloc(sizeof(Array));
    array_init(parser->ast->errors);

    return parser;
}

AstStatement* statement_make(char* name)
{
    AstStatement* statement = (AstStatement*)malloc(sizeof(AstStatement));
    statement->name = name;

    return statement;
}

void advance(Parser* parser)
{
    *parser->tokens++;
}

void previus(Parser* parser)
{
    *parser->tokens--;
}

AstStatement* parser_statement(Parser* parser)
{
    printf("Parser Token: %s\n", token_type_name((*parser->tokens)->type));

    switch ((*parser->tokens)->type)
    {
        case TOKEN_IDENTIFIER: {
            AstStatement* stmt = statement_make((*parser->tokens)->value);
            advance(parser); // eat identifier
            return stmt;
        } break;
        default: {
            printf("Unexpected token: %s\n", token_type_name((*parser->tokens)->type));
            advance(parser);
            return NULL;
        } break;
    }
}

Array* parser_statements(Parser* parser)
{
    Array* statements = malloc(sizeof(Array));
    array_init(statements);

    printf("loop started inside parser_statements\n");
    while ((*parser->tokens)->type != TOKEN_EOF)
    {
        AstStatement* statement = parser_statement(parser);
        printf("parser_statement finished inside loop\n");
        if (statement != NULL)
        {
            printf("statement != NULL\n");
            array_push(statements, statement);
        }
    }
    printf("loop finished inside parser_statements\n");

    return statements;
}

void parser_parse(Parser* parser)
{
    printf("parser_parse\n");

    parser->ast->statements = (Array*)parser_statements(parser);

    printf("parser_parse finished\n");
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
