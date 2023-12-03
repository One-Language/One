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
