/**
 The One Programming Language

 File: ast.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef ONE_AST_H
#define ONE_AST_H

typedef Array AstArguments;
typedef Array AstStatements;
typedef Array AstFunctions;
typedef Array AstExpressions;

typedef struct _ast_expression AstExpression;
typedef enum _token_type TokenType;

typedef enum
{
	AST_TYPE_I8,
	AST_TYPE_I16,
	AST_TYPE_I32,
	AST_TYPE_I64,
	AST_TYPE_I128,

	AST_TYPE_U8,
	AST_TYPE_U16,
	AST_TYPE_U32,
	AST_TYPE_U64,
	AST_TYPE_U128,

	AST_TYPE_F32,
	AST_TYPE_F64,

	AST_TYPE_STRING,
	AST_TYPE_CHAR,
	AST_TYPE_BOOL,
} AstValueType;

typedef enum
{
	AST_STATEMENT_PRINT,
	AST_STATEMENT_PRINTNL,
	AST_STATEMENT_PRINTDB,
	AST_STATEMENT_PRINTDBNL,

	AST_STATEMENT_RETURN,
} AstStatementType;

/*
typedef enum
{
	AST_OPERATOR_DIRECT, // without an operator!

	AST_OPERATOR_PLUS,
	AST_OPERATOR_MINUS,
	AST_OPERATOR_MUL,
	AST_OPERATOR_DIV,
	AST_OPERATOR_POW,

	TOKEN_OPERATOR_IF, // ? :
	TOKEN_OPERATOR_IFIF, // ??
	// TODO: adding more operators!
} AstOperatorType;
 */

typedef struct _ast_statement
{
	AstStatementType type;
	AstExpressions* expressions;
	AstExpression* expression;
} AstStatement;

typedef struct _ast_block
{
	AstStatements* statements;
} AstBlock;

typedef struct _ast_type
{
	int type;
	bool hasArray;
} AstType;

typedef struct _ast_expression
{
	//	AstOperatorType operator;
	TokenType operator;

	int vint;
	float vfloat;
	char* vstring;
	bool vbool;

	AstExpression* left;
	AstExpression* right;
	AstExpression* third;
} AstExpression;

typedef struct _ast_argument
{
	char* name;
	AstType* type;
} AstArgument;

typedef struct _ast_function
{
	char* name;
	AstArguments* arguments;
	AstBlock* block;
} AstFunction;

typedef struct _ast_root
{
	char* package;
	AstFunctions* functions;
} AstRoot;

AstType* astType(int, bool);

AstBlock* astBlock(AstStatements*);

AstArgument* astArgument(char*, AstType*);

AstFunction* astFunction(char*, AstArguments*, AstBlock*);

AstRoot* astRoot(char*, AstFunctions*);

AstStatement* astStatement(AstStatementType);

char* astOperatorName(TokenType);

char* astStatementName(AstStatementType);

AstExpression* astExpression(TokenType, int, float, char*, bool, AstExpression*, AstExpression*);

AstExpression* astExpression3(TokenType, int, float, char*, bool, AstExpression*, AstExpression*, AstExpression*);

#endif //ONE_AST_H
