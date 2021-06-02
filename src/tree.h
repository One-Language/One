/**
 The One Programming Language

 File: tree.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _TREE_H_
#define _TREE_H_

#include "ast.h"

void print_tabs(size_t);

void treeLog(AstRoot*);

void treeStatement(AstStatement*);

void treeStatements(AstStatements*);

void treeBlock(AstBlock*);

void treeFunction(AstFunction*);

void treeLog(AstRoot*);

void treeExpression(AstExpression*);

void treeExpressions(AstExpressions*);

#endif //_TREE_H_
