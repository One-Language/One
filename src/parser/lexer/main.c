/**
 The One Programming Language

 File: lexer/main.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include <stdio.h>
#include <stdlib.h>

#include <builtins/file.h>

#include "lexer.h"
extern Token* current;

int main(int argc, char** argv)
{
	char* input_file;
	char* output_file;
	FILE* file_out = stdout;

	if (argc == 1)
	{
		printf("Error: arguments are not correct!\n");
		printf("./lexer input.one output.tokens\n");
		printf("./lexer \"your input here as string\"\n");
		return 1;
	}
	else if (argc == 2)
	{
		input_file = argv[1];
	}
	else if (argc == 3)
	{
		input_file = argv[1];
		output_file = argv[2];
		file_out = fopen(output_file, "wa+");

		if (!file_out)
		{
			fprintf(stderr, "Error: it's unable to write output to %s file!\n", output_file);
			exit(1);
		}
	}

	char* data = file_reads(input_file);
	lexer_init(data);

	// Lexer Tracer for debugging
	while (!peekFor(TOKEN_EOF))
	{
		char* t_name = token_name(current->type);

		bool has1 = file_convert_index_to_rc(data, current->pos.index, &current->pos.line, &current->pos.column);
		bool has2 = file_convert_index_to_rc(data, current->pos_end.index, &current->pos_end.line, &current->pos_end.column);

		fprintf(file_out, "[%zu:%zu] [%zu:%zu - %zu:%zu] %s", current->pos.tokens, current->length, current->pos.line, current->pos.column, current->pos_end.line, current->pos_end.column, t_name);

		if (current->value != NULL)
		{
			fprintf(file_out, ": \"%s\"", current->value);
		}
		fprintf(file_out, "\n");

		advance();
	}

	assert(current->type == TOKEN_EOF);
	free(current);
	lexer_free();
	free(data);
	if (file_out != stdout) fclose(file_out);

	return 0;
}
