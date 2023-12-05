#ifndef _ONE_LEXER_TOKEN_H_
#define _ONE_LEXER_TOKEN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../builtins/array.h"

typedef array_t array_token_t;

typedef enum {
    TOKEN_TYPE_ERROR,
    TOKEN_TYPE_EOF,
    TOKEN_TYPE_LINE,

    TOKEN_TYPE_IF,
    TOKEN_TYPE_ELSE,

    TOKEN_TYPE_OPERATOR,

    TOKEN_TYPE_NUMBER,

    TOKEN_TYPE_STRING_DOUBLE,
    TOKEN_TYPE_STRING_SINGLE,
} lexer_token_type_t;

typedef enum {
    TOKEN_OP_TYPE_NONE = -1, // default
    TOKEN_OP_TYPE_ERROR, // error

    TOKEN_OP_TYPE_MUL,
    TOKEN_OP_TYPE_DIV,
    TOKEN_OP_TYPE_PLUS,
    TOKEN_OP_TYPE_PLUS_PLUS,
    TOKEN_OP_TYPE_MINUS,
    TOKEN_OP_TYPE_MINUS_MINUS,
    TOKEN_OP_TYPE_EQUAL,
    TOKEN_OP_TYPE_EQUAL_PLUS,
    TOKEN_OP_TYPE_EQUAL_MINUS,
    TOKEN_OP_TYPE_EQUAL_MUL,
    TOKEN_OP_TYPE_EQUAL_DIV,
    TOKEN_OP_TYPE_EQUAL_EQUAL,
    TOKEN_OP_TYPE_GT,
    TOKEN_OP_TYPE_LT,
    TOKEN_OP_TYPE_GT_E,
    TOKEN_OP_TYPE_LT_E,
} lexer_token_op_type_t;

typedef struct {
    int length;

    int start_line;
    int start_column;

    int end_line;
    int end_column;
} lexer_token_location_t;

typedef struct {
    lexer_token_type_t type;
    void* value;
    char ch;
    lexer_token_op_type_t op;

    lexer_token_location_t* location;
} lexer_token_t;

lexer_token_t* token_init(lexer_token_type_t type);

lexer_token_t* token_init_value(lexer_token_type_t type, void* value);

lexer_token_t* token_set_value(lexer_token_t* token, void* value);

lexer_token_t* token_set_location(lexer_token_t* token, lexer_token_location_t* location);

lexer_token_t* token_set_location_init(lexer_token_t* token, int length, int start_line, int start_column, int end_line, int end_column);

bool is_digit(char c);

char* lexer_token_type_name(lexer_token_type_t type);

lexer_token_type_t token_name_type(char* type_name);

char* op_type_name(lexer_token_op_type_t type);

lexer_token_op_type_t op_name_type(char* type_name);

#endif