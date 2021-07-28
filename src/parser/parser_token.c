/**
 The One Programming Language

 File: parser/parser_token.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "parser_token.h"

// Global variable(s)
extern Parser parser;

/*
 * @function: parser_token_skip
 * @description: skip current tokens if these are token_is_skip we will skip from all of these.
 * @arguments: nothing
 * @return: bool, true mean we skipped some whitespace, false mean nothing to skip!
 */
bool parser_token_skip()
{
	debug_parser("parser_token_skip");
	size_t i = parser.index;
	while (token_is_skip(parser_token_get_type()))
	{
		parser_token_next();
	}
	if (parser.index != i)
		return true;
	return false;
}

/*
 * @function: parser_token_skip_get
 * @description: skip current tokens if these are token_is_skip we will skip from all of these and return next token.
 * @arguments: nothing
 * @return: Token*
 */
Token* parser_token_skip_get()
{
	debug_parser("parser_token_skip_get");

	parser_token_skip();

	return parser_token_get();
}

/*
 * @function: parser_token_expect
 * @description: if type of current token is equal to `t` we will skip it.
 * @arguments: TokenType t
 * @return: void
 */
void parser_token_expect(TokenType type)
{
	debug_parser("parser_token_expect");

	Token* t = parser.tokens[parser.index];
	if (t->type == type)
	{
		parser_token_next();
	}
	else
	{
		error_parser("We expect %s but found %s!", token_name(type), token_name(t->type));
	}
}

/*
 * @function: parser_token_has
 * @description: if type of current token is equal to `t` we will skip it and return true, otherwise we return false.
 * @arguments: TokenType t
 * @return: bool, true or false
 */
bool parser_token_has(TokenType type)
{
	debug_parser("parser_token_has");

	Token* t = parser.tokens[parser.index];
	if (t->type == type)
	{
		parser_token_next();
		return true;
	}

	return false;
}

/*
 * @function: parser_token_is
 * @description: if type of current token is equal to `t` return true, otherwise we will return false.
 * @arguments: TokenType t
 * @return: bool
 */
bool parser_token_is(TokenType type)
{
	debug_parser("parser_token_is");

	Token* t = parser.tokens[parser.index];
	if (t->type == type)
	{
		parser_token_next();
		return true;
	}
	return false;
}

/*
 * @function: parser_token_next
 * @description: go to next token and return its
 * @arguments: nothing
 * @return: Token*
 */
Token* parser_token_next()
{
	debug_parser("parser_token_next");

	parser.index++;
	return parser.tokens[parser.index];
}

/*
 * @function: parser_token_previous
 * @description: go to prev token and return its
 * @arguments: nothing
 * @return: Token*
 */
Token* parser_token_previous()
{
	debug_parser("parser_token_previous");

	parser.index--;
	return parser.tokens[parser.index];
}

/*
 * @function: parser_token_get
 * @description: get the current token and return its
 * @arguments: nothing
 * @return: Token*
 */
Token* parser_token_get()
{
	debug_parser("parser_token_get");

	return parser.tokens[parser.index];
}

/*
 * @function: parser_token_get_type
 * @description: get type of current token and return its type
 * @arguments: nothing
 * @return: TokenType
 */
TokenType parser_token_get_type()
{
	debug_parser("parser_token_get_type");

	Token* t = parser.tokens[parser.index];
	return t->type;
}

/*
 * @function: parser_token_at
 * @description: get the Token* at `index`th and return its
 * @arguments: nothing
 * @return: Token*
 */
Token* parser_token_at(size_t index)
{
	debug_parser("parser_token_at");

	return parser.tokens[index];
}

/*
 * @function: parser_token_at_type
 * @description: get type of Token* at `index`th and return its type
 * @arguments: nothing
 * @return: TokenType
 */
TokenType parser_token_at_type(size_t index)
{
	debug_parser("parser_token_at_type");

	Token* t = parser.tokens[index];
	return t->type;
}
