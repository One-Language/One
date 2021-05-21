/**
 File: parser.h
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _PARSER_H_
#define _PARSER_H_

#include "one.h"

void parser(Lexer*);
void parser_statement(Lexer*);
void parser_statements(Lexer*);
void parser_except(Lexer*, char);

#endif

