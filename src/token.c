/**
 The One Programming Language
 File: token.c
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#include "token.h"

/**
 * @brief Initialize a token object
 * 
 * @param token_type_t type
 * @param char* start
 * @param char* end
 * @param location_t start_location
 * @param location_t end_location
 * 
 * @return token_t*
 */
token_t* token_init(token_type_t type, char* start, char* end, location_t start_location, location_t end_location)
{
    token_t* token = (token_t*)malloc(sizeof(token_t));
    token->type = type;
    token->start = start;
    token->end = end;
    token->start_location = start_location;
    token->end_location = end_location;
    token->value = NULL;
    return token;
}

/**
 * @brief Initialize a token object with value
 * 
 * @param token_type_t type
 * @param char* start
 * @param char* end
 * @param location_t start_location
 * @param location_t end_location
 * @param char* value
 * 
 * @return token_t*
 */
token_t* token_init_value(token_type_t type, char* start, char* end, location_t start_location, location_t end_location, char* value)
{
    token_t* token = token_init(type, start, end, start_location, end_location);
    token->value = value;
    return token;
}

/**
 * @brief Get the token name
 * 
 * @param type 
 * @return char* 
 */
char* token_name(token_type_t type)
{
    switch (type) {
        case TOKEN_ERROR: return "error";
        case TOKEN_IF: return "if";
        case TOKEN_ELSE: return "else";
        case TOKEN_RET: return "ret";
        case TOKEN_NUMBER: return "number";
        case TOKEN_IDENTIFIER: return "identifier";
        case TOKEN_STRING: return "string";

        case TOKEN_INCREMENT: return "increment";
        case TOKEN_DECREMENT: return "decrement";
        case TOKEN_EQUAL: return "equal";
        case TOKEN_EQUAL_EQUAL: return "equal_equal";
        case TOKEN_LESS_EQUAL: return "less_equal";
        case TOKEN_LESS: return "less";
        case TOKEN_GREATER_EQUAL: return "greater_equal";
        case TOKEN_GREATER: return "greater";
        case TOKEN_PLUS: return "plus";
        case TOKEN_MINUS: return "minus";
        case TOKEN_STAR: return "star";
        case TOKEN_EXPONENT: return "exponent";
        case TOKEN_SLASH: return "slash";
        case TOKEN_DOT: return "dot";
        case TOKEN_COMMA: return "comma";
        case TOKEN_SEMICOLON: return "semicolon";
        case TOKEN_BANG: return "bang";
        case TOKEN_BANG_EQUAL: return "bang_equal";
        case TOKEN_LEFT_PAREN: return "left_paren";
        case TOKEN_RIGHT_PAREN: return "right_paren";
        case TOKEN_LEFT_BRACE: return "left_brace";
        case TOKEN_RIGHT_BRACE: return "right_brace";
        case TOKEN_LEFT_BRACKET: return "left_bracket";
        case TOKEN_RIGHT_BRACKET: return "right_bracket";

        case TOKEN_EOF: return "eof";
        default: return "unknown";
    }
}

/**
 * @brief Initialize the token list object
 * 
 * @param void
 * 
 * @return token_list_t* 
 */
token_list_t* token_list_init()
{
    token_list_t* list = (token_list_t*)malloc(sizeof(token_list_t));
    list->capacity = 2;
    list->size = 0;
    list->data = (token_t**)malloc(sizeof(token_t*) * list->capacity);
    return list;
}

/**
 * @brief Add a token to the list
 * 
 * @param token_list_t* list
 * @param token_t* token
 * 
 * @return void
 */
void token_list_add(token_list_t* list, token_t* token)
{
    if (list->size >= list->capacity) {
        list->capacity += 2;
        list->data = (token_t**)realloc(list->data, sizeof(token_t*) * list->capacity);
    }
    list->data[list->size++] = token;
}

/**
 * @brief Free the token list object
 * 
 * @param token_list_t* list
 * 
 * @return void
 */
void token_list_free(token_list_t* list)
{
    for (int i = 0; i < list->size; i++) {
        free(list->data[i]);
    }
    free(list->data);
    free(list);
}

/**
 * @brief Print the token list object
 * 
 * @param token_list_t* list
 * 
 * @return void
 */
void token_list_print(token_list_t* list)
{
    printf("%d Tokens\n", list->size);
    for (int i = 0; i < list->size; i++) {
        token_t* token = list->data[i];

        printf("\t" "%s" "\t" "%.*s" "\t" "%d:%d" "\t" "%d:%d" "\t", token_name(token->type), (int)(token->end - token->start), token->start, token->start_location.line, token->start_location.column, token->end_location.line, token->end_location.column);

        if (token->value != NULL) printf("%s", token->value);

        printf("\n");
    }
}
