/**
 The One Programming Language

 File: compile.h
  _        _
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _COMPILE_H_
#define _COMPILE_H_

#include "arg.h"
#include "compile.h"

void link(Args *, ErrorsContainer *);
int compileString(char *);
int compile(Args *, ErrorsContainer *);

#endif
