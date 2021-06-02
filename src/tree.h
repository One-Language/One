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

void treeInit();

void treeLog(AstRoot*);

void treeFree();

#endif //_TREE_H_
