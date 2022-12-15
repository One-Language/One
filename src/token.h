/**
 The One Programming Language
 File: token.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#ifndef _ONE_TOKEN_H
#define _ONE_TOKEN_H

typedef enum {
    TOKEN_ERROR,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FUNC,
    TOKEN_RET,
    TOKEN_NUMBER,
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
    location_t* location;
} token_t;

typedef struct {
    token_t** tokens;
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

#endif
