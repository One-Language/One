#include <stdio.h>
#include <stdlib.h>

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

    lexer_token_location_t* location;
} lexer_token_t;

lexer_token_t* token_init(lexer_token_type_t type);

lexer_token_t* token_init_value(lexer_token_type_t type, void* value);

lexer_token_t* token_set_value(lexer_token_t* token, void* value);

lexer_token_t* token_set_location(lexer_token_t* token, lexer_token_location_t* location);

lexer_token_t* token_set_location_init(lexer_token_t* token, int length, int start_line, int start_column, int end_line, int end_column);
