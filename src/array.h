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

/**
 * @brief Initialize array
 * 
 * @param void
 * 
 * @return array_t* 
 */
array_t* array_init();

/**
 * @brief Add element to array
 * 
 * @param array_t* array
 * @param void* element
 * 
 * @return array_t* 
 */
array_t* array_push(array_t* array, void* element);

/**
 * @brief Remove last element from array and return it
 * 
 * @param array_t* array
 * 
 * @return void*
 */
void* array_pop(array_t* array);

/**
 * @brief Get last element from array
 * 
 * @param array_t* array
 * 
 * @return void*
 */
void* array_peak(array_t* array);

/**
 * @brief Get element from array
 * 
 * @param array_t* array
 * @param int index
 * 
 * @return void*
 */
void* array_get(array_t* array, int index);

/**
 * @brief Set element to array
 * 
 * @param array_t* array
 * @param int index
 * @param void* element
 * 
 * @return void*
 */
void* array_set(array_t* array, int index, void* element);

/**
 * @brief Remove element from array
 * 
 * @param array_t* array
 * @param int index
 * 
 * @return void*
 */
void* array_remove(array_t* array, int index);

/**
 * @brief Free array
 * 
 * @param array_t* array
 * 
 * @return void 
 */
void array_free(array_t* array);

#endif
