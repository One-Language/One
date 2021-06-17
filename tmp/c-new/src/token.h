/**
 The One Programming Language

 File: token.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <stdio.h>
#include <stdlib.h>
//#include <malloc.h>
#include <stdbool.h>
#include <string.h>

typedef struct _lexer Lexer;

typedef struct _location
{
	size_t line; // line number: default is 1
	size_t column; // column number: default is 0
} Location;

typedef enum _token_type
{
	TOKEN_EOF = -1,
	TOKEN_UNKNOWM,
	// ================= keywords
	TOKEN_EXTERN,
	TOKEN_CONST,
	TOKEN_FINAL,
	TOKEN_RETURN,
	TOKEN_IF,
	TOKEN_ELSE,
	TOKEN_DO,
	TOKEN_WHILE,
	TOKEN_FOR,
	TOKEN_SWTICH,
	TOKEN_CONTINUE,
	TOKEN_BREAK,
	TOKEN_PACKAGE,
	TOKEN_IMPORT,
	TOKEN_IN,
	TOKEN_IS,
	TOKEN_AS,
	TOKEN_NULL,
	TOKEN_STATIC,
	TOKEN_THIS,
	TOKEN_SUPER,
	TOKEN_TRUE,
	TOKEN_FALSE,
	// ================= prints
	TOKEN_PRINT,
	TOKEN_PRINTNL,
	TOKEN_PRINTDB,
	TOKEN_PRINTNLDB,
	// ================= values
	TOKEN_VALUE_IDENTIFIER,
	TOKEN_VALUE_STRING,
	TOKEN_VALUE_NUMBER,
	TOKEN_VALUE_BOOL,
	// ================= types
	TOKEN_TYPE_ANY,
	TOKEN_TYPE_SIZE,

	TOKEN_TYPE_I8,
	TOKEN_TYPE_I16,
	TOKEN_TYPE_I32,
	TOKEN_TYPE_I64,
	TOKEN_TYPE_I128,

	TOKEN_TYPE_U8,
	TOKEN_TYPE_U16,
	TOKEN_TYPE_U32,
	TOKEN_TYPE_U64,
	TOKEN_TYPE_U128,

	TOKEN_TYPE_F32,
	TOKEN_TYPE_F64,

	TOKEN_TYPE_BOOL,
	TOKEN_TYPE_CHAR,
	TOKEN_TYPE_STRING,
	// ================= operators
	TOKEN_OPERATOR_DOLLAR, // $

	TOKEN_OPERATOR_PLUS, // +
	TOKEN_OPERATOR_PLUSPLUS, //++

	TOKEN_OPERATOR_MINUS, // -
	TOKEN_OPERATOR_MINUSMINUS, // --

	TOKEN_OPERATOR_MUL, // *
	TOKEN_OPERATOR_POW, // **

	TOKEN_OPERATOR_DIV, // /
	TOKEN_OPERATOR_DIVINT, // //

	TOKEN_OPERATOR_BIT_AND, // &
	TOKEN_OPERATOR_AND, // &&

	TOKEN_OPERATOR_NOT, // !

	TOKEN_OPERATOR_BIT_OR, // |
	TOKEN_OPERATOR_BIT_XOR, // ^
	TOKEN_OPERATOR_OR, // ||

	TOKEN_OPERATOR_EQUAL, // =
	TOKEN_OPERATOR_EQUALEQUAL, // =
	TOKEN_OPERATOR_EQUALEQUALEQUAL, // ===

	TOKEN_OPERATOR_NOTEQUAL, // !=
	TOKEN_OPERATOR_NOTEQUALEQUAL, // !==

	TOKEN_OPERATOR_DOT, // .
	TOKEN_OPERATOR_DOTDOT, // ..
	TOKEN_OPERATOR_DOTDOTDOT, // ...

	TOKEN_OPERATOR_COLON, // :
	TOKEN_OPERATOR_COLONCOLON, // ::

	TOKEN_OPERATOR_IF, // ... ? ... : ...
	TOKEN_OPERATOR_IFIF, // ??
	TOKEN_OPERATOR_DIRECT, // <value>

	TOKEN_OPERATOR_SEMICOLON, // ;
	TOKEN_OPERATOR_VIRGOOL, // ,

	TOKEN_OPERATOR_SHIFT_RIGHT, // <<
	TOKEN_OPERATOR_SHIFT_LEFT, // >>

	TOKEN_OPERATOR_REM, // %

	TOKEN_OPERATOR_G, // >
	TOKEN_OPERATOR_GE, // >=

	TOKEN_OPERATOR_L, // <
	TOKEN_OPERATOR_LE, // <=

	// ================= other operators
	TOKEN_SECTION_OPEN, // {
	TOKEN_SECTION_CLOSE, // }

	TOKEN_BRACKET_OPEN, // ( round
	TOKEN_BRACKET_CLOSE, // ) round

	TOKEN_SQUARE_OPEN, // [
	TOKEN_SQUARE_CLOSE, // ]

	TOKEN_OPERATOR_QUESTION, // ?
	TOKEN_OPERATOR_QUESTIONQUESTION, // ??
} TokenType;

typedef struct _token
{
	TokenType type;
	Location location;

	int vint;
	char *vstring;
} Token;

typedef struct _keyword
{
	const char *identifier;
	size_t length;
	TokenType type;
	bool caseSensetice; // true = lowercase or uppervase not matter, flase means full equal `===`
} Keyword;

static Keyword keywords[] = {
	 {"_", 1, TOKEN_PRINT, false},
	 {"__", 2, TOKEN_PRINTNL, false},
	 {"!_", 2, TOKEN_PRINTDB, false},
	 {"!__", 3, TOKEN_PRINTNLDB, false},

	 {"switch", 6, TOKEN_SWTICH, false},
	 {"break", 5, TOKEN_BREAK, false},
	 {"continue", 8, TOKEN_CONTINUE, false},

	 {"package", 7, TOKEN_PACKAGE, false},
	 {"import", 6, TOKEN_IMPORT, false},

	 {"if", 2, TOKEN_IF, false},
	 {"else", 4, TOKEN_ELSE, false},

	 {"while", 5, TOKEN_WHILE, false},
	 {"for", 3, TOKEN_FOR, false},
	 {"in", 2, TOKEN_IN, false},
	 {"as", 2, TOKEN_AS, false},

	 {"is", 2, TOKEN_IS, false},
	 {"null", 4, TOKEN_NULL, false},
	 {"ret", 3, TOKEN_RETURN, false},
	 {"static", 6, TOKEN_STATIC, false},

	 {"this", 4, TOKEN_THIS, false},
	 {"super", 5, TOKEN_SUPER, false},

	 {"false", 5, TOKEN_FALSE, false},
	 {"true", 4, TOKEN_TRUE, false},

	 // data types
	 {"i8", 2, TOKEN_TYPE_I8, true},
	 {"i16", 3, TOKEN_TYPE_I16, true},
	 {"i32", 3, TOKEN_TYPE_I32, true},
	 {"i64", 3, TOKEN_TYPE_I64, true},
	 {"f32", 3, TOKEN_TYPE_F32, true},
	 {"f64", 3, TOKEN_TYPE_F64, true},

	 {NULL, 0, TOKEN_EOF, false} // Sentinel to mark the end of the array.
};

void token_init();

bool token_is_space(char);

bool token_is_line(char);

bool token_is_freespace(char);

bool token_is_freeline(char);

bool token_is_free(char);

bool token_is_alphaasci(char);

bool token_is_alpha(char);

bool token_is_number(char);

bool token_is_digit(char);

bool token_is_ident(char);

bool token_is_eof(char);

bool tokenEOF(Lexer *);

void tokenNextChar(Lexer *);

void tokenPrevChar(Lexer *);

Token *tokenNext(Lexer *);

char *tokenName(TokenType);

#endif
