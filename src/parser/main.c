/**
 The One Programming Language

 File: parser/main.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

int main(int argc, char** argv)
{
	char* data;
	char* input_file;
	char* output_file;
	Token** tokens = NULL;

	if (argc == 2)
	{
		// printf("Error: pass the arguments correctly!\n");
		// printf("./parser input.one output\n");
		// return 1;
		input_file = "input";
		data = argv[1];
		tokens = tokenizer_string(data);
	}
	else if (argc == 3)
	{
		input_file = argv[1];
		output_file = argv[2];

		printf("Input file is: %s\n", input_file);
		printf("Output file is: %s\n", output_file);

		data = file_reads(input_file);
		tokens = tokenizer_string(data);
	}
	else
	{
		printf("Error: arguments are not correct!\n");
		printf("./parser input.one output\n");
		printf("./parser \"your input here as string\"\n");
		return 1;
	}

	if(tokens != NULL) {
		parser_init(input_file, tokens);
		parser_free();

		lexer_trace(stdout, data, tokens);
	}

	return 0;
}
