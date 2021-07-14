/**
 The One Programming Language

 File: error.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _location Location;
typedef struct _token Token;

typedef enum
{
	ERROR,
	WARNING,
	NOTE,
} ErrorLevel;

typedef struct _error
{
	char *filename;
	char *message;
	Location location;
	ErrorLevel level;
} Error;

typedef struct _errors
{
	int error_count;
	int error_capacity;
	Error *errors;
} ErrorsContainer;

void ErrorsInit(ErrorsContainer *);

void ErrorsPrint(FILE *, Error *);

void ErrorsPrints(FILE *, ErrorsContainer *);

void ErrorsFree(ErrorsContainer *);

void ErrorsAdd(ErrorsContainer *, ErrorLevel, Location, char *);

void error(char *);

char *ErrorLevelName(ErrorLevel);

#endif
