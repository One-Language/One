/**
 The One Programming Language
 File: value.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#ifndef _ONE_VALUE_H_
#define _ONE_VALUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    VALUE_TYPE_INT,
    VALUE_TYPE_FLOAT,
    VALUE_TYPE_STR,
    VALUE_TYPE_BOOL,
} value_type_t;

typedef struct {
    value_type_t type;
    union {
        int int_value;
        float float_value;
        char* str_value;
        bool bool_value;
    } value;
} value_t;

/**
 * @brief Get type name of a value type
 *
 * @param value_type_t type
 *
 * @return char*
 */
char* value_name(value_type_t type);

/**
 * @brief Initialize the value object
 *
 * @param value_type_t type
 *
 * @return value_t*
 */
value_t* value_init(value_type_t type);

/**
 * @brief Initialize the value object with a string
 *
 * @param char* value
 *
 * @return value_t*
 */
value_t* value_init_string(char* value);

/**
 * @brief Initialize the value object with a integer
 *
 * @param int value
 *
 * @return value_t*
 */
value_t* value_init_integer(int value);

/**
 * @brief Initialize the value object with a float
 *
 * @param float value
 *
 * @return value_t*
 */
value_t* value_init_float(float value);

/**
 * @brief Initialize the value object with a boolean
 *
 * @param bool value
 *
 * @return value_t*
 */
value_t* value_init_boolean(bool value);

/**
 * @brief Get the type of the value
 * @param value_t* value
 * @return value_type_t
 */
value_type_t value_type(value_t* value);

/**
 * @brief Get the string value of the value
 *
 * @param value_t* value
 *
 * @return char*
 */
char* value_string(value_t* value);

/**
 * @brief Get the integer value of the value
 *
 * @param value_t* value
 *
 * @return int
 */
int value_integer(value_t* value);

/**
 * @brief Get the float value of the value
 *
 * @param value_t* value
 *
 * @return float
 */
float value_float(value_t* value);

#endif
