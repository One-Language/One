//
// Created by max on 6/9/21.
//

#include "lexer.h"

// Global variable(s)
Lexer lexer;

void lexer_init(char* source) {
	lexer.start = source;
	lexer.current = source;
	lexer.loc.line=1;
	lexer.loc.column=0;
}
