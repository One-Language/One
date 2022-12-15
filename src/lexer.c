/**
 The One Programming Language
 File: lexer.c
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#include "lexer.h"

/**
 * @brief Initialize the lexer object
 * 
 * @param file_t* file
 * 
 * @return lexer_t*
 */
lexer_t* lexer_init(file_t* file)
{
    lexer_t* lexer = (lexer_t*)malloc(sizeof(lexer_t));
    lexer->file = file;
    lexer->start = file->content[0];
    lexer->current = file->content[0];
    return lexer;
}

/**
 * @brief Lex the content of the file
 * 
 * @param lexer_t* lexer
 * 
 * @return void
 */
void lexer_lex(lexer_t* lex)
{
    printf("%c\n", lex->start[0]);
}

/**
 * @brief Get the token list
 * 
 * @param lexer_t* lexer
 * 
 * @return token_list_t*
 */
token_list_t* lexer_tokens(lexer_t* lex)
{
    token_list_t* tokens = (token_list_t*)malloc(sizeof(token_list_t));
    tokens->tokens = (token_t**)malloc(sizeof(token_t*));
    tokens->size = 0;
    return tokens;
}

