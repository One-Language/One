/**
 The One Programming Language

 File: ast/ast.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef _ONE_AST_AST_H_
#define _ONE_AST_AST_H_

typedef enum _token_type TokenType;

/*
package main
package test
package firstName.subName
*/
typedef struct {
	char* name;
} AstModule;

typedef struct {
	AstModule module;
	Array imports; // AstImport
	Array blocks; // AstBlock

	char* path;
	char* path_base;
} AstFile;

/*
import math // math.sin(), math.cos()
import math { sin } // sin()
import math { sin, cos } // sin(), cos()
import parentLib.childLib // childLib.functionName()
import parentLib.childLib as pc // pc.functionName()
import parentLib {childLib.functionName as a_fn} // a_fn()
import file // file.create()
import file { create } // create()
import file { create as cr } // cr()
*/
typedef struct {
	// IMPORT ****.****.*** { *** } AS ***
	// ^ pos
	//        ^ pos_names
	//                      ^ pos_symbols
	//                              ^ pos_alias
	Location pos;
	Location pos_names;
	Location pos_symbols;
	Location pos_alias;

	Array names; // AstImportName
	Array symbols; // AstImportSymbol
	char* alias;
} AstImport;

typedef struct {
	Location pos;

	char* name;
} AstImportName;

typedef struct {
	Location pos_names;
	Location pos_alias;

	Array names;
	char* alias;
} AstImportSymbol;

typedef struct {
	Location pos;

	AstBlockType type;
	union {
		AstFunction function;
		AstStruct structure;
		AstType type;
		AstStatement statement;
	} value;
} AstBlock;

typedef enum {
	BLOCK_FUNCTION,
	BLOCK_STRUCT,
	BLOCK_TYPE,
	BLOCK_STATEMENT,
} AstBlockType;

typedef struct {
	// [main] FN ( mut name type ) fn_name () type { }
	// ^ pos_attribute
	//        ^ pos_function
	//           ^ pos_reciver
	//                             ^ pos_name
	//                                      ^ pos_param
	//                                        ^ pos_return
	//                                             ^ pos_body
	Location pos_attribute;
	Location pos_function;
	Location pos_reciver;
	Location pos_name;
	Location pos_param;
	Location pos_return;
	Location pos_body;

	bool is_main;
	bool is_noreturn;
	bool is_public;
	bool is_depracted;

	bool has_return;

	AstParam reciver;
	Array params; // AstParam
	Array statements; // AstBlock
} AstFunction;

typedef struct {
	Location pos_type;
	Location pos_name;

	bool is_mut;
	char* name;

	AstParamData type;
	char* name;
} AstParam;

/*
i8, u8
i16, u16
i32, u32
i64, u64
i128, u128
f32, f64
bool
char, string
pubName.publicTypeName
*/
typedef struct {
	Location pos;

	Array names; // AstParamDataItem
} AstParamData;

typedef struct {
	Location pos;

	char* name; // char*
} AstParamDataItem;

// typedef enum {
// 	TYPE_STRUCT,
// 	TYPE_SUMTYPE,
// } AstParamDataType;

typedef struct {
	Location pos;

	bool is_public;
	char* name;
	Array fields; // AstStructField
} AstStruct;

typedef struct {
	Location pos;
	Location pos_type;
	Location pos_name;

	bool is_mut;
	bool is_public;
	bool is_global;

	bool has_default;

	AstParamData type;
	char* name;

	// TODO: attributes
} AstStructField;

typedef struct {

} AstType;

typedef struct {

} AstStatement;


// char* ast_statement_name(AstStatementType type);

// char* ast_value_name(AstValueType type);

#endif // _ONE_AST_AST_H_
