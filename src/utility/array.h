#ifndef _ONE_UTILITY_ARRAY_H_
#define _ONE_UTILITY_ARRAY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void **data;
    size_t size;
    size_t capacity;
} array;

array* array_new();

void array_push(array* a, void* item);

void* array_pop(array* a);

void* array_get(array* a, int index);

void array_set(array* a, int index, void* item);

void array_free(array* a);

void array_clear(array* a);

int array_size(array* a);

void array_resize(array* a, int size);

void array_insert(array* a, int index, void* item);

void array_remove(array* a, int index);

void array_remove_range(array* a, int start, int end);

void array_reverse(array* a);

void array_foreach(array* a, void (*callback)(void*));

// void array_sort(array* a, int (*compare)(void*, void*));

#endif
