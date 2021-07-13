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

// typedef struct _token Token;
// typedef enum _token_type TokenType;
// typedef struct _location Location;

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
 * @description: [0 ..... start-th ................. length-th]
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

/*
 * @function: lexer_skip_comment_multiline
 * @description: Check if current character is /*, so it's a multi-line-comment and we have to skip it!
 * @arguments: nothing
 * @return: Always NULL
 */
Token* lexer_skip_comment_multiline();

/*
 * @function: lexer_skip_whitespace
 * @description: Check if current characters are whitespace \t \r \n space and also inline-comment or multi-line-comment
 				 so skip all of them in a infinity loop!
 * @arguments: nothing
 * @return: Always NULL
 */
Token* lexer_skip_whitespace();

/*
 * @function: lexer_number
 * @description: Parse current character since it's a number, so we skip that number and return TOKEN_VALUE_NUMBER with value
                 [0-9]+
                 [0-9]+_[0-9]+...
 * @arguments: nothing
 * @return: Always a pointer of Token struct (TOKEN_VALUE_NUMBER)
 */
Token* lexer_number();

/*
 * @function: lexer_char
 * @description: Parse current character since it's a character, we only want a single character.
 				 maybe it's a asci char or maybe it's a single UTF8 character
 * @arguments: nothing
 * @return: Always a pointer of Token struct (TOKEN_VALUE_CHAR)
 */
Token* lexer_char();

/*
 * @function: lexer_char
 * @description: Parse current character since it's a string, we only want skip all character of that string.
 				 so we except " at first and a " at end.
 * @arguments: nothing
 * @return: Always a pointer of Token struct (TOKEN_VALUE_STRING)
 */
Token* lexer_string();

/*
 * @function: lexer_identifier
 * @description: Parse current character since it's a identifier.
 				 Only we have to check it's a user-defined variable or a registered Keyword refer to `keywords` variable
 * @arguments: nothing
 * @return: Always a pointer of Token struct (TOKEN_VALUE_IDENTIFIER or other TokenType refer to `keywords` table)
 */
Token* lexer_identifier();

/*
 * @function: lexer_scan
 * @description: Start to check characters. it's entry point of lexer stage.
 * @arguments: nothing
 * @return: Always a pointer of Token struct
 */
Token* lexer_scan();

/*
 * @function: lexer_free
 * @description: Free allocated memory for the lexer stage! TODO
 				 Only we have to check it's a user-defined variable or a registered Keyword refer to `keywords` variable
 * @arguments: nothing
 * @return: nothing, void
 */
void lexer_free();

#endif // _ONE_LEXER_LEXER_H_
