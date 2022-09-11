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

struct AstExpression;

typedef struct {
    char* name;
    AstStatementType type;
    union {
        AstFunction* function;
        struct AstExpression* expression;
    } stmt;
} AstStatement;

typedef enum {
//    AST_VALUE,
    AST_VALUE_BOOL,
    AST_VALUE_INT,
    AST_VALUE_FLOAT,
    AST_VALUE_STRING
} AstValueType;

typedef enum {
    AST_EXPRESSION_MEMBER,
    AST_EXPRESSION_CONDITIONAL,
    AST_EXPRESSION_UNARY,
    AST_EXPRESSION_BINARY,
    AST_EXPRESSION_CALL,
    AST_EXPRESSION_LOGICAL,
    AST_EXPRESSION_LITERAL,
    AST_EXPRESSION_POSTFIX,
    AST_EXPRESSION_TERNARY,
    AST_EXPRESSION_PREFIX,
} AstExpressionType;

typedef struct {
    TokenType operator;
    struct AstExpression* left;
    struct AstExpression* right;
} AstBinaryExpression;

typedef struct {
    AstValueType* type;
    union {
        bool boolean;
        int integer;
        float floating;
        char* string;
    } value;
} AstLiteralExpression;

typedef struct {
    struct AstExpression* callee;
    Array* arguments;
} AstCallExpression;

typedef struct {
    TokenType operator;
    struct AstExpression* left;
    struct AstExpression* right;
} AstLogicalExpression;

typedef struct {
    TokenType operator;
    struct AstExpression* argument;
} AstUnaryExpression;

typedef struct {
    struct AstExpression* test;
    struct AstExpression* consequent;
    struct AstExpression* alternate;
} AstConditionalExpression;

typedef struct {
    struct AstExpression* condition;
    struct AstExpression* true_value;
    struct AstExpression* false_value;
} AstTernaryExpression;

typedef struct {
    TokenType operator;
    struct AstExpression* left;
    struct AstExpression* right;
} AstAssignmentExpression;

typedef struct {
    TokenType operator;
    struct AstExpression* right;
} AstPrefixExpression;

typedef struct {
    TokenType operator;
    struct AstExpression* operand;
} AstPostfixExpression;

typedef struct {
    struct AstExpression* expression;
} AstExpressionStatement;

typedef struct {
    AstExpressionType type;
    union {

    } expr;
} AstExpression;
#endif //ONE_PARSER_AST_H
