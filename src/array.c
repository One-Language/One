/**
 The One Programming Language

 File: array.c
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include <stdlib.h>

#include "array.h"

void arrayInit(Array* list)
{
	list->count = 0;
	list->size = 0;
	list->data = NULL;
}

void arrayPush(Array* list, void* item)
{
	if (list->count == list->size) {
		// Set size of new array to 4, and double size if it's next...
		list->size = list->size == 0 ? 4 : 2 * list->size;
		list->data = (void**)realloc(list->data, list->size * sizeof(void*));
	}
	list->data[list->count] = item;
	list->count++;
}

void* arrayPop(Array* list) {
    list->count--;
    void* ret = list->data[list->count];
    return ret;
}
void arrayFree(Array* list)
{
  free(list->data); // it's void**
  list->count = 0;
  list->size = 0;
  list->data = NULL;
}
