//
// Created by max on 6/9/21.
//

#include <stdlib.h>

#include "array.h"

static void array_init(Array *list)
{
	list->count = 0;
	list->size = 0;
	list->data = NULL;
}

static void array_push(Array *list, void *item)
{
	if (list->count == list->size)
	{
		// Set size of new array to 4, and double size if it's next...
		list->size = list->size == 0 ? 4 : 2 * list->size;
		list->data = (void **)realloc(list->data, list->size * sizeof(void *));
	}
	list->data[list->count] = item;
	list->count++;
}

static void *array_pop(Array *list)
{
	list->count--;
	void *ret = list->data[list->count];
	return ret;
}

static void array_free(Array *list)
{
	free(list->data); // it's void**
	list->count = 0;
	list->size = 0;
	list->data = NULL;
}
