/**
 The One Programming Language

 File: tokenizer/tokenizer.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "tokenizer.h"
#include "../lexer.h"

/*
 * @function: tokenizer_file
 * @description: Create a array of tokens from a filepath
 * @inputs: char* of a one' pathfile
 * @return: Array of Token
 */
Token** tokenizer_file(char* filepath)
{
	debug_token("tokenizer_file");
	debug_token("tokenizer_file: %s", filepath);

	char* data = file_reads(filepath);
	Token** tokens = tokenizer_string(data);
	// TODO: free(data);
	return tokens;
}

/*
 * @function: tokenizer_string
 * @description: Create a array of tokens from a one program source-code char*
 * @inputs: char* of a One program source-code
 * @return: Array of Token
 */
Token** tokenizer_string(char* data)
{
	debug_token("tokenizer_string");
	debug_token("tokenizer_string: %s", data);

	lexer_init(data);

	Array tokens;
	array_init(&tokens);

	size_t i;
	Token* t;
	for (;;)
	{
		t = lexer_scan();
		// printf("==>%s\n", token_name(t->type));
		array_push(&tokens, t);
		debug_parser("parser_scan: print_token %s", token_name(t->type));
		if (t->type == TOKEN_ERROR)
		{
			printf("Error: %s\n", t->value);
			break;
		}
		else if (t->type == TOKEN_EOF)
			break;
	}

	// while (*data != '\0')
	// {
	// 	Token* t = token_make_value(TOKEN_VALUE_IDENTIFIER, (char*){data});
	// 	array_push(&tokens, t);
	// 	data++;
	// }

	return (Token**)tokens.data;
}
