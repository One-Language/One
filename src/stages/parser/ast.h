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
    // Table
    Array* variables;
    Array* functions;
} AstBlock;

typedef struct {
    char* type;
    bool isArray;
    bool isPointer;
} AstType;

typedef struct {
    char* name;
    Array* arguments;
    AstBlock* block;
    AstType* returnType;
} AstFunction;

typedef struct {
    AstType* type;
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
