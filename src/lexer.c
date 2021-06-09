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

Token lexer_scan()
{
	debug("lexer_scan");

	lexer.start = lexer.current;

	if(token_is_end()) return token_make(TOKEN_EOF);

	char c = token_advance();
	switch(c) {
		case '(': return token_make(TOKEN_OPERATOR_BRACKET_ROUND_LEFT);
		case ')': return token_make(TOKEN_OPERATOR_BRACKET_ROUND_RIGHT);
		case '[': return token_make(TOKEN_OPERATOR_BRACKET_SQUARE_LEFT);
		case ']': return token_make(TOKEN_OPERATOR_BRACKET_SQUARE_RIGHT);
		case '{': return token_make(TOKEN_OPERATOR_BRACKET_CURLY_LEFT);
		case '}': return token_make(TOKEN_OPERATOR_BRACKET_CURLY_RIGHT);

		case ',': return token_make(TOKEN_OPERATOR_BRACKET_CURLY_RIGHT);

		case '+': return token_make(token_match('+') ? TOKEN_OPERATOR_PLUSPLUS : TOKEN_OPERATOR_PLUS);
		case '-': return token_make(TOKEN_OPERATOR_MINUS);
		case '*': return token_make(TOKEN_OPERATOR_STAR);
		case '/': return token_make(TOKEN_OPERATOR_SLASH);
	}

	return token_error("Unexpected character.");

}
