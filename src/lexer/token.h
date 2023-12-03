#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int duration;

    int start_line;
    int start_column;

    int end_line;
    int end_column;
} lexer_token_location_t;

typedef enum {
    TOKEN_TYPE_IF,
    TOKEN_TYPE_ELSE,

    TOKEN_TYPE_OPERATOR,

    TOKEN_TYPE_NUMBER,

    TOKEN_TYPE_STRING_DOUBLE,
    TOKEN_TYPE_STRING_SINGLE,
} lexer_token_type_t;

lexer_token_t* token_init(lexer_token_type_t type);

lexer_token_t* token_init_value(lexer_token_type_t type, void* value);

lexer_token_t* token_set_value(lexer_token_t* token, void* value);
