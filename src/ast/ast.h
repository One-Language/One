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
		AstEnumDeclaration enumerate;
		AstTypeDeclaration type;
		AstStatementDeclaration statement;
	} value;
} AstBlockDeclaration;

typedef enum
{
	AST_BLOCK_FUNCTION,
	AST_BLOCK_STRUCT,
	AST_BLOCK_ENUM,
	AST_BLOCK_TYPE,
	AST_BLOCK_STATEMENT,
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
	AstExprDeclaration value;

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
	AstExprDeclaration value;

	char* name;
	// TODO: attributes
} AstEnumField;

typedef struct
{
	Location pos;

	AstExprType type;
	AstOperatorType op;

	AstExprDeclaration left;
	AstExprDeclaration right;

	enum
	{
		char i8;
		unsigned char u8;

		short i16;
		unsigned short u16;

		int i32;
		unsigned int u32;

		int64_t i64;
		uint64_t u64;

		float f32;
		double f64;

		bool bool;

		char * string;
		char * ch;
	}
	value;
} AstExprDeclaration;

typedef enum
{
	AST_OPERATOR_PLUS, // -
	AST_OPERATOR_PLUS_PLUS, // --

	AST_OPERATOR_MINUS, // -
	AST_OPERATOR_MINUS_MINUS, // --

	AST_OPERATOR_STAR, // *
	AST_OPERATOR_STAR_STAR, // **

	AST_OPERATOR_SLASH, // /
	AST_OPERATOR_SLASH_INT, // //

	AST_OPERATOR_SHIFT_LEFT, // >>
	AST_OPERATOR_SHIFT_RIGHT, // <<

	AST_OPERATOR_AND, // &&
	AST_OPERATOR_AND_BIT, // &

	AST_OPERATOR_OR, // ||
	AST_OPERATOR_OR_BIT, // |

	AST_OPERATOR_NOT, // !
	AST_OPERATOR_NOT_EQUAL, // !=
	AST_OPERATOR_NOT_EQUAL_EQUAL, // !==

	AST_OPERATOR_EQUAL, // =
	AST_OPERATOR_EQUAL_EQUAL, // ==
	AST_OPERATOR_EQUAL_EQUAL, // ===

	// Relational Operators
	AST_OPERATOR_GREATER, // >
	AST_OPERATOR_GREATER_EQUAL, // >=
	AST_OPERATOR_LESS, // <
	AST_OPERATOR_LESS_EQUAL, // <=

	AST_OPERATOR_DOT, // parent.sub
	AST_OPERATOR_DOT_DOT, // [1..4]
	AST_OPERATOR_DOT_DOT_DOT, // {...objects}
} AstOperatorType;

typedef enum
{
	AST_EXPRESSION_TYPE_OPERATOR,

	AST_EXPRESSION_TYPE_I8,
	AST_EXPRESSION_TYPE_U8,

	AST_EXPRESSION_TYPE_I16,
	AST_EXPRESSION_TYPE_U16,

	AST_EXPRESSION_TYPE_I32,
	AST_EXPRESSION_TYPE_U32,

	AST_EXPRESSION_TYPE_I64,
	AST_EXPRESSION_TYPE_U64,

	AST_EXPRESSION_TYPE_I128,
	AST_EXPRESSION_TYPE_U128,

	AST_EXPRESSION_TYPE_F32,
	AST_EXPRESSION_TYPE_F64,

	AST_EXPRESSION_TYPE_BOOL,
	AST_EXPRESSION_TYPE_STRING,
	AST_EXPRESSION_TYPE_CHAR,
} AstExprType;

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

	union
	{
		AstTypeFunctionDeclaration function;
		AstTypeAliasDeclaration alias;
		AstTypeSumDeclaration sum;
	} value;
} AstTypeDeclaration;

typedef enum
{
	AST_TYPE_SUM,
	AST_TYPE_ALIAS,
	AST_TYPE_FUNCTION,
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
