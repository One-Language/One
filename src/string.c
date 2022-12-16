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
string_t* string_init()
{
    string_t* string = (string_t*)malloc(sizeof(string_t));
    string->value = malloc(sizeof(char) * (string->capacity = 10));
    strcpy(string->value, "");
    string->length = 0;
    return string;
}

/**
 * @brief Initialize a string object with a value
 * 
 * @param char* value
 * 
 * @return string_t*
 */
string_t* string_init_value(char* value)
{
    string_t* string = (string_t*)malloc(sizeof(string_t));
    string->value = value;
    string->length = strlen(value);
    string->capacity = string->length <= 0 ? 8 : string->length;
    return string;
}

/**
 * @brief Resize a string object
 * 
 * @param string_t* input
 * @param size_t new_size
 * 
 * @return string_t*
 */
string_t* string_resize(string_t* input, size_t new_size)
{
    if (input->capacity < new_size) {
        input->capacity = new_size;
        input->value = realloc(input->value, input->capacity);
    }
    return input;
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
 * @brief Append a string to the string object
 * 
 * @param string_t* string
 * @param char* value
 * 
 * @return char*
 */
char* string_append(string_t* string, char* value)
{
    if (value == NULL) return string->value;
    int length = strlen(value);

    return string_append_size(string, value, length);
}

/**
 * @brief Append a string to the string object with format
 * 
 * @param string_t* string
 * @param char* format
 * @param ...
 * 
 * @return char*
 */
char* string_append_format(string_t* string, char* format, ...)
{
    va_list args;
    va_start(args, format);
    int length = vsnprintf(NULL, 0, format, args);
    va_end(args);

    if (string->length + length >= string->capacity) {
        string->capacity = string->length + length + 1 + 20; // 20 is for extra space
        string->value = (char*)realloc(string->value, string->capacity);
    }

    va_start(args, format);
    vsnprintf(string->value + string->length, length + 1, format, args);
    va_end(args);

    string->length += length;

    return string->value;
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
    if (length == 0) return string->value;

    if (string->length + length >= string->capacity) {
        string->capacity = string->length + length + 1;
        string->value = (char*)realloc(string->value, string->capacity);
    }

    if (string->length == 0) memcpy(string->value, value, length);
    else memcpy(string->value + string->length, value, length);

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

/**
 * @brief Convert the int to char
 * 
 * @param int value
 * 
 * @return char*
 */
char* int_to_chars(int value)
{
    char* buffer = (char*)malloc(12);
    sprintf(buffer, "%d", value);
    return buffer;
}

/**
 * @brief Convert the long to char
 * 
 * @param long value
 * 
 * @return char*
 */
char* long_to_chars(long value)
{
    char* buffer = (char*)malloc(12);
    sprintf(buffer, "%ld", value);
    return buffer;
}

/**
 * @brief Convert the long long to char
 * 
 * @param long long value
 * 
 * @return char*
 */
char* long_long_to_chars(long long value)
{
    char* buffer = (char*)malloc(12);
    sprintf(buffer, "%lld", value);
    return buffer;
}

/**
 * @brief Convert the float to char
 * 
 * @param float value
 * 
 * @return char*
 */
char* float_to_chars(float value)
{
    char* buffer = (char*)malloc(12);
    sprintf(buffer, "%f", value);
    return buffer;
}

/**
 * @brief Convert the double to char
 * 
 * @param double value
 * 
 * @return char*
 */
char* double_to_chars(double value)
{
    char* buffer = (char*)malloc(12);
    sprintf(buffer, "%lf", value);
    return buffer;
}

/**
 * @brief Convert the long double to char
 * 
 * @param long double value
 * 
 * @return char*
 */
char* long_double_to_chars(long double value)
{
    char* buffer = (char*)malloc(12);
    sprintf(buffer, "%Lf", value);
    return buffer;
}

/**
 * @brief Convert the string to char*
 * 
 * @param string_t* string
 * 
 * @return char*
 */
char* string_to_chars(string_t* string)
{
    char* buffer = (char*)malloc(string->length + 1);
    memcpy(buffer, string->value, string->length);
    buffer[string->length] = '\0';
    return buffer;
}

/**
 * @brief Convert the size to char
 * 
 * @param size_t value
 * 
 * @return char*
 */
char* size_to_chars(size_t value)
{
    char* buffer = (char*)malloc(12);
    sprintf(buffer, "%zu", value);
    return buffer;
}

/**
 * @brief Convert the string to lower case
 * 
 * @param string_t* string
 * 
 * @return char* 
 */
char* string_to_lower(string_t* string)
{
    for (int i = 0; i < string->length; i++) string->value[i] = tolower(string->value[i]);

    return string->value;
}

/**
 * @brief Convert the string to upper case
 * 
 * @param string_t* string
 * 
 * @return char*
 */
char* string_to_upper(string_t* string)
{
    for (int i = 0; i < string->length; i++) string->value[i] = toupper(string->value[i]);

    return string->value;
}

/**
 * @brief Get a char from the string object
 * 
 * @param string_t* string
 * @param int index
 * 
 * @return char
 */
char string_get(string_t* string, int index)
{
    if (index >= string->length) return '\0';
    return string->value[index];
}

/**
 * @brief Repeat the string
 * 
 * @param string_t* string
 * @param int count
 * 
 * @return string_t* 
 */
string_t* string_repeat(string_t* string, int count)
{
    int str_len = string->length;
    if (count <= 0 || str_len == 0) return string_init_value("");

    int length = str_len * count;
    string_resize(string, length);

    for (int i = 1; i < count; i++) {
        string_append(string, string->value);
    }

    return string;
}

/**
 * @brief Repeat the string and return the char*
 * 
 * @param string_t* string
 * @param int count
 * 
 * @return char*
 */
char* string_repeat_chars(string_t* string, int count)
{
    int str_len = string->length;
    if (count <= 0 || str_len == 0) return "";

    int length = str_len * count;
    char* buffer = (char*)malloc(length + 1);

    for (int i = 0; i < count; i++) memcpy(buffer + i * string->length, string->value, string->length);

    buffer[length] = '\0';
    return buffer;
}

/**
 * @brief Repeat the char* and return the char*
 * 
 * @param char* string
 * @param int count
 * 
 * @return char*
 */
char* chars_repeat(char* str, int count)
{
    int str_len = strlen(str);
    if (count <= 0 || str_len == 0) return "";

    int length = str_len * count;
    char* buffer = (char*)malloc(length + 1);

    for (int i = 0; i < count; i++) memcpy(buffer + i * strlen(str), str, strlen(str));

    buffer[length] = '\0';
    return buffer;
}

/**
 * @brief Repeat the char and return the char*
 * 
 * @param char ch
 * @param int count
 * 
 * @return char*
 */
char* char_repeat(char ch, int count)
{
    if (count <= 0) return "";

    char* buffer = (char*)malloc(count + 1);
    for (int i = 0; i < count; i++) {
        buffer[i] = ch;
    }
    buffer[count] = '\0';
    return buffer;
}
