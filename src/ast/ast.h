/**
 The One Programming Language

 File: ast/ast.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef _ONE_AST_AST_H_
#define _ONE_AST_AST_H_

#include <inttypes.h>

#include "../builtins/array.h"
#include "../lexer/tokenizer/token.h"

typedef enum _token_type TokenType;
typedef struct _location Location;

/*
package main
package test
package firstName.subName
*/
typedef struct
{
	char* name;
} AstPackage;

// typedefs
typedef struct _ast_file AstFile;
typedef struct _ast_import_declaration AstImportDeclaration;
typedef struct _ast_import_name AstImportName;
typedef struct _ast_import_symbol AstImportSymbol;
typedef struct _ast_block_declaration AstBlockDeclaration;
typedef enum _ast_block_type AstBlockType;
typedef struct _ast_function_declaration AstFunctionDeclaration;
typedef enum _ast_attribute_type AstAttributeType;
typedef struct _ast_attribute_declaration AstAttributeDeclaration;
typedef struct _ast_param AstParam;
typedef struct _ast_data AstData;
typedef struct _ast_data_item AstDataItem;
typedef struct _ast_struct_declaration AstStructDeclaration;
typedef struct _ast_struct_field AstStructField;
typedef struct _ast_enum_declaration AstEnumDeclaration;
typedef struct _ast_enum_field AstEnumField;
typedef struct _ast_expr_declaration AstExprDeclaration;
typedef enum _ast_operator_type AstOperatorType;
typedef enum _ast_expr_type AstExprType;
typedef struct _ast_type_declaration AstTypeDeclaration;
typedef enum _ast_type_declaration_type AstTypeDeclarationType;
typedef struct _ast_type_function_declaration AstTypeFunctionDeclaration;
typedef struct _ast_type_alias_declaration AstTypeAliasDeclaration;
typedef struct _ast_type_sum_declaration AstTypeSumDeclaration;
typedef struct _ast_type_sum_item AstTypeSumItem;
typedef struct _ast_statement_declaration AstStatementDeclaration;
typedef enum _ast_statement_type AstStatementType;
typedef struct _ast_statement_if AstStatementIf;
typedef struct _ast_statement_for AstStatementFor;
typedef enum _ast_statement_for_type AstStatementForType;
typedef struct _ast_statement_for_c AstStatementForC;
typedef struct _ast_statement_for_each AstStatementForEach;
typedef struct _ast_statement_for_map AstStatementForMap;
typedef struct _ast_statement_for_loop AstStatementForLoop;
typedef struct _ast_statement_match AstStatementMatch;
typedef struct _ast_statement_ret AstStatementRet;
typedef struct _ast_statement_assign AstStatementAssign;
typedef struct _ast_statement_assign_const AstStatementAssignConst;
typedef struct _ast_statement_const_item AstStatementAssignConstItem;
typedef struct _ast_statement_variable AstStatementVariable;
typedef struct _ast_statement_expr AstStatementExpr;

// Array
typedef Array AstFunctionDeclarationArray; // AstFunctionDeclaration
typedef Array AstStructDeclarationArray; // AstStructDeclaration
typedef Array AstEnumDeclarationArray; // AstEnumDeclaration
typedef Array AstTypeDeclarationArray; // AstTypeDeclaration
typedef Array AstStatementDeclarationArray; // AstStatementDeclaration

typedef Array AstImportSymbolArray; // AstImportSymbol
typedef Array AstImportNameArray; // AstImportName
typedef Array AstImportDeclarationArray; // AstImportDeclaration
// typedef Array AstBlockDeclarationArray; // AstBlockDeclaration
typedef Array StringArray; // char
typedef Array AstParamArray; // AstParam
typedef Array AstAttributeDeclarationArray; // AstAttributeDeclaration
typedef Array AstDataItemArray; // AstDataItem
typedef Array AstStructFieldArray; // AstStructField
typedef Array AstEnumFieldArray; // AstEnumField
typedef Array AstTypeSumItemArray; // AstTypeSumItem
typedef Array AstStatementAssignConstItemArray; // AstStatementAssignConstItem

typedef struct _ast_file
{
	AstPackage* module;
	AstImportDeclarationArray* imports; // AstImportDeclaration
	AstBlockDeclaration* blocks;

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
typedef struct _ast_import_declaration
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

	AstImportNameArray* names; // AstImportName
	AstImportSymbolArray* symbols; // AstImportSymbol
	char* alias;
} AstImportDeclaration;

typedef struct _ast_import_name
{
	Location pos;

	char* name;
} AstImportName;

typedef struct _ast_import_symbol
{
	Location pos_names;
	Location pos_alias;

	bool has_alias;

	StringArray* names; // char*
	char* alias;
} AstImportSymbol;

typedef enum _ast_block_type
{
	AST_BLOCK_FUNCTION,
	AST_BLOCK_STRUCT,
	AST_BLOCK_ENUM,
	AST_BLOCK_TYPE,
	AST_BLOCK_STATEMENT,
} AstBlockType;

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
typedef struct _ast_data
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

	AstDataItemArray* names; // AstDataItem
	StringArray* generics; // char*
} AstData;

typedef struct _ast_data_item
{
	Location pos;

	char* name; // char*
} AstDataItem;

typedef struct _ast_param
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
	AstData* type;
} AstParam;

typedef struct _ast_function_declaration
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

	char* name;
	AstParam* reciver;
	AstParamArray* params; // AstParam
	AstBlockDeclaration* statements;
	AstAttributeDeclarationArray* attributes; // AstAttributeDeclaration
} AstFunctionDeclaration;

typedef enum _ast_attribute_type
{
	AST_ATTRIBUTE_IDENTIFIER,
	AST_ATTRIBUTE_KEY,
} AstAttributeType;

typedef struct _ast_attribute_declaration
{
	Location pos;
	Location pos_name;
	Location pos_value;

	AstAttributeType type;

	bool has_value;

	char* name;
	char* value;
} AstAttributeDeclaration;

typedef struct _ast_struct_declaration
{
	Location pos;
	Location pos_attribute;
	Location pos_name;
	Location pos_body;

	char* name;

	// Array global; // AstStructField
	// Array pub_mut; // AstStructField
	// Array pub; // AstStructField
	// Array mut; // AstStructField
	// Array imut; // AstStructField

	AstStructFieldArray* fields; // AstStructField
	AstAttributeDeclarationArray* attributes; // AstAttributeDeclaration
} AstStructDeclaration;

typedef struct _ast_enum_declaration
{
	Location pos;
	Location pos_attribute;
	Location pos_name;
	Location pos_body;

	char* name;
	AstEnumFieldArray* fields; // AstEnumField
	AstAttributeDeclarationArray* attributes; // AstAttributeDeclaration
} AstEnumDeclaration;

typedef enum _ast_type_declaration_type
{
	AST_TYPE_SUM,
	AST_TYPE_ALIAS,
	AST_TYPE_FUNCTION,
} AstTypeDeclarationType;

typedef struct _ast_type_function_declaration
{
	Location pos;
	Location pos_public;
	Location pos_name;
	Location pos_type;

	bool is_public;

	char* name;
	AstData* data; // TODO: AstData can store a function type?
} AstTypeFunctionDeclaration;

typedef struct _ast_type_alias_declaration
{
	Location pos;
	Location pos_public;
	Location pos_name;
	Location pos_type;

	bool is_public;

	char* name;
	AstData* data;
} AstTypeAliasDeclaration;

typedef struct _ast_type_sum_declaration
{
	Location pos;
	Location pos_public;
	Location pos_names;

	bool is_public;

	char* name;
	AstTypeSumItemArray* data; // AstTypeSumItem
} AstTypeSumDeclaration;

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
typedef struct _ast_type_declaration
{
	Location pos;
	Location pos_public;
	Location pos_name;

	AstTypeDeclarationType type;

	bool is_public;

	char* name;

	union
	{
		AstTypeFunctionDeclaration* function;
		AstTypeAliasDeclaration* alias;
		AstTypeSumDeclaration* sum;
	} value;
} AstTypeDeclaration;

typedef enum _ast_operator_type
{
	AST_OPERATOR_NONE, // emit data

	AST_OPERATOR_PLUS, // -
	AST_OPERATOR_PLUS_PLUS, // --

	AST_OPERATOR_MINUS, // -
	AST_OPERATOR_MINUS_MINUS, // --

	AST_OPERATOR_STAR, // *
	AST_OPERATOR_STAR_STAR, // **

	AST_OPERATOR_MOD, // %

	AST_OPERATOR_SLASH, // /
	AST_OPERATOR_SLASH_INT, // //

	AST_OPERATOR_SHIFT_LEFT, // >>
	AST_OPERATOR_SHIFT_RIGHT, // <<

	AST_OPERATOR_BIT_AND, // &
	AST_OPERATOR_BIT_OR, // |
	AST_OPERATOR_BIT_XOR, // ^
	AST_OPERATOR_BIT_NOT, // ~

	AST_OPERATOR_AND, // &&
	AST_OPERATOR_OR, // ||

	AST_OPERATOR_NOT, // !
	AST_OPERATOR_NOT_EQUAL, // !=
	// AST_OPERATOR_NOT_EQUAL_EQUAL, // !==

	AST_OPERATOR_EQUAL, // =
	AST_OPERATOR_EQUAL_ASSIGN, // :=
	AST_OPERATOR_EQUAL_EQUAL, // ==
	// AST_OPERATOR_EQUAL_EQUAL, // ===

	// Relational Operators
	AST_OPERATOR_GREATER, // >
	AST_OPERATOR_GREATER_EQUAL, // >=
	AST_OPERATOR_LESS, // <
	AST_OPERATOR_LESS_EQUAL, // <=

	AST_OPERATOR_DOT, // parent.sub
	AST_OPERATOR_DOT_DOT, // [1..4]
	AST_OPERATOR_DOT_DOT_DOT, // {...objects}

	// Assignment Operators
	AST_OPERATOR_EQUAL_PLUS, // +=
	AST_OPERATOR_EQUAL_MINUS, // -=
	AST_OPERATOR_EQUAL_STAR, // *=
	AST_OPERATOR_EQUAL_STAR_STAR, // **=
	AST_OPERATOR_EQUAL_SLASH, // /=
	AST_OPERATOR_EQUAL_MOD, // %=
	AST_OPERATOR_EQUAL_BIT_AND, // &=
	AST_OPERATOR_EQUAL_BIT_OR, // |=
	AST_OPERATOR_EQUAL_BIT_NOT, // ^=
	AST_OPERATOR_EQUAL_SHIFT_LEFT, // >>=
	AST_OPERATOR_EQUAL_SHIFT_RIGHT, // <<=

} AstOperatorType;

typedef enum _ast_expr_type
{
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

typedef struct _ast_expr_declaration
{
	Location pos;
	Location pos_op;
	Location pos_left;
	Location pos_right;
	Location pos_value;

	AstExprType type;
	AstOperatorType op;

	AstExprDeclaration* left;
	AstExprDeclaration* right;

	union
	{
		char vi8;
		unsigned char vu8;

		short vi16;
		unsigned short vu16;

		int vi32;
		unsigned int vu32;

		int64_t vi64;
		uint64_t vu64;

		float vf32;
		double vf64;

		bool vbool;

		char* vstring;
		char* vchar;
	} value;
} AstExprDeclaration;

typedef struct _ast_statement_for_c
{
	// for i:=i;
	Location pos;
	Location pos_init;
	Location pos_clauses;
	Location pos_action;
	Location pos_body;

	bool has_init;
	bool has_clauses;
	bool has_action;

	AstExprDeclaration* init;
	AstExprDeclaration* clauses;
	AstExprDeclaration* action;

	AstBlockDeclaration* body;
} AstStatementForC;

typedef struct _ast_statement_for_each
{
	// names := ['Max', 'Ali', 'Javad', 'John']
	// for i, name in names {}

	// mut numbers := [0, 1, 2]
	// for mut num in numbers {
	// 	num++
	// }
	Location pos;

	// TODO
} AstStatementForEach;

typedef struct _ast_statement_for_map
{
	Location pos;

	// TODO
} AstStatementForMap;

typedef struct _ast_statement_for_loop
{
	// mut sum := 0
	// mut i := 0
	// for i <= 100 {
	// 	sum += i
	// 	i++
	// }
	Location pos;

	// TODO
} AstStatementForLoop;

typedef struct _ast_statement_match
{
	// match ... { }
	Location pos;

	// TODO
} AstStatementMatch;

typedef struct _ast_statement_ret
{
	// return <expr>
	// ^ pos
	//        ^pos_expr
	// return
	// ^ pos
	Location pos;
	Location pos_expr;

	bool has_expr;
	AstExprDeclaration* expr;
} AstStatementRet;

typedef struct _ast_statement_assign
{
	// const <name> := <value>
	Location pos;
	Location pos_name;
	Location pos_op;
	Location pos_value;

	char* name;
	AstExprDeclaration* value;
} AstStatementAssign;

typedef struct _ast_statement_assign_const
{
	// const (
	// 	  pi    = 3.14
	// 	  world = '世界'
	// )
	// const <name> = <value>
	Location pos;
	Location pos_open;
	Location pos_close;

	bool is_multi;

	AstStatementAssignConstItemArray* fields; // AstStatementAssignConstItem
	// Array name; // char*
	// Array value; // AstExprDeclaration
} AstStatementAssignConst;

typedef struct _ast_statement_const_item
{
	Location pos_name;
	Location pos_op;
	Location pos_value;

	char* name;
	AstExprDeclaration* value;
} AstStatementAssignConstItem;

typedef struct _ast_statement_variable
{
	// varName = 5
	// varName += 7
	// varStructName.fieldName = 7
	// varStructName.fieldName *= 7
	Location pos;
	Location pos_left;
	Location pos_op;
	Location pos_right;

	// Assignment Operators
	AstOperatorType op;

	AstExprDeclaration* left;
	AstExprDeclaration* right;
} AstStatementVariable;

typedef struct _ast_statement_expr
{
	// <expr>
	// ^ pos
	Location pos;

	AstExprDeclaration* expr;
} AstStatementExpr;

typedef enum _ast_statement_type
{
	AST_STATEMENT_IF,
	AST_STATEMENT_FOR,
	AST_STATEMENT_MATCH,
	AST_STATEMENT_RET,
	AST_STATEMENT_ASSIGN,
	AST_STATEMENT_ASSIGN_CONST,
	AST_STATEMENT_VARIABLE,
	AST_STATEMENT_EXPRESSION,
} AstStatementType;

typedef struct _ast_statement_if
{
	// if <expr> {} else ...
	Location pos;
	Location pos_expr;
	Location pos_body;
	Location pos_else;

	bool has_else;

	AstExprDeclaration* expr;
	AstBlockDeclaration* body;
	AstStatementIf* otherwise;
} AstStatementIf;

typedef enum _ast_statement_for_type
{
	AST_STATEMENT_FOR_C,
	AST_STATEMENT_FOR_EACH,
	AST_STATEMENT_FOR_MAP,
	AST_STATEMENT_FOR_LOOP,
} AstStatementForType;

typedef struct _ast_statement_for
{
	Location pos;
	AstStatementForType type;
	union
	{
		AstStatementForC* c;
		AstStatementForEach* each;
		AstStatementForMap* map;
		AstStatementForLoop* loop;
	} value;
} AstStatementFor;

typedef struct _ast_statement_declaration
{
	Location pos;

	AstStatementType type;

	union
	{
		AstStatementIf* clauses;
		AstStatementFor* foreach;
		AstStatementMatch* match;
		AstStatementRet* ret;
		AstStatementAssign* assign;
		AstStatementAssignConst* assign_const;
		AstStatementVariable* variable;
		AstStatementExpr* expr;
	} value;
} AstStatementDeclaration;

typedef struct _ast_block_item
{
	Location pos;

	AstBlockType type;

	union
	{
		AstFunctionDeclaration* function;
		AstStructDeclaration* structure;
		AstEnumDeclaration* enumerate;
		AstTypeDeclaration* type;
		AstStatementDeclaration* statement;
	} value;

} AstBlockItem;

typedef struct _ast_block_declaration
{
	Location pos;

	AstFunctionDeclarationArray* functions;
	AstStructDeclarationArray* structures;
	AstEnumDeclarationArray* enumerates;
	AstTypeDeclarationArray* types;
	AstStatementDeclarationArray* statements;
} AstBlockDeclaration;

typedef struct _ast_struct_field
{
	Location pos;
	Location pos_attribute;
	Location pos_type;
	Location pos_name;
	Location pos_value;

	bool is_mut;
	bool is_public;
	bool is_global;

	bool has_default;
	AstExprDeclaration* value;

	AstData* type;
	char* name;
	AstAttributeDeclarationArray* attributes; // AstAttributeDeclaration
} AstStructField;

typedef struct _ast_enum_field
{
	Location pos;
	Location pos_attribute;
	Location pos_name;
	Location pos_value;

	bool has_default;
	AstExprDeclaration* value;

	char* name;
	AstAttributeDeclarationArray* attributes; // AstAttributeDeclaration
} AstEnumField;

typedef struct _ast_type_sum_item
{
	Location pos;
	AstData* data;
} AstTypeSumItem;

// char* ast_statement_name(AstStatementType type);

// char* ast_value_name(AstValueType type);

void ast_init(const char* input_file, const char* data, Token** tokens, AstFile* ast);

void ast_trace(FILE* f, AstFile* ast);

void ast_free();

#endif // _ONE_AST_AST_H_
