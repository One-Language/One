//
// Created by Max on 9/4/2022.
//

#include "str.h"

str* str_init(char* value)
{
    return str_init_size(value, (size_t) strlen(value));
}

str* str_init_size(char* value, size_t size)
{
    str* str = malloc(sizeof(str));
    str->value = value;
    str->length = strlen(value);
    str->capacity = size;

    return str;
}

void str_append(str* str, char* value)
{
    size_t length = strlen(value);
    size_t new_length = str->length + length;

    if (new_length > str->capacity)
    {
        str->capacity = new_length;
        str->value = realloc(str->value, str->capacity);
    }

    memcpy(str->value + str->length, value, length);
    str->length = new_length;
}