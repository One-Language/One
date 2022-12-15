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
    lex->line = 1;

    lex->tokens = token_list_init();

    return lex;
}

/**
 * @brief Lex the next token in the content
 * 
 * @param lex 
 */
void lexer_lex_next(lexer_t* lex)
{
    switch (lex->start[0])
    {
        case ' ':
        case '\t':
        case '\n':
        case '\r':
            lex->current++;
            lex->start = lex->current;
            lexer_lex_next(lex);
            break;

        case '\0':
            lexer_add_token(lex, TOKEN_EOF);
            break;

        case 'a'...'z':
        case 'A'...'Z':
        case '_':
            lexer_read_identifier(lex);
            break;

        case '(':
            lexer_add_token(lex, TOKEN_LEFT_PAREN);
            break;
        
        case ')':
            lexer_add_token(lex, TOKEN_RIGHT_PAREN);
            break;

        case '{':
            lexer_add_token(lex, TOKEN_LEFT_BRACE);
            break;
        
        case '}':
            lexer_add_token(lex, TOKEN_RIGHT_BRACE);
            break;

        case '[':
            lexer_add_token(lex, TOKEN_LEFT_BRACKET);
            break;
        
        case ']':
            lexer_add_token(lex, TOKEN_RIGHT_BRACKET);
            break;

        case ',':
            lexer_add_token(lex, TOKEN_COMMA);
            break;
        
        case '.':
            lexer_add_token(lex, TOKEN_DOT);
            break;
        
        case '-':
            if (lex->start[1] == '-') {
                lexer_add_token(lex, TOKEN_DECREMENT);
            } else {
                lexer_add_token(lex, TOKEN_MINUS);
            }
            break;
        
        case '+':
            if (lex->start[1] == '+') {
                lexer_add_token(lex, TOKEN_INCREMENT);
                lex->current++;
                lex->start = lex->current;
            }
            else {
                lexer_add_token(lex, TOKEN_PLUS);
            }
            break;
        
        case ';':
            lexer_add_token(lex, TOKEN_SEMICOLON);
            break;
        
        case '*':
            if (lex->start[1] == '*') {
                lexer_add_token(lex, TOKEN_EXPONENT);
                lex->current++;
                lex->start = lex->current;
            }
            else {
                lexer_add_token(lex, TOKEN_STAR);
            }
            break;
        
        case '!':
            if (lex->start[1] == '=') {
                lexer_add_token(lex, TOKEN_BANG_EQUAL);
                lex->current++;
                lex->start = lex->current;
            }
            else {
                lexer_add_token(lex, TOKEN_BANG);
            }
            break;
        
        case '=':
            lex->current++;
            if (lex->current[0] == '=') {
                lexer_add_token(lex, TOKEN_EQUAL_EQUAL);
            }
            else {
                lexer_add_token(lex, TOKEN_EQUAL);
            }
            break;
        
        case '<':
            lex->current++;
            if (lex->current[0] == '=') {
                lexer_add_token(lex, TOKEN_LESS_EQUAL);
            }
            else {
                lexer_add_token(lex, TOKEN_LESS);
            }
            break;
        
        case '>':
            lex->current++;
            if (lex->current[0] == '=') {
                lexer_add_token(lex, TOKEN_GREATER_EQUAL);
            }
            else {
                lexer_add_token(lex, TOKEN_GREATER);
            }
            break;
        
        case '/':
            lex->current++;
            if (lex->current[0] == '/') {
                while (lex->current[0] != '\n' && lex->current[0] != '\0') {
                    lex->current++;
                }
            }
            else {
                lexer_add_token(lex, TOKEN_SLASH);
            }
            break;
        
        case '"':
            lexer_read_string(lex);
            break;

        default:
            lex->current++;
            lexer_add_token(lex, TOKEN_ERROR);
            break;
    }
}

/**
 * @brief Lex all tokens from the content
 * 
 * @param lexer_t* lexer
 * 
 * @return void
 */
void lexer_lex(lexer_t* lex)
{
    while(lex->current[0] != '\0') lexer_lex_next(lex);
}

/**
 * @brief Lex a double string
 * 
 * @param lexer_t* lexer
 * 
 * @return void
 */
void lexer_read_string(lexer_t* lex)
{
    lex->current++;

    while (lex->current[0] != '"' && lex->current[0] != '\0') {
        if (lex->current[0] == '\n') lex->line++;
        lex->current++;
    }

    if (lex->current[0] == '\0') {
        lexer_add_token(lex, TOKEN_ERROR);
        return;
    }

    lex->current++;

    char* value = (char*)malloc(lex->current - lex->start);
    memcpy(value, lex->start, lex->current - lex->start);
    value[lex->current - lex->start - 1] = '\0';

    lexer_add_token_value(lex, TOKEN_STRING, value);
}

/**
 * @brief Lex a identifier
 * 
 * @param lexer_t* lexer
 * 
 * @return void
 */
void lexer_read_identifier(lexer_t* lex)
{
    while (lex->current[0] != '\0' && (isalpha(lex->current[0]) || isdigit(lex->current[0]) || lex->current[0] == '_')) {
        lex->current++;
    }

    char* value = (char*)malloc(sizeof(char) * (lex->current - lex->start + 1));
    memcpy(value, lex->start, lex->current - lex->start);
    value[lex->current - lex->start] = '\0';

    lexer_add_token_value(lex, TOKEN_IDENTIFIER, value);
}

/**
 * @brief Add a token to the token list
 * 
 * @param lexer_t* lexer
 * @param token_type_t type
 * 
 * @return void
 */
void lexer_add_token(lexer_t* lex, token_type_t type)
{
    token_t* token = token_init(type, lex->start, lex->current);
    token_list_add(lex->tokens, token);

    lex->start = lex->current;
}

/**
 * @brief Add a token with value to the token list
 * 
 * @param lexer_t* lexer
 * @param token_type_t type
 * @param char* value
 * 
 * @return void
 */
void lexer_add_token_value(lexer_t* lex, token_type_t type, char* value)
{
    token_t* token = token_init_value(type, lex->start, lex->current, value);
    token_list_add(lex->tokens, token);

    lex->start = lex->current;
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
