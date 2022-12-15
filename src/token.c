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
 * 
 * @return token_t*
 */
token_t* token_init(token_type_t type, char* start, char* end)
{
    token_t* token = (token_t*)malloc(sizeof(token_t));
    token->type = type;
    token->start = start;
    token->end = end;
    token->value = NULL;
    return token;
}

/**
 * @brief Initialize a token object with value
 * 
 * @param token_type_t type
 * @param char* start
 * @param char* end
 * @param char* value
 * 
 * @return token_t*
 */
token_t* token_init_value(token_type_t type, char* start, char* end, char* value)
{
    token_t* token = token_init(type, start, end);
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
        printf("\t%s(%s)\n", token_name(token->type), token->value == NULL ? "None" : token->value);
    }
}
