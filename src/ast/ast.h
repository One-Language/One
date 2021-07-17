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
	Location pos; // aka pos_names
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

typedef enum {
	
} AstFunction;

typedef enum {

} AstStruct;

typedef enum {

} AstType;

typedef enum {

} AstStatement;


// char* ast_statement_name(AstStatementType type);

// char* ast_value_name(AstValueType type);

#endif // _ONE_AST_AST_H_
