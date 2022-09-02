/**
 The One Programming Language
 File: utilities/io.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2020-2022; One Language Contributors
 **/

#include "io.h"

char* file_reads(FILE* file)
{
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(size + 1);
    if (buffer == NULL) {
        printf("Could not allocate memory for file buffer");
        return NULL;
    }
    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    return buffer;
}