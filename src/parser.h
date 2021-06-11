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

#endif //ONE_PARSER_H
