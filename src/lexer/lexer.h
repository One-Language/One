/**
 The One Programming Language

 File: lexer/lexer.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef _ONE_LEXER_LEXER_H_
#define _ONE_LEXER_LEXER_H_

#include "../builtins/error.h"

#include "../tokenizer/tokenizer.h"

typedef struct _token Token;
typedef enum _token_type TokenType;
typedef struct _location Location;

typedef struct
{
	const char* start;
	const char* current;
	Location loc;
} Lexer;

/*
 * @function: lexer_init
 * @description: Set default value for the global `lexer` variable
 * @arguments: char*; input of One source-code program
 * @return: void; nothing
 */
void lexer_init(char* source);

/*
 * @function: lexer_check_keyword
 * @description: [..... start-th ................. length-th]
                        ^..........................^
                            if was equal to rest,
                            so return type as Token,
                            otherwise return TOKEN_VALUE_IDENTIFIER
 * @arguments: int start, int length, const char* rest, TokenType type
 * @return: TokenType
 */
TokenType lexer_check_keyword(int start, int length, const char* rest, TokenType type);

/*
 * @function: lexer_identifier_type
 * @description: Check current characters, check it's a registered keywords
 				 or no it's user-defined identifier. anyway return TokenType. wherever it's userdefined is TOKEN_VALUE_IDENTIFIER otherwisw from keyword map variable
 * @arguments: nothing
 * @return: TokenType
 */
TokenType lexer_identifier_type();

/*
 * @function: lexer_skip_comment_inline
 * @description: Check if current character is //, so it's a inline-comment and we have to skip it!
 * @arguments: nothing
 * @return: Always NULL
 */
Token* lexer_skip_comment_inline();

Token* lexer_skip_comment_multiline();

Token* lexer_skip_whitespace();

Token* lexer_number();

Token* lexer_char();

Token* lexer_string();

Token* lexer_scan();

void lexer_free();

Token* lexer_identifier();

#endif // _ONE_LEXER_LEXER_H_
