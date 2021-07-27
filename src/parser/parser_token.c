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
 * @description: skip current tokens if these are token_is_skip we will skip from all of these and return next token.
 * @arguments: nothing
 * @return: Token*
 */
Token* parser_token_skip()
{
	while (token_is_skip(parser_token_get()->type))
	{
		parser_token_next();
		parser.tokens++;
	}
	return *parser.tokens;
}

/*
 * @function: parser_token_expect
 * @description: if type of current token is equal to `t` we will skip it and return next token, otherwise we will return current token.
 * @arguments: TokenType t
 * @return: Token*
 */
Token* parser_token_expect(TokenType t)
{
}

/*
 * @function: parser_token_next
 * @description: go to next token and return its
 * @arguments: nothing
 * @return: Token*
 */
Token* parser_token_next()
{
}

/*
 * @function: parser_token_previous
 * @description: go to prev token and return its
 * @arguments: nothing
 * @return: Token*
 */
Token* parser_token_previous()
{
}

/*
 * @function: parser_token_get
 * @description: get the current token and return its
 * @arguments: nothing
 * @return: Token*
 */
Token* parser_token_get()
{
}

/*
 * @function: parser_token_get_type
 * @description: get type of current token and return its type
 * @arguments: nothing
 * @return: TokenType
 */
TokenType parser_token_get_type()
{
}

/*
 * @function: parser_token_at
 * @description: get the Token* at `index`th and return its
 * @arguments: nothing
 * @return: Token*
 */
Token* parser_token_at(size_t index)
{
}

/*
 * @function: parser_token_at_type
 * @description: get type of Token* at `index`th and return its type
 * @arguments: nothing
 * @return: Token*
 */
Token* parser_token_at_type(size_t index)
{
}
