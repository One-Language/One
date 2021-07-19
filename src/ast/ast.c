/**
 The One Programming Language

 File: ast/ast.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "ast.h"

char* ast_statement_name(AstStatementType type)
{
	switch (type)
	{
		// case AST_GLOBAL_STATEMENT_FN:
		// 	return "FN";
		// case AST_GLOBAL_STATEMENT_VAR:
		// 	return "VAR";
		// case AST_GLOBAL_STATEMENT_ENUM:
		// 	return "ENUM";
		// case AST_GLOBAL_STATEMENT_STRUCT:
		// 	return "STRUCT";
		// case AST_GLOBAL_STATEMENT_TYPE:
		// 	return "TYPE";

		// case AST_STATEMENT_RET:
		// 	return "RET";
		// case AST_STATEMENT_PRINT:
		// 	return "PRINT";
		// case AST_STATEMENT_PRINTNL:
		// 	return "PRINTNL";
		// case AST_STATEMENT_PRINTDB:
		// 	return "PRINTDB";
		// case AST_STATEMENT_PRINTDBNL:
		// 	return "PRINTDBNL";

		// case AST_STATEMENT_WHILE:
		// 	return "WHILE";
		// case AST_STATEMENT_FOR:
		// 	return "FOR";
		// case AST_STATEMENT_DO:
		// 	return "DO";
		// case AST_STATEMENT_MATCH:
		// 	return "MATCH";

		// case AST_STATEMENT_EXPRESSION:
		// 	return "EXPRESSIONS";

		// case AST_STATEMENT_IF:
		// 	return "IF";

		// case AST_STATEMENT_VARIABLE:
		// 	return "VARIABLE";

		default:
			return "UNKNOWN";
	}
}

char* ast_value_name(AstValueType type)
{
	switch (type)
	{
		// case AST_TYPE_I8:
		// 	return "i8";
		// case AST_TYPE_I16:
		// 	return "i16";
		// case AST_TYPE_I32:
		// 	return "i32";
		// case AST_TYPE_I64:
		// 	return "i64";
		// case AST_TYPE_I128:
		// 	return "i128";

		// case AST_TYPE_U8:
		// 	return "u8";
		// case AST_TYPE_U16:
		// 	return "u16";
		// case AST_TYPE_U32:
		// 	return "u32";
		// case AST_TYPE_U64:
		// 	return "u64";
		// case AST_TYPE_U128:
		// 	return "u128";

		// case AST_TYPE_F32:
		// 	return "f32";
		// case AST_TYPE_F64:
		// 	return "f64";

		// case AST_TYPE_STRING:
		// 	return "string";
		// case AST_TYPE_CHAR:
		// 	return "char";
		// case AST_TYPE_BOOL:
		// 	return "bool";

		default:
			return "UNKNOWN";
	}
}
