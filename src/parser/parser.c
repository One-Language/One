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
void parser_init(char* path, char* input, Token** tokens)
{
	debug_parser("parser_init");

	parser.path = path;
	parser.path_base = (const char*)file_get_parent(path);

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

	ast->names = malloc(sizeof(AstImportNameArray));
	array_init(ast->names);

	ast->symbols = malloc(sizeof(AstImportSymbolArray));
	array_init(ast->symbols);

	parser_token_expect(TOKEN_IMPORT);

	Token* value;
	AstImportName* name;
	do
	{
		parser_token_skip();

		value = parser_token_expect_get(TOKEN_VALUE_IDENTIFIER);
		info_parser("parser_scan_import: %s", value->value);

		name = malloc(sizeof(AstImportName));
		name->name = value->value;

		array_push(ast->names, name);

		parser_token_skip();
	} while (parser_token_has(TOKEN_OPERATOR_DOT));

	// AS <skip> IDENTIFIER
	if (parser_token_has(TOKEN_AS))
	{
		parser_token_skip();

		Token* alias = parser_token_expect_get(TOKEN_VALUE_IDENTIFIER);
		info_parser("parser_scan_import: set alias as %s", ast->alias);
		ast->alias = strdup(alias->value);
		free(alias);
	}

	parser_token_skip();

	// { <skip> [[<names> <skip> AS <skip> IDENTIFIER ]]  }
	if (parser_token_has(TOKEN_OPERATOR_BRACKET_CURLY_LEFT))
	{
		parser_token_skip();

		while (parser_token_get_type() == TOKEN_VALUE_IDENTIFIER)
		{
			AstImportSymbol* symbol = malloc(sizeof(AstImportSymbol));

			Token* symbol_name;
			symbol->names = malloc(sizeof(StringArray));
			array_init(symbol->names);

			do
			{
				parser_token_skip();

				symbol_name = parser_token_expect_get(TOKEN_VALUE_IDENTIFIER);

				array_push(symbol->names, strdup(symbol_name->value));
				info_parser("parser_scan_import: symbol name: %s", symbol_name->value);
				free(symbol_name);

				parser_token_skip();
			} while (parser_token_has(TOKEN_OPERATOR_DOT));


			if (parser_token_has(TOKEN_AS))
			{
				parser_token_skip();

				symbol->has_alias = true;
				Token* symbol_alias = parser_token_expect_get(TOKEN_VALUE_IDENTIFIER);
				symbol->alias = strdup(symbol_alias->value);
				info_parser("parser_scan_import: symbol alias as: %s", symbol_alias->value);
				free(symbol_alias);

				parser_token_skip();
			}
			else
			{
				symbol->has_alias = false;
			}

			array_push(ast->symbols, symbol);

			parser_token_has(TOKEN_OPERATOR_COMMA); // optional token

			parser_token_skip();
		}
		parser_token_expect(TOKEN_OPERATOR_BRACKET_CURLY_RIGHT);

		info_parser("parser_scan_import: count of symbols is %d", ast->symbols->count);
	}

	return ast;
}

/*
 * @function: parser_scan_fn
 * @description: scan fn statement
 * @arguments: nothing
 * @return: AstBlockItem
 */
AstBlockItem* parser_scan_fn()
{
	debug_parser("parser_scan_fn");

	// FN <skip> IDENTIFIER
	AstBlockItem* ast = malloc(sizeof(AstBlockItem));
	ast->type = AST_BLOCK_FUNCTION;

	ast->value.function = malloc(sizeof(AstFunctionDeclaration));

	parser_token_expect(TOKEN_FN);

	parser_token_skip();

	Token* name = parser_token_expect_get(TOKEN_VALUE_IDENTIFIER);
	ast->value.function->name = strdup(name->value);
	free(name);
	info_parser("parser_scan_fn: name is %s", ast->value.function->name);

	parser_token_skip();

	parser_scan_block();

	return ast;
}

/*
 * @function: parser_scan_expression
 * @description: scan expression statement
 * @arguments: nothing
 * @return: AstExprDeclaration*
 */
AstExprDeclaration* parser_scan_expression()
{
	debug_parser("parser_scan_expression");

	AstExprDeclaration* ast = malloc(sizeof(AstExprDeclaration));

	if (parser_token_has(TOKEN_VALUE_IDENTIFIER) == true)
	{
		parser_token_next();
	}
	else if (parser_token_has(TOKEN_VALUE_NUMBER) == true)
	{
		parser_token_next();
	}
	else if (parser_token_has(TOKEN_VALUE_STRING) == true)
	{
		parser_token_next();
	}
	else if (parser_token_has(TOKEN_VALUE_CHAR) == true)
	{
		parser_token_next();
	}

	return ast;
}

/*
 * @function: parser_scan_if
 * @description: scan if statement
 * @arguments: nothing
 * @return: AstBlockItem
 */
AstBlockItem* parser_scan_block_if()
{
	debug_parser("parser_scan_block_if");

	// IF <skip> <expr> <skip> <BLOCK>
	AstBlockItem* ast = malloc(sizeof(AstBlockItem));
	ast->type = AST_BLOCK_STATEMENT;
	ast->value.statement = malloc(sizeof(AstStatementDeclaration));
	ast->value.statement->type = AST_STATEMENT_IF;

	ast->value.statement->value.clauses = malloc(sizeof(AstStatementIf));

	parser_token_expect(TOKEN_IF);

	parser_token_skip();

	ast->value.statement->value.clauses->expr = parser_scan_expression();

	parser_token_skip();

	ast->value.statement->value.clauses->body = parser_scan_block();

	return ast;
}

/*
 * @function: parser_scan_block_for
 * @description: scan for statement
 * @arguments: nothing
 * @return: AstBlockItem
 */
AstBlockItem* parser_scan_block_for()
{
	debug_parser("parser_scan_block_for");

	// FOR <skip> <expr> <skip> <BLOCK> // TODO
	AstBlockItem* ast = malloc(sizeof(AstBlockItem));
	ast->type = AST_BLOCK_STATEMENT;
	ast->value.statement = malloc(sizeof(AstStatementDeclaration));
	ast->value.statement->type = AST_STATEMENT_FOR;

	ast->value.statement->value.foreach = malloc(sizeof(AstStatementFor));

	parser_token_expect(TOKEN_FOR);

	parser_token_skip();

	return ast;
}

/*
 * @function: parser_scan_block_ret
 * @description: scan ret statement
 * @arguments: nothing
 * @return: AstBlockItem*
 */
AstBlockItem* parser_scan_block_ret()
{
	debug_parser("parser_scan_block_ret");

	// RET <skip> <expr> <skip>
	AstBlockItem* ast = malloc(sizeof(AstBlockItem));
	ast->type = AST_BLOCK_STATEMENT;
	ast->value.statement = malloc(sizeof(AstStatementDeclaration));
	ast->value.statement->type = AST_STATEMENT_RET;

	ast->value.statement->value.ret = malloc(sizeof(AstStatementRet));

	parser_token_expect(TOKEN_RET);

	parser_token_skip();

	return ast;
}

/*
 * @function: parser_scan_block_match
 * @description: scan match statement
 * @arguments: nothing
 * @return: AstBlockItem*
 */
AstBlockItem* parser_scan_block_match()
{
	debug_parser("parser_scan_block_match");

	// FOR <skip> <expr> <skip> <BLOCK> // TODO
	AstBlockItem* ast = malloc(sizeof(AstBlockItem));
	ast->type = AST_BLOCK_STATEMENT;
	ast->value.statement = malloc(sizeof(AstStatementDeclaration));
	ast->value.statement->type = AST_STATEMENT_MATCH;
	ast->value.statement->value.match = malloc(sizeof(AstStatementMatch));

	parser_token_expect(TOKEN_MATCH);

	parser_token_skip();

	return ast;
}

/*
 * @function: parser_scan_block_statement
 * @description: scan statenent
 * @arguments: nothing
 * @return: AstBlockItem*
 */
AstBlockItem* parser_scan_block_statement()
{
	debug_parser("parser_scan_block_statement");

	AstBlockItem* ast = malloc(sizeof(AstBlockItem));

	TokenType t = parser_token_get_type();
	if (t == TOKEN_FOR)
	{
		ast = parser_scan_block_for();
	}
	else if (t == TOKEN_IF)
	{
		ast = parser_scan_block_if();
	}
	else if (t == TOKEN_RET)
	{
		ast = parser_scan_block_ret();
	}
	else if (t == TOKEN_MATCH)
	{
		ast = parser_scan_block_match();
	}
	else
	{
		info_parser("unknown token as stmt %s\n", token_name(t));
		parser_token_next();
	}

	return ast;
}

/*
 * @function: parser_scan_block
 * @description: scan block
 * @arguments: nothing
 * @return: AstBlockDeclaration
 */
AstBlockDeclaration* parser_scan_block()
{
	debug_parser("parser_scan_block");

	// { <stmts> }
	AstBlockDeclaration* ast = malloc(sizeof(AstBlockDeclaration));

	ast->functions = malloc(sizeof(AstFunctionDeclarationArray));
	ast->structures = malloc(sizeof(AstStructDeclarationArray));
	ast->enumerates = malloc(sizeof(AstEnumDeclarationArray));
	ast->types = malloc(sizeof(AstTypeDeclarationArray));
	ast->statements = malloc(sizeof(AstStatementDeclarationArray));

	array_init(ast->functions);
	array_init(ast->structures);
	array_init(ast->enumerates);
	array_init(ast->types);
	array_init(ast->statements);

	parser_token_expect(TOKEN_OPERATOR_BRACKET_CURLY_LEFT);

	parser_token_skip();

	while (parser_token_has(TOKEN_OPERATOR_BRACKET_CURLY_RIGHT) == false)
	{
		AstBlockItem* item = parser_scan_block_statement();
		if (item != NULL)
		{
			if (item->type == AST_BLOCK_FUNCTION)
			{
				array_push(ast->functions, item->value.function);
			}
			else if (item->type == AST_BLOCK_STRUCT)
			{
				array_push(ast->structures, item->value.structure);
			}
			else if (item->type == AST_BLOCK_ENUM)
			{
				array_push(ast->enumerates, item->value.enumerate);
			}
			else if (item->type == AST_BLOCK_TYPE)
			{
				array_push(ast->types, item->value.type);
			}
			else if (item->type == AST_BLOCK_STATEMENT)
			{
				array_push(ast->statements, item->value.statement);
			}
		}
	}

	printf("--->count stmt: %d\n", ast->statements->count);

	parser_token_skip();

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

	Token* value = parser_token_expect_get(TOKEN_VALUE_IDENTIFIER);
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

	ast->path = parser.path;
	ast->path_base = parser.path_base;

	ast->module = malloc(sizeof(AstPackage));
	ast->module->name = NULL;

	ast->imports = malloc(sizeof(AstImportDeclarationArray));
	array_init(ast->imports);

	ast->blocks = malloc(sizeof(AstBlockDeclarationArray));
	array_init(ast->blocks);

	parser_token_skip();

	if (parser_token_get_type() == TOKEN_PACKAGE)
	{
		free(ast->module);
		ast->module = parser_scan_package();
	}

	TokenType type = parser_token_get_type();

	while (type != TOKEN_EOF && type != TOKEN_ERROR)
	{
		if (parser_token_skip())
		{
			type = parser_token_get_type();
		}

		if (type == TOKEN_IMPORT)
		{
			AstImportDeclaration* import = parser_scan_import();
			if (import != NULL)
			{
				array_push(ast->imports, import);
			}
		}
		else if (type == TOKEN_FN)
		{
			AstBlockItem* func = parser_scan_fn();
			if (func != NULL)
			{
				array_push(ast->blocks, func);
			}
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
