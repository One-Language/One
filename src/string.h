/**
 The One Programming Language
 File: string.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#ifndef _ONE_STRING_H_
#define _ONE_STRING_H_

#include <stdio.h> // printf, sprintf, fprintf
#include <stdlib.h> // malloc, free, realloc
#include <stdarg.h> // va_list, va_start, va_end
#include <string.h> // strlen
#include <ctype.h> // toupper, tolower

typedef struct {
    char* value;
    int length;
    int capacity;
} string_t;

/**
 * @brief Initialize a string object
 * 
 * @param char* value
 * 
 * @return string_t*
 */
string_t* string_init();

/**
 * @brief Initialize a string object with a value
 * 
 * @param char* value
 * 
 * @return string_t*
 */
string_t* string_init_value(char* value);

/**
 * @brief Initialize a string object with length
 * 
 * @param char* value
 * @param int length
 * 
 * @return string_t*
 */
string_t* string_init_length(char* value, int length);

/**
 * @brief Initialize a string object with length and capacity
 * 
 * @param char* value
 * @param int length
 * @param int capacity
 * 
 * @return string_t*
 */
string_t* string_init_length_capacity(char* value, int length, int capacity);

/**
 * @brief Initialize a string object with capacity
 * 
 * @param char* value
 * @param int length
 * @param int capacity
 * 
 * @return string_t*
 */
string_t* string_init_capacity(int capacity);

/**
 * @brief Append a string to the string object
 * 
 * @param string_t* string
 * @param char* value
 * 
 * @return char*
 */
char* string_append(string_t* string, char* value);

/**
 * @brief Append a string to the string object with format
 * 
 * @param string_t* string
 * @param char* format
 * @param ...
 * 
 * @return char*
 */
char* string_append_format(string_t* string, char* format, ...);

/**
 * @brief Append a string with size to the string object
 * 
 * @param string_t* string
 * @param char* value
 * @param int length
 * 
 * @return char*
 */
char* string_append_size(string_t* string, char* value, int length);

/**
 * @brief Append a char to the string object
 * 
 * @param string_t* string
 * @param char value
 * 
 * @return char*
 */
char* string_append_char(string_t* string, char value);

/**
 * @brief Free the string object
 * 
 * @param string_t
 * 
 * @return void
 */
void string_free(string_t* string);

/**
 * @brief Convert the int to char
 * 
 * @param int value
 * 
 * @return char*
 */
char* int_to_chars(int value);

/**
 * @brief Convert the long to char
 * 
 * @param long value
 * 
 * @return char*
 */
char* long_to_chars(long value);

/**
 * @brief Convert the long long to char
 * 
 * @param long long value
 * 
 * @return char*
 */
char* long_long_to_chars(long long value);

/**
 * @brief Convert the float to char
 * 
 * @param float value
 * 
 * @return char*
 */
char* float_to_chars(float value);

/**
 * @brief Convert the double to char
 * 
 * @param double value
 * 
 * @return char*
 */
char* double_to_chars(double value);

/**
 * @brief Convert the long double to char
 * 
 * @param long double value
 * 
 * @return char*
 */
char* long_double_to_chars(long double value);

/**
 * @brief Convert the string to char*
 * 
 * @param string_t* string
 * 
 * @return char*
 */
char* string_to_chars(string_t* string);

/**
 * @brief Convert the size to char
 * 
 * @param size_t value
 * 
 * @return char*
 */
char* size_to_chars(size_t value);

/**
 * @brief Convert the string to lower case
 * 
 * @param string_t* string
 * 
 * @return char* 
 */
char* string_to_lower(string_t* string);

/**
 * @brief Convert the string to upper case
 * 
 * @param string_t* string
 * 
 * @return char*
 */
char* string_to_upper(string_t* string);

/**
 * @brief Get a char from the string object
 * 
 * @param string_t* string
 * @param int index
 * 
 * @return char
 */
char string_get(string_t* string, int index);

/**
 * @brief Resize a string object
 * 
 * @param string_t* input
 * @param size_t new_size
 * 
 * @return string_t*
 */
string_t* string_resize(string_t* input, size_t new_size);


/**
 * @brief Repeat the string
 * 
 * @param string_t* string
 * @param int count
 * 
 * @return string_t* 
 */
string_t* string_repeat(string_t* string, int count);

/**
 * @brief Repeat the string and return the char*
 * 
 * @param string_t* string
 * @param int count
 * 
 * @return char*
 */
char* string_repeat_chars(string_t* string, int count);

/**
 * @brief Repeat the char* and return the char*
 * 
 * @param char* string
 * @param int count
 * 
 * @return char*
 */
char* chars_repeat(char* str, int count);

/**
 * @brief Repeat the char and return the char*
 * 
 * @param char ch
 * @param int count
 * 
 * @return char*
 */
char* char_repeat(char ch, int count);

#endif
