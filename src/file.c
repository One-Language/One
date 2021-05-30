/**
 The One Programming Language

 File: file.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "error.h"
#include "file.h"

char *fileReads(const char *filename, ErrorsContainer *errors)
{
	FILE *onefile = fopen(filename, "rb");
	if (onefile == NULL)
	{
		return NULL;
	}
	fseek(onefile, 0L, SEEK_END);
	size_t onefilesize = ftell(onefile);
	rewind(onefile);
	char *onebuffer = (char *)malloc(onefilesize + 1);
	if (onebuffer == NULL)
	{
		error("error malloc onebuffer\n");
		return NULL;
	}
	size_t onebytesread = fread(onebuffer, 1, onefilesize, onefile);
	if (onebytesread < onefilesize)
	{
		free(onebuffer);
		error("Could not read file.one\n");
		return NULL;
	}
	onebuffer[onebytesread] = '\0';
	fclose(onefile);
	return onebuffer;
}

