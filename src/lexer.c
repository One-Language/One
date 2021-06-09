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

}
