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

//// File:
//// 	char* package
//// 	Array<Import> imports
//// 	Array<Block> blocks
typedef struct {
	char* package;
	Array imports;
	Array blocks;
} AstFile;
// typedef Array ArrayImport;
// typedef Array ArrayBlock;

//// Import:
//// 	Array names = [math], [parentLib, childLib], [file]
//// 	Array as = [pc, cr]
//// 	Array symbols = [sin], [sin, cos], [create]
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
	Array names;
	Array as;
	Array symbols;
} AstImport;

Block:
	BlockType type
	Function function
	DefineStruct define_struct
	DefineType define_type
	Statement statement

BlockType:
	BLOCK_FUNCTION
	BLOCK_STRUCT
	BLOCK_TYPE
	BLOCK_STATEMENT


// char* ast_statement_name(AstStatementType type);

// char* ast_value_name(AstValueType type);

#endif // _ONE_AST_AST_H_
