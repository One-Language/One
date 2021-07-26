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
 * @arguments: char* input, Token** tokens
 * @return: void; nothing
 */
void parser_init(char* input, Token** tokens)
{
	debug_parser("parser_init");

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
	return ast;
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
