/**
 The One Programming Language
 File: value.c
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#include "value.h"

/**
 * @brief Get type name of a value type
 *
 * @param value_type_t type
 *
 * @return char*
 */
char* value_name(value_type_t type)
{
    switch (type) {
        case VALUE_TYPE_INT:
            return "int";
        case VALUE_TYPE_FLOAT:
            return "float";
        case VALUE_TYPE_STR:
            return "string";
        case VALUE_TYPE_BOOL:
            return "bool";
        default:
            return "unknown";
    }
}
/**
 * @brief Initialize the value object
 *
 * @param value_type_t type
 *
 * @return value_t*
 */
value_t* value_init(value_type_t type)
{
    value_t* value = malloc(sizeof(value_t));
    value->type = type;
    return value;
}

/**
 * @brief Initialize the value object with a string
 *
 * @param char* value
 *
 * @return value_t*
 */
value_t* value_init_string(char* value)
{
    value_t* valueObject = value_init(VALUE_TYPE_STR);
    valueObject->value.str_value = value;
    return valueObject;
}

/**
 * @brief Initialize the value object with a integer
 *
 * @param int value
 *
 * @return value_t*
 */
value_t* value_init_integer(int value)
{
    value_t* valueObject = value_init(VALUE_TYPE_INT);
    valueObject->value.int_value = value;
    return valueObject;
}

/**
 * @brief Initialize the value object with a float
 *
 * @param float value
 *
 * @return value_t*
 */
value_t* value_init_float(float value)
{
    value_t* valueObject = value_init(VALUE_TYPE_FLOAT);
    valueObject->value.float_value = value;
    return valueObject;
}

/**
 * @brief Initialize the value object with a boolean
 *
 * @param bool value
 *
 * @return value_t*
 */
value_t* value_init_boolean(bool value)
{
    value_t* valueObject = value_init(VALUE_TYPE_BOOL);
    valueObject->value.bool_value = value;
    return valueObject;
}

/**
 * @brief Get the type of the value
 *
 * @param value_t* value
 *
 * @return value_type_t
 */
value_type_t value_type(value_t* value)
{
    return value->type;
}

/**
 * @brief Get the string value of the value
 *
 * @param value_t* value
 *
 * @return char*
 */
char* value_string(value_t* value)
{
    return value->value.str_value;
}

/**
 * @brief Get the integer value of the value
 *
 * @param value_t* value
 *
 * @return int
 */
int value_integer(value_t* value)
{
    return value->value.int_value;
}

/**
 * @brief Get the float value of the value
 *
 * @param value_t* value
 *
 * @return float
 */
float value_float(value_t* value)
{
    return value->value.float_value;
}
