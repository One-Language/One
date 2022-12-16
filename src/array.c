/**
 The One Programming Language
 File: array.c
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#include "array.h"

/**
 * @brief Initialize array
 * 
 * @param void
 * 
 * @return array_t* 
 */
array_t* array_init()
{
    array_t* array = (array_t*)malloc(sizeof(array_t));
    array->data = (void**)malloc(sizeof(void*) * 0);
    array->size = 0;
    array->capacity = 5;
    return array;
}

/**
 * @brief Add element to array
 * 
 * @param array_t* array
 * @param void* element
 * 
 * @return array_t* 
 */
array_t* array_append(array_t* array, void* element)
{
    if (array->size == array->capacity) {
        array->capacity += 8;
        array->data = (void**)realloc(array->data, sizeof(void*) * array->capacity);
    }
    array->data[array->size++] = element;
    return array;
}

/**
 * @brief Remove last element from array and return it
 * 
 * @param array_t* array
 * 
 * @return void*
 */
void* array_pop(array_t* array)
{
    if (array->size == 0) {
        return NULL;
    }
    void* element = array->data[array->size - 1];
    array->size--;
    return element;
}

/**
 * @brief Get last element from array
 * 
 * @param array_t* array
 * 
 * @return void*
 */
void* array_peak(array_t* array)
{
    if (array->size == 0) {
        return NULL;
    }
    return array->data[array->size - 1];
}

/**
 * @brief Get element from array
 * 
 * @param array_t* array
 * @param int index
 * 
 * @return void*
 */
void* array_get(array_t* array, int index)
{
    if (index >= array->size) {
        return NULL;
    }
    return array->data[index];
}

/**
 * @brief Set element to array
 * 
 * @param array_t* array
 * @param int index
 * @param void* element
 * 
 * @return void*
 */
void* array_set(array_t* array, int index, void* element)
{
    if (index >= array->size) {
        return NULL;
    }
    array->data[index] = element;
    return array->data[index];
}

/**
 * @brief Remove element from array
 * 
 * @param array_t* array
 * @param int index
 * 
 * @return void*
 */
void* array_remove(array_t* array, int index)
{
    if (index >= array->size) {
        return NULL;
    }
    void* element = array->data[index];
    for (int i = index; i < array->size - 1; i++) {
        array->data[i] = array->data[i + 1];
    }
    array->size--;
    return element;
}

/**
 * @brief Free array
 * 
 * @param array_t* array
 * 
 * @return void 
 */
void array_free(array_t* array)
{
    free(array->data);
    free(array);
}
