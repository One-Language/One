#ifndef _ONE_STRING_H_
#define _ONE_STRING_H_

#include <stdlib.h> // malloc, free, realloc
#include <string.h> // strlen

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
string_t* string_init(char* value);

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
 * @brief Initialize a string object with length and capacity
 * 
 * @param char* value
 * @param int length
 * @param int capacity
 * 
 * @return string_t*
 */
string_t* string_init_length_capacity(int length, int capacity);

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

#endif
