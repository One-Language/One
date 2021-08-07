/**
 The One Programming Language

 File: ast/ast.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "ast.h"

// char* ast_statement_name(AstStatementType type)
// {
// 	switch (type)
// 	{
// 		// case AST_GLOBAL_STATEMENT_FN:
// 		// 	return "FN";
// 		// case AST_GLOBAL_STATEMENT_VAR:
// 		// 	return "VAR";
// 		// case AST_GLOBAL_STATEMENT_ENUM:
// 		// 	return "ENUM";
// 		// case AST_GLOBAL_STATEMENT_STRUCT:
// 		// 	return "STRUCT";
// 		// case AST_GLOBAL_STATEMENT_TYPE:
// 		// 	return "TYPE";

// 		// case AST_STATEMENT_RET:
// 		// 	return "RET";
// 		// case AST_STATEMENT_PRINT:
// 		// 	return "PRINT";
// 		// case AST_STATEMENT_PRINTNL:
// 		// 	return "PRINTNL";
// 		// case AST_STATEMENT_PRINTDB:
// 		// 	return "PRINTDB";
// 		// case AST_STATEMENT_PRINTDBNL:
// 		// 	return "PRINTDBNL";

// 		// case AST_STATEMENT_WHILE:
// 		// 	return "WHILE";
// 		// case AST_STATEMENT_FOR:
// 		// 	return "FOR";
// 		// case AST_STATEMENT_DO:
// 		// 	return "DO";
// 		// case AST_STATEMENT_MATCH:
// 		// 	return "MATCH";

// 		// case AST_STATEMENT_EXPRESSION:
// 		// 	return "EXPRESSIONS";

// 		// case AST_STATEMENT_IF:
// 		// 	return "IF";

// 		// case AST_STATEMENT_VARIABLE:
// 		// 	return "VARIABLE";

// 		default:
// 			return "UNKNOWN";
// 	}
// }

// char* ast_value_name(AstValueType type)
// {
// 	switch (type)
// 	{
// 		// case AST_TYPE_I8:
// 		// 	return "i8";
// 		// case AST_TYPE_I16:
// 		// 	return "i16";
// 		// case AST_TYPE_I32:
// 		// 	return "i32";
// 		// case AST_TYPE_I64:
// 		// 	return "i64";
// 		// case AST_TYPE_I128:
// 		// 	return "i128";

// 		// case AST_TYPE_U8:
// 		// 	return "u8";
// 		// case AST_TYPE_U16:
// 		// 	return "u16";
// 		// case AST_TYPE_U32:
// 		// 	return "u32";
// 		// case AST_TYPE_U64:
// 		// 	return "u64";
// 		// case AST_TYPE_U128:
// 		// 	return "u128";

// 		// case AST_TYPE_F32:
// 		// 	return "f32";
// 		// case AST_TYPE_F64:
// 		// 	return "f64";

// 		// case AST_TYPE_STRING:
// 		// 	return "string";
// 		// case AST_TYPE_CHAR:
// 		// 	return "char";
// 		// case AST_TYPE_BOOL:
// 		// 	return "bool";

// 		default:
// 			return "UNKNOWN";
// 	}
// }

void ast_init(const char* input_file, const char* data, Token** tokens, AstFile* ast)
{
}

void ast_trace(FILE* file_out, AstFile* ast)
{
	fprintf(file_out, "Program %s (%s)\n", ast->path, ast->path_base);
	fprintf(file_out, "Module %s\n", (ast->module->name != NULL) ? ast->module->name : "none");

	AstImportDeclaration* name_item;
	AstImportSymbol* symbol_item;

	AstImportName* name;
	AstImportSymbol* symbol;

	AstImportNameArray* names;
	AstImportSymbolArray* symbols;

	fprintf(file_out, "Imports (%d) [\n", ast->imports->count);
	for (int i = 0; i < ast->imports->count; i++)
	{
		name_item = (AstImportDeclaration*)ast->imports->data[i];
		fprintf(file_out, "\tImport {\n");

		names = name_item->names;
		fprintf(file_out, "\t\tNames = [ ");
		for (int i = 0; i < names->count; i++)
		{
			name = (AstImportName*)names->data[i];
			fprintf(file_out, "%s", name->name);
			if (i + 1 != names->count)
			{
				fprintf(file_out, "->");
			}
		}
		fprintf(file_out, " ]\n");

		fprintf(file_out, "\t\tAlias = %s\n", name_item->alias == NULL ? "none" : name_item->alias);

		symbols = name_item->symbols;
		fprintf(file_out, "\t\tSymbols = (%d) [", symbols->count);
		if (symbols->count == 0)
		{
			fprintf(file_out, " ]\n");
		}
		else
		{
			fprintf(file_out, "\n");
			for (int i = 0; i < symbols->count; i++)
			{
				symbol = (AstImportSymbol*)symbols->data[i];

				names = symbol->names;
				fprintf(file_out, "\t\t\t{ ");
				fprintf(file_out, "Names = (%d) [ ", names->count);
				for (int i = 0; i < names->count; i++)
				{
					name = (AstImportName*)names->data[i];
					fprintf(file_out, "%s", name->name);
					if (i + 1 != names->count)
					{
						fprintf(file_out, ", ");
					}
				}

				fprintf(file_out, " ], ");

				if (symbol->has_alias)
				{
					fprintf(file_out, "Alias = %s", symbol->alias);
				}
				else
				{
					fprintf(file_out, "Alias = None");
				}
				fprintf(file_out, " }\n");
			}
			fprintf(file_out, "\t\t]\n");
		}
		fprintf(file_out, "\t}\n");
	}
	fprintf(file_out, "]\n");
}

void ast_free()
{
}
