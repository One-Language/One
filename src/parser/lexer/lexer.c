/**
 The One Programming Language

 File: lexer/lexer.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <builtins/error.h>

#ifdef _ONE_TEST_
#define debug_lexer(format, args...)   \
	printf(CYAN "Lexer Debug: " format \
				"\n" RESET,            \
		 ##args);
// printf(CYAN "Lexer Debug: " format " at %d on %s in %s" \
	// 			"\n" RESET,                                 \
	// 	 ##args,                                            \
	// 	 __LINE__,                                          \
	// 	 "file",                                            \
	// 	 __FUNCTION__);
// #define debug_lexer(format, args...)
#else
#define debug_lexer(format, args...)
#endif

Lexer lexer;
Token* current;

/*
 * @function: lexer_init
 * @description: Set default value for the global `lexer` variable
 * @arguments: char*; input of One source-code program
 * @return: void; nothing
 */
void lexer_init(char* source)
{
	debug_lexer("lexer_init");
	debug_lexer("lexer_init: source is %s", source);

	lexer.start = source;
	lexer.current = source;

	lexer.pos.tokens = 0;
	lexer.pos.index = 0;
	lexer.pos.line = 1;
	lexer.pos.column = 0;

	lexer.pos_end.tokens = 0;
	lexer.pos_end.index = 0;
	lexer.pos_end.line = 1;
	lexer.pos_end.column = 0;

	//Get the first TOKEN into current
	advance();
}

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
TokenType lexer_check_keyword(int start, int length, const char* rest, TokenType type)
{ // This function not used in productions, so we used `lexer_identifier` right now.
	debug_lexer("lexer_check_keyword");

	if (lexer.current - lexer.start == start + length &&
		 memcmp(lexer.start + start, rest, length) == 0)
	{
		return type;
	}

	return TOKEN_VALUE_IDENTIFIER;
}

/*
 * @function: lexer_identifier_type
 * @description: Check current characters, check it's a registered keywords
 				 or no it's user-defined identifier. anyway return TokenType. wherever it's userdefined is TOKEN_VALUE_IDENTIFIER otherwisw from keyword map variable
 * @arguments: nothing
 * @return: TokenType
 */
TokenType lexer_identifier_type()
{ // This function not used in productions, so we used `lexer_identifier` right now.
	debug_lexer("lexer_identifier_type");

	switch (lexer.start[0])
	{
		case 'i':
			return lexer_check_keyword(1, 1, "f", TOKEN_IF);
			// TODO
	}
	return TOKEN_VALUE_IDENTIFIER;
}

/*
 * @function: lexer_identifier
 * @description: Parse current character since it's a identifier.
 				 Only we have to check it's a user-defined variable or a registered Keyword refer to `keywords` variable
 * @arguments: nothing
 * @return: Always a pointer of Token struct (TOKEN_VALUE_IDENTIFIER or other TokenType refer to `keywords` table)
 */
Token* lexer_identifier()
{
	debug_lexer("lexer_identifier");

	// printf("First ==>%c\n", *lexer.current);
	// printf("Second ==>%c\n", *lexer.start);

	//	char tmp_str[1024] = {};
	char* tmp_str = (char*)malloc(1024 * sizeof(char) + 1);
	size_t ident_length = 0;

	tmp_str[ident_length++] = token_advance();
	while (token_is_ident(token_peek()) && !token_is_end())
	{
		tmp_str[ident_length++] = token_advance();
	}
	tmp_str[ident_length] = '\0';

	debug_lexer("lexer_identifier: print identifier %s", tmp_str);
	debug_lexer("lexer_identifier: identifier length is %zu", ident_length);

	for (size_t j = 0;; j++)
	{
		if (keywords[j].type == TOKEN_VALUE_IDENTIFIER) // it's end of the Keyword list/table
		{
			return token_make_value(TOKEN_VALUE_IDENTIFIER, tmp_str);
			break;
		}
		else if (keywords[j].length == ident_length // fast search performance
			 && strncmp(keywords[j].identifier, tmp_str, keywords[j].length) == 0)
		{
			return token_make(keywords[j].type);
			break;
		}
	}
	//	return token_make(TOKEN_VALUE_IDENTIFIER);
}

/*
 * @function: lexer_skip_comment_inline
 * @description: Check if current character is //, so it's a inline-comment and we have to skip it!
 * @arguments: nothing
 * @return: Maybe NULL
 */
Token* lexer_skip_comment_inline()
{
	debug_lexer("lexer_skip_comment_inline");

	if (token_peek() == '/' && token_peek_next() == '/')
	{
		while (token_peek() != '\n' && !token_is_end()) token_advance();
	}

	return token_make(TOKEN_SKIP_COMMENT_SINGLE);
	// return NULL;
}

/*
 * @function: lexer_skip_comment_multiline
 * @description: Check if current character is `/` `*`, so it's a multi-line-comment and we have to skip it!
 * @arguments: nothing
 * @return: Always NULL
 */
Token* lexer_skip_comment_multiline()
{
	debug_lexer("lexer_skip_comment_multiline");

	if (token_match('/') && token_match('*'))
	{
		for (;;)
		{
			char c1 = token_advance();
			char c2 = token_peek();
			if (token_is_end()) return token_make_error("You not close multi-line comment and we face to EOF!");

			if (c1 == '*' && c2 == '/')
			{
				break;
			}
		}
	}

	token_match('/');
	//	if(!token_match('/'))
	//		return token_make_error("You have to close multi-line comment correctly!");

	return token_make(TOKEN_SKIP_COMMENT_MULTI);
	// return NULL;
}

/*
 * @function: lexer_skip_whitespace
 * @description: Check if current characters are whitespace \t \r \n space
 * @arguments: nothing
 * @return: Maybe NULL
 */
Token* lexer_skip_whitespace()
{
	debug_lexer("lexer_skip_whitespace");

	char c = token_peek();
	bool hasComment = false;
	bool hasLine = false;

	while (c == '\r' || c == '\n' || c == '\t' || c == ' ')
	{
		hasComment = true;
		if (hasLine == false && c == '\n')
		{
			hasLine = true;
		}
		c = token_advance_next();
	}

	if (hasComment == true)
	{
		return token_make(hasLine ? TOKEN_SKIP_WHITESPACE_LINE : TOKEN_SKIP_WHITESPACE);
	}

	return NULL;
}

/*
 * @function: lexer_skip_space
 * @description: Check if current characters are whitespace \t \r \n space and also inline-comment or multi-line-comment
 				 so skip all of them in a loop!
 * @arguments: nothing
 * @return: Maybe NULL
 */
Token* lexer_skip_space()
{
	debug_lexer("lexer_skip_space");

	Token* t = lexer_skip_whitespace();
	if (t != NULL) return t;

	// lex comments
	if (token_peek() == '/')
	{
		// single inline-comment
		if (token_peek_next() == '/')
		{
			t = lexer_skip_comment_inline();
			if (t != NULL) return t;
		}
		else if (token_peek_next() == '*')
		{ // multi-line comment
			t = lexer_skip_comment_multiline();
			if (t != NULL) return t;
		}
	}

	// for (;;)
	// {
	// 	c = token_peek();
	// 	switch (c)
	// 	{
	// 		case ' ':
	// 		case '\t':
	// 		case '\r':
	// 			token_advance();
	// 			break;
	// 		case '\n':
	// 			// lexer.pos.line++;
	// 			token_advance();
	// 			break;
	// 		case '/':
	// 			c2 = token_peek_next();
	// 			if (c2 == '/')
	// 			{
	// 				t = lexer_skip_comment_inline();
	// 				if (t != NULL) return t;
	// 			}
	// 			else if (c2 == '*')
	// 			{
	// 				t = lexer_skip_comment_multiline();
	// 				if (t != NULL) return t;
	// 			}
	// 			else
	// 			{
	// 				return NULL;
	// 			}
	// 			break;
	// 		default:
	// 			return NULL;
	// 	}
	// }

	return NULL; // default return-value
}

/*
 * @function: lexer_number
 * @description: Parse current character since it's a number, so we skip that number and return TOKEN_VALUE_NUMBER with value
                 [0-9]+
                 [0-9]+_[0-9]+...
 * @arguments: nothing
 * @return: Always a pointer of Token struct (TOKEN_VALUE_NUMBER)
 */
Token* lexer_number()
{
	debug_lexer("lexer_number");

	char* tmp_str = (char*)malloc(60 * sizeof(char) + 1);
	size_t i = 0;

	char c = token_peek();
	while (token_is_digit(c) || c == '_')
	{
		// char c1= token_peek();
		// char c2 = token_advance();
		// printf(">>>> %c, %c\n", c1, c2);
		// printf(">>>> %c, %c\n", token_peek(), token_advance());
		// printf("LOOP: Currently token is: '%c'\n", token_peek());
		if (c == '_')
		{
			token_advance();
		}
		else
		{
			tmp_str[i++] = token_advance();
		}
		c = token_peek();
	}

	// printf("Currently token is: '%c'\n", token_peek());

	if (token_match('.'))
	{
		if (token_is_digit(token_peek()))
		{
			tmp_str[i++] = '.';
			while (token_is_digit(token_peek()))
			{
				tmp_str[i++] = token_advance();
			}
		}
	}
	tmp_str[i] = '\0';

	//	printf("===>%s\n", tmp_str);

	//	return token_make(TOKEN_VALUE_NUMBER);
	return token_make_value(TOKEN_VALUE_NUMBER, tmp_str);
}

/*
 * @function: lexer_char
 * @description: Parse current character since it's a character, we only want a single character.
 				 maybe it's a asci char or maybe it's a single UTF8 character
 * @arguments: nothing
 * @return: Always a pointer of Token struct (TOKEN_VALUE_CHAR)
 */
Token* lexer_char()
{
	debug_lexer("lexer_char");
	//	char tmp_str[1024] = {};
	char* tmp_str = (char*)malloc(1024 * sizeof(char) + 1);
	size_t i = 0;

	token_match('\'');
	while (token_peek() != '\'' && !token_is_end())
	{
		tmp_str[i++] = token_peek();
		if (token_utf8_string_length(tmp_str) > 1) break;
		token_advance();
	}
	tmp_str[i] = '\0';

	debug_lexer("lexer_char: tmp_str is '%s'", tmp_str);
	debug_lexer("lexer_char: tmp_str utf8 length is %zu", token_utf8_string_length(tmp_str));

	if (!token_match('\''))
		return token_make_error("Expected ' but found another char!");

	//	return token_make(TOKEN_VALUE_CHAR);
	return token_make_value(TOKEN_VALUE_CHAR, tmp_str);
}

/*
 * @function: lexer_char
 * @description: Parse current character since it's a string, we only want skip all character of that string.
 				 so we except " at first and a " at end.
 * @arguments: nothing
 * @return: Always a pointer of Token struct (TOKEN_VALUE_STRING)
 */
Token* lexer_string()
{
	debug_lexer("lexer_string");

	//	char tmp_str[1024] = {};
	char* tmp_str = (char*)malloc(1024 * sizeof(char) + 1);
	size_t i = 0;

	token_match('"');
	while (token_peek() != '"' && !token_is_end())
	{
		tmp_str[i++] = token_peek();
		token_advance();
	}
	tmp_str[i] = '\0';

	token_match('"');

	//	return token_make(TOKEN_VALUE_STRING);
	return token_make_value(TOKEN_VALUE_STRING, tmp_str);
}

/*
 * @function: lexer_scan
 * @description: Start to check characters. it's entry point of lexer stage.
 * @arguments: nothing
 * @return: Always a pointer of Token struct
 */
Token* lexer_scan()
{
	debug_lexer("lexer_scan");

	lexer.start = lexer.current;
	lexer.pos.index = lexer.pos_end.index;

	Token* t = lexer_skip_space();
	if (t != NULL)
	{
		return t;
	}

	// Again update the position of start...
	lexer.pos.index = lexer.pos_end.index;

	// it's EOF, so return and stop recursice calling!
	if (token_is_end()) return token_make(TOKEN_EOF);

	char c = token_advance();
	if (token_is_digit(c))
	{
		token_recede();
		return lexer_number();
	}
	if (c == '"') return lexer_string();
	if (c == '\'') return lexer_char();

	switch (c)
	{
		// (
		case '(': return token_make(TOKEN_OPERATOR_BRACKET_ROUND_LEFT);
		// )
		case ')': return token_make(TOKEN_OPERATOR_BRACKET_ROUND_RIGHT);
		// [
		case '[': return token_make(TOKEN_OPERATOR_BRACKET_SQUARE_LEFT);
		// ]
		case ']': return token_make(TOKEN_OPERATOR_BRACKET_SQUARE_RIGHT);
		// {
		case '{': return token_make(TOKEN_OPERATOR_BRACKET_CURLY_LEFT);
		// }
		case '}': return token_make(TOKEN_OPERATOR_BRACKET_CURLY_RIGHT);

		// ,
		case ',': return token_make(TOKEN_OPERATOR_COMMA);

		// ?
		case '?': return token_make(TOKEN_OPERATOR_QUESTION);

		// ::
		// :
		case ':': return token_make(token_match(':') ? TOKEN_OPERATOR_COLONCOLON : TOKEN_OPERATOR_COLON);

		// !=
		// !__
		// !_
		// !
		case '!': return token_make(token_match('=') ? TOKEN_OPERATOR_EQUAL_BANG : (token_match('_') ? TOKEN_PRINTDB : (token_match('_') ? TOKEN_PRINTDBNL : TOKEN_OPERATOR_BANG)));

		// &&=
		// &&
		// &=
		// &
		case '&': return token_make(token_match('&') ? (token_match('=') ? TOKEN_OPERATOR_EQUAL_AND : TOKEN_OPERATOR_AND) : (token_match('=') ? TOKEN_OPERATOR_EQUAL_BITWISE_AND : TOKEN_OPERATOR_BITWISE_AND));

		// ||=
		// |=
		// ||
		// |
		case '|': return token_make(token_match('|') ? (token_match('=') ? TOKEN_OPERATOR_EQUAL_OR : TOKEN_OPERATOR_OR) : (token_match('=') ? TOKEN_OPERATOR_EQUAL_BITWISE_OR : TOKEN_OPERATOR_BITWISE_OR));

		// ...
		// ..
		// .
		case '.': return token_make(token_match('.') ? (token_match('.') ? TOKEN_OPERATOR_DOTDOTDOT : TOKEN_OPERATOR_DOTDOT) : TOKEN_OPERATOR_DOT);

		// +=
		// ++
		// +
		case '+': return token_make(token_match('=') ? TOKEN_OPERATOR_EQUAL_PLUS : (token_match('+') ? TOKEN_OPERATOR_PLUSPLUS : TOKEN_OPERATOR_PLUS));

		// -=
		// --
		// -
		case '-': return token_make(token_match('=') ? TOKEN_OPERATOR_EQUAL_MINUS : (token_match('-') ? TOKEN_OPERATOR_MINUSMINUS : TOKEN_OPERATOR_MINUS));

		// *=
		// **
		// *
		case '*': return token_make(token_match('=') ? TOKEN_OPERATOR_EQUAL_STAR : (token_match('*') ? TOKEN_OPERATOR_POWER : TOKEN_OPERATOR_STAR));

		// /=
		// /=
		// //=
		// //
		// /
		case '/': return token_make(token_match('=') ? TOKEN_OPERATOR_EQUAL_SLASH : (token_match('/') ? (token_match('=') ? TOKEN_OPERATOR_EQUAL_SLASH_INT : TOKEN_OPERATOR_SLASH_INT) : TOKEN_OPERATOR_SLASH));

		// >=
		// >>=
		// >>
		// >
		case '>': return token_make(token_match('=') ? TOKEN_OPERATOR_GREATER_EQUAL : (token_match('>') ? (token_match('=') ? TOKEN_OPERATOR_EQUAL_SHIFT_RIGHT : TOKEN_OPERATOR_SHIFT_RIGHT) : TOKEN_OPERATOR_GREATER));

		// <=>
		// <=
		// <<=
		// <<
		// <
		case '<': return token_make(token_match('=') ? (token_match('>') ? TOKEN_OPERATOR_EQUAL_THREE : TOKEN_OPERATOR_LESS_EQUAL) : (token_match('<') ? (token_match('=') ? TOKEN_OPERATOR_EQUAL_SHIFT_LEFT : TOKEN_OPERATOR_SHIFT_LEFT) : TOKEN_OPERATOR_LESS));

		// ===
		// ==
		// =
		case '=': return token_make(token_match('=') ? (token_match('=') ? TOKEN_OPERATOR_EQUAL_EQUAL_EQUAL : TOKEN_OPERATOR_EQUAL_EQUAL) : TOKEN_OPERATOR_EQUAL);

		// %=
		// %
		case '%': return token_make(token_match('=') ? TOKEN_OPERATOR_EQUAL_REMAINDER : TOKEN_OPERATOR_REMAINDER);

		// ;
		case ';': token_match(';'); return lexer_scan();

		default:
			if (token_is_alpha(c))
			{ // _ [a-z] [A-Z]
				token_recede(); // go to prev token (so after that current token will be IS_ALPHA)
				return lexer_identifier(); // now this functions will reads the identifier characters!
			}
			break; // if it's not a alpha character so break the switch cases!
	}

	// if you are here, so probably it's a error/bad token and we unable to parse this token!
	// for example we cannot handle 'ش' as a token!
	// remember: we can handle اتاتیبتنلتنیابلتنیلب as string if you put a " at first and end of that identifier!
	debug_lexer("lexer_scan: last bad character is %c'", *lexer.current);

	char* msg = (char*)malloc(50 * sizeof(char));
	sprintf(msg, "Unexpected '%c' character!", *lexer.current);
	return token_make_error(msg); // return a error token!
}

/*
	advance the token stream to the next token
*/
void advance()
{
	current = lexer_scan();
}

/*
	Is the current token of type t
*/
bool peekFor(TokenType t)
{
	return (current->type == t);
}

/*
 * @function: lexer_free
 * @description: Free allocated memory for the lexer stage! TODO
 * @arguments: nothing
 * @return: nothing, void
 */
void lexer_free()
{
	debug_lexer("lexer_free");

	// free(lexer.start);
	// free(lexer.current);
}
