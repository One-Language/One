//
// Created by max on 6/9/21.
//

#include <stdio.h>
#include <stdlib.h>

#include "error.h"

#include "interpret.h"

static char* file_reads(const char* path)
{
	FILE* file = fopen(path, "rb");
	if (file == NULL)
	{
		error_panic("Could not open file \"%s\".\n", path);
		exit(74);
	}

	fseek(file, 0L, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	char* buffer = (char*)malloc(fileSize + 1);
	if (buffer == NULL)
	{
		error_panic("Not enough memory to read \"%s\".\n", path);
		exit(74);
	}
	size_t bytesRead = fread(buffer, sizeof char, fileSize, file);
	if (bytesRead < fileSize)
	{
		error_panic("Could not read the \"%s\".\n", path);
		exit(74);
	}

	buffer[bytesRead] = '\0';

	fclose(file);
	return buffer;
}

static int interpret_file(const char* path)
{
	char* source = file_reads(path);
	int ret = interpret_source(source);
	free(source);
	return ret;
}

static int interpret_source(const char* source)
{
	// https://www.freebsd.org/cgi/man.cgi?query=sysexits&apropos=0&sektion=0&manpath=FreeBSD+4.3-RELEASE&format=html
	int ret = EXIT_SUCCESS;
	scanner_init(source);
	parser_init();
	return ret;
}
