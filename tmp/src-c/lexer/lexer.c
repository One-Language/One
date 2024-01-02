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

    lexer->line = 1;
    lexer->column = 0;

    return lexer;
}

lexer_t* lexer_run(char* source)
{
    lexer_t* lexer = lexer_init(source);
    lexer = lexer_scan_tokens(lexer);

    return lexer;
}

char* lexer_log(lexer_t* lexer)
{
    int tokens_count = array_count(lexer->tokens);
    printf("NUMBER OF TOKENS: %d\n", tokens_count);
    for (int i = 0; i < tokens_count; i++) {
        lexer_token_t* current_token = array_getat(lexer->tokens, i);

        printf("   %d -> [%d:%d]-[%d:%d] TOKEN: %s", i+1, current_token->location->start_line, current_token->location->start_column, current_token->location->end_line, current_token->location->end_column, lexer_token_type_name(current_token->type));

        if (current_token->value != NULL) printf("(%s)\n", current_token->value);
        else if (current_token->ch != '\0') printf("(%c)\n", current_token->ch);
        else if (current_token->op ) printf("(%c)\n", op_type_name(current_token->op));
        else printf("\n");
    }
    
    return "";
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

void lexer_error(lexer_t* lexer, char* error_format, ...) {
    lexer_token_t* token = token_init(TOKEN_TYPE_ERROR);
    token_set_location_init(token, 1, lexer->line, lexer->column, lexer->line, lexer->column + 1);
    
    va_list args;
    va_start(args, error_format);

    int size = vsnprintf(NULL, 0, error_format, args);
    token->value = malloc(size + 1); // +1 for null terminator
    vsnprintf(token->value, size + 1, error_format, args);

    va_end(args);

    lexer_add_token(lexer, token);
}

bool lexer_match(lexer_t* lexer, char target)
{
    char c = *lexer->current;
    *lexer->current++;

    if (c != target) {
        lexer_error(lexer, "expecting %c but we are seeing %c\n", target, *lexer->current);
        return false;
    }

    return true;
}

void lexer_scan_token(lexer_t* lexer)
{
    // printf("TOKEN SCAN %c\n", *lexer->current);

    switch (*lexer->current) {
        case 'a'...'z':
        case 'A'...'Z':
        case '_': {
            string_t* identifier = string_init_size(10);
            int start_column = lexer->column;

            while (is_digit(*lexer->current) || is_alpha(*lexer->current)) {
                string_append_char(identifier, *lexer->current);
                *lexer->current++;
                lexer->column++;
            }

            lexer_token_t* token = token_init(TOKEN_TYPE_IDENTIFIER);
            token_set_location_init(token, lexer->column - start_column, lexer->line, start_column, lexer->line, lexer->column);
            token_set_value(token, string_to_array(identifier));
            lexer_add_token(lexer, token);

            // TODO: Free identifier
        } break;

        case '0'...'9': {
            int start_column = lexer->column;
            while (is_digit(*lexer->current)) {
                *lexer->current++;
                lexer->column++;
            }

            lexer_token_t* token = token_init(TOKEN_TYPE_NUMBER);
            token_set_location_init(token, lexer->column - start_column, lexer->line, start_column, lexer->line, lexer->column);
            lexer_add_token(lexer, token);
        } break;

        case '\'': {
            // eat '
            *lexer->current++;
            lexer->column++;

            string_t* string = string_init_size(10);
            while (!lexer_is_at_end(lexer) && *lexer->current != '\'') {
                // TODO: if (mb_strlen(string) > 1) {}
                string_append_char(string, *lexer->current);
                *lexer->current++;
                lexer->column++;
            }

            if (lexer_is_at_end(lexer)) {
                lexer_error(lexer, "facing EOF but need to close char first!\n");
                return;
            } else if (*lexer->current != '\'') {
                lexer_error(lexer, "need to close char first!\n");
                *lexer->current++;
                lexer->column++;
                return;
            }

            // Skip '
            *lexer->current++;
            lexer->column++;

            // printf("TOKEN: CLOSE STRING\n");
            lexer_token_t* token = token_init(TOKEN_TYPE_STRING_SINGLE);
            token_set_value(token, string_to_array(string));
            lexer_add_token(lexer, token);
        } break;

        case '"': {
            // eat "
            *lexer->current++;
            lexer->column++;

            string_t* string = string_init_size(10);
            while (!lexer_is_at_end(lexer) && *lexer->current != '"') {
                string_append_char(string, *lexer->current);
                *lexer->current++;
                lexer->column++;
            }

            if (lexer_is_at_end(lexer)) {
                lexer_error(lexer, "facing EOF but need to close string first!\n");
                return;
            } else if (*lexer->current != '"') {
                lexer_error(lexer, "need to close string first!\n");
                *lexer->current++;
                lexer->column++;
                return;
            }

            // Skip "
            *lexer->current++;
            lexer->column++;

            // printf("TOKEN: CLOSE STRING\n");
            lexer_token_t* token = token_init(TOKEN_TYPE_STRING_DOUBLE);
            token_set_value(token, string_to_array(string));
            lexer_add_token(lexer, token);
        } break;

        case ' ':
        case '\t': {
            *lexer->current++;
            // while (*lexer->current == ' ' || *lexer->current == '\t') *lexer->current++;
            // while (*lexer->current == '\n' || *lexer->current == '\r' || *lexer->current == ' ' || *lexer->current == '\t') *lexer->current++;
            lexer->column++;
            return lexer_scan_token(lexer);
        };

        case '+': {
            lexer_token_t* token = token_init(TOKEN_TYPE_OPERATOR);
            token_set_location_init(token, 1, lexer->line, lexer->column, lexer->line, lexer->column+1);
            token->ch = *lexer->current;
            lexer_add_token(lexer, token);

            *lexer->current++;
            lexer->column++;
        } break;

        case '-': {
            lexer_token_t* token = token_init(TOKEN_TYPE_OPERATOR);
            token_set_location_init(token, 1, lexer->line, lexer->column, lexer->line, lexer->column+1);
            token->ch = *lexer->current;
            lexer_add_token(lexer, token);

            *lexer->current++;
            lexer->column++;
        } break;

        case '*': {
            lexer_token_t* token = token_init(TOKEN_TYPE_OPERATOR);
            token_set_location_init(token, 1, lexer->line, lexer->column, lexer->line, lexer->column+1);
            token->ch = *lexer->current;
            lexer_add_token(lexer, token);

            *lexer->current++;
            lexer->column++;
        } break;

        case '/': {
            lexer_token_t* token = token_init(TOKEN_TYPE_OPERATOR);
            token_set_location_init(token, 1, lexer->line, lexer->column, lexer->line, lexer->column+1);
            token->ch = *lexer->current;
            lexer_add_token(lexer, token);

            *lexer->current++;
            lexer->column++;
        } break;

        case '\n':
        case '\r': {
            *lexer->current++;
            lexer->column++;
            // while (*lexer->current == '\n' || *lexer->current == '\r') *lexer->current++;
            // while (*lexer->current == '\n' || *lexer->current == '\r' || *lexer->current == ' ' || *lexer->current == '\t') *lexer->current++;
            if (*lexer->current == '\n') { lexer->line++; lexer->column = 0; }
            return lexer_scan_token(lexer);

            // lexer_token_t* token = token_init(TOKEN_TYPE_LINE);
            // lexer_add_token(lexer, token);
        } break;
    
        case '\0': {
            return;
        } break;

        default: {
            lexer_error(lexer, "unknown character %c", *lexer->current); // TODO
            *lexer->current++;
            lexer->column++;
        } break;
    }
}

lexer_t* lexer_scan_tokens(lexer_t* lexer)
{
    if (lexer_is_at_end(lexer)) {
        lexer->line = lexer->column = 0;

        lexer_token_t* token = token_init(TOKEN_TYPE_EOF);
        token_set_location_init(token, 0, lexer->line, lexer->column, lexer->line, lexer->column);
        lexer_add_token(lexer, token);

        return lexer;
    }

    lexer_token_t* last_token = NULL;
    // printf("%s\n", lexer->source);
    while (!lexer_is_at_end(lexer)) {
        // lexer->source = lexer->current;
        // printf("...\n");
        lexer_scan_token(lexer);

        last_token = array_last(lexer->tokens);
        // printf("TOKEN TYPE: %s\n", lexer_token_type_name(last_token->type));
    }

    if (last_token->type != TOKEN_TYPE_EOF) {
        lexer_token_t* token = token_init(TOKEN_TYPE_EOF);
        token_set_location_init(token, 1, lexer->line, lexer->column, lexer->line, lexer->column+1);
        lexer_add_token(lexer, token);
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