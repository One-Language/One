/**
 The One Programming Language
 File: string.c
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#include "string.h"

/**
 * @brief Initialize a string object
 * 
 * @param char* value
 * 
 * @return string_t*
 */
string_t* string_init(char* value)
{
    string_t* string = (string_t*)malloc(sizeof(string_t));
    string->value = value;
    string->length = strlen(value);
    return string;
}

/**
 * @brief Initialize a string object with length
 * 
 * @param char* value
 * @param int length
 * 
 * @return string_t*
 */
string_t* string_init_length(char* value, int length)
{
    string_t* string = (string_t*)malloc(sizeof(string_t));
    string->value = value;
    string->length = length;
    return string;
}

/**
 * @brief Initialize a string object with length and capacity
 * 
 * @param char* value
 * @param int length
 * @param int capacity
 * 
 * @return string_t*
 */
string_t* string_init_length_capacity(char* value, int length, int capacity)
{
    string_t* string = (string_t*)malloc(sizeof(string_t));
    string->value = value;
    string->length = length;
    string->capacity = capacity;
    return string;
}

/**
 * @brief Initialize a string object with capacity
 * 
 * @param char* value
 * @param int length
 * @param int capacity
 * 
 * @return string_t*
 */
string_t* string_init_capacity(int capacity)
{
    string_t* string = (string_t*)malloc(sizeof(string_t));
    string->value = (char*)malloc(capacity);
    string->length = 0;
    string->capacity = capacity;
    return string;
}

/**
 * @brief Initialize a string object with length and capacity
 * 
 * @param char* value
 * @param int length
 * @param int capacity
 * 
 * @return string_t*
 */
string_t* string_init_length_capacity(int length, int capacity)
{
    string_t* string = (string_t*)malloc(sizeof(string_t));
    string->value = (char*)malloc(capacity);
    string->length = length;
    string->capacity = capacity;
    return string;
}

/**
 * @brief Append a string to the string object
 * 
 * @param string_t* string
 * @param char* value
 * 
 * @return char*
 */
char* string_append(string_t* string, char* value)
{
    int length = strlen(value);
    return string_append_size(string, value, length);
}

/**
 * @brief Append a string with size to the string object
 * 
 * @param string_t* string
 * @param char* value
 * @param int length
 * 
 * @return char*
 */
char* string_append_size(string_t* string, char* value, int length)
{
    if (string->length + length >= string->capacity) {
        string->capacity = string->length + length + 1;
        string->value = (char*)realloc(string->value, string->capacity);
    }
    memcpy(string->value + string->length, value, length);
    string->length += length;
    string->value[string->length] = '\0';
    return string->value;
}

/**
 * @brief Append a char to the string object
 * 
 * @param string_t* string
 * @param char value
 * 
 * @return char*
 */
char* string_append_char(string_t* string, char value)
{
    if (string->length + 1 >= string->capacity) {
        string->capacity = string->length + 1 + 1;
        string->value = (char*)realloc(string->value, string->capacity);
    }
    string->value[string->length] = value;
    string->length += 1;
    string->value[string->length] = '\0';
    return string->value;
}

/**
 * @brief Free the string object
 * 
 * @param string_t
 * 
 * @return void
 */
void string_free(string_t* string)
{
    free(string->value);
    free(string);
}
