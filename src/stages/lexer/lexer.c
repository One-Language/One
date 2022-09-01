#include "lexer.h"

char* file_reads(FILE* file)
{
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(size + 1);
    if (buffer == NULL) {
        printf("Could not allocate memory for file buffer");
        return NULL;
    }
    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    return buffer;
}

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

Token* token_make(TokenType type, char* value, Location start, Location end)
{
    Token* token = malloc(sizeof(Token));
    token->type = type;
    token->value = value;
    token->start = start;
    token->end = end;

    return token;
}

char lexer_get_current_char(Lexer* lexer)
{
    return lexer->source[lexer->offset];
}

char lexer_get_next_char(Lexer* lexer)
{
    return lexer->source[lexer->offset++];
}

char lexer_get_prev_char(Lexer* lexer)
{
    return lexer->source[lexer->offset - 1];
}

bool lexer_is_eof(Lexer* lexer)
{
    return lexer->offset >= strlen(lexer->source) || lexer_get_current_char(lexer) == '\0';
}

bool lexer_is_whitespace(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '\v' || ch == '\f';
}

void lexer_skip_whitespace(Lexer* lexer)
{
    while (!lexer_is_eof(lexer) && lexer_is_whitespace(lexer_get_current_char(lexer))) {
        lexer_get_next_char(lexer);
    }
}

bool lexer_is_identifier(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

bool lexer_is_digit(char ch)
{
    return ch >= '0' && ch <= '9';
}

bool lexer_is_alpha(char ch)
{
    return lexer_is_identifier(ch) || lexer_is_digit(ch);
}

Token* lexer_read_identifier(Lexer* lexer)
{
    Location start = lexer->location;
    char* buffer = malloc(1);
    buffer[0] = '\0';
    int len = 0;

    while (!lexer_is_eof(lexer) && lexer_is_alpha(lexer_get_current_char(lexer))) {
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
    else if (lexer_is_whitespace(c)) {
        lexer_skip_whitespace(lexer);
        return lexer_next_token(lexer);
    }
    else if (c == '(') {
        lexer_get_next_char(lexer);
        return token_make(TOKEN_OPERATOR_PAREN_LEFT, "(", start, lexer->location);
    }
    else if (c == ')') {
        lexer_get_next_char(lexer);
        return token_make(TOKEN_OPERATOR_PAREN_RIGHT, ")", start, lexer->location);
    }
    else if (c == '{') {
        lexer_get_next_char(lexer);
        return token_make(TOKEN_OPERATOR_BRACE_LEFT, "{", start, lexer->location);
    }
    else if (c == '}') {
        lexer_get_next_char(lexer);
        return token_make(TOKEN_OPERATOR_BRACE_RIGHT, "}", start, lexer->location);
    }
    else if (c == ';') {
        lexer_get_next_char(lexer);
        return token_make(TOKEN_OPERATOR_SEMICOLON, ";", start, lexer->location);
    }
    else if (c == ',') {
        lexer_get_next_char(lexer);
        return token_make(TOKEN_OPERATOR_COMMA, ",", start, lexer->location);
    }
    else if (lexer_is_identifier(c)) {
        return lexer_read_identifier(lexer);
    }
}

Token** lexer_lex(Lexer* lexer)
{
    if (lexer->source == NULL) {
        printf("Could not read source");
        return NULL;
    }

    lexer->tokens = malloc(sizeof(Token*) * 100);
    lexer->token_count = 0;

    Token* token = lexer_next_token(lexer);
    while (token != NULL) {
        lexer->tokens[lexer->token_count] = token;
        lexer->token_count++;
        token = lexer_next_token(lexer);
    }

    printf("Lexed %d tokens", lexer->token_count);

    lexer->tokens[lexer->token_count] = NULL;

    return lexer->tokens;
}
