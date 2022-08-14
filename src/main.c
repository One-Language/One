/**
The One Programming Language

File: main.c
 _        _
/ \ |\ | |_    Max Base
\_/ | \| |_    Copyright 2022; One Language Contributors

**/

#include <stdio.h>
#include <stdlib.h>

#include "utils/array.h"
#include "utils/file.h"

#include "stages/lexer/lexer.h"

int main(int argc, char** argv)
{
	char* data;
	char* input_file;
	char* output_file;

	if (argc == 2)
	{
		input_file = argv[1];
		char* data = file_read_contents(input_file);

		printf("%s\n", data);
		Lexer* lexer = lexer_init(input_file, data);
		lexer_execute(lexer);
	}
	else if (argc == 3)
	{
		input_file = argv[1];
		output_file = argv[2];

		printf("Input file is: %s\n", input_file);
		printf("Output file is: %s\n", output_file);
	}
	else
	{
		printf("Error: arguments are not correct!\n");
		printf("one input.one output\n");
		printf("one \"your input here as string\"\n");
		return 1;
	}

	return 0;
}
