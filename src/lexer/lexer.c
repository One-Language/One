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

        case TOKEN_COMMA: return "COMMA";
        case TOKEN_DOT: return "DOT";
        case TOKEN_LBRACE: return "LBRACE";
        case TOKEN_RBRACE: return "RBRACE";

        case TOKEN_FN: return "FN";
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
    // printf("Input: %s\n", lexer->buffer);
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
    t->value = NULL;
    return t;
}

void lexer_next(Lexer* lexer) {
    char c = lexer->buffer[lexer->offset];
    // printf("Current: %c\n", c);

    switch (c) {
        case '\0': {
            array_push(lexer->tokens, token_make(TOKEN_EOF));
            return;
        }

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

        case '.': {
            lexer->offset++;
            lexer->column++;
            Token* t = token_make(TOKEN_DOT);
            array_push(lexer->tokens, t);
            break;
        }
        case ',': {
            lexer->offset++;
            lexer->column++;
            Token* t = token_make(TOKEN_COMMA);
            array_push(lexer->tokens, t);
            break;
        }
        case '{':
            array_push(lexer->tokens, token_make(TOKEN_LBRACE));
            lexer->offset++;
            lexer->column++;
            break;
        case '}':
            array_push(lexer->tokens, token_make(TOKEN_RBRACE));
            lexer->offset++;
            lexer->column++;
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
            printf("Warning: Unknown character '%c'(%d) at %d\n", c, c, lexer->offset);
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

void lexer_debug(Lexer* lexer) {
    printf("Lexer: %d tokens\n", lexer->tokens->size);
    for (int i = 0; i < lexer->tokens->size; i++) {
        Token* t = lexer->tokens->data[i];
        if (t->value != NULL) {
            printf("Token: %s(%s)\n", token_name(t->type), t->value);
        } else {
            printf("Token: %s\n", token_name(t->type));
        }
    }
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

    TokenType type = TOKEN_IDENTIFIER;
    // keywords
    if (length == 2) {
        // if
        if (value[0] == 'i' && value[1] == 'f') type = TOKEN_IF;
        // fn
        else if (value[0] == 'f' && value[1] == 'n') type = TOKEN_FN;
    }
    else if (length == 3) {
        // for
        if (value[0] == 'f' && value[1] == 'o' && value[2] == 'r') type = TOKEN_FOR;
    }
    else if (length == 4) {
        // else
        if (value[0] == 'e' && value[1] == 'l' && value[2] == 's' && value[3] == 'e') type = TOKEN_ELSE;
        // true
        // else if (value[0] == 't' && value[1] == 'r' && value[2] == 'u' && value[3] == 'e') type = TOKEN_TRUE;
    }
    else if (length == 5) {
        // while
        if (length == 5 && value[0] == 'w' && value[1] == 'h' && value[2] == 'i' && value[3] == 'l' && value[4] == 'e') type = TOKEN_WHILE;
        // false
        // else if (value[0] == 'f' && value[1] == 'a' && value[2] == 'l' && value[3] == 's' && value[4] == 'e') type = TOKEN_FALSE;
        // break
        // else if (value[0] == 'b' && value[1] == 'r' && value[2] == 'e' && value[3] == 'a' && value[4] == 'k') type = TOKEN_BREAK;
    }
    else if (length == 8) {
        // continue
        if (value[0] == 'c' && value[1] == 'o' && value[2] == 'n' && value[3] == 't' && value[4] == 'i' && value[5] == 'n' && value[6] == 'u' && value[7] == 'e') type = TOKEN_CONTINUE;
    }

    array_push(lexer->tokens, token_make_value(type, value));
}

void lexer_free(Lexer* lexer) {
    // free input
    // free tokens
    // free lexer
}
