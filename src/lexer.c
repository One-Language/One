/**
 The One Programming Language
 File: lexer.c
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#include "lexer.h"

/**
 * @brief Increment the lexer position
 * 
 * @param lexer_t* lexer
 * @param int count
 * 
 * @return void
 */
void lexer_read_offset(lexer_t* lex, int offset)
{
    lex->current += offset;
    lex->current_location.column += offset;
    lex->current_location.offset += offset;
}

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

    lex->start_location.line = 1;
    lex->start_location.column = 0;
    lex->start_location.offset = 0;

    lex->current_location.line = lex->start_location.line;
    lex->current_location.column = lex->start_location.column;
    lex->current_location.offset = lex->start_location.offset;

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
            lexer_read_offset(lex, 1);

            lex->start = lex->current;
            lex->start_location = lex->current_location;
            lexer_lex_next(lex);
            break;

        case '\n':
        case '\r':
            lex->current++;
            lex->current_location.column = 0;
            lex->current_location.offset++;
            lex->current_location.line++;

            lex->start = lex->current;
            lex->start_location = lex->current_location;
            lexer_lex_next(lex);
            break;

        case '\0':
            break;

        case 'a'...'z':
        case 'A'...'Z':
        case '_':
            lexer_read_identifier(lex);
            break;

        case '(':
            lexer_read_offset(lex, 1);

            lexer_add_token(lex, TOKEN_LEFT_PAREN);
            break;
        
        case ')':
            lexer_read_offset(lex, 1);

            lexer_add_token(lex, TOKEN_RIGHT_PAREN);
            break;

        case '{':
            lexer_read_offset(lex, 1);

            lexer_add_token(lex, TOKEN_LEFT_BRACE);
            break;
        
        case '}':
            lexer_read_offset(lex, 1);

            lexer_add_token(lex, TOKEN_RIGHT_BRACE);
            break;

        case '[':
            lexer_read_offset(lex, 1);

            lexer_add_token(lex, TOKEN_LEFT_BRACKET);
            break;
        
        case ']':
            lexer_read_offset(lex, 1);

            lexer_add_token(lex, TOKEN_RIGHT_BRACKET);
            break;

        case ',':
            lexer_read_offset(lex, 1);

            lexer_add_token(lex, TOKEN_COMMA);
            break;
        
        case '.':
            lexer_read_offset(lex, 1);

            lexer_add_token(lex, TOKEN_DOT);
            break;
        
        case '-':
            if (lex->current[1] == '-') {
                lexer_read_offset(lex, 2);

                lexer_add_token(lex, TOKEN_DECREMENT);
            } else {
                lexer_read_offset(lex, 1);
                
                lexer_add_token(lex, TOKEN_MINUS);
            }
            break;
        
        case '+':
            if (lex->current[1] == '+') {
                lexer_read_offset(lex, 2);

                lexer_add_token(lex, TOKEN_INCREMENT);
            }
            else {
                lexer_read_offset(lex, 1);

                lexer_add_token(lex, TOKEN_PLUS);
            }
            break;
        
        case ';':
            lexer_read_offset(lex, 1);

            lexer_add_token(lex, TOKEN_SEMICOLON);
            break;
        
        case '*':
            if (lex->current[1] == '*') {
                lexer_read_offset(lex, 2);

                lexer_add_token(lex, TOKEN_EXPONENT);
            }
            else {
                lexer_read_offset(lex, 1);

                lexer_add_token(lex, TOKEN_STAR);
            }
            break;
        
        case '!':
            if (lex->current[1] == '=') {
                lexer_read_offset(lex, 2);

                lexer_add_token(lex, TOKEN_BANG_EQUAL);
                lex->start = lex->current;
            }
            else {
                lex->current++;
                lexer_add_token(lex, TOKEN_BANG);
            }
            break;
        
        case '=':
            if (lex->current[1] == '=') {
                lexer_read_offset(lex, 2);

                lexer_add_token(lex, TOKEN_EQUAL_EQUAL);
            }
            else {
                lexer_read_offset(lex, 1);

                lexer_add_token(lex, TOKEN_EQUAL);
            }
            break;
        
        case '<':
            if (lex->current[1] == '=') {
                lexer_read_offset(lex, 2);

                lexer_add_token(lex, TOKEN_LESS_EQUAL);
            }
            else {
                lexer_read_offset(lex, 1);

                lexer_add_token(lex, TOKEN_LESS);
            }
            break;
        
        case '>':
            if (lex->current[1] == '=') {
                lexer_read_offset(lex, 2);

                lexer_add_token(lex, TOKEN_GREATER_EQUAL);
            }
            else {
                lexer_read_offset(lex, 1);

                lexer_add_token(lex, TOKEN_GREATER);
            }
            break;
        
        case '/':
            if (lex->current[1] == '/') {
                lexer_read_comment_single_line(lex);

                lex->start = lex->current;
                lex->start_location = lex->current_location;
                lexer_lex_next(lex);
            }
            else if (lex->current[1] == '*') {
                lexer_read_comment_multi_line(lex);

                lex->start = lex->current;
                lex->start_location = lex->current_location;
                lexer_lex_next(lex);
            }
            else {
                lexer_read_offset(lex, 1);

                lexer_add_token(lex, TOKEN_SLASH);
            }
            break;
        
        case '"':
            lexer_read_string(lex);
            break;

        default:
            lexer_read_offset(lex, 1);

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

    lexer_add_token(lex, TOKEN_EOF);
}

/**
 * @brief Lex a multi line comment
 * 
 * @param lexer_t* lexer
 * 
 * @return void
 */
void lexer_read_comment_multi_line(lexer_t* lex)
{
    lexer_read_offset(lex, 2);

    while (lex->current[0] != '*' && lex->current[1] != '/' && lex->current[0] != '\0') {
        lexer_read_offset(lex, 1);

        if (lex->current[0] == '\n') {
            lex->current_location.line++;
            lex->current_location.column = 0;
        }
    }

    if (lex->current[0] == '\0') {
        lexer_add_token(lex, TOKEN_ERROR);
        return;
    }

    lexer_read_offset(lex, 2);
}

/**
 * @brief Lex a single line comment
 * 
 * @param lexer_t* lexer
 * 
 * @return void
 */
void lexer_read_comment_single_line(lexer_t* lex)
{
    lexer_read_offset(lex, 2);

    while (lex->current[0] != '\n' && lex->current[0] != '\0') {
        lexer_read_offset(lex, 1);
    }
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
    lexer_read_offset(lex, 1);

    while (lex->current[0] != '"' && lex->current[0] != '\0') {
        lexer_read_offset(lex, 1);

        if (lex->current[0] == '\n') {
            lex->current_location.line++;
            lex->current_location.column = 0;
        }
    }

    if (lex->current[0] == '\0') {
        lexer_add_token(lex, TOKEN_ERROR);
        return;
    }

    lexer_read_offset(lex, 1);

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
        lexer_read_offset(lex, 1);
    }

    int length = lex->current - lex->start;
    char* value = (char*)malloc(sizeof(char) * (length + 1));
    memcpy(value, lex->start, lex->current - lex->start);
    value[lex->current - lex->start] = '\0';

    // Check if the identifier is a reserved keyword
    switch (length) {
        case 2:
            if (value[0] == 'i' && value[1] == 'f') {
                lexer_add_token(lex, TOKEN_IF);
                return;
            }
            break;

        case 3:
            if (value[0] == 'r' && value[1] == 'e' && value[2] == 't') {
                lexer_add_token(lex, TOKEN_RET);
                return;
            }
            break;
        
        case 4:
            if (value[0] == 'e' && value[1] == 'l' && value[2] == 's' && value[3] == 'e') {
                lexer_add_token(lex, TOKEN_ELSE);
                return;
            }
            else if (value[0] == 'f' && value[1] == 'u' && value[2] == 'n' && value[3] == 'c') {
                lexer_add_token(lex, TOKEN_FUNC);
                return;
            }
            break;
    }

    // Otherwise it's an identifier
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
    token_t* token = token_init(type, lex->start, lex->current, lex->start_location, lex->current_location);
    token_list_add(lex->tokens, token);

    lex->start = lex->current;
    lex->start_location = lex->current_location;
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
    token_t* token = token_init_value(type, lex->start, lex->current, lex->start_location, lex->current_location, value);
    token_list_add(lex->tokens, token);

    lex->start = lex->current;
    lex->start_location = lex->current_location;
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
