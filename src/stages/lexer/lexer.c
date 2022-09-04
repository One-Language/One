//
// Created by Max on 9/4/2022.
//

#include "lexer.h"

Lexer* lexer_init(char* source)
{
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->source = source;
    lexer->position = (Location){0, 1, 0};
    lexer->tokens = malloc(sizeof(Array));
    array_init(lexer->tokens);

    return lexer;
}

Token* token_init(TokenType type, char* value, Location start, Location end)
{
    Token* token = malloc(sizeof(Token));
    token->type = type;
    token->value = value;
    token->start = start;
    token->end = end;

    return token;
}

void lexer_tokenizer(Lexer* lexer)
{
    array_push(lexer->tokens, token_init(TOKEN_EOF, "EOF", lexer->position, lexer->position));
}

char* location_string(Location location)
{
    char* str = malloc(sizeof(char) * 100);
    sprintf(str, "%d:%d:%d", location.offset, location.line, location.column);
    return str;
}

char* token_type_name(TokenType type)
{
    switch (type)
    {
        case TOKEN_EOF: return "EOF";
        case TOKEN_ERROR: return "ERROR";

        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_FN: return "FN";

        case TOKEN_LPAREN: return "LPAREN";
        case TOKEN_RPAREN: return "RPAREN";
        case TOKEN_LBRACE: return "LBRACE";
        case TOKEN_RBRACE: return "RBRACE";

        default: return "UNKNOWN";
    }
}

sds lexer_trace(Lexer* lexer)
{
    printf("lexer_trace\n");
    sds temp = sdsnew("<Lexer>\n");
    char* ident_str1 = string_repeat(" ", 4 * 1);
    char* ident_str2 = string_repeat(" ", 4 * 2);

    for (int i = 0; i < lexer->tokens->count; i++)
    {
        Token* token = lexer->tokens->data[i];
        temp = sdscatprintf(temp, "%s<token id=\"%d\">\n", ident_str1, i + 1);
            temp = sdscatfmt(temp, "%s<type>%s</type>\n", ident_str2, token_type_name(token->type));
            temp = sdscatfmt(temp, "%s<value>%s</value>\n", ident_str2, token->value);
            temp = sdscatfmt(temp, "%s<start>%s</start>\n", ident_str2, location_string(token->start));
            temp = sdscatfmt(temp, "%s<end>%s</end>\n", ident_str2, location_string(token->end));
        temp = sdscatfmt(temp, "%s</token>\n", ident_str1);
    }

    temp = sdscat(temp, "</Lexer>");

    return temp;
}
