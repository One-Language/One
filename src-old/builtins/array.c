/**
 The One Programming Language

 File: builtins/array.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "array.h"

/*
 * @function: array_init
 * @description: if you want to init the default value of a Array struct, you have to use this function.
 * @arguments: a pointer to Array
 * @return: void
 */
void array_init(Array *list)
{
	debug_builtins("array_init");

	list->count = 0;
	list->size = 0;
	list->data = NULL;
}

/*
 * @function: array_push
 * @description: if you want to add a item to your list
 * @arguments: a pointer to Array, a void-pointer of new value
 * @return: void
 */
void array_push(Array *list, void *item)
{
	debug_builtins("array_push");

	if (list->count == list->size)
	{
		// Set size of new array to 4, and double size if it's next...
		list->size = list->size == 0 ? 4 : 2 * list->size;
		list->data = (void **)realloc(list->data, list->size * sizeof(void *));
	}
	list->data[list->count] = item;
	list->count++;
}

/*
 * @function: array_push
 * @description: remove last value from your list
 * @arguments: a pointer to Array
 * @return: void
 */
void *array_pop(Array *list)
{
	debug_builtins("array_pop");

	list->count--;
	void *ret = list->data[list->count];
	return ret;
}

/*
 * @function: array_free
 * @description: free your list
 * @arguments: a pointer to Array
 * @return: void
 */
void array_free(Array *list)
{
	debug_builtins("array_free");

	free(list->data); // it's void**
	list->count = 0;
	list->size = 0;
	list->data = NULL;
}
