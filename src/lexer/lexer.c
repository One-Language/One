#include "lexer.h"
#include "../utility/file.h"

// #define LEXER_CURRENT_CHAR(lexer) (lexer->buffer[lexer->offset])
// #define LEXER_NEXT_CHAR(lexer) (lexer->buffer[lexer->offset + 1])

// #define LEXER_INCREMENT_INDEX(lexer) (lexer->offset++)
// #define LEXER_DECREMENT_INDEX(lexer) (lexer->offset--)

char* token_name(TokenType type) {
    switch(type) {
        case TOKEN_EOF: return "EOF";
        case TOKEN_PLUS: return "PLUS";
        case TOKEN_MINUS: return "MINUS";
        case TOKEN_STAR: return "STAR";
        case TOKEN_SLASH: return "SLASH";
        case TOKEN_PERCENT: return "PERCENT";
        case TOKEN_CARET: return "CARET";
        case TOKEN_AMPERSAND: return "AMPERSAND";
        case TOKEN_PIPE: return "PIPE";
        case TOKEN_TILDE: return "TILDE";
        case TOKEN_EXCLAMATION: return "EXCLAMATION";
        case TOKEN_QUESTION: return "QUESTION";
        case TOKEN_COLON: return "COLON";
        case TOKEN_SEMICOLON: return "SEMICOLON";
        case TOKEN_COMMA: return "COMMA";
        case TOKEN_DOT: return "DOT";
        case TOKEN_EQUAL: return "EQUAL";
        case TOKEN_LESS: return "LESS";
        case TOKEN_GREATER: return "GREATER";
        case TOKEN_LPAREN: return "LPAREN";
        case TOKEN_RPAREN: return "RPAREN";
        case TOKEN_LBRACE: return "LBRACE";
        case TOKEN_RBRACE: return "RBRACE";
        case TOKEN_LBRACKET: return "LBRACKET";
        case TOKEN_RBRACKET: return "RBRACKET";
        case TOKEN_IDENTIFIER: return "IDENTIFIER";
        case TOKEN_STRING: return "STRING";
        case TOKEN_INTEGER: return "INTEGER";
        case TOKEN_FLOAT: return "FLOAT";
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

    while (lexer->offset < lexer->length) {
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
        case '\n':
            lexer->offset++;
            lexer->line++;
            lexer->column = 0;
            return lexer_next(lexer);
            break;
        case '+':
            lexer->offset++;
            lexer->column++;
            break;
        case '-':
            lexer->offset++;
            lexer->column++;
            break;
        case '*':
            lexer->offset++;
            lexer->column++;
            break;
        case '/':
            lexer->offset++;
            lexer->column++;
            break;
        case '%':
            lexer->offset++;
            lexer->column++;
            break;
        case '^':
            lexer->offset++;
            lexer->column++;
            break;
        case '=':
            lexer->offset++;
            lexer->column++;
            break;
        case '!':
            lexer->offset++;
            lexer->column++;
            break;
        case '<':
            lexer->offset++;
            lexer->column++;
            break;
        case '>':
            lexer->offset++;
            lexer->column++;
            break;
        case '&':
            lexer->offset++;
            lexer->column++;
            break;
        case '|':
            lexer->offset++;
            lexer->column++;
            break;
        case '~':
            lexer->offset++;
            lexer->column++;
            break;
        case '(':
            lexer->offset++;
            lexer->column++;
            break;
        case ')':
            lexer->offset++;
            lexer->column++;
            break;
        case '[':
            lexer->offset++;
            lexer->column++;
            break;
        case ']':
            lexer->offset++;
            lexer->column++;
            break;
        case '{':
            lexer->offset++;
            lexer->column++;
            break;
        case '}':
            lexer->offset++;
            lexer->column++;
            break;
        case ',':
            lexer->offset++;
            lexer->column++;
            break;
        case '.':
            lexer->offset++;
            lexer->column++;
            break;
        case ':':
            lexer->offset++;
            lexer->column++;
            break;
        case ';':
            lexer->offset++;
            lexer->column++;
            break;
        case '?':
            lexer->offset++;
            lexer->column++;
            break;
        case '#':
            lexer->offset++;
            lexer->column++;
            break;
        case '\'':
            lexer->offset++;
            lexer->column++;
            break;
        case '"':
            lexer->offset++;
            lexer->column++;
            break;
        default:
            printf("Warning: Unknown character '%c' at %d", c, lexer->offset);
            lexer->offset++;
            lexer->column++;
            break;
    }
}

void lexer_free(Lexer* lexer) {
    // free input
    // free tokens
    // free lexer
}
