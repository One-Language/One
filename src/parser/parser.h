/**
 The One Programming Language

 File: parser/parser.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef _ONE_PARSER_PARSER_H_
#define _ONE_PARSER_PARSER_H_

#include "../lexer/lexer.h"

#include "../ast/ast.h"

#include "parser_token.h"

#include "../builtins/array.h"

typedef struct
{
	AstFile* ast;

	const char* path;

	const char* data;

	// tokens
	Token** tokens;
	size_t index;
} Parser;

/*
 * @function: parser_init
 * @description: Set default value for the global `parser` variable
 * @arguments: char* filepath, char* input, Token** tokens
 * @return: void; nothing
 */
void parser_init(char* filepath, char* input, Token** tokens);

/*
 * @function: parser_scan_import
 * @description: scan import statement
 * @arguments: nothing
 * @return: AstImportDeclaration
 */
AstImportDeclaration* parser_scan_import();

/*
 * @function: parser_scan_fn
 * @description: scan fn statement
 * @arguments: nothing
 * @return: AstFunctionDeclaration
 */
AstFunctionDeclaration* parser_scan_fn();

/*
 * @function: parser_scan_block
 * @description: scan block
 * @arguments: nothing
 * @return: AstBlockDeclaration
 */
AstBlockDeclaration* parser_scan_block();

/*
 * @function: parser_scan_package
 * @description: scan package statement
 * @arguments: nothing
 * @return: AstPackage
 */
AstPackage* parser_scan_package();

/*
 * @function: parser_scan
 * @description: Start to check tokens. it's entry point of parser stage.
 * @arguments: nothing
 * @return: Always a pointer of AST (AstFile) struct
 */
AstFile* parser_scan();

/*
 * @function: parser_trace
 * @description: Log and trace items of tokens
 * @arguments: FILE* file_out, char* data, Token** tokens, AstFile* ast
 * @return: nothing, void
 */
void parser_trace(FILE* file_out, char* data, Token** tokens, AstFile* ast);

/*
 * @function: parser_free
 * @description: Free allocated memory for the parser stage! TODO
 * @arguments: nothing
 * @return: nothing, void
 */
void parser_free();

#endif // _ONE_PARSER_PARSER_H_
