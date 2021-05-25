/**
 The One Programming Language

 File: error.h
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _ERROR_H_
#define _ERROR_H_

typedef int Position;

typedef enum {
  ERROR,
  WARNING,
  NOTE,
} ErrorLevel;

typedef struct {
  char* message;
  Position position;
  ErrorLevel level;
} Error;

typedef struct {
  int error_count;
  int error_capacity;
  Error* errors;
} ErrorsContainer;

#endif
