#include "lexer.h"

lexer_t* lexer_init(char* source)
{
    lexer_t* lexer = malloc(sizeof(lexer_t));
    if (lexer == NULL) {
        printf("Error: Not enough memory to create a lexer.");
        exit(74);
    }

    lexer->source = source;
    lexer->current = source;
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
    return *lexer->current == '\0' || *lexer->current == EOF;
}

void lexer_scan_token(lexer_t* lexer)
{

}

lexer_t* lexer_scan_tokens(lexer_t* lexer)
{
    while (!lexer_is_at_end(lexer)) {
        lexer->line = 1;
        lexer->column = 1;

        lexer->current = lexer->source;

        lexer_scan_token(lexer);
    }

    return lexer;
}

void lexer_free(lexer_t* lexer)
{
    free(lexer->source);
    free(lexer->current);

    array_free(lexer->tokens);

    free(lexer);
}
