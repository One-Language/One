/**
 File: scanner.h
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _SCANNER_H_
#define _SCANNER_H_

#include "one.h"
#include "token.h"
#include "lexer.h"

void scanner_parse(Lexer* lex);

#endif
