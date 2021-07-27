/**
 The One Programming Language

 File: parser/parser.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "parser.h"

// Global variable(s)
Parser parser;

/*
 * @function: parser_init
 * @description: Set default value for the global `parser` variable
 * @arguments: char* filepath, char* input, Token** tokens
 * @return: void; nothing
 */
void parser_init(char* filepath, char* input, Token** tokens)
{
	debug_parser("parser_init");

	parser.path = filepath;
	parser.data = input;
	parser.tokens = tokens;
}

/*
 * @function: parser_scan
 * @description: Start to check tokens. it's entry point of parser stage.
 * @arguments: nothing
 * @return: Always a pointer of AST (AstFile) struct
 */
AstFile* parser_scan()
{
	debug_parser("parser_scan");

	AstFile* ast = malloc(sizeof(AstFile));
	Token** tokens = parser.tokens;

	while (tokens != NULL && *tokens != NULL)
	{
		Token* t = *tokens;
		if(t->type == 	TOKEN_SKIP_WHITESPACE,
	TOKEN_SKIP_WHITESPACE_LINE,
	TOKEN_SKIP_COMMENT_SINGLE,
	TOKEN_SKIP_COMMENT_MULTI,
)
		char* t_name = token_name(t->type);

		bool has1 = file_convert_index_to_rc(parser.data, t->pos.index, &t->pos.line, &t->pos.column);
		bool has2 = file_convert_index_to_rc(parser.data, t->pos_end.index, &t->pos_end.line, &t->pos_end.column);

		printf("[%d:%d] [%d:%d - %d:%d] %s", t->pos.tokens, t->length, t->pos.line, t->pos.column, t->pos_end.line, t->pos_end.column, t_name);
		if (t->value != NULL)
		{
			printf(": \"%s\"", t->value);
		}
		printf("\n");

		tokens++;
	}

	return ast;
}

/*
 * @function: parser_trace
 * @description: Log and trace items of tokens
 * @arguments: FILE* file_out, char* data, Token** tokens, AstFile* ast
 * @return: nothing, void
 */
void parser_trace(FILE* file_out, char* data, Token** tokens, AstFile* ast)
{
	debug_parser("parser_trace");
}

/*
 * @function: parser_free
 * @description: Free allocated memory for the parser stage! TODO
 * @arguments: nothing
 * @return: nothing, void
 */
void parser_free()
{
	debug_parser("parser_free");
}
