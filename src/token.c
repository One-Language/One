//
// Created by max on 6/9/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "error.h"
#include "lexer.h"

#include "token.h"

// Global variable(s)
extern Lexer lexer;

bool token_is_alpha(char c)
{
	debug("token_is_alpha");

	return (c >= 'a' && c <= 'z') ||
		 (c >= 'A' && c <= 'Z') ||
		 c == '_';
}

bool token_is_ident(char c)
{
	debug("token_is_ident");

	return (c >= 'a' && c <= 'z') ||
		 (c >= 'A' && c <= 'Z') ||
		 c == '_' ||
		 (c >= '0' && c <= '9');
}

bool token_is_digit(char c)
{
	debug("token_is_digit");

	return c >= '0' && c <= '9';
}

bool token_is_end()
{
	debug("token_is_end");

	return *lexer.current == '\0';
}

char token_recede() {
	debug("token_recede");

	lexer.current--;
	return lexer.current[-1];
}

char token_advance()
{
	debug("token_advance");

	lexer.current++;
	return lexer.current[-1];
}

char token_peek()
{
	debug("token_peek");

	return *lexer.current;
}

char token_peek_next()
{
	debug("token_peek_next");

	if (token_is_end()) return '\0';
	return lexer.current[1];
}

char token_peek_prev()
{
	debug("token_peek_prev");

	if (token_is_end()) return '\0';
	return lexer.current[-1]; // TODO: Review
}

bool token_match(char expected)
{
	debug("token_match");

	if (token_is_end()) return false;
	if (*lexer.current != expected) return false;
	lexer.current++;
	return true;
}

Token token_make(TokenType type)
{
	debug("token_make");

	Token t;
	t.type = type;
	t.start = lexer.start;
	t.length = (int)(lexer.current - lexer.start);
	t.loc.line = lexer.loc.line;
	t.loc.column = lexer.loc.column;
	return t;
}

Token token_error(const char* message)
{
	debug("token_error");

	Token t;
	t.type = TOKEN_ERROR;
	t.start = message;
	t.length = (int)strlen(message);
	t.loc.line = lexer.loc.line;
	t.loc.column = lexer.loc.column;
	return t;
}

void token_skip_comment_inline()
{
	debug("token_skip_comment_inline");

	if (token_peek() == '/' && token_peek_next() == '/')
	{
		while (token_peek() != '\n' && !token_is_end()) token_advance();
	}
}

void token_skip_comment_multiline()
{
	debug("token_skip_comment_multiline");

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

void token_skip_whitespace()
{
	debug("token_skip_whitespace");

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

char* token_name(TokenType type)
{
	debug("token_name");

	switch (type)
	{
		case TOKEN_EOF:
			return "EOF";
		case TOKEN_ERROR:
			return "Error";

		case TOKEN_VALUE_IDENTIFIER:
			return "value_identifier";

		case TOKEN_VALUE_NUMBER:
			return "value_number";
		case TOKEN_VALUE_STRING:
			return "value_string";
		case TOKEN_VALUE_CHAR:
			return "value_char";

		case TOKEN_VALUE_BOOL_TRUE:
			return "value_true";
		case TOKEN_VALUE_BOOL_FALSE:
			return "value_false";

		case TOKEN_OPERATOR_GREATER:
			return ">";
		case TOKEN_OPERATOR_GREATER_EQUAL:
			return "<=";
		case TOKEN_OPERATOR_LESS:
			return "<";
		case TOKEN_OPERATOR_LESS_EQUAL:
			return "<=";

		case TOKEN_OPERATOR_PLUS:
			return "+";
		case TOKEN_OPERATOR_PLUSPLUS:
			return "++";
		case TOKEN_OPERATOR_MINUS:
			return "-";
		case TOKEN_OPERATOR_MINUSMINUS:
			return "--";
		case TOKEN_OPERATOR_STAR:
			return "*";
		case TOKEN_OPERATOR_POWER:
			return "**";
		case TOKEN_OPERATOR_SLASH:
			return "/";
		case TOKEN_OPERATOR_SLASH_INT:
			return "//";

		case TOKEN_OPERATOR_REMAINDER:
			return "%";

		case TOKEN_OPERATOR_SHIFT_LEFT:
			return "<<";
		case TOKEN_OPERATOR_SHIFT_RIGHT:
			return ">>";

		case TOKEN_OPERATOR_AND:
			return "&&";
		case TOKEN_OPERATOR_BITWISE_AND:
			return "&";

		case TOKEN_OPERATOR_OR:
			return "||";
		case TOKEN_OPERATOR_BITWISE_OR:
			return "|";

		case TOKEN_OPERATOR_BITWISE_XOR:
			return "^";

		case TOKEN_OPERATOR_EQUAL_PLUS:
			return "+=";
		case TOKEN_OPERATOR_EQUAL_MINUS:
			return "-=";
		case TOKEN_OPERATOR_EQUAL_STAR:
			return "*=";
		case TOKEN_OPERATOR_EQUAL_POWER:
			return "**=";
		case TOKEN_OPERATOR_EQUAL_SLASH:
			return "/=";
		case TOKEN_OPERATOR_EQUAL_SLASH_INT:
			return "//=";
		case TOKEN_OPERATOR_EQUAL_SHIFT_LEFT:
			return "<<=";
		case TOKEN_OPERATOR_EQUAL_SHIFT_RIGHT:
			return ">>=";

		case TOKEN_OPERATOR_BRACKET_ROUND_LEFT:
			return "(";
		case TOKEN_OPERATOR_BRACKET_ROUND_RIGHT:
			return ")";

		case TOKEN_OPERATOR_BRACKET_SQUARE_LEFT:
			return "[";
		case TOKEN_OPERATOR_BRACKET_SQUARE_RIGHT:
			return "]";

		case TOKEN_OPERATOR_BRACKET_CURLY_LEFT:
			return "{";
		case TOKEN_OPERATOR_BRACKET_CURLY_RIGHT:
			return "}";

		case TOKEN_OPERATOR_COMMA:
			return ",";
		case TOKEN_OPERATOR_COLON:
			return ":";
		case TOKEN_OPERATOR_COLONCOLON:
			return "::";
		case TOKEN_OPERATOR_QUESTION:
			return "?";
		case TOKEN_OPERATOR_DOT:
			return ".";
		case TOKEN_OPERATOR_DOTDOT:
			return "..";
		case TOKEN_OPERATOR_DOTDOTDOT:
			return "...";

		case TOKEN_IF:
			return "IF";
		case TOKEN_ELSE:
			return "ELSE";
		case TOKEN_WHILE:
			return "WHILE";
		case TOKEN_FOR:
			return "FOR";
		case TOKEN_RET:
			return "RET";
		case TOKEN_FN:
			return "FN";
		case TOKEN_CONST:
			return "CONST";
		case TOKEN_FINAL:
			return "FINAL";

			//	case TOKEN_CLASS:
			//	case TOKEN_THIS:
			//	case TOKEN_SUPER:

		case TOKEN_SEMICOLON:
			return "SEMICOLON";
		default:
			return "UNKNOWN";
	}
}
