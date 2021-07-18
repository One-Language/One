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
typedef struct
{
	char* name;
} AstModule;

typedef struct
{
	AstModule module;
	Array imports; // AstImportDeclaration
	Array blocks; // AstBlockDeclaration

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
typedef struct
{
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
} AstImportDeclaration;

typedef struct
{
	Location pos;

	char* name;
} AstImportName;

typedef struct
{
	Location pos_names;
	Location pos_alias;

	bool has_alias;

	Array names;
	char* alias;
} AstImportSymbol;

typedef struct
{
	Location pos;

	AstBlockType type;
	union
	{
		AstFunctionDeclaration function;
		AstStructDeclaration structure;
		AstTypeDeclaration type;
		AstStatementDeclaration statement;
	} value;
} AstBlockDeclaration;

typedef enum
{
	BLOCK_FUNCTION,
	BLOCK_STRUCT,
	BLOCK_TYPE,
	BLOCK_STATEMENT,
} AstBlockType;

typedef struct
{
	// [main] FN ( mut name type ) fn_name () type { }
	// ^ pos_attribute
	//        ^ pos_function
	//           ^ pos_reciver
	//                             ^ pos_name
	//                                      ^ pos_param
	//                                        ^ pos_return
	//                                             ^ pos_body
	Location pos;
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
	Array statements; // AstBlockDeclaration
} AstFunctionDeclaration;

typedef struct
{
	// fn (mut t MyTime) century() int {}
	//	   mut t MyTime
	//	   ^ pos_mut
	//	       ^ pos_name
	//	         ^ pos_type
	Location pos;
	Location pos_mut;
	Location pos_name;
	Location pos_type;

	bool is_mut;

	char* name;
	AstData type;
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
typedef struct
{
	// &Node<T>
	// ^ pos_address
	//  ^ pos_name
	//      ^ pos_generic

	// Node<T>
	// ^ pos_address or maybe nil
	// ^ pos_name
	//     ^ pos_generic
	Location pos;
	Location pos_address;
	Location pos_name;
	Location pos_generic;

	bool has_address;
	bool has_generic;

	Array names; // AstDataItem
	Array generics; // char*
} AstData;

typedef struct
{
	Location pos;

	char* name; // char*
} AstDataItem;

typedef struct
{
	Location pos;
	Location pos_name;
	Location pos_body;

	char* name;

	// Array global; // AstStructField
	// Array pub_mut; // AstStructField
	// Array pub; // AstStructField
	// Array mut; // AstStructField
	// Array imut; // AstStructField
	Array fields; // AstStructField
	// TODO: attributes
} AstStructDeclaration;

typedef struct
{
	Location pos;
	Location pos_type;
	Location pos_name;
	Location pos_value;

	bool is_mut;
	bool is_public;
	bool is_global;

	bool has_default;
	AstExpr value;

	AstData type;
	char* name;
	// TODO: attributes
} AstStructField;

typedef struct
{
	Location pos;
	Location pos_name;
	Location pos_body;

	char* name;
	Array fields; // AstEnumField
	// TODO: attributes
} AstEnumDeclaration;

typedef struct
{
	Location pos;
	Location pos_name;
	Location pos_value;

	bool has_default;
	AstExpr value;

	char* name;
	// TODO: attributes
} AstEnumField;

typedef struct
{
} AstExpr;

/*
struct Point {
	x int
	y int
}
struct Line {
	p1 Point
	p2 Point
}
type ObjectSumType = Line | Point

struct Moon {}
struct Mars {}
struct Venus {}
type World = Mars | Moon | Venus

type Filter = fn (string) string
*/
typedef struct
{
	Location pos;
	Location pos_public;
	Location pos_name;

	AstTypeDeclarationType type;

	bool is_public;

	char* name;

	enum
	{
		AstTypeFunctionDeclaration function;
		AstTypeAliasDeclaration alias;
		AstTypeSumDeclaration sum;
	}
	value;
} AstTypeDeclaration;

typedef enum
{
	STATEMENT_TYPE_SUM,
	STATEMENT_TYPE_ALIAS,
	STATEMENT_TYPE_FUNCTION,
} AstTypeDeclarationType;

typedef struct
{
	Location pos;
	Location pos_public;
	Location pos_name;
	Location pos_type;

	bool is_public;

	char* name;
	AstData data; // TODO: AstData can store a function type?
} AstTypeFunctionDeclaration;

typedef struct
{
	Location pos;
	Location pos_public;
	Location pos_name;
	Location pos_type;

	bool is_public;

	char* name;
	AstData data;
} AstTypeAliasDeclaration;

typedef struct
{
	Location pos;
	Location pos_public;
	Location pos_name;
	Location pos_name;

	bool is_public;

	char* name;
	Array data; // AstTypeSumItem
} AstTypeSumDeclaration;

typedef struct
{
	Location pos;
	AstData data;
} AstTypeSumItem;

// typedef enum {
// 	TYPE_STRUCT,
// 	TYPE_SUMTYPE,
// } AstParamDataType;

typedef struct
{
} AstStatementDeclaration;

// char* ast_statement_name(AstStatementType type);

// char* ast_value_name(AstValueType type);

#endif // _ONE_AST_AST_H_
