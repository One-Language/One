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
    lexer_t* lex = (lexer_t*)malloc(sizeof(lexer_t));
    lex->file = file;
    lex->start = file->content;
    lex->current = file->content;

    lex->tokens = token_list_init();

    return lex;
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
    printf("%s\n-------------------\n", lex->start);
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
    return lex->tokens;
}

/**
 * @brief Free the lexer object
 * 
 * @param lexer_t* lexer
 * 
 * @return void
 */
void lexer_free(lexer_t* lex)
{
    free(lex);
}
