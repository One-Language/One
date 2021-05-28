/**
 File: parser.h
  _        _
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _PARSER_H_
#define _PARSER_H_

#include "one.h"

void parser(Lexer *);
void parser_statement(Lexer *);
void parser_statements(Lexer *);
void parser_except(Lexer *, char);
void parser_function(Lexer *);
void parser_function_arguments(Lexer *);
void parse_statement_return(Lexer *);
void parse_expression(Lexer *);
int parser_operator_precedence(int);
int parser_bin_op_rhs(Lexer *, int, int);
int parser_unary(Lexer *, int);
int parser_expression(Lexer *);

#endif
