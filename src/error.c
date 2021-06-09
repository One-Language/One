//
// Created by max on 6/9/21.
//


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "error.h"

static void error(ErrorType type, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	// TODO: Show error type with another custom color!
	fprintf(stderr, error_name(type));
	vfprintf(stderr, format, args);
	va_end(args);
	fputs("\n", stderr);

	if (type != ERROR_WARNING)
	{
		exit(1);
	}
}

static char* error_name(ErrorType type)
{
	switch (type)
	{
		case ERROR_WARNING:
			return "WARNING";
		case ERROR_PANIC:
			return "ERROR";
		case ERROR_TOKEN:
			return "TOKEN ERROR";
		case ERROR_PARSER:
			return "PARSER ERROR";
		default:
			return "UNKNOWN ERROR";
	}
}