/**
 The One Programming Language
 File: lexer.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#ifndef _ONE_LEXER_H_
#define _ONE_LEXER_H_

#include "token.h"

typedef struct {
    file_t* file;
    char* start;
    char* current;
    token_list_t* tokens;
} lexer_t;

#endif
