/**
 The One Programming Language
 File: stages/lexer/token.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2020-2022; One Language Contributors
 **/

#include "token.h"

bool is_whitespace(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

bool is_identifier(char ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

bool is_digit(char ch)
{
    return ch >= '0' && ch <= '9';
}

bool is_alpha(char ch)
{
    return is_identifier(ch) || is_digit(ch);
}

char* get_token_name(Token* t)
{
    switch(t->type) {
        case TOKEN_IDENTIFIER:
            return "TokenIdentifier";
        case TOKEN_KEYWORD_IF:
            return "TokenKeywordIf";
        case TOKEN_KEYWORD_ELSE:
            return "TokenKeywordElse";
        case TOKEN_KEYWORD_WHILE:
            return "TokenKeywordWhile";
        case TOKEN_KEYWORD_RETURN:
            return "TokenKeywordReturn";
        case TOKEN_KEYWORD_FOR:
            return "TokenKeywordFor";
        case TOKEN_KEYWORD_FN:
            return "TokenKeywordFn";
        case TOKEN_OPERATOR_PAREN_LEFT:
            return "TokenOperatorParenLeft";
        case TOKEN_OPERATOR_PAREN_RIGHT:
            return "TokenOperatorParenRight";
        case TOKEN_OPERATOR_BRACE_LEFT:
            return "TokenOperatorBraceLeft";
        case TOKEN_OPERATOR_BRACE_RIGHT:
            return "TokenOperatorBraceRight";
        case TOKEN_OPERATOR_SEMICOLON:
            return "TokenOperatorSemicolon";
        case TOKEN_OPERATOR_COMMA:
            return "TokenOperatorComma";
        case TOKEN_EOF:
            return "TokenEof";
        default:
            return "TokenUnknown";
    }
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

