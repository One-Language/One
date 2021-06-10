//
// Created by max on 6/9/21.
//

#ifndef ONE_LEXER_H
#define ONE_LEXER_H

typedef struct _token Token;
typedef enum _token_type TokenType;

typedef struct _location
{
	int line;
	int column;
} Location;

typedef struct
{
	const char* start;
	const char* current;
	Location loc;
} Lexer;

void lexer_init(char* source);

Token* lexer_skip_whitespace();

Token* lexer_number();

Token* lexer_char();

Token* lexer_string();

Token* lexer_scan();

void lexer_free();

Token* lexer_skip_comment_inline();

Token* lexer_skip_comment_multiline();

TokenType lexer_check_keyword(int start, int length, const char* rest, TokenType type);

TokenType lexer_identifier_type();

Token* lexer_identifier();

#endif //ONE_LEXER_H
