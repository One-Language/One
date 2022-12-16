/**
 The One Programming Language
 File: lexer.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#ifndef _ONE_LEXER_H_
#define _ONE_LEXER_H_

#include <stdio.h> // printf
#include <stdlib.h> // malloc, free
#include <ctype.h> // isalpha, isdigit
#include <string.h> // memcpy

#include "file.h" // file_t
#include "token.h" // token_t, token_list_t, location_t

typedef struct {
    file_t* file;
    char* start;
    char* current;
    location_t start_location;
    location_t current_location;
    token_list_t* tokens;
} lexer_t;

/**
 * @brief Initialize the lexer object
 * 
 * @param file_t* file
 * 
 * @return lexer_t*
 */
lexer_t* lexer_init(file_t* file);

/**
 * @brief Lex the next token in the content
 * 
 * @param lex 
 */
void lexer_lex_next(lexer_t* lex);

/**
 * @brief Lex all tokens from the content
 * 
 * @param lexer_t* lexer
 * 
 * @return void
 */
void lexer_lex(lexer_t* lex);

/**
 * @brief Get the token list
 * 
 * @param lexer_t* lexer
 * 
 * @return token_list_t*
 */
token_list_t* lexer_tokens(lexer_t* lex);

/**
 * @brief Free the lexer object
 * 
 * @param lexer_t* lexer
 * 
 * @return void
 */
void lexer_free(lexer_t* lex);

/**
 * @brief Add a token to the token list
 * 
 * @param lexer_t* lexer
 * @param token_type_t type
 * 
 * @return void
 */
void lexer_add_token(lexer_t* lex, token_type_t type);

/**
 * @brief Add a token with value to the token list
 * 
 * @param lexer_t* lexer
 * @param token_type_t type
 * @param char* value
 * 
 * @return void
 */
void lexer_add_token_value(lexer_t* lex, token_type_t type, char* value);

/**
 * @brief Lex a identifier
 * 
 * @param lexer_t* lexer
 * 
 * @return void
 */
void lexer_read_identifier(lexer_t* lex);

/**
 * @brief Lex a double string
 * 
 * @param lexer_t* lexer
 * 
 * @return void
 */
void lexer_read_string(lexer_t* lex);

/**
 * @brief Increment the lexer position
 * 
 * @param lexer_t* lexer
 * @param int count
 * 
 * @return void
 */
void lexer_read_offset(lexer_t* lex, int offset);

/**
 * @brief Lex a multi line comment
 * 
 * @param lexer_t* lexer
 * 
 * @return void
 */
void lexer_read_comment_multi_line(lexer_t* lex);

/**
 * @brief Lex a single line comment
 * 
 * @param lexer_t* lexer
 * 
 * @return void
 */
void lexer_read_comment_single_line(lexer_t* lex);

#endif
