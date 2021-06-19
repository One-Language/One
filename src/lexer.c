/**
 The One Programming Language

 File: lexer.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"

#include "lexer.h"
#include "token.h"

// Global variable(s)
Lexer lexer;

void lexer_init(char* source)
{
	debug_lexer("lexer_init");
	debug_lexer("lexer_init: source is %s", source);

	lexer.start = source;
	lexer.current = source;
	lexer.loc.line = 1;
	lexer.loc.column = 0;
}

TokenType lexer_check_keyword(int start, int length, const char* rest, TokenType type)
{
	debug_lexer("lexer_check_keyword");

	if (lexer.current - lexer.start == start + length &&
		 memcmp(lexer.start + start, rest, length) == 0)
	{
		return type;
	}

	return TOKEN_VALUE_IDENTIFIER;
}

TokenType lexer_identifier_type()
{
	debug_lexer("lexer_identifier_type");

	switch (lexer.start[0])
	{
		case 'i':
			return lexer_check_keyword(1, 1, "f", TOKEN_IF);
	}
	return TOKEN_VALUE_IDENTIFIER;
}

Token* lexer_skip_comment_inline()
{
	debug_lexer("lexer_skip_comment_inline");

	if (token_peek() == '/' && token_peek_next() == '/')
	{
		while (token_peek() != '\n' && !token_is_end()) token_advance();
	}
	return NULL;
}

Token* lexer_skip_comment_multiline()
{
	debug_lexer("lexer_skip_comment_multiline");

	if (token_match('/') && token_match('*'))
	{
		for (;;)
		{
			char c1 = token_advance();
			char c2 = token_peek();
			if (token_is_end()) return token_error("You not close multi-line comment and we face to EOF!");

			if (c1 == '*' && c2 == '/')
			{
				break;
			}
		}
	}

	token_match('/');
	//	if(!token_match('/'))
	//		return token_error("You have to close multi-line comment correctly!");

	return NULL;
}

Token* lexer_skip_whitespace()
{
	debug_lexer("lexer_skip_whitespace");

	Token* t;
	char c, c2;
	for (;;)
	{
		c = token_peek();
		switch (c)
		{
			case ' ':
			case '\t':
			case '\r':
				token_advance();
				break;
			case '\n':
				lexer.loc.line++;
				token_advance();
				break;
			case '/':
				c2 = token_peek_next();
				if (c2 == '/')
				{
					t = lexer_skip_comment_inline();
					if (t != NULL) return t;
				}
				else if (c2 == '*')
				{
					t = lexer_skip_comment_multiline();
					if (t != NULL) return t;
				}
				else
				{
					return NULL;
				}
				break;
			default:
				return NULL;
		}
	}
}

Token* lexer_number()
{
	debug_lexer("lexer_number");

	char* tmp_str = malloc(60 * sizeof(char) + 1);
	size_t i = 0;

	while (token_is_digit(token_peek()))
	{
		//		char c1= token_peek();
		//		char c2 = token_advance();
		//		printf(">>>> %c, %c\n", c1, c2);
		//		printf(">>>> %c, %c\n", token_peek(), token_advance());
		tmp_str[i++] = token_advance();
	}

	if (token_peek() == '.' && token_is_digit(token_peek_next()))
	{
		tmp_str[i++] = token_advance();
		while (token_is_digit(token_peek()))
		{
			tmp_str[i++] = token_advance();
		}
	}
	tmp_str[i] = '\0';

	//	printf("===>%s\n", tmp_str);

	//	return token_make(TOKEN_VALUE_NUMBER);
	return token_make_value(TOKEN_VALUE_NUMBER, tmp_str);
}

Token* lexer_char()
{
	debug_lexer("lexer_char");
	//	char tmp_str[1024] = {};
	char* tmp_str = malloc(1024 * sizeof(char) + 1);
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
		return token_error("Expected ' but found another char!");

	//	return token_make(TOKEN_VALUE_CHAR);
	return token_make_value(TOKEN_VALUE_CHAR, tmp_str);
}

Token* lexer_string()
{
	debug_lexer("lexer_string");

	//	char tmp_str[1024] = {};
	char* tmp_str = malloc(1024 * sizeof(char) + 1);
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

Token* lexer_identifier()
{
	debug_lexer("lexer_identifier");

	//	char tmp_str[1024] = {};
	char* tmp_str = malloc(1024 * sizeof(char) + 1);
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

Token* lexer_scan()
{
	debug_lexer("lexer_scan");

	lexer.start = lexer.current;

	Token* t = lexer_skip_whitespace();
	if (t != NULL)
		return t;

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
		case '(': return token_make(TOKEN_OPERATOR_BRACKET_ROUND_LEFT);
		case ')': return token_make(TOKEN_OPERATOR_BRACKET_ROUND_RIGHT);
		case '[': return token_make(TOKEN_OPERATOR_BRACKET_SQUARE_LEFT);
		case ']': return token_make(TOKEN_OPERATOR_BRACKET_SQUARE_RIGHT);
		case '{': return token_make(TOKEN_OPERATOR_BRACKET_CURLY_LEFT);
		case '}': return token_make(TOKEN_OPERATOR_BRACKET_CURLY_RIGHT);

		case ',': return token_make(TOKEN_OPERATOR_COMMA);
		case '?': return token_make(TOKEN_OPERATOR_QUESTION);
		case ':': return token_make(token_match(':') ? TOKEN_OPERATOR_COLONCOLON : TOKEN_OPERATOR_COLON);

		case '!': return token_make(token_match('=') ? TOKEN_OPERATOR_EQUAL_BANG : TOKEN_OPERATOR_BANG);

		case '&': return token_make(token_match('&') ? (token_match('=') ? TOKEN_OPERATOR_EQUAL_AND: TOKEN_OPERATOR_AND) : (token_match('=') ? TOKEN_OPERATOR_EQUAL_BITWISE_AND : TOKEN_OPERATOR_BITWISE_AND));

		case '|': return token_make(token_match('|') ? (token_match('=') ? TOKEN_OPERATOR_EQUAL_OR: TOKEN_OPERATOR_OR) : (token_match('=') ? TOKEN_OPERATOR_EQUAL_BITWISE_OR : TOKEN_OPERATOR_BITWISE_OR));


		case '.': return token_make(token_match('.') ? (token_match('.') ? TOKEN_OPERATOR_DOTDOTDOT : TOKEN_OPERATOR_DOTDOT) : TOKEN_OPERATOR_DOT);

		case '+': return token_make(token_match('=') ? TOKEN_OPERATOR_EQUAL_PLUS : (token_match('+') ? TOKEN_OPERATOR_PLUSPLUS : TOKEN_OPERATOR_PLUS));
		case '-': return token_make(token_match('=') ? TOKEN_OPERATOR_EQUAL_MINUS : (token_match('-') ? TOKEN_OPERATOR_MINUSMINUS : TOKEN_OPERATOR_MINUS));

		case '*': return token_make(token_match('=') ? TOKEN_OPERATOR_EQUAL_STAR : (token_match('*') ? TOKEN_OPERATOR_POWER : TOKEN_OPERATOR_STAR));
		case '/': return token_make(token_match('=') ? TOKEN_OPERATOR_EQUAL_SLASH : (token_match('/') ? (token_match('=') ? TOKEN_OPERATOR_EQUAL_SLASH_INT : TOKEN_OPERATOR_SLASH_INT) : TOKEN_OPERATOR_SLASH));

		case '>': return token_make(token_match('=') ? TOKEN_OPERATOR_GREATER_EQUAL : (token_match('>') ? (token_match('=') ? TOKEN_OPERATOR_EQUAL_SHIFT_RIGHT : TOKEN_OPERATOR_SHIFT_RIGHT) : TOKEN_OPERATOR_GREATER));
		case '<': return token_make(token_match('=') ? TOKEN_OPERATOR_LESS_EQUAL : (token_match('<') ? (token_match('=') ? TOKEN_OPERATOR_EQUAL_SHIFT_LEFT : TOKEN_OPERATOR_SHIFT_LEFT) : TOKEN_OPERATOR_LESS));
		case '=': return token_make(token_match('=') ? TOKEN_OPERATOR_EQUAL_EQUAL : TOKEN_OPERATOR_EQUAL);
		case ';': token_match(';'); return lexer_scan();

		default:
			if (token_is_alpha(c))
			{ // _ [a-z] [A-Z]
				token_recede();
				return lexer_identifier();
			}
			break;
	}

	debug_lexer("lexer_scan: last bad character is %c'", *lexer.current);

	char* msg = (char*)malloc(50 * sizeof(char));
	sprintf(msg, "Unexpected '%c' character!", *lexer.current);
	return token_error(msg);
}

void lexer_free()
{
	//	free(lexer.start);
	//	free(lexer.current);
}
