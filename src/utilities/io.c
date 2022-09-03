/**
 The One Programming Language
 File: utilities/io.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2020-2022; One Language Contributors
 **/

#include "io.h"

char* file_reads(FILE* infile)
{
    /* declare a file pointer */
    char    *buffer;
    long    numbytes;

    /* quit if the file does not exist */
    if(infile == NULL) return NULL;

    /* Get the number of bytes */
    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);

    /* reset the file position indicator to the beginning of the file */
    fseek(infile, 0L, SEEK_SET);

    /* grab sufficient memory for the buffer to hold the text */
    buffer = (char*)calloc(numbytes, sizeof(char));

    /* memory error */
    if(buffer == NULL) return 1;

    /* copy all the text into the buffer */
    fread(buffer, sizeof(char), numbytes, infile);
    fclose(infile);

    return buffer;
}