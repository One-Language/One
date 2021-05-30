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

    // skip the free space
    while (token_is_free(*lex->source) == true) {
        tokenNextChar(lex);
    }

    // end if it's EOF
    if (tokenEOF(lex) == true) {
        t->type = tok_eof;
        return t;
    }

    // single-line comment
    // multi-line comment
    // DIIVIDE operator
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
                if (c1 == '*' && c2 == '/') { // if first char was * and second was /, so we have to close multi-line comment and stop this loop!
                    break; // END multi-line comment and looking loop!
                } else {
                    // Why we not need to go back to prevChar? Since we still not call the tokenNextChar function...
                    // If you write: tokenPrevChar(lex);, this will stop at a unlimit LOOP, so we not need to call this function, since we still not called `tokenNextChar(lex)` yet!
                    // continue;
                }
            }

            return tokenNext(lex);
        } else {
            t->type = tok_op_div;
            return t;
        }
    }

    // identifier
    if (token_is_alpha(*lex->source) == true) {
        t->vstring = malloc(sizeof(char) * 200 + 1);
        int i = 0;
        while (token_is_ident(*lex->source) == true) {
            t->vstring[i++] = *lex->source;
            tokenNextChar(lex);
        }
        t->vstring[i] = '\0';

        if (strcmp(t->vstring, "if") == 0) {
            t->type = tok_if;
        } else {
            t->type = tok_identifier;
        }
        return t;
    }

    // unknowm token
    t->type = tok_unknowm;
    return t;
}

char *tokenName(TokenType type) {
    switch (type) {
        case tok_eof:
            return "EOF";

        case tok_if:
            return "IF";
        case tok_else:
            return "ELSE";
        case tok_do:
            return "DO";
        case tok_while:
            return "WHILE";
        case tok_for:
            return "FOR";
        case tok_switch:
            return "SWITCH";

        case tok_identifier:
            return "IDENTIFIER";

        case tok_op_plus:
            return "OPERATOR_PLUS";
        case tok_op_minus:
            return "OPERATOR_MINUS";
        case tok_op_mul:
            return "OPERATOR_MUL";
        case tok_op_div:
            return "OPERATOR_DIVIDE";

        case tok_unknowm:
            return "UNKNOWM";
        default:
            return "UNKNOWM";
    }
}