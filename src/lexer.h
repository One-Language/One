/**
 The One Programming Language
 File: lexer.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#ifndef _ONE_LEXER_H_
#define _ONE_LEXER_H_

#include "token.h"

typedef struct {
    file_t* file;
    char* start;
    char* current;
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
 * @brief Lex the content of the file
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

#endif
