#include "lexer.h"

lexer_t* lexer_init(char* source)
{
    lexer_t* lexer = malloc(sizeof(lexer_t));
    if (lexer == NULL) {
        printf("Error: Not enough memory to create a lexer.");
        exit(74);
    }

    lexer->original_source = source;
    lexer->source = lexer->original_source;
    lexer->current = lexer->original_source;
    lexer->tokens = array_init();

    return lexer;
}

/**
 * @brief Checks if the lexer is at the end of the source code.
 * @note This function checks if the lexer is at the end of the source code.
 * 
 * @param lexer The lexer to check.
 * 
 * @return True if the lexer is at the end of the source code, false otherwise.
 * 
 * @code
 * if (lexer_is_at_end(lexer)) {}
 * else {}
 * @endcode
 */
bool lexer_is_at_end(lexer_t* lexer)
{
    return *lexer->current == '\0';
}

void lexer_add_token(lexer_t* lexer, lexer_token_t* token)
{
    array_push(lexer->tokens, token);
}

bool lexer_eat(lexer_t* lexer, char ch)
{
    if (*lexer->current == ch) {
        *lexer->current++;
    }
}

void lexer_match(lexer_t* lexer, char ch)
{
    if (*lexer->current != ch) {
        printf("Error: expecting %c but we are seeing %c\n", ch, *lexer->current);

        lexer_token_t* token = token_init(TOKEN_TYPE_ERROR);
        lexer_add_token(lexer, token);

        *lexer->current++;
        return;
    }

    *lexer->current++;
}

void lexer_scan_token(lexer_t* lexer)
{
    // printf("TOKEN SCAN %c\n", *lexer->current);

    switch (*lexer->current) {
        case '0'...'9': {
            while (is_digit(*lexer->current)) {
                *lexer->current++;
            }

            lexer_token_t* token = token_init(TOKEN_TYPE_NUMBER);
            lexer_add_token(lexer, token);
        } break;

        case '"': {
            // eat "
            *lexer->current++;

            while (!lexer_is_at_end(lexer) && *lexer->current != '"') {
                printf("TOKEN: READ STRING CHAR %c\n", *lexer->current);
                *lexer->current++;
            }

            if (lexer_is_at_end(lexer)) {
                printf("Error: facing EOF but need to close string first!\n");

                lexer_token_t* token = token_init(TOKEN_TYPE_ERROR);
                lexer_add_token(lexer, token);
                return;
            } else if (*lexer->current != '"') {
                printf("Error: need to close string first\n");

                lexer_token_t* token = token_init(TOKEN_TYPE_ERROR);
                lexer_add_token(lexer, token);

                *lexer->current++;
                return;
            }

            // Skip "
            *lexer->current++;

            // printf("TOKEN: CLOSE STRING\n");
            lexer_token_t* token = token_init(TOKEN_TYPE_STRING_DOUBLE);
            lexer_add_token(lexer, token);
        } break;

        case ' ':
        case '\t': {
            // *lexer->current++;
            // while (*lexer->current == ' ' || *lexer->current == '\t') *lexer->current++;
            while (*lexer->current == '\n' || *lexer->current == '\r' || *lexer->current == ' ' || *lexer->current == '\t') *lexer->current++;
            return lexer_scan_token(lexer);
        };

        case '\n':
        case '\r': {
            // *lexer->current++;
            // while (*lexer->current == '\n' || *lexer->current == '\r') *lexer->current++;
            while (*lexer->current == '\n' || *lexer->current == '\r' || *lexer->current == ' ' || *lexer->current == '\t') *lexer->current++;
            return lexer_scan_token(lexer);

            // lexer_token_t* token = token_init(TOKEN_TYPE_LINE);
            // lexer_add_token(lexer, token);
        } break;

        // case 'a'...'z':
        // case 'A'...'Z': {
        // } break;
        
        default: {
            printf("WHAT IS THIS CHAR '%c'\n", *lexer->current);
            *lexer->current++;

            lexer_token_t* token = token_init(TOKEN_TYPE_ERROR);
            lexer_add_token(lexer, token);
        } break;
    }
}

lexer_t* lexer_scan_tokens(lexer_t* lexer)
{
    if (lexer_is_at_end(lexer)) {
        lexer->line = 0;
        lexer->column = 0;

        lexer_token_t* token = token_init(TOKEN_TYPE_EOF);
        token_set_location_init(token, 0, 0, 0, 0, 0);
        lexer_add_token(lexer, token);

        return lexer;
    } else {
        lexer->line = 1;
        lexer->column = 0;
    }
    
    // printf("%s\n", lexer->source);
    while (!lexer_is_at_end(lexer)) {
        // lexer->source = lexer->current;

        lexer_scan_token(lexer);

        lexer_token_t* last_token = array_last(lexer->tokens);
        printf("TOKEN TYPE: %s\n", token_type_name(last_token->type));
    }

    lexer_token_t* token = token_init(TOKEN_TYPE_EOF);
    token_set_location_init(token, 1, lexer->line, lexer->column, lexer->line+1, lexer->column+1);
    lexer_add_token(lexer, token);

    return lexer;
}

void lexer_free(lexer_t* lexer)
{
    free(lexer->source);
    free(lexer->current);

    array_free(lexer->tokens);

    free(lexer);
}
