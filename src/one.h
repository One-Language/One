/**
 File: one.h
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include <stdio.h>
#include <stdlib.h>

#define DEBUG
#define ONE_VERSION "0.4.0"

void error(char*);
void help(void);
char *file_read(char*);
void file_parse(char*);
int main(int, char**);

typedef enum {
	FALSE,
	TRUE
} bool;



