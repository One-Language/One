#ifndef _ARRAYLIST_H_
#define _ARRAYLIST_H_

#include <pthread.h>

typedef struct {
  int count;
  int capacity;
  void** data;
} ArrayList;

void initArrayList(ArrayList* list);

void freeArrayList(ArrayList* list);

void pushToArrayList(ArrayList* list, void* item);

void* popFromArrayList(ArrayList* list);

void setInArrayList(ArrayList* list, int index, void* item);

void* getFromArrayList(ArrayList* list, int index);

#endif