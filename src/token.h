/**
 The One Programming Language

 File: token.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _TOKEN_H_
#define _TOKEN_H_

bool token_is_space(char);
bool token_is_alpha(char);
bool token_is_number(char);
bool token_is_digit(char);
bool token_is_ident(char);

#endif
