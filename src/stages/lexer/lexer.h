//
// Created by max on 4/12/22.
//

#ifndef ONE_LEXER_H
#define ONE_LEXER_H

#include "../../utils/array.h"
#include "token.h"

typedef struct {
	char* path;
	char* input;
	char* current_pos;
	Array* tokens;
} Lexer;

Lexer* lexer_init(char* file_path, char* input);
Token* lexer_next(Lexer* lexer);
void lexer_execute(Lexer* lexer);

#endif //ONE_LEXER_H
