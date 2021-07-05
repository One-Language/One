/**
 The One Programming Language

 File: parser.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef ONE_PARSER_H
#define ONE_PARSER_H

typedef struct _token Token;

typedef struct
{
	const char* package;
	const char* path;

	Token** tokens;
	size_t tokens_index;
	size_t tokens_count;
} Parser;

void parser_init();

void parser_scan();

void parser_start();

void parser_push(Token* t);

AstRoot* parser_check();

void parser_free();

bool parser_expect(TokenType expected);

bool parser_has(TokenType expected);

AstGlobalStatenent* parser_parse();

void parser_parse_package();

AstFunction* parser_parse_fn();

AstBlock* parser_parse_block();

AstBlock* parser_parse_statements();

AstStatement* parser_parse_statement();

AstStatement* parser_parse_statement_prints();

AstStatement* parser_parse_statement_print();

AstStatement* parser_parse_statement_printnl();

AstStatement* parser_parse_statement_printdb();

AstStatement* parser_parse_statement_printdbnl();

AstExpressions parser_parse_expressions();

AstExpression* parser_parse_expression();

void parser_next();

void parser_prev();

void parser_tokens_log();

typedef void (*ParseFn)(bool canAssign);

typedef int Precedence;

/*
 * typedef enum
{
	PREC_ASSIGNMENT, // =
	PREC_OR, // or
	PREC_AND, // and
	PREC_EQUALITY, // == !=
	PREC_COMPARISON, // < > <= >=
	PREC_TERM, // + -
	PREC_FACTOR, // * /
	PREC_UNARY, // ! -
	PREC_CALL, // . ()
	PREC_PRIMARY,
	PREC_NONE, // non operators!
} Precedence;
*/

char* precedence_name(Precedence type);

typedef struct
{
	ParseFn prefix;
	ParseFn infix;
	Precedence precedence;
} ParseRule;

AstExpression* parser_parse_expression_primary();

void parser_preapre();

AstImport* parser_parse_import();

AstStruct* parser_parse_struct();

AstTypeDef* parser_parse_type();

#endif //ONE_PARSER_H
