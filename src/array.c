//
// Created by max on 6/9/21.
//

#include <stdio.h>
#include <stdlib.h>

#include "error.h"

#include "array.h"

void array_init(Array *list)
{
	debug("array_init");

	list->count = 0;
	list->size = 0;
	list->data = NULL;
}

void array_push(Array *list, void *item)
{
	debug("array_push");

	if (list->count == list->size)
	{
		// Set size of new array to 4, and double size if it's next...
		list->size = list->size == 0 ? 4 : 2 * list->size;
		list->data = (void **)realloc(list->data, list->size * sizeof(void *));
	}
	list->data[list->count] = item;
	list->count++;
}

void *array_pop(Array *list)
{
	debug("array_pop");

	list->count--;
	void *ret = list->data[list->count];
	return ret;
}

void array_free(Array *list)
{
	debug("array_free");

	free(list->data); // it's void**
	list->count = 0;
	list->size = 0;
	list->data = NULL;
}
