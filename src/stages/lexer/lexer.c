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
//    array_push(lexer->tokens, token_init(TOKEN_EOF, "EOF", lexer->position, lexer->position));
}

str* lexer_trace(Lexer* lexer)
{
    printf("lexer_trace\n");
    str* temp = str_init_size("<Lexer>\n", 100);

//    for (int i = 0; i < lexer->tokens->size; i++)
//    {
//        Token* token = lexer->tokens->data[i];
//        str_append(temp, token->value);
//        str_append(temp, " ");
//    }

    str_append(&temp, "</Lexer>");

    return temp;
}
