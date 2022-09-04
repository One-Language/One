//
// Created by Max on 9/4/2022.
//

#ifndef ONE_LEXER_STR_H
#define ONE_LEXER_STR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char* value;
    size_t length;
    size_t capacity;
} str;

str* str_init(char* value);

str* str_init_size(char* value, size_t size);

void str_append(str* str, char* value);

#endif //ONE_LEXER_STR_H
