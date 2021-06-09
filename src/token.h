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

typedef struct _location Location;

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
	TOKEN_OPERATOR_PLUSPLUS, // ++
	TOKEN_OPERATOR_MINUS, // -
	TOKEN_OPERATOR_MINUSMINUS, // --
	TOKEN_OPERATOR_STAR, // *
	TOKEN_OPERATOR_POWER, // **
	TOKEN_OPERATOR_SLASH, // /
	TOKEN_OPERATOR_SLASH_INT, // //

	TOKEN_OPERATOR_REMAINDER, // %
	TOKEN_OPERATOR_COMMA, // ,
	TOKEN_OPERATOR_COLON, // :
	TOKEN_OPERATOR_COLONCOLON, // ::
	TOKEN_OPERATOR_QUESTION, // ?
	TOKEN_OPERATOR_DOT, // .
	TOKEN_OPERATOR_DOTDOT, // ..
	TOKEN_OPERATOR_DOTDOTDOT, // ...

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

	TOKEN_OPERATOR_BRACKET_ROUND_LEFT, // (
	TOKEN_OPERATOR_BRACKET_ROUND_RIGHT, // )

	TOKEN_OPERATOR_BRACKET_SQUARE_LEFT, // [
	TOKEN_OPERATOR_BRACKET_SQUARE_RIGHT, // ]

	TOKEN_OPERATOR_BRACKET_CURLY_LEFT, // {
	TOKEN_OPERATOR_BRACKET_CURLY_RIGHT, // }

	TOKEN_SEMICOLON, // ;

	TOKEN_IF, // if
	TOKEN_ELSE, // else
	TOKEN_WHILE, // while
	TOKEN_FOR, // for
	TOKEN_RET, // ret
	TOKEN_FN, // fn
	TOKEN_CONST, // const
	TOKEN_FINAL, // final


	//	TOKEN_CLASS, // class
	//	TOKEN_THIS, // this
	//	TOKEN_SUPER, // super

} TokenType;

typedef struct _token
{
	TokenType type;
	const char* start;
	size_t length;
	Location loc;
} Token;

bool token_is_alpha(char c);

bool token_is_ident(char c);

bool token_is_digit(char c);

bool token_is_end();

char token_advance();

char token_peek();

char token_peek_next();

char token_peek_prev();

bool token_match(char expected);

Token token_make(TokenType type);

Token token_error(const char* message);

void token_skip_comment_inline();

void token_skip_comment_multiline();

void token_skip_whitespace();

char* token_name(TokenType type);

#endif //ONE_TOKEN_H
