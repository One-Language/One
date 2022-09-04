//
// Created by Max on 9/4/2022.
//

#ifndef ONE_PARSER_AST_H
#define ONE_PARSER_AST_H

#include "../../builtins/array.h"
#include "../../builtins/str.h"

typedef struct {
    Array* statements;
    Array* errors;
} AstProgram;

typedef struct {
    char* name;
} AstStatement;

#endif //ONE_PARSER_AST_H
