/**
 The One Programming Language

 File: builtins/array.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef _ONE_BUILTINS_ARRAY_H_
#define _ONE_BUILTINS_ARRAY_H_

#include <stdlib.h>
#include <stddef.h>

#include "error.h"

typedef struct
{
	int count;
	int size;
	void** data;
} Array;

/*
 * @function: array_init
 * @description: if you want to init the default value of a Array struct, you have to use this function.
 * @arguments: a pointer to Array
 * @return: void
 */
void array_init(Array* list);

/*
 * @function: array_push
 * @description: if you want to add a item to your list
 * @arguments: a pointer to Array, a void-pointer of new value
 * @return: void
 */
void array_push(Array* list, void* item);

/*
 * @function: array_push
 * @description: remove last value from your list
 * @arguments: a pointer to Array
 * @return: void
 */
void* array_pop(Array* list);

/*
 * @function: array_free
 * @description: free your list
 * @arguments: a pointer to Array
 * @return: void
 */
void array_free(Array* list);

#endif // _ONE_BUILTINS_ARRAY_H_
