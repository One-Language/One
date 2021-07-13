/**
 The One Programming Language

 File: tokenizer/main.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include <stdio.h>

int main(int argc, char** argv)
{
	if (argc < 3 || argc > 3)
	{
		printf("Error: pass the arguments correcly!\n");
		printf("./tokenizer input.one output.tokens");
		return 1;
	}

	char* input_file = argv[1];
	char* output_file = argv[2];

	printf("Input file is: %s\n", input_file);
	printf("Output file is: %s\n", output_file);

	Token* tokens = tokenizerFile(input_file);

	return 0;
}
