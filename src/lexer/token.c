#include "lexer.h"

lexer_token_t* token_init(lexer_token_type_t type)
{
    lexer_token_t* token = malloc(sizeof(lexer_token_t));
    token->type = type;
    token->value = NULL;
    token->ch = '\0';
    token->location = malloc(sizeof(lexer_token_location_t));
    return token;
}

lexer_token_t* token_init_value(lexer_token_type_t type, void* value)
{
    lexer_token_t* token = malloc(sizeof(lexer_token_t));
    token->type = type;
    token->value = value;
    token->ch = '\0';
    token->location = malloc(sizeof(lexer_token_location_t));
    return token;
}

lexer_token_t* token_set_value(lexer_token_t* token, void* value)
{
    token->value = value;
}

lexer_token_t* token_set_location(lexer_token_t* token, lexer_token_location_t* location)
{
    token->location->length = location->length;

    token->location->start_line = location->start_line;
    token->location->start_column = location->start_column;

    token->location->end_line = location->end_line;
    token->location->end_column = location->end_column;

    return token;
}

lexer_token_t* token_set_location_init(lexer_token_t* token, int length, int start_line, int start_column, int end_line, int end_column)
{
    token->location->length = length;

    token->location->start_line = start_line;
    token->location->start_column = start_column;

    token->location->end_line = end_line;
    token->location->end_column = end_column;

    return token;
}

bool is_digit(char c)
{
    return c >= '0' && c <= '9';
}

char* token_type_name(lexer_token_type_t type)
{
    switch (type) {
        case TOKEN_TYPE_EOF: return "eof";
        case TOKEN_TYPE_ERROR: return "error";
        case TOKEN_TYPE_LINE: return "line";

        case TOKEN_TYPE_IF: return "if";
        case TOKEN_TYPE_ELSE: return "else";

        case TOKEN_TYPE_OPERATOR: return "operator";

        case TOKEN_TYPE_NUMBER: return "number";

        case TOKEN_TYPE_STRING_DOUBLE: return "string_double";
        case TOKEN_TYPE_STRING_SINGLE: return "string_single";

        default: return "unknown";
    }
}

lexer_token_type_t token_name_type(char* type_name)
{
    if (strcmp(type_name, "eof") == 0) return TOKEN_TYPE_EOF;
    else if (strcmp(type_name, "error") == 0) return TOKEN_TYPE_ERROR;
    else if (strcmp(type_name, "line") == 0) return TOKEN_TYPE_LINE;

    else if (strcmp(type_name, "if") == 0) return TOKEN_TYPE_IF;
    else if (strcmp(type_name, "else") == 0) return TOKEN_TYPE_ELSE;

    else if (strcmp(type_name, "operator") == 0) return TOKEN_TYPE_OPERATOR;

    else if (strcmp(type_name, "number") == 0) return TOKEN_TYPE_NUMBER;

    else if (strcmp(type_name, "string_double") == 0) return TOKEN_TYPE_STRING_DOUBLE;
    else if (strcmp(type_name, "string_single") == 0) return TOKEN_TYPE_STRING_SINGLE;
}

char* op_type_name(lexer_token_op_type_t type)
{
    switch (type) {
        case TOKEN_OP_TYPE_NONE: return "none";
        case TOKEN_OP_TYPE_MUL: return "*";
        case TOKEN_OP_TYPE_DIV: return "/";
        case TOKEN_OP_TYPE_PLUS: return "+";
        case TOKEN_OP_TYPE_PLUS_PLUS: return "++";
        case TOKEN_OP_TYPE_MINUS: return "-";
        case TOKEN_OP_TYPE_MINUS_MINUS: return "--";
        case TOKEN_OP_TYPE_EQUAL: return "=";
        case TOKEN_OP_TYPE_EQUAL_MINUS: return "-=";
        case TOKEN_OP_TYPE_EQUAL_PLUS: return "+=";
        case TOKEN_OP_TYPE_EQUAL_DIV: return "/=";
        case TOKEN_OP_TYPE_EQUAL_MUL: return "*=";
        case TOKEN_OP_TYPE_EQUAL_EQUAL: return "==";
        case TOKEN_OP_TYPE_GT: return ">";
        case TOKEN_OP_TYPE_LT: return "<";
        case TOKEN_OP_TYPE_GT_E: return ">=";
        case TOKEN_OP_TYPE_LT_E: return "<=";
        case TOKEN_OP_TYPE_ERROR: return "error";
        default: return "unknown";
    }
}

lexer_token_op_type_t op_name_type(char* type_name)
{
    if (strcmp(type_name, "none")) return TOKEN_OP_TYPE_NONE;
    else if (strcmp(type_name, "*")) return TOKEN_OP_TYPE_MUL;
    else if (strcmp(type_name, "/")) return TOKEN_OP_TYPE_DIV;
    else if (strcmp(type_name, "+")) return TOKEN_OP_TYPE_PLUS;
    else if (strcmp(type_name, "++")) return TOKEN_OP_TYPE_PLUS_PLUS;
    else if (strcmp(type_name, "-")) return TOKEN_OP_TYPE_MINUS;
    else if (strcmp(type_name, "--")) return TOKEN_OP_TYPE_MINUS_MINUS;
    else if (strcmp(type_name, "=")) return TOKEN_OP_TYPE_EQUAL;
    else if (strcmp(type_name, "-=")) return TOKEN_OP_TYPE_EQUAL_MINUS;
    else if (strcmp(type_name, "+=")) return TOKEN_OP_TYPE_EQUAL_PLUS;
    else if (strcmp(type_name, "/=")) return TOKEN_OP_TYPE_EQUAL_DIV;
    else if (strcmp(type_name, "*=")) return TOKEN_OP_TYPE_EQUAL_MUL;
    else if (strcmp(type_name, "==")) return TOKEN_OP_TYPE_EQUAL_EQUAL;
    else if (strcmp(type_name, ">")) return TOKEN_OP_TYPE_GT;
    else if (strcmp(type_name, "<")) return TOKEN_OP_TYPE_LT;
    else if (strcmp(type_name, ">=")) return TOKEN_OP_TYPE_GT_E;
    else if (strcmp(type_name, "<=")) return TOKEN_OP_TYPE_LT_E;
    else if (strcmp(type_name, "error")) return TOKEN_OP_TYPE_ERROR;
    else return TOKEN_OP_TYPE_ERROR;
}
