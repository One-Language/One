/**
 The One Programming Language

 File: file.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include <stdio.h>
#include <stdlib.h>

#include "error.h"

#include "file.h"

char* file_reads(const char* path)
{
	debug("file_reads");
	debug("file_reads: %s", path);

	FILE* file = fopen(path, "rb");
	if (file == NULL)
	{
		error_panic("Could not open file \"%s\".", path);
		exit(74);
	}

	fseek(file, 0L, SEEK_END);
	size_t fileSize = ftell(file);
	debug("file_reads: fileSize is %zu", fileSize);
	rewind(file);

	char* buffer = (char*)malloc(fileSize + 1);
	if (buffer == NULL)
	{
		error_panic("Not enough memory to read \"%s\".", path);
		exit(74);
	}
	size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
	debug("file_reads: bytesRead is %zu", bytesRead);
	if (bytesRead < fileSize)
	{
		error_panic("Could not read the \"%s\".", path);
		exit(74);
	}

	buffer[bytesRead] = '\0';

	fclose(file);
	return buffer;
}
