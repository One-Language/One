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

bool lexer_is_eof(Lexer* lexer)
{
    return lexer->offset >= strlen(lexer->source) || lexer->source[lexer->offset] == '\0';
}

Token* lexer_lex(Lexer* lexer)
{
    Location start;
    start.line = lexer->location.line;
    start.column = lexer->location.column;
    start.offset = lexer->offset;

    if (lexer_is_eof(lexer)) {
        lexer->offset++;

        lexer->location.offset++;
        lexer->location.column++;

        return token_make(TOKEN_EOF, NULL, start, lexer->location);
    }
    else {
        char ch = lexer->source[lexer->offset];
        if (is_whitespace(ch)) {
            while (is_whitespace(ch)) {
                lexer->offset++;
                ch = lexer->source[lexer->offset];

                lexer->location.offset++;
                lexer->location.column++;
            }
            return lexer_lex(lexer);
        }
        else if (is_identifier(ch)) {
            long length = 0;
            char* value = malloc(1);

            do {
                value = realloc(value, strlen(value) + 2);
                value[strlen(value) + 1] = '\0';
                value[strlen(value)] = ch;

                lexer->offset++;
                ch = lexer->source[lexer->offset];

                lexer->location.offset++;
                lexer->location.column++;

                length++;
            }
            while (!lexer_is_eof(lexer) && is_alpha(ch));

            value[length] = '\0';

            printf("-> %s\n", get_location(start));
            printf("-> %s\n", get_location(lexer->location));

            return token_make(TOKEN_IDENTIFIER, value, start, lexer->location);
        }
        else if (is_digit(ch)) {
            long length = 0;
            char* value = malloc(1);

            do {
                value = realloc(value, strlen(value) + 2);
                value[length+1] = '\0';
                value[length] = ch;

                lexer->offset++;
                ch = lexer->source[lexer->offset];

                lexer->location.offset++;
                lexer->location.column++;

                length++;
            }
            while (!lexer_is_eof(lexer) && is_digit(ch));

            value[length] = '\0';

            printf("-> %s\n", get_location(start));
            printf("-> %s\n", get_location(lexer->location));

            return token_make(TOKEN_VALUE_INT, value, start, lexer->location);
        }
        else if (ch == '(') {
            lexer->offset++;
            lexer->location.offset++;
            lexer->location.column++;
            return token_make(TOKEN_OPERATOR_PAREN_LEFT, "(", start, lexer->location);
        }
        else if (ch == ')') {
            lexer->offset++;
            lexer->location.offset++;
            lexer->location.column++;
            return token_make(TOKEN_OPERATOR_PAREN_RIGHT, ")", start, lexer->location);
        }
        else if (ch == '{') {
            lexer->offset++;
            lexer->location.offset++;
            lexer->location.column++;
            return token_make(TOKEN_OPERATOR_BRACE_LEFT, "{", start, lexer->location);
        }
        else if (ch == '}') {
            lexer->offset++;
            lexer->location.offset++;
            lexer->location.column++;
            return token_make(TOKEN_OPERATOR_BRACE_RIGHT, "}", start, lexer->location);
        }
        else if (ch == ';') {
            lexer->offset++;
            lexer->location.offset++;
            lexer->location.column++;
            return token_make(TOKEN_OPERATOR_SEMICOLON, ";", start, lexer->location);
        }
        else {
            lexer->offset++;
            lexer->location.offset++;
            lexer->location.column++;
            return token_make(TOKEN_UNKNOWN, NULL, start, lexer->location);
        }
    }
}

void lexer_debug(Lexer* lexer)
{
    printf("Number of tokens: %d\n", lexer->token_count);
    if (lexer->token_count == 0) {
        printf("No tokens found in lexer!\n");
        return;
    }

    for (int i = 0; i < lexer->token_count; i++) {
        Token* t = lexer->tokens[i];
        printf("Token %s (%s, %s)\n", get_token_name(t->type), get_location(t->start), get_location(t->end));
    }
}

Token** lexer_tokenizer(Lexer* lexer)
{
    if (lexer->source == NULL) {
        return NULL;
    }

    lexer->tokens = malloc(sizeof(Token*) * 100);
    lexer->token_count = 0;
    lexer->offset = 0;

    Token* token = lexer_lex(lexer);
    while (token != NULL && token->type != TOKEN_EOF) {
        lexer->tokens[lexer->token_count] = token;
        lexer->token_count++;
        token = lexer_lex(lexer);
    }

    lexer->tokens[lexer->token_count] = NULL;

    return lexer->tokens;
}
