/**
 The One Programming Language

 File: token.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "token.h"
#include "lexer.h"

void token_init() {

}

// TODO: inline function
bool token_is_freespace(char c) {
    if (c == ' ')
        return true;
    else if (c == '\t')
        return true;
    return false;
}

// TODO: inline function
bool token_is_freeline(char c) {
    if (c == '\n')
        return true;
    else if (c == '\r')
        return true;
    return false;
}

bool token_is_line(char c) {
    if (c == '\n')
        return true;
    return false;
}

bool token_is_space(char c) {
    if (c == ' ')
        return true;
    return false;
}

bool token_is_free(char c) {
    return token_is_freeline(c) || token_is_freespace(c);
}

bool token_is_alphaasci(char c) {
    if (c >= 'a' && c <= 'z')
        return true;
    else if (c >= 'A' && c <= 'Z')
        return true;
    return false;
}

bool token_is_alpha(char c) {
    if (token_is_alphaasci(c))
        return true;
    else if (c == '_')
        return true;
    return false;
}

bool token_is_number(char c) {
    if (c >= '0' && c <= '9')
        return true;
    return false;
}

bool token_is_digit(char c) {
    if (token_is_number(c) == true)
        return true;
    else if (c == '.')
        return true;
    return false;
}

bool token_is_ident(char c) {
    if (token_is_alpha(c) == true) {
        return true;
    } else if (token_is_number(c) == true) {
        return true;
    }
    return false;
}

bool token_is_eof(char c) {
    return (c == EOF || c == '\0') ? true : false;
}

bool tokenEOF(Lexer *lex) {
    return token_is_eof(*lex->source);
}

void tokenNextChar(Lexer *lex) {
    lex->source++;
}

void tokenPrevChar(Lexer *lex) {
    lex->source--;
}

Token *tokenNext(Lexer *lex) {
    Token *t = malloc(sizeof(Token));
    t->vstring = NULL;

    // skip the free space
    while (token_is_free(*lex->source) == true) {
        tokenNextChar(lex);
    }

    // end if it's EOF
    if (tokenEOF(lex) == true) {
        t->type = TOKEN_EOF;
        return t;
    }

    // single-line comment
    // multi-line comment
    // DIVIDE operator
    if (*lex->source == '/') { // it's single-line comment or divide operator!
        tokenNextChar(lex);
        if (*lex->source == '/') { // it's single-line comment
            while (token_is_eof(*lex->source) == false && token_is_line(*lex->source) == false) {
                tokenNextChar(lex);
            }
            return tokenNext(lex);
        } else if (*lex->source == '*') { // it's multi-line comment
            // Going to next characters while looking for `*/`
            while (token_is_eof(*lex->source) == false) { // Going next while it's still not END of the source!
                char c1 = *lex->source; // get current char and store it at `c1`
                tokenNextChar(lex); // go to next char
                if (token_is_eof(*lex->source) == true) { // again check and make sure it's not END of the source!
                    // Error: EOF without complete close multi-line comment
                    // TODO: ErrorAppend(...)
                    break; // break loop and stop looking for `*/`.
                }

                char c2 = *lex->source; // get current token, it may be second part of `*/`
                if (c1 == '*' && c2 ==
                                 '/') { // if first char was * and second was /, so we have to close multi-line comment and stop this loop!
                    tokenNextChar(lex); // Skip the `/` character and go to next character
                    break; // END multi-line comment and looking loop!
                } else {
                    // Why we not need to go back to prevChar? Since we still not call the tokenNextChar function...
                    // If you write: tokenPrevChar(lex);, this will stop at a unlimit LOOP, so we not need to call this function, since we still not called `tokenNextChar(lex)` yet!
                    // continue;
                }
            }

            return tokenNext(lex);
        } else {
            t->type = TOKEN_OPERATOR_DIV;
            return t;
        }
    }

    // identifier
    if (token_is_alpha(*lex->source) ==
        true) { // check if current char is a-z or A-Z or `_`, if it's so it's a user defined identifier or a compiler registered IDENTIFIER
        t->vstring = malloc(sizeof(char) * 200 +
                            1); // malloc and create a string, since we need to store and save identifier name at token struct.

        size_t length = 0;
        while (token_is_ident(*lex->source) == true) { // if current char is a-z OR A-Z or 0-9 or `_`
            t->vstring[length++] = *lex->source; // append and store current char at `->vstring`
            tokenNextChar(lex); // go to next char, and loop will repeat and going up!
        }
        t->vstring[length] = '\0'; // In C, we need to define end of the string, so it will be useful for future functionality with this string

        // TODO: check identifier is equal to compiler registered Words by filtereing to it's LENGTH.
        // if(i == 2) {}
        // else if(i == 3) {}

        t->type = TOKEN_VALUE_IDENTIFIER;

        // A test to make sure identifier is COMPILER word registered or a user defined identifier
        for (int i = 0; keywords[i].identifier != NULL; i++) {
            if (length == keywords[i].length &&
                memcmp(t->vstring, keywords[i].identifier, length) == 0) {
                t->type = keywords[i].type;
                break;
            }
        }

        if (t->type != TOKEN_VALUE_IDENTIFIER) {
            free(t->vstring);
            t->vstring = NULL;
        }

        return t;
    }

    // unknowm token
    t->type = TOKEN_UNKNOWM;
    return t;
}

char *tokenName(TokenType type) {
    switch (type) {
        case TOKEN_EOF:
            return "EOF";

        case TOKEN_IF:
            return "IF";
        case TOKEN_ELSE:
            return "ELSE";
        case TOKEN_DO:
            return "DO";
        case TOKEN_WHILE:
            return "WHILE";
        case TOKEN_FOR:
            return "FOR";
        case TOKEN_SWTICH:
            return "SWITCH";

        case TOKEN_BREAK:
            return "BREAK";
        case TOKEN_CONTINUE:
            return "CONTINUE;";
        case TOKEN_PACKAGE:
            return "PACKAGE";
        case TOKEN_IMPORT:
            return "IMPORT";

        case TOKEN_IN:
            return "IN";
        case TOKEN_AS:
            return "AS";
        case TOKEN_IS:
            return "IS";

        case TOKEN_NULL:
            return "NULL";

        case TOKEN_RETURN:
            return "RETURN";
        case TOKEN_STATIC:
            return "STATIC";

        case TOKEN_THIS:
            return "THIS";

        case TOKEN_SUPER:
            return "SUPER";

        case TOKEN_FALSE:
            return "FALSE";

        case TOKEN_TRUE:
            return "TRUE";

        case TOKEN_VALUE_IDENTIFIER:
            return "IDENTIFIER";

        case TOKEN_OPERATOR_PLUS:
            return "OPERATOR_PLUS";
        case TOKEN_OPERATOR_MINUS:
            return "OPERATOR_MINUS";
        case TOKEN_OPERATOR_MULL:
            return "OPERATOR_MUL";
        case TOKEN_OPERATOR_DIV:
            return "OPERATOR_DIV";

        case TOKEN_UNKNOWM:
            return "UNKNOWM";
        default:
            return "UNKNOWM";
    }
}