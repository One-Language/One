#include <stdlib.h>

#include "arraylist.h"
#include "util.h"

void initArrayList(ArrayList* list)
{
  list->count = 0;
  list->capacity = 0;
  list->data = NULL;
}

void freeArrayList(ArrayList* list)
{
  free(list->data);
  initArrayList(list);
}

void pushToArrayList(ArrayList* list, void* item)
{
  if (list->count == list->capacity) {
    list->capacity = list->capacity == 0 ? 4 : 2 * list->capacity;
    list->data = (void**)realloc(list->data, list->capacity * sizeof(void*));
  }
  list->data[list->count] = item;
  list->count++;
}

void* popFromArrayList(ArrayList* list)
{
  list->count--;
  return (void*) list->data[list->count];
}

void setInArrayList(ArrayList* list, int index, void* item)
{
  list->data[index] = item;
}

void* getFromArrayList(ArrayList* list, int index)
{
  return (void*) list->data[index];
}
