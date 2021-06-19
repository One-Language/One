/**
 The One Programming Language

 File: ast.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef ONE_AST_H
#define ONE_AST_H

typedef Array AstArguments;
typedef Array AstStatements;
typedef Array AstFunctions;
typedef Array AstStructs;
typedef Array AstEnums;
typedef Array AstConsts;
typedef Array AstTypes;
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
	AST_GLOBAL_STATEMENT_FN,
	AST_GLOBAL_STATEMENT_VAR,
	AST_GLOBAL_STATEMENT_ENUM,
	AST_GLOBAL_STATEMENT_STRUCT,
	AST_GLOBAL_STATEMENT_TYPE,

	AST_STATEMENT_PRINT,
	AST_STATEMENT_PRINTNL,
	AST_STATEMENT_PRINTDB,
	AST_STATEMENT_PRINTDBNL,

	AST_STATEMENT_RET,

	AST_STATEMENT_WHILE,
	AST_STATEMENT_FOR,
	AST_STATEMENT_DO,
	AST_STATEMENT_MATCH,

	AST_STATEMENT_EXPRESSION,

	AST_STATEMENT_IF,

	AST_STATEMENT_VARIABLE,
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
	AstExpressions expressions;
	AstExpression* expression;
} AstStatement;

typedef struct _ast_block
{
	AstStatements statements;
} AstBlock;

typedef struct _ast_type
{
	AstValueType type;
	bool hasArray;
} AstType;

typedef struct _ast_expression
{
	//	AstOperatorType operator;
	TokenType operator;
	AstType type;

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
	AstArguments arguments;
	AstBlock* block;
} AstFunction;

typedef struct _ast_root
{
	char* package;

	AstFunctions functions;

	Array* vars;
	Array* types;
	Array* strucs;
	Array* enums;
} AstRoot;

typedef struct _ast_global_statement
{
	AstStatementType type;

	AstFunction* fn;
} AstGlobalStatenent;

char* ast_statement_name(AstStatementType type);

char* ast_value_name(AstValueType type);

AstType* ast_make_type(int type, bool hasArray);

AstBlock* ast_make_block(AstStatements stmts);

AstExpression* ast_make_expression_unary(TokenType op, AstExpression* value);

AstExpression* ast_make_expression_3(TokenType op, int value, AstExpression* left, AstExpression* right, AstExpression* third);

AstExpression* ast_make_expression_2(TokenType op, int value, AstExpression* left, AstExpression* right);

AstArgument* ast_make_argument(char* name, AstType* type);

AstFunction* ast_make_function(char* name, AstArguments args, AstBlock* block);

AstRoot* ast_make_root(char* package, AstFunctions funcs);

AstStatement* ast_make_statement(AstStatementType type);

void ast_free(AstRoot** root);

#endif //ONE_AST_H
