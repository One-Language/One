#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

typedef struct {
    void** data;
    // Memory allocated for the array
    size_t capacity;
    // Number of data inside out of the allocated memory
    size_t count;
} array_t;

array_t* array_init();

array_t* array_init_size(size_t size, size_t capacity);

size_t array_size(array_t* array);

size_t array_count(array_t* array);

void array_push(array_t* array, void *item);

void* array_first(array_t *array);

void* array_last(array_t *array);

void *array_pop(array_t* list);

void array_free(array_t* list);

void* array_getat(array_t* array, int index);
