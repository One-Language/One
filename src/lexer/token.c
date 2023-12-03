#include "lexer.h"

lexer_token_t* token_init(lexer_token_type_t type)
{
    lexer_token_t* token = malloc(sizeof(lexer_token_t));
    token->type = TOKEN_TYPE_STRING_DOUBLE;
    token->value = NULL;
    return token;
}

lexer_token_t* token_init_value(lexer_token_type_t type, void* value)
{
    lexer_token_t* token = malloc(sizeof(lexer_token_t));
    token->type = TOKEN_TYPE_STRING_DOUBLE;
    token->value = value;
    return token;
}

lexer_token_t* token_set_value(lexer_token_t* token, void* value)
{
    token->value = value;
}
