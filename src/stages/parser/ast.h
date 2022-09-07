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

typedef enum {
    STATEMENT_EXPRESSION,
    STATEMENT_RETURN,
    STATEMENT_FUNCTION,
    STATEMENT_IF,
    STATEMENT_WHILE,
    STATEMENT_FOR,
//    STATEMENT_ERROR
} AstStatementType;

typedef struct {
    Array* statements;
} AstBlock;

typedef struct {
    char* name;
    Array* arguments;
    AstBlock* block;
} AstFunction;

typedef struct {
    char* type;
    char* name;
} AstFunctionArgument;

typedef struct {
    char* name;
    AstStatementType type;
    union {
        AstFunction* function;
    } stmt;
} AstStatement;

#endif //ONE_PARSER_AST_H
