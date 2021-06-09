//
// Created by max on 6/9/21.
//

#ifndef ONE_TOKEN_H
#define ONE_TOKEN_H

//
// Created by max on 6/9/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "token.h"

static bool token_is_alpha(char c);

static bool token_is_digit(char c);

static bool token_is_end();

static char token_advance();

static char token_peek();

static char token_peek_next();

static char token_peek_prev();

static bool token_match(char expected);

static Token token_make(TokenType type);

static Token token_error(const char* message);

static void token_skip_comment_inline();

static void token_skip_comment_multiline();

static void token_skip_whitespace();

#endif //ONE_TOKEN_H
