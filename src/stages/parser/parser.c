//
// Created by Max on 9/4/2022.
//

#include "parser.h"
#include "../lexer/lexer.h"

Parser* parser_init(Lexer* lexer)
{
    Parser* parser = (Parser*)malloc(sizeof(Parser));
    parser->lexer = lexer;

    parser->tokens = (Token**) lexer->tokens->data;
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

bool peekFor(Parser* parser, TokenType type)
{
    if ((*parser->tokens)->type == type) return true;
    return false;
}

bool peekForNext(Parser* parser, TokenType type)
{
    if ((*parser->tokens + 1)->type == type) return true;
    return false;
}

bool peekForPrevius(Parser* parser, TokenType type)
{
    if ((*parser->tokens - 1)->type == type) return true;
    return false;
}

Token* expect(Parser* parser, TokenType type)
{
    if ((*parser->tokens)->type == type) {
        Token* t = *parser->tokens;
        advance(parser);
        return t;
    }
    else {
        printf("Parser Error: Expected %s, got %s", token_type_name(type), token_type_name((*parser->tokens)->type));
        return NULL;
//    array_push(parser->ast->errors, error_make("Expected token type %d, but got %d", type, (*parser->tokens)->type));
    }
}

AstBlock* parse_block(Parser* parser)
{
    AstBlock* block = (AstBlock*)malloc(sizeof(AstBlock));
    block->statements = malloc(sizeof(Array));
    array_init(block->statements);

    if (expect(parser, TOKEN_LBRACE) == NULL) return NULL;

    while (!peekFor(parser, TOKEN_RBRACE)) {
        array_push(block->statements, parser_statement(parser));
    }

    if (expect(parser, TOKEN_RBRACE) == NULL) return NULL;

    return block;
}

char* ast_statement_type_name(AstStatementType type)
{
    switch(type) {
        case STATEMENT_EXPRESSION:
            return "STATEMENT_EXPRESSION";
        case STATEMENT_RETURN:
            return "STATEMENT_RETURN";
        case STATEMENT_FUNCTION:
            return "STATEMENT_FUNCTION";
        case STATEMENT_IF:
            return "STATEMENT_IF";
        case STATEMENT_WHILE:
            return "STATEMENT_WHILE";
        case STATEMENT_FOR:
            return "STATEMENT_FOR";
        default:
            return "STATEMENT_ERROR";
    }
}

AstStatement* parser_fn(Parser* parser)
{
    AstStatement* statement = malloc(sizeof(AstStatement));
    statement->type = STATEMENT_FUNCTION;
    statement->stmt.function = malloc(sizeof(AstFunction));
    statement->stmt.function->arguments = malloc(sizeof(Array));
    array_init(statement->stmt.function->arguments);

    if (expect(parser, TOKEN_FN) == NULL) return NULL;

    Token* ident = expect(parser, TOKEN_IDENTIFIER);
    if (ident == NULL) return NULL;
    statement->stmt.function->name = ident->value;

    if (expect(parser, TOKEN_LPAREN) == NULL) return NULL;
    // TODO: arguments
    if (expect(parser, TOKEN_RPAREN) == NULL) return NULL;

    statement->stmt.function->block = parse_block(parser);
    if (statement->stmt.function->block == NULL) return NULL;

    return statement;
}

AstStatement* parser_statement(Parser* parser)
{
    printf("Parser Token: %s\n", token_type_name((*parser->tokens)->type));

    switch ((*parser->tokens)->type)
    {
        case TOKEN_FN: {
            return parser_fn(parser);
        } break;
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

    while ((*parser->tokens)->type != TOKEN_EOF)
    {
        AstStatement* statement = parser_statement(parser);
        if (statement != NULL)
        {
            array_push(statements, statement);
        }
    }

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

    temp = sdscatprintf(temp, "\t<Statements count=\"%d\">\n", parser->ast->statements->count);
    for (int i = 0; i < parser->ast->statements->count; i++)
    {
        AstStatement* stmt = parser->ast->statements->data[i];
        printf("=> %s\n", ast_statement_type_name(stmt->type));
        switch (stmt->type) {
            case STATEMENT_FUNCTION: {
                temp = sdscatprintf(temp, "\t\t<Function name=\"%s\">\n", stmt->stmt.function->name);
                if (stmt->stmt.function->arguments->count == 0) {
                    temp = sdscatprintf(temp, "\t\t\t<FunctionArguments count=\"%d\" />\n", stmt->stmt.function->arguments->count);
                } else {
                    temp = sdscatprintf(temp, "\t\t\t<FunctionArguments count=\"%d\">\n", stmt->stmt.function->arguments->count);
                    // TODO: arguments
                    temp = sdscatprintf(temp, "\t\t\t</FunctionArguments>\n");
                }
                temp = sdscatprintf(temp, "\t\t</Function>>\n");
            } break;
            default: {
                temp = sdscatprintf(temp, "\t\t<Statement name=\"%s\" />\n", stmt->name);
            } break;
        }
    }
    temp = sdscat(temp, "\t</Statements>\n");

    temp = sdscat(temp, "</Parser>");

    return temp;
}
