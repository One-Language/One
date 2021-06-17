/**
 The One Programming Language

 File: array.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef ONE_ARRAY_H
#define ONE_ARRAY_H

typedef struct
{
	int count;
	int size;
	void **data;
} Array;

void array_init(Array *list);

void array_push(Array *list, void *item);

void *array_pop(Array *list);

void array_free(Array *list);

#endif //ONE_ARRAY_H
