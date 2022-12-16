/**
 The One Programming Language
 File: array.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#ifndef _ONE_ARRAY_H_
#define _ONE_ARRAY_H_

// #include <stdio.h> // printf, scanf, puts, NULL
#include <stdlib.h> // malloc, free, realloc

typedef struct {
    int size;
    int capacity;
    void** data;
} array_t;

#endif
