/**
 The One Programming Language
 File: file.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#ifndef _ONE_FILE_H_
#define _ONE_FILE_H_

#include <stdio.h> // fopen, fclose, FILE
#include <stdlib.h> // malloc, free
#include <stdbool.h> // bool, true, false

typedef struct {
    char* directory;
    char* path;
    char* name;
    char* extension;
    char* content;
    FILE* file;
    size_t size;
    bool exists;
} file_t;

#endif
