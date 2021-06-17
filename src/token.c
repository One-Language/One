/**
 The One Programming Language

 File: token.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

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
	debug_token("token_is_alpha");

	return (c >= 'a' && c <= 'z') ||
		 (c >= 'A' && c <= 'Z') ||
		 c == '_';
}

bool token_is_ident(char c)
{
	debug_token("token_is_ident");

	return (c >= 'a' && c <= 'z') ||
		 (c >= 'A' && c <= 'Z') ||
		 c == '_' ||
		 (c >= '0' && c <= '9');
}

bool token_is_digit(char c)
{
	debug_token("token_is_digit");

	return c >= '0' && c <= '9';
}

bool token_is_end()
{
	debug_token("token_is_end");

	return *lexer.current == '\0';
}

char token_recede()
{
	debug_token("token_recede");

	lexer.current--;
	return lexer.current[-1];
}

char token_advance()
{
	debug_token("token_advance");

	lexer.current++;
	return lexer.current[-1];
}

char token_peek()
{
	debug_token("token_peek");

	return *lexer.current;
}

char token_peek_next()
{
	debug_token("token_peek_next");

	if (token_is_end()) return '\0';
	return lexer.current[1];
}

char token_peek_prev()
{
	debug_token("token_peek_prev");

	return lexer.current[-1]; // TODO: Review
}

bool token_match(char expected)
{
	debug_token("token_match");

	if (token_is_end()) return false;
	if (*lexer.current != expected) return false;
	lexer.current++;
	return true;
}

Token* token_make_value(TokenType type, char* value)
{
	debug_token("token_make_string");

	Token* t = malloc(sizeof(Token));
	t->value = value;
	t->type = type;
	t->length = (int)(lexer.current - lexer.start);
	t->loc.line = lexer.loc.line;
	t->loc.column = lexer.loc.column;
	return t;
}

Token* token_make(TokenType type)
{
	debug_token("token_make");

	return token_make_value(type, NULL);
}

Token* token_error(char* message)
{
	debug_token("token_error");

	return token_make_value(TOKEN_ERROR, message);
}

char* token_name(TokenType type)
{
	//	debug_token("token_name");

	switch (type)
	{
		case TOKEN_EOF:
			return "EOF";
		case TOKEN_ERROR:
			return "Error";

		case TOKEN_VALUE_IDENTIFIER:
			return "value_identifier";

		case TOKEN_TYPE_I8:
			return "type_i8";
		case TOKEN_TYPE_I16:
			return "type_i16";
		case TOKEN_TYPE_I32:
			return "type_i32";
		case TOKEN_TYPE_I64:
			return "type_i64";
		case TOKEN_TYPE_I128:
			return "type_i128";

		case TOKEN_TYPE_U8:
			return "type_u8";
		case TOKEN_TYPE_U16:
			return "type_u16";
		case TOKEN_TYPE_U32:
			return "type_u32";
		case TOKEN_TYPE_U64:
			return "type_u64";
		case TOKEN_TYPE_U128:
			return "type_u128";

		case TOKEN_TYPE_F32:
			return "type_f32";
		case TOKEN_TYPE_F64:
			return "type_f64";

		case TOKEN_TYPE_BOOL:
			return "type_bool";
		case TOKEN_TYPE_STRING:
			return "type_string";
		case TOKEN_TYPE_CHAR:
			return "type_char";

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

		case TOKEN_OPERATOR_NONE:
			return "NonOp";

		case TOKEN_OPERATOR_EQUAL_EQUAL:
			return "==";
		case TOKEN_OPERATOR_EQUAL:
			return "=";

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
		case TOKEN_MATCH:
			return "MATCH";
		case TOKEN_FOR:
			return "FOR";
		case TOKEN_DO:
			return "do";

		case TOKEN_RET:
			return "RET";
		case TOKEN_FN:
			return "FN";

			//	case TOKEN_CLASS:
			//	case TOKEN_THIS:
			//	case TOKEN_SUPER:

		case TOKEN_IS:
			return "is";
		case TOKEN_IN:
			return "in";
		case TOKEN_AS:
			return "as";
		case TOKEN_SWITCH:
			return "switch";
		case TOKEN_CASE:
			return "case";
		case TOKEN_BREAK:
			return "break";
		case TOKEN_CONTINUE:
			return "continue";
		case TOKEN_GO:
			return "go";

		case TOKEN_PRINT:
			return "_";
		case TOKEN_PRINTNL:
			return "__";
		case TOKEN_OPERATOR_BANG:
			return "!";
		case TOKEN_OPERATOR_EQUAL_BANG:
			return "!=";
		case TOKEN_PRINTDB:
			return "!_";
		case TOKEN_PRINTDBNL:
			return "!__";

		case TOKEN_PACKAGE:
			return "package";
		case TOKEN_IMPORT:
			return "import";

		case TOKEN_CONST:
			return "CONST";
		case TOKEN_FINAL:
			return "FINAL";
		case TOKEN_STATIC:
			return "static";

		case TOKEN_SEMICOLON:
			return "SEMICOLON";
		default:
			return "UNKNOWN";
	}
}

size_t token_utf8_string_length(char* s)
{
	size_t len = 0;
	for (; *s; ++s)
		if ((*s & 0xC0) != 0x80) ++len;
	return len;
}
