#include "lexer.h"

lexer_t* lexer_init(char** source)
{

}

lexer_t* lexer_scan_tokens(lexer_t* lexer)
{

}

void lexer_free(lexer_t* lexer)
{
    free(lexer->source);
    free(lexer->current);

    array_free(lexer->tokens);

    free(lexer);
}
