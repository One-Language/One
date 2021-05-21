/**
 File: one.h
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _ONE_H_
#define _ONE_H_

#include <stdio.h>
#include <stdlib.h>
#include "sds.h"

#define DEBUG
#define ONE_VERSION "0.4.0"

void error(char* format, ...);
void help(void);
char *file_read(char*);
void file_parse(char*);
int main(int, char**);

typedef enum {
	FALSE,
	TRUE
} bool;

#endif
