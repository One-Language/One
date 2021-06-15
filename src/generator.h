//
// Created by max on 6/13/21.
//

#ifndef ONE_GENERATOR_H
#define ONE_GENERATOR_H

#include <llvm-c/Core.h>
#include <llvm-c/DebugInfo.h>

LLVMModuleRef generator_init(AstRoot* root);

bool generator_root(AstRoot* ast, char* file, LLVMMetadataRef file_meta, LLVMModuleRef module, LLVMDIBuilderRef dibuilder, LLVMBuilderRef builder);

void generator_free();

LLVMMetadataRef generateTypeMeta(LLVMDIBuilderRef dibuilder, LLVMTypeRef type, LLVMMetadataRef file);

bool generateFunctionBody(AstFunction* ast, LLVMModuleRef module, LLVMDIBuilderRef dibuilder, LLVMBuilderRef builder);

bool generateFunctionShell(AstFunction* ast, char* file, LLVMModuleRef module, LLVMDIBuilderRef dibuilder, LLVMBuilderRef builder);

LLVMValueRef generateValueInFunction(AstStatement* ast, LLVMDIBuilderRef dibuilder, LLVMBuilderRef builder);

#endif //ONE_GENERATOR_H
