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
    value_type_t* type;
    union {
        int int_value;
        float float_value;
        char* str_value;
        bool bool_value;
    } value;
} value_t;

#endif
