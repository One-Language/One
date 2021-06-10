//
// Created by max on 6/9/21.
//

#include <stdio.h>
#include <stdlib.h>

#include "error.h"

#include "lexer.h"
#include "token.h"

// Global variable(s)
Lexer lexer;

void lexer_init(char* source)
{
	debug("lexer_init");
	debug("lexer_init: source is %s", source);

	lexer.start = source;
	lexer.current = source;
	lexer.loc.line = 1;
	lexer.loc.column = 0;
}

Token* lexer_skip_comment_inline()
{
	debug("lexer_skip_comment_inline");

	if (token_peek() == '/' && token_peek_next() == '/')
	{
		while (token_peek() != '\n' && !token_is_end()) token_advance();
	}
	return NULL;
}

Token* lexer_skip_comment_multiline()
{
	debug("lexer_skip_comment_multiline");

	if (token_match('/') && token_match('*'))
	{
		for (;;)
		{
			char c1 = token_advance();
			char c2 = token_peek();
			if (token_is_end()) token_error("You not close multi-line comment and we face to EOF!");

			if (c1 == '*' && c2 == '/')
			{
				break;
			}
		}
	}
	return NULL;
}

Token* lexer_skip_whitespace()
{
	debug("lexer_skip_whitespace");

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
					return lexer_skip_comment_inline();
				}
				else if (c2 == '*')
				{
					return lexer_skip_comment_multiline();
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
	while (token_is_digit(token_peek()))
		token_advance();

	if (token_peek() == '.' && token_is_digit(token_peek_next()))
	{
		token_advance();
		while (token_is_digit(token_peek()))
			token_advance();
	}

	return token_make(TOKEN_VALUE_NUMBER);
}

Token* lexer_char()
{
	debug("lexer_char");
	char tmp_str[1024] = {};
	size_t i = 0;

	token_match('\'');
	while (token_peek() != '\'' && !token_is_end())
	{
		tmp_str[i++] = token_peek();
		if (token_utf8_string_length(tmp_str) > 1) break;
		token_advance();
	}
	tmp_str[i] = '\0';

	debug("lexer_char: tmp_str is '%s'", tmp_str);
	debug("lexer_char: tmp_str utf8 length is %zu", token_utf8_string_length(tmp_str));

	if (!token_match('\''))
		return token_error("Expected ' but found another char!");

	return token_make(TOKEN_VALUE_CHAR);
}

Token* lexer_string()
{
	debug("lexer_string");

	token_match('"');
	while (token_peek() != '"' && !token_is_end())
		token_advance();
	token_match('"');

	return token_make(TOKEN_VALUE_STRING);
}

Token* lexer_scan()
{
	debug("lexer_scan");

	lexer.start = lexer.current;

	Token* t = lexer_skip_whitespace();
	if (t != NULL)
		return t;

	if (token_is_end()) return token_make(TOKEN_EOF);

	//	printf("-->%c\n", *lexer.current);
	//	char c1 = token_advance();
	//	printf("-->%c\n", c1);
	//	printf("-->%c\n", *lexer.current);
	//	printf("token_peek_next is: %c\n", token_peek_next());
	//	printf("token_peek_prev is: %c\n", token_peek_prev());
	//	printf("-->%c\n", *lexer.current);
	//
	//	exit(1);
	//	lexer.current++;
	//	return token_error("");

	char c = token_advance();
	if (token_is_digit(c)) return lexer_number();
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

		case ',': return token_make(TOKEN_OPERATOR_BRACKET_CURLY_RIGHT);
		case '?': return token_make(TOKEN_OPERATOR_QUESTION);
		case ':': return token_make(token_match(':') ? TOKEN_OPERATOR_COLONCOLON : TOKEN_OPERATOR_COLON);
		case '.': return token_make(token_match('.') ? (token_match('.') ? TOKEN_OPERATOR_DOTDOTDOT : TOKEN_OPERATOR_DOTDOT) : TOKEN_OPERATOR_DOT);

		case '+': return token_make(token_match('+') ? TOKEN_OPERATOR_PLUSPLUS : TOKEN_OPERATOR_PLUS);
		case '-': return token_make(token_match('-') ? TOKEN_OPERATOR_MINUSMINUS : TOKEN_OPERATOR_MINUS);

		case '*': return token_make(token_match('*') ? TOKEN_OPERATOR_POWER : TOKEN_OPERATOR_STAR);
		case '/': return token_make(token_match('/') ? TOKEN_OPERATOR_SLASH_INT : TOKEN_OPERATOR_SLASH);

		case '>': return token_make(token_match('=') ? TOKEN_OPERATOR_GREATER_EQUAL : (token_match('>') ? (token_match('=') ? TOKEN_OPERATOR_EQUAL_SHIFT_RIGHT : TOKEN_OPERATOR_SHIFT_RIGHT) : TOKEN_OPERATOR_GREATER));
		case '<': return token_make(token_match('=') ? TOKEN_OPERATOR_LESS_EQUAL : (token_match('<') ? (token_match('=') ? TOKEN_OPERATOR_EQUAL_SHIFT_LEFT : TOKEN_OPERATOR_SHIFT_LEFT) : TOKEN_OPERATOR_LESS));

		case ';': token_match(';'); return lexer_scan();
	}

	return token_error("Unexpected character.");
}

void lexer_free()
{
	//	free(lexer.start);
	//	free(lexer.current);
}
