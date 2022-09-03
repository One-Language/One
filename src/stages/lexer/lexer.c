/**
 The One Programming Language
 File: stages/lexer/lexer.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2020-2022; One Language Contributors
 **/

#include "lexer.h"

Lexer* lexer_make_string(char* string)
{
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->file = NULL;
    lexer->source = string;
    lexer->tokens = NULL;
    lexer->token_count = 0;

    return lexer;
}

Lexer* lexer_make(FILE* file)
{
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->file = file;
    lexer->source = file_reads(file);
    lexer->tokens = NULL;
    lexer->token_count = 0;

    return lexer;
}

char lexer_get_current_char(Lexer* lexer)
{
    return lexer->source[lexer->offset];
}

void lexer_go_next_char(Lexer* lexer)
{
    lexer->offset++;
}

void lexer_go_prev_char(Lexer* lexer)
{
    lexer->offset--;
}

char lexer_get_next_char(Lexer* lexer)
{
    return lexer->source[lexer->offset + 1];
}

char lexer_get_prev_char(Lexer* lexer)
{
    return lexer->source[lexer->offset - 1];
}

bool lexer_is_eof(Lexer* lexer)
{
    return lexer->offset >= strlen(lexer->source) || lexer->source[lexer->offset] == '\0';
}

void lexer_skip_whitespace(Lexer* lexer)
{
    while (!lexer_is_eof(lexer) && is_whitespace(lexer_get_current_char(lexer))) {
        lexer_go_next_char(lexer);
    }
}

Token* lexer_read_identifier(Lexer* lexer)
{
    Location start = lexer->location;
    char* buffer = malloc(1);
    buffer[0] = '\0';
    int len = 0;

    while (!lexer_is_eof(lexer) && is_alpha(lexer_get_current_char(lexer))) {
        char c = lexer_get_next_char(lexer);
        buffer = realloc(buffer, len + 2);
        buffer[len] = c;
        buffer[len + 1] = '\0';
        len++;
    }

    return token_make(TOKEN_IDENTIFIER, buffer, start, lexer->location);
}

Token* lexer_next_token(Lexer* lexer)
{
    char c = lexer_get_current_char(lexer);
    Location start = lexer->location;

    if (lexer_is_eof(lexer)) {
        return token_make(TOKEN_EOF, NULL, start, lexer->location);
    }
    else if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
        lexer_skip_whitespace(lexer);
        return lexer_next_token(lexer);
    }
    else if (c == '(') {
        lexer_go_next_char(lexer);
        return token_make(TOKEN_OPERATOR_PAREN_LEFT, "(", start, lexer->location);
    }
    else if (c == ')') {
        lexer_go_next_char(lexer);
        return token_make(TOKEN_OPERATOR_PAREN_RIGHT, ")", start, lexer->location);
    }
    else if (c == '{') {
        lexer_go_next_char(lexer);
        return token_make(TOKEN_OPERATOR_BRACE_LEFT, "{", start, lexer->location);
    }
    else if (c == '}') {
        lexer_go_next_char(lexer);
        return token_make(TOKEN_OPERATOR_BRACE_RIGHT, "}", start, lexer->location);
    }
    else if (c == ';') {
        lexer_go_next_char(lexer);
        return token_make(TOKEN_OPERATOR_SEMICOLON, ";", start, lexer->location);
    }
    else if (c == ',') {
        lexer_go_next_char(lexer);
        return token_make(TOKEN_OPERATOR_COMMA, ",", start, lexer->location);
    }
    else if (is_identifier(c)) {
        return lexer_read_identifier(lexer);
    }
}

Token** lexer_lex(Lexer* lexer)
{
    if (lexer->source == NULL) {
        printf("Could not read source");
        return NULL;
    }

    printf("Lexing source: %s\n", lexer->source);

    lexer->tokens = malloc(sizeof(Token*) * 100);
    lexer->token_count = 0;

    Token* token = lexer_next_token(lexer);
//    while (token != NULL) {
//        lexer->tokens[lexer->token_count] = token;
//        lexer->token_count++;
//        token = lexer_next_token(lexer);
//    }
    printf("Lexed %d tokens", lexer->token_count);

    lexer->tokens[lexer->token_count] = NULL;

    return lexer->tokens;
}
