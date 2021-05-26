/**
 The One Programming Language

 File: array.h
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _ARRAY_H_
#define _ARRAY_H_

typedef struct {
    int count;
    int capacity;
    void** data;
} Array;

void arrayInit(Array* list);

void arrayFree(Array* list);

#endif
