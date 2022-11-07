#ifndef _ONE_PARSER_AST_H_
#define _ONE_PARSER_AST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../utility/array.h"

typedef struct {
    array* functions;
} Ast;

typedef struct {
    char* name;
    array* parameters;
    array* statements;
} AstFunction;

typedef struct {
    
} AstExpression;

typedef struct {

} AstFunctionParameter;

typedef struct {
    array* variables;
    array* statements;
} AstBlock;

typedef enum {
    STATEMENT_IF,
    STATEMENT_WHILE,
    STATEMENT_FOR,
    STATEMENT_RET,
    STATEMENT_BREAK,
    STATEMENT_CONTINUE,
    STATEMENT_EXPRESSION
} AstStatementType;

typedef struct {
    AstStatementType type;
    union {
        struct {
            AstExpression* condition;
            AstBlock* block;
        } if_statement;
        struct {
            AstExpression* condition;
            AstBlock* block;
        } while_statement;
        struct {
            AstExpression* condition;
            AstBlock* block;
        } for_statement;
        struct {
            AstExpression* expression;
        } ret_statement;
        struct {
            AstExpression* expression;
        } expression_statement;
    };
} AstStatement;

Ast* ast_new();

#endif
