/**
 The One Programming Language

 File: generator.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef ONE_GENERATOR_H
#define ONE_GENERATOR_H

#include <llvm-c/Core.h>
#include <llvm-c/DebugInfo.h>

#include <llvm-c/Linker.h>
#include <llvm-c/Transforms/PassManagerBuilder.h>
#include <llvm-c/Transforms/Scalar.h>
#include <llvm-c/Target.h>
#include <llvm-c/TargetMachine.h>
#include <llvm-c/BitWriter.h>
#include <llvm-c/BitReader.h>
#include <llvm-c/IRReader.h>

LLVMModuleRef generator_init(AstRoot* root);

bool generator_root(AstRoot* ast, char* file, LLVMMetadataRef file_meta, LLVMModuleRef module, LLVMDIBuilderRef dibuilder, LLVMBuilderRef builder);

void generator_free();

LLVMMetadataRef generateTypeMeta(LLVMDIBuilderRef dibuilder, LLVMTypeRef type, LLVMMetadataRef file);

bool generateFunctionBody(AstFunction* ast, LLVMModuleRef module, LLVMDIBuilderRef dibuilder, LLVMBuilderRef builder);

bool generateFunctionShell(AstFunction* ast, char* file, LLVMModuleRef module, LLVMDIBuilderRef dibuilder, LLVMBuilderRef builder);

LLVMValueRef generateValueInFunction(AstStatement* ast, LLVMDIBuilderRef dibuilder, LLVMBuilderRef builder);

#endif //ONE_GENERATOR_H
