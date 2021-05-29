/**
 The One Programming Language

 File: error.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "error.h"

void ErrorsInit(ErrorsContainer *container)
{
}

void ErrorsPrint(FILE *f, ErrorsContainer *errors)
{
}

void ErrorsAdd(ErrorsContainer *errors, char *message)
{
}

void ErrorsFree(ErrorsContainer *errors)
{
}

void error(char *message)
{
	// TODO: this function will remove and ErrorsAdd() will be use!
	printf("[Error]: %s", message);
}
