//
// Created by max on 6/9/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "token.h"

static bool token_is_alpha(char c)
{
	return (c >= 'a' && c <= 'z') ||
		 (c >= 'A' && c <= 'Z') ||
		 c == '_';
}

static bool token_is_digit(char c)
{
	return c >= '0' && c <= '9';
}

static bool token_is_end()
{
	return *lexer.current == '\0';
}

static char token_advance()
{
	lexer.current++;
	return lexer.current[-1];
}

static char token_peek()
{
	return *lexer.current;
}

static char token_peek_next()
{
	if (token_is_end()) return '\0';
	return lexer.current[1];
}

static char token_peek_prev()
{
	if (token_is_end()) return '\0';
	return lexer.current[-1]; // TODO: Review
}

static bool token_match(char expected)
{
	if (token_is_end()) return false;
	if (*lexer.current != expected) return false;
	lexer.current++;
	return true;
}

static Token token_make(TokenType type)
{
	Token t;
	t.type = type;
	t.start = lexer.start;
	t.length = (int)(lexer.current - lexer.start);
	t.loc.line = lexer.line;
	t.loc.column = lexer.column;
	return t;
}

static Token token_error(const char* message)
{
	Token t;
	t.type = TOKEN_ERROR;
	t.start = message;
	t.length = (int)strlen(message);
	t.loc.line = lexer.loc.line;
	t.loc.column = lexer.loc.column;
	return t;
}

static void token_skip_comment_inline()
{
	if (token_peek() == '/' && token_peek_next() == '/')
	{
		while (token_peek() != '\n' && !token_is_end()) token_advance();
	}
}

static void token_skip_comment_multiline()
{
	if (token_peek() == '/' && token_peek_next() == '*')
	{
		for (;;)
		{
			char c1 = token_peek();
			char c2 = token_peek_next();
			if (c1 == '*' && c2 == '/')
			{
				break;
			}
		}
	}
}

static void token_skip_whitespace()
{
	for (;;)
	{
		char c = token_peek();
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
				char c2 = token_peek_next();
				if (c2 == '/')
				{
					token_skip_comment_inline();
				}
				else if (c2 == '*')
				{
					token_skip_comment_multiline();
				}
				else
				{
					return;
				}
				break;
			default:
				return;
		}
	}
}
