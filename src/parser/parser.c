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
 * @function: parser_scan_import
 * @description: scan import statement
 * @arguments: nothing
 * @return: AstImportDeclaration
 */
AstImportDeclaration* parser_scan_import()
{
	debug_parser("parser_scan_import");

	// IMPORT <skip> <names> (| { <symbols> } )
	AstImportDeclaration* ast = malloc(sizeof(AstImportDeclaration));

	parser_token_expect(TOKEN_IMPORT);

	parser_token_skip();

	Token* value = parser_token_get();
	debug_parser("parser_scan_import: current token is %s", token_name(parser_token_get_type()));
	parser_token_expect(TOKEN_VALUE_IDENTIFIER);
	info_parser("parser_scan_import: %s", value->value);

	ast->names = malloc(sizeof(AstImportNameArray));
	array_init(ast->names);

	ast->symbols = malloc(sizeof(AstImportSymbolArray));
	array_init(ast->symbols);

	if (parser_token_get_type(TOKEN_AS))
	{
	}
	return ast;
}

/*
 * @function: parser_scan_package
 * @description: scan package statement
 * @arguments: nothing
 * @return: AstPackage
 */
AstPackage* parser_scan_package()
{
	debug_parser("parser_scan_package");

	// PACKAGE <skip> <name>
	AstPackage* ast = malloc(sizeof(AstPackage));

	parser_token_expect(TOKEN_PACKAGE);

	parser_token_skip();

	Token* value = parser_token_get();
	debug_parser("parser_scan_package: current token is %s", token_name(parser_token_get_type()));
	parser_token_expect(TOKEN_VALUE_IDENTIFIER);
	info_parser("parser_scan_package: %s", value->value);

	ast->name = strdup(value->value);

	free(value);
	// printf("==>%s\n", ast->name);

	return ast;
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

	parser_token_skip();

	if (parser_token_get_type() == TOKEN_PACKAGE)
	{
		ast->module = parser_scan_package();
	}

	parser_token_skip();

	TokenType type = parser_token_get_type();

	while (type != TOKEN_EOF && type != TOKEN_ERROR)
	{
		if (type == TOKEN_IMPORT)
		{
			parser_scan_import();
		}
		else
		{
			error_parser("%s is unknown statement in the file!", token_name(type));
		}
		type = parser_token_get_type();
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
