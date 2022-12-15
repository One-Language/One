/**
 The One Programming Language
 File: token.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#ifndef _ONE_TOKEN_H
#define _ONE_TOKEN_H

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free

typedef enum {
    TOKEN_ERROR,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FUNC,
    TOKEN_RET,
    TOKEN_NUMBER,
    TOKEN_IDENTIFIER,
    TOKEN_STRING,

    TOKEN_INCREMENT, // ++
    TOKEN_DECREMENT, // --
    TOKEN_EQUAL, // =
    TOKEN_EQUAL_EQUAL, // ==
    TOKEN_LESS_EQUAL, // <=
    TOKEN_LESS, // <
    TOKEN_GREATER_EQUAL, // >=
    TOKEN_GREATER, // >
    TOKEN_PLUS, // +
    TOKEN_MINUS, // -
    TOKEN_STAR, // *
    TOKEN_EXPONENT, // **
    TOKEN_SLASH, // /
    TOKEN_DOT, // .
    TOKEN_COMMA, // ,
    TOKEN_SEMICOLON, // ;
    TOKEN_BANG, // !
    TOKEN_BANG_EQUAL, // !=
    TOKEN_LEFT_PAREN, // (
    TOKEN_RIGHT_PAREN, // )
    TOKEN_LEFT_BRACE, // {
    TOKEN_RIGHT_BRACE, // }
    TOKEN_LEFT_BRACKET, // [
    TOKEN_RIGHT_BRACKET, // ]

    TOKEN_EOF
} token_type_t;

typedef struct {
    int line;
    int column;
    int offset;
} location_t;

typedef struct {
    token_type_t type;
    char* value;
    char* start;
    char* end;
    // location_t* location;
} token_t;

typedef struct {
    token_t** data;
    int size;
    int capacity;
} token_list_t;

/**
 * @brief Get the token name
 * 
 * @param type 
 * @return char* 
 */
char* token_name(token_type_t type);

/**
 * @brief Initialize the token list object
 * 
 * @param void
 * 
 * @return token_list_t* 
 */
token_list_t* token_list_init();

/**
 * @brief Add a token to the list
 * 
 * @param token_list_t* list
 * @param token_t* token
 * 
 * @return void
 */
void token_list_add(token_list_t* list, token_t* token);

/**
 * @brief Free the token list object
 * 
 * @param token_list_t* list
 * 
 * @return void
 */
void token_list_free(token_list_t* list);

/**
 * @brief Print the token list object
 * 
 * @param token_list_t* list
 * 
 * @return void
 */
void token_list_print(token_list_t* list);

/**
 * @brief Initialize a token object
 * 
 * @param token_type_t type
 * @param char* start
 * @param char* end
 * 
 * @return token_t*
 */
token_t* token_init(token_type_t type, char* start, char* end);

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
token_t* token_init_value(token_type_t type, char* start, char* end, char* value);

#endif
