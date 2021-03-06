/**
 The One Programming Language

 File: builtins/array.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "file.h"

/*
 * @function: file_reads
 * @description: read whole of a filepath
 * @arguments: const char* filepath
 * @return: char*
 */
char* file_reads(const char* filepath)
{
	debug("file_reads");
	debug("file_reads: %s", filepath);

	FILE* file = fopen(filepath, "rb");
	if (file == NULL)
	{
		error_panic("Could not open file \"%s\".", filepath);
		exit(74);
	}

	fseek(file, 0L, SEEK_END);
	size_t fileSize = ftell(file);
	debug("file_reads: fileSize is %zu", fileSize);
	rewind(file);

	char* buffer = (char*)malloc(fileSize + 1);
	if (buffer == NULL)
	{
		error_panic("Not enough memory to read \"%s\".", filepath);
		exit(74);
	}

	size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
	debug("file_reads: bytesRead is %zu", bytesRead);
	if (bytesRead < fileSize)
	{
		error_panic("Could not read the \"%s\".", filepath);
		exit(74);
	}

	buffer[bytesRead] = '\0';

	fclose(file);
	return buffer;
}
