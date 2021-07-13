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

#include "error.h"

/*
 * @function: file_reads
 * @description: read whole of a filepath
 * @arguments: const char* filepath
 * @return: char*
 */
char* file_reads(const char* filepath);

#endif // _ONE_BUILTINS_FILE_H_

