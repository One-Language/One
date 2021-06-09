//
// Created by max on 6/9/21.
//

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
