#ifndef _ONE_BUILTINS_STRING_H_
#define _ONE_BUILTINS_STRING_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

typedef struct {
    char* data;
    size_t length;
    size_t capacity;
} string_t;

string_t* string_init();

string_t* string_init_size(size_t capacity);

size_t string_length(string_t* str);

size_t string_capacity(string_t* str);

void string_append(string_t* str, const char* item);

void string_append_char(string_t* str, char ch);

char* string_to_array(string_t* str);

void string_free(string_t* str);

char string_char_at(string_t* str, int index);

void string_set_char_at(string_t* str, int index, char ch);

#endif
