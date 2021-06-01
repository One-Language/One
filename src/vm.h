/**
 The One Programming Language

 File: vm.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _VM_H_
#define _VM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ast.h"

void vmInit(AstRoot*);
void vmLog(AstRoot* );
void vmFree(AstRoot* );

#endif //_VM_H_
