//
// Created by max on 6/9/21.
//

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

typedef enum {
	PREC_NONE,
	PREC_ASSIGNMENT,  // =
	PREC_OR,          // or
	PREC_AND,         // and
	PREC_EQUALITY,    // == !=
	PREC_COMPARISON,  // < > <= >=
	PREC_TERM,        // + -
	PREC_FACTOR,      // * /
	PREC_UNARY,       // ! -
	PREC_CALL,        // . ()
	PREC_PRIMARY
} Precedence;

typedef struct {
	ParseFn prefix;
	ParseFn infix;
	Precedence precedence;
} ParseRule;

AstExpression *parser_parse_expression_primary();

#endif //ONE_PARSER_H
