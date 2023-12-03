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

void lexer_scan_token(lexer_t* lexer)
{
    printf("%c\n", *lexer->current);
    *lexer->source++;
    // printf("%c\n", *lexer->current);
    // *lexer->current++;
    lexer_token_t* token = token_init(TOKEN_TYPE_STRING_DOUBLE);
    lexer_add_token(lexer, token);
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
    
    while (!lexer_is_at_end(lexer)) {
        lexer->current = lexer->source;

        lexer_scan_token(lexer);
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
