//
// Created by max on 6/9/21.
//

#ifndef ONE_TOKEN_H
#define ONE_TOKEN_H

//
// Created by max on 6/9/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
	int line;
	int column;
} Location;

typedef enum
{
	TOKEN_EOF,
	TOKEN_ERROR,

	TOKEN_VALUE_IDENTIFIER,
	TOKEN_VALUE_NUMBER,
	TOKEN_VALUE_STRING,
	TOKEN_VALUE_CHAR,

	TOKEN_VALUE_BOOL_TRUE,
	TOKEN_VALUE_BOOL_FALSE,

	TOKEN_OPERATOR_GREATER, // >
	TOKEN_OPERATOR_GREATER_EQUAL, // >=
	TOKEN_OPERATOR_LESS, // <
	TOKEN_OPERATOR_LESS_EQUAL, // <=

	TOKEN_OPERATOR_PLUS, // +
	TOKEN_OPERATOR_MINUS, // -
	TOKEN_OPERATOR_STAR, // *
	TOKEN_OPERATOR_POWER, // **
	TOKEN_OPERATOR_SLASH, // /
	TOKEN_OPERATOR_SLASH_INT, // //

	TOKEN_OPERATOR_REMAINDER, // %

	TOKEN_OPERATOR_SHIFT_LEFT, // <<
	TOKEN_OPERATOR_SHIFT_RIGHT, // >>

	TOKEN_OPERATOR_AND, // &&
	TOKEN_OPERATOR_BITWISE_AND, //

	TOKEN_OPERATOR_OR, // ||
	TOKEN_OPERATOR_BITWISE_OR, // |

	TOKEN_OPERATOR_BITWISE_XOR, // ^

	TOKEN_OPERATOR_EQUAL_PLUS, // +=
	TOKEN_OPERATOR_EQUAL_MINUS, // -=
	TOKEN_OPERATOR_EQUAL_STAR, // *=
	TOKEN_OPERATOR_EQUAL_POWER, // **=
	TOKEN_OPERATOR_EQUAL_SLASH, // /=
	TOKEN_OPERATOR_EQUAL_SLASH_INT, // //=
	TOKEN_OPERATOR_EQUAL_SHIFT_LEFT, // <<=
	TOKEN_OPERATOR_EQUAL_SHIFT_RIGHT, // >>=

	TOKEN_IF, // if
	TOKEN_ELSE, // else
	TOKEN_WHILE, // while
	TOKEN_FOR, // while
	TOKEN_FOR, // for
	TOKEN_RETURN, // ret
	TOKEN_FN, // fn
	TOKEN_CONST, // const
	TOKEN_FINAL, // final

//	TOKEN_CLASS, // class
//	TOKEN_THIS, // this
//	TOKEN_SUPER, // super

	TOKEN_SEMICOLON, // ;

} TokenType;

typedef struct
{
	TokenType type;
	const char* start;
	size_t length;
	Location loc;
} Token;

static bool token_is_alpha(char c);

static bool token_is_digit(char c);

static bool token_is_end();

static char token_advance();

static char token_peek();

static char token_peek_next();

static char token_peek_prev();

static bool token_match(char expected);

static Token token_make(TokenType type);

static Token token_error(const char* message);

static void token_skip_comment_inline();

static void token_skip_comment_multiline();

static void token_skip_whitespace();

#endif //ONE_TOKEN_H
