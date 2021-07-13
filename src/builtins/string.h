/**
 The One Programming Language

 File: builtins/string.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef _ONE_BUILTINS_STRING_H_
#define _ONE_BUILTINS_STRING_H_

#include <stdio.h>
#include <stdlib.h>

#define STRING_SIZE_INIT 16

typedef struct
{
	char* str; // a null terminated C string
	char* end; // a pointer to the null byte, to be able to repeatedly append
		 // without using strlen() every time.
	size_t size; // currently allocated size for *str, so we know when we
		 // need to grow.
} string;

/*
 * @function: string_new
 * @desctipion: Creates a new string,
 				if there is not enough memory, will return a null pointer instead.
 * @arguments: nothing
 * @return: mallocated string
 */
string* string_new();

/*
 * @function: string_append
 * @description: Append to a string string, growing the allocated memory if needed
 				 on error, will return the longest string possible, which may truncate the suffix.
 * @arguments: string target, char* value want to be added
 * @return: void
 */
void string_append(string* ss, char* suffix);

#endif // _ONE_BUILTINS_STRING_H_
