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

void parser_check();

void parser_free();

bool parser_expect(TokenType expected);

bool parser_has(TokenType expected);

void parser_parse();

void parser_parse_package();

void parser_parse_fn();

void parser_parse_block();

void parser_parse();

void parser_parse_statements();

void parser_parse_statement();

void parser_parse_statement_prints();

void parser_parse_statement_print();

void parser_parse_statement_printnl();

void parser_parse_statement_printdb();

void parser_parse_statement_printdbnl();

void parser_parse_expressions();

void parser_parse_expression();

#endif //ONE_PARSER_H
