/**
 The One Programming Language

 File: tokenizer/token.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef _ONE_TOKENIZER_TOKEN_H_
#define _ONE_TOKENIZER_TOKEN_H_

#include <stdlib.h>
#include <stdbool.h>

typedef enum _token_type
{
	TOKEN_EOF = 0,
	TOKEN_ERROR,

	TOKEN_SKIP_WHITESPACE,
	TOKEN_SKIP_WHITESPACE_LINE,
	TOKEN_SKIP_COMMENT_SINGLE,
	TOKEN_SKIP_COMMENT_MULTI,

	TOKEN_VALUE_NUMBER,
	TOKEN_VALUE_STRING,
	TOKEN_VALUE_CHAR,

	TOKEN_VALUE_IDENTIFIER,

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
	TOKEN_TYPE_STRING,
	TOKEN_TYPE_CHAR,

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

	TOKEN_OPERATOR_EQUAL_REMAINDER, // %=
	TOKEN_OPERATOR_EQUAL_PLUS, // +=
	TOKEN_OPERATOR_EQUAL_MINUS, // -=
	TOKEN_OPERATOR_EQUAL_STAR, // *=
	TOKEN_OPERATOR_EQUAL_POWER, // **=
	TOKEN_OPERATOR_EQUAL_SLASH, // /=
	TOKEN_OPERATOR_EQUAL_SLASH_INT, // //=
	TOKEN_OPERATOR_EQUAL_SHIFT_LEFT, // <<=
	TOKEN_OPERATOR_EQUAL_SHIFT_RIGHT, // >>=

	TOKEN_OPERATOR_EQUAL_THREE, // <=>

	TOKEN_OPERATOR_EQUAL_AND, // &&=
	TOKEN_OPERATOR_EQUAL_BITWISE_AND, // &=

	TOKEN_OPERATOR_EQUAL_OR, // ||=
	TOKEN_OPERATOR_EQUAL_BITWISE_OR, // |=

	TOKEN_OPERATOR_BRACKET_ROUND_LEFT, // (
	TOKEN_OPERATOR_BRACKET_ROUND_RIGHT, // )

	TOKEN_OPERATOR_NONE, // none

	TOKEN_OPERATOR_BRACKET_SQUARE_LEFT, // [
	TOKEN_OPERATOR_BRACKET_SQUARE_RIGHT, // ]

	TOKEN_OPERATOR_BRACKET_CURLY_LEFT, // {
	TOKEN_OPERATOR_BRACKET_CURLY_RIGHT, // }

	TOKEN_OPERATOR_BANG, // !
	TOKEN_OPERATOR_EQUAL_BANG, // !=

	TOKEN_OPERATOR_EQUAL, // =
	TOKEN_OPERATOR_EQUAL_EQUAL, // ==
	TOKEN_OPERATOR_EQUAL_EQUAL_EQUAL, // ===

	TOKEN_SEMICOLON, // ;

	TOKEN_PRINT, // _
	TOKEN_PRINTNL, // __
	TOKEN_PRINTDB, // !_
	TOKEN_PRINTDBNL, // !__

	TOKEN_IF, // if
	TOKEN_ELSE, // else

	//	TOKEN_WHILE, // while
	TOKEN_FOR, // for
	//	TOKEN_DO, // do
	TOKEN_MATCH, // match

	TOKEN_RET, // ret
	TOKEN_FN, // fn
	TOKEN_CONST, // const
	TOKEN_FINAL, // final
	TOKEN_STATIC, // static

	TOKEN_PACKAGE, // package
	TOKEN_IMPORT, // import
	TOKEN_IN, // in
	TOKEN_IS, // is
	TOKEN_AS, // as

	TOKEN_ASSERT,
	TOKEN_STRUCT,
	TOKEN_TYPE,
	TOKEN_INTERFACE,

	TOKEN_SWITCH, // switch
	TOKEN_CASE, // case
	TOKEN_BREAK, // break
	TOKEN_CONTINUE, // continue
	TOKEN_GO, // go

	//	TOKEN_CLASS, // class
	//	TOKEN_THIS, // this
	//	TOKEN_SUPER, // super

} TokenType;

typedef struct _location
{
	size_t tokens; // index of current token: default is 0
	size_t index; // file source index' character: default is 0
	size_t line; // line number: default is 1
	size_t column; // column number: default is 0
} Location;

typedef struct _token
{
	TokenType type;

	const char* value;
	size_t length;
	Location pos;
	Location pos_end;
} Token;

typedef struct _keyword
{
	const char* identifier;
	size_t length;
	TokenType type;
	bool caseSensitive; // true = lowercase or uppercase not matter, false means full equal `===`
} Keyword;

static Keyword keywords[] = {
	 {"_", 1, TOKEN_PRINT, false},
	 {"__", 2, TOKEN_PRINTNL, false},

	 {"switch", 6, TOKEN_SWITCH, false},
	 {"break", 5, TOKEN_BREAK, false},
	 {"continue", 8, TOKEN_CONTINUE, false},
	 {"case", 4, TOKEN_CASE, false},

	 {"package", 7, TOKEN_PACKAGE, false},
	 {"import", 6, TOKEN_IMPORT, false},

	 {"fn", 2, TOKEN_FN, false},
	 {"if", 2, TOKEN_IF, false},
	 {"else", 4, TOKEN_ELSE, false},

	 //	 {"do", 2, TOKEN_DO, false},
	 //	 {"while", 5, TOKEN_WHILE, false},
	 {"for", 3, TOKEN_FOR, false},
	 {"match", 5, TOKEN_MATCH, false},

	 {"in", 2, TOKEN_IN, false},
	 {"as", 2, TOKEN_AS, false},
	 {"is", 2, TOKEN_IS, false},

	 {"ret", 3, TOKEN_RET, false},
	 //	 {"return", 6, TOKEN_RETURN, false},

	 {"assert", 6, TOKEN_ASSERT, false},
	 {"struct", 6, TOKEN_STRUCT, false},
	 {"type", 4, TOKEN_TYPE, false},
	 {"interface", 9, TOKEN_INTERFACE, false},

	 {"static", 6, TOKEN_STATIC, false},
	 {"final", 5, TOKEN_FINAL, false},
	 {"const", 5, TOKEN_CONST, false},

	 {"false", 5, TOKEN_VALUE_BOOL_FALSE, false},
	 {"true", 4, TOKEN_VALUE_BOOL_TRUE, false},

	 // data types
	 {"int", 3, TOKEN_TYPE_I32, false},
	 {"i8", 2, TOKEN_TYPE_I8, false},
	 {"i16", 3, TOKEN_TYPE_I16, false},
	 {"i32", 3, TOKEN_TYPE_I32, false},
	 {"i64", 3, TOKEN_TYPE_I64, false},

	 {"uint", 3, TOKEN_TYPE_U32, false},
	 {"u8", 2, TOKEN_TYPE_U8, false},
	 {"u16", 3, TOKEN_TYPE_U16, false},
	 {"u32", 3, TOKEN_TYPE_U32, false},
	 {"u64", 3, TOKEN_TYPE_U64, false},

	 {"float", 5, TOKEN_TYPE_F32, false},
	 {"f32", 3, TOKEN_TYPE_F32, false},
	 {"f64", 3, TOKEN_TYPE_F64, false},

	 //	 {"!_", 2, TOKEN_PRINTDB, false},
	 //	 {"!__", 3, TOKEN_PRINTDBNL, false},

	 {NULL, 0, TOKEN_VALUE_IDENTIFIER, false} // Sentinel to mark the end of the array.
};

/*
 * @function: token_is_alpha
 * @description: check a char is a-z or A-Z or _
 * @arguments: char c is a character input
 * @return: bool, true or false
 */
bool token_is_alpha(char c);

/*
 * @function: token_is_ident
 * @description: check a char is a-z or A-Z or _ or 0-9
 * @arguments: char c is a character input
 * @return: bool, true or false
 */
bool token_is_ident(char c);

/*
 * @function: token_is_digit
 * @description: check a char is 0-9 (Not - +)
 * @arguments: char c is a character input
 * @return: bool, true or false
 */
bool token_is_digit(char c);

/*
 * @function: token_is_end
 * @description: check a char is \0 EOF
 * @arguments: char c is a character input
 * @return: bool, true or false
 */
bool token_is_end();

/*
 * @function: token_recede
 * @description: return -1th character of current source code
 * @arguments: nothing
 * @return: char, if not exists will be ... (TODO)
 */
char token_recede();

/*
 * @function: token_recede_next
 * @description: go to back character of current source code and return it
 * @arguments: nothing
 * @return: char, if not exists will be ... (TODO)
 */
char token_recede_next();

/*
 * @function: token_recede_next_next
 * @description: return current character of current source code and go to back
 * @arguments: nothing
 * @return: char, if not exists will be ... (TODO)
 */
char token_recede_next_next();

/*
 * @function: token_advance
 * @description: return current character and go to next position of the source code
 * @arguments: nothing
 * @return: char
 */
char token_advance();

/*
 * @function: token_advance_next
 * @description: go to next position of the source code and return it
 * @arguments: nothing
 * @return: char
 */
char token_advance_next();

/*
 * @function: token_peek
 * @description: return current character of current source code
 * @arguments: nothing
 * @return: char
 */
char token_peek();

/*
 * @function: token_peek_next
 * @description: return next character of current source code
 * @arguments: nothing
 * @return: char
 */
char token_peek_next();

/*
 * @function: token_peek_prev
 * @description: return prev character of current source code
 * @arguments: nothing
 * @return: char
 */
char token_peek_prev();

/*
 * @function: token_match
 * @description: check current character of lexer is equal to `expected`, it's yes or no
 * @arguments: char expected
 * @return: bool, true or false
 */
bool token_match(char expected);

/*
 * @function: token_make
 * @description: create a pointer to Token struct without value
 * @arguments: TokenType
 * @return: A pointer to Token struct
 */
Token* token_make(TokenType type);

/*
 * @function: token_make_value
 * @description: create a pointer to Token struct with a value
 * @arguments: TokenType and a char* value
 * @return: A pointer to Token struct
 */
Token* token_make_value(TokenType type, char* value);

/*
 * @function: token_make_error
 * @description: create a pointer to a Error Token struct with a error message
 * @arguments: char* error message
 * @return: A pointer to Token struct
 */
Token* token_make_error(char* message);

/*
 * @function: token_name
 * @description: convert TokenType to token name as char*
 * @arguments: TokenType type
 * @return: char*: token name
 */
char* token_name(TokenType type);

/*
 * @function: token_utf8_string_length
 * @description: strlen while counting the character in utf8 mode not asci mode
 * @arguments: char* s
 * @return: size_t: number it will be >= 0
 */
size_t token_utf8_string_length(char* s);

/*
 * @function: token_is_skip
 * @description: check this tokentype is whitespace, comment-inline and multiline comment etc.
 * @arguments: TokenType
 * @return: bool: 0 or 1, true or false
 */
bool token_is_skip(TokenType type);

#endif // _ONE_TOKENIZER_TOKEN_H_
