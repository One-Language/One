#include "lexer.h"
#include "../utility/file.h"

// #define LEXER_CURRENT_CHAR(lexer) (lexer->buffer[lexer->offset])
// #define LEXER_NEXT_CHAR(lexer) (lexer->buffer[lexer->offset + 1])

// #define LEXER_INCREMENT_INDEX(lexer) (lexer->offset++)
// #define LEXER_DECREMENT_INDEX(lexer) (lexer->offset--)

char* token_name(TokenType type) {
    switch(type) {
        case TOKEN_EOF: return "EOF";

        case TOKEN_NUMBER: return "NUMBER";
        case TOKEN_STRING: return "STRING";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";

        case TOKEN_IF: return "IF";
        case TOKEN_ELSE: return "ELSE";
        case TOKEN_WHILE: return "WHILE";
        case TOKEN_FOR: return "FOR";
        case TOKEN_RETURN: return "RETURN";
        case TOKEN_BREAK: return "BREAK";
        case TOKEN_CONTINUE: return "CONTINUE";

        case TOKEN_ASSIGN: return "ASSIGN";
        case TOKEN_EQUAL: return "EQUAL";
        case TOKEN_PLUS: return "PLUS";
        case TOKEN_MINUS: return "MINUS";
        case TOKEN_STAR: return "STAR";
        case TOKEN_SLASH: return "SLASH";
        case TOKEN_PERCENT: return "PERCENT";

        default: return "UNKNOWN";
    }
}

Lexer* lexer_new(char* file, char* data) {
    Lexer* lexer = malloc(sizeof(Lexer));

    lexer->file = file;
    lexer->file_dir = get_file_dir(file);

    lexer->buffer = data != NULL ? data : file_reads(file);
    lexer->length = strlen(lexer->buffer);
    lexer->offset = 0;

    lexer->tokens = array_new();

    return lexer;
}

int lexer_run(Lexer* lexer) {
    printf("Lexer: %s\n", lexer->file);
    printf("Input: %s\n", lexer->buffer);
    printf("Input Size: %d\n", lexer->length);

    if (lexer->length == 0) return 1;

    while (!lexer_eof(lexer)) {
        lexer_next(lexer);
    }
    return 0;
}

Token* token_make_value(TokenType type, char* value) {
    Token* t = (Token*) malloc(sizeof(Token));
    t->type = type;
    t->value = value;
    return t;
}

Token* token_make(TokenType type) {
    Token* t = (Token*) malloc(sizeof(Token));
    t->type = type;
    return t;
}

void lexer_next(Lexer* lexer) {
    char c = lexer->buffer[lexer->offset];
    printf("Current: %c\n", c);

    switch (c) {
        case ' ':
        case '\t':
        case '\r':
            lexer->offset++;
            lexer->column++;
            return lexer_next(lexer);
            break;

        case '+' :
            array_push(lexer->tokens, token_make(TOKEN_PLUS));
            lexer->offset++;
            lexer->column++;
            break;
        case '-' :
            array_push(lexer->tokens, token_make(TOKEN_MINUS));
            lexer->offset++;
            lexer->column++;
            break;
        case '*' :
            array_push(lexer->tokens, token_make(TOKEN_STAR));
            lexer->offset++;
            lexer->column++;
            break;
        case '/' :
            array_push(lexer->tokens, token_make(TOKEN_SLASH));
            lexer->offset++;
            lexer->column++;
            break;
        case '%' :
            array_push(lexer->tokens, token_make(TOKEN_PERCENT));
            lexer->offset++;
            lexer->column++;
            break;
        case '=' :
            array_push(lexer->tokens, token_make(TOKEN_EQUAL));
            lexer->offset++;
            lexer->column++;
            break;
        
        case '0' ... '9' :
            lexer_number(lexer);
            break;
        
        case 'a' ... 'z' :
        case 'A' ... 'Z' :
        case '_' :
            lexer_identifier(lexer);
            break;

        default:
            printf("Warning: Unknown character '%c' at %d", c, lexer->offset);
            lexer->offset++;
            lexer->column++;
            break;
    }
}

bool lexer_eof(Lexer* lexer) {
    return lexer->offset >= lexer->length;
}

void lexer_number(Lexer* lexer) {
    int start = lexer->offset;
    int end = lexer->offset;

    while (lexer->buffer[end] >= '0' && lexer->buffer[end] <= '9') {
        end++;
    }

    char* value = malloc(end - start + 1);
    memcpy(value, &lexer->buffer[start], end - start);
    value[end - start] = '\0';

    array_push(lexer->tokens, token_make_value(TOKEN_NUMBER, value));
    lexer->offset = end;
    lexer->column = end;
}

void lexer_identifier(Lexer* lexer) {
    int start = lexer->offset;
    int length = 0;

    while (!lexer_eof(lexer)) {
        char c = lexer->buffer[lexer->offset];
        if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9' || c == '_') {
            lexer->offset++;
            lexer->column++;
            length++;
        } else {
            break;
        }
    }

    char* value = malloc(length + 1);
    memcpy(value, lexer->buffer + start, length);
    value[length] = '\0';

    array_push(lexer->tokens, token_make_value(TOKEN_IDENTIFIER, value));
}

void lexer_free(Lexer* lexer) {
    // free input
    // free tokens
    // free lexer
}
