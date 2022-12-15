/**
 The One Programming Language

 File: builtins/array.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef _ONE_BUILTINS_FILE_H_
#define _ONE_BUILTINS_FILE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdbool.h>

#include "error.h"

/*
 * @function: file_reads
 * @description: read whole of a filepath
 * @arguments: const char* filepath
 * @return: char*
 */
char* file_reads(const char* filepath);

/*
 * @function: file_convert_index_to_rc
 * @description: We get index of a position and point in string and looking to find its rows and column number and we will pass new value throw argument
 * @arguments: const char* input, int index, int* rows, int* columns
 * @return: bool / True or False; does that index exists or no. maybe current index is out of the file and filelength is less that `index` value!
 */
bool file_convert_index_to_rc(const char* input, int index, size_t* rows, size_t* columns);

/*
 * @function: file_get_parent
 * @description: If you want to get directory path from a full-file path, this function will be useful and can return the directory path for you.
 * @arguments: const char* path
 * @return: char*
 */
char* file_get_parent(const char* path);

#endif // _ONE_BUILTINS_FILE_H_
