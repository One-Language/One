//
// Created by max on 6/13/21.
//

#include <string.h>

#include <llvm-c/Core.h>
#include <llvm-c/DebugInfo.h>

#include "array.h"
#include "lexer.h"
#include "token.h"
#include "ast.h"
#include "parser.h"

#include "generator.h"

LLVMValueRef func_main;
LLVMModuleRef generator_init(AstRoot* root)
{
	char* filename = "input.one";
	LLVMModuleRef module = LLVMModuleCreateWithName(filename);
	LLVMSetSourceFileName(module, filename, strlen(filename));
	LLVMBuilderRef builder = LLVMCreateBuilder();
	LLVMDIBuilderRef dibuilder = NULL;
	LLVMMetadataRef file_meta = NULL;

	if (!generateRoot(root, filename, file_meta, module, dibuilder, builder))
	{
		LLVMDisposeModule(module);
		LLVMDisposeBuilder(builder);
		return NULL;
	}
	else
	{
		LLVMDisposeBuilder(builder);
		return module;
	}
}

bool generateRoot(AstRoot* ast, char* file, LLVMMetadataRef file_meta, LLVMModuleRef module, LLVMDIBuilderRef dibuilder, LLVMBuilderRef builder)
{
	bool error = false;
	for (int i = 0; i < ast->functions.count; i++)
	{
		AstFunction* fn = ast->functions.data[i];
		if (!generateFunctionShell(fn, "input.one", module, dibuilder, builder))
		{
			error = true;
		}
	}

	for (int i = 0; i < ast->functions.count; i++)
	{
		AstFunction* fn = ast->functions.data[i];
		if (!generateFunctionBody(fn, module, dibuilder, builder))
		{
			error = true;
		}
	}

	return !error;
}

LLVMMetadataRef generateTypeMeta(LLVMDIBuilderRef dibuilder, LLVMTypeRef type, LLVMMetadataRef file)
{
	if (type == NULL)
	{
		return NULL;
	}
	switch (LLVMGetTypeKind(type))
	{
		case LLVMPointerTypeKind:
		{
			LLVMMetadataRef base = generateTypeMeta(dibuilder, LLVMGetElementType(type), file);
			return LLVMDIBuilderCreatePointerType(dibuilder, base, 64, 0, 0, NULL, 0);
		}
		case LLVMArrayTypeKind:
		{
			LLVMMetadataRef base = generateTypeMeta(dibuilder, LLVMGetElementType(type), file);
			LLVMMetadataRef size = LLVMDIBuilderGetOrCreateSubrange(dibuilder, 0, LLVMGetArrayLength(type));
			return LLVMDIBuilderCreateArrayType(dibuilder, LLVMGetArrayLength(type) * LLVMDITypeGetSizeInBits(base), 0, base, &size, 1);
		}
		case LLVMIntegerTypeKind:
		{
			int len = LLVMGetIntTypeWidth(type);
			char name[12];
			int size = sprintf(name, "i%i", len);
			return LLVMDIBuilderCreateBasicType(dibuilder, name, size, len, 5, 0);
		}
		case LLVMHalfTypeKind:
		{
			return LLVMDIBuilderCreateBasicType(dibuilder, "f16", 4, 16, 4, 0);
		}
		case LLVMFloatTypeKind:
		{
			return LLVMDIBuilderCreateBasicType(dibuilder, "f32", 4, 32, 4, 0);
		}
		case LLVMDoubleTypeKind:
		{
			return LLVMDIBuilderCreateBasicType(dibuilder, "f64", 4, 64, 4, 0);
		}
		case LLVMX86_FP80TypeKind:
		{
			return LLVMDIBuilderCreateBasicType(dibuilder, "f80", 4, 80, 4, 0);
		}
		case LLVMFP128TypeKind:
		{
			return LLVMDIBuilderCreateBasicType(dibuilder, "f128", 4, 128, 4, 0);
		}
		case LLVMFunctionTypeKind:
		{
			int paramc = 1 + LLVMCountParamTypes(type);
			LLVMMetadataRef paramts[paramc];
			LLVMTypeRef params[paramc];
			LLVMGetParamTypes(type, params);
			paramts[0] = generateTypeMeta(dibuilder, LLVMGetReturnType(type), file);
			for (int i = 0; i < paramc - 1; i++)
			{
				paramts[1 + i] = generateTypeMeta(dibuilder, params[i], file);
			}
			return LLVMDIBuilderCreateSubroutineType(dibuilder, file, paramts, paramc, 0);
		}
		default:
			return NULL;
	}
}

bool generateFunctionShell(AstFunction* ast, char* file, LLVMModuleRef module, LLVMDIBuilderRef dibuilder, LLVMBuilderRef builder)
{
	bool error = false;
	LLVMTypeRef return_type;

	return_type = LLVMVoidType();

	LLVMTypeRef* parameter_types = (LLVMTypeRef*)malloc(sizeof(LLVMTypeRef) * 1);

	LLVMTypeRef function_type = LLVMFunctionType(return_type, parameter_types, 0, false);
	LLVMValueRef function = LLVMAddFunction(module, ast->name, function_type);

	func_main = function;

	free(parameter_types);
	return !error;
}

LLVMValueRef generateValueInFunction(AstStatement * ast, LLVMDIBuilderRef dibuilder, LLVMBuilderRef builder) {
	if(ast == NULL) {
		return NULL;
	}


}

LLVMValueRef generateValueCodeBlock(AstBlock * ast, LLVMDIBuilderRef dibuilder, LLVMBuilderRef builder) {
	bool error = false;

	for(int i = 0; i < ast->statements.count; i++) {
		LLVMValueRef value = NULL;
		if(value == NULL) {
			error = true;
		}
	}

	if(error) {
		return NULL;
	} else {
		return (LLVMValueRef)1;
	}
}

bool generateFunctionBody(AstFunction* ast, LLVMModuleRef module, LLVMDIBuilderRef dibuilder, LLVMBuilderRef builder)
{
	LLVMBasicBlockRef entry = LLVMAppendBasicBlock(func_main, "");
	LLVMBasicBlockRef block = LLVMAppendBasicBlock(func_main, "");
	LLVMBasicBlockRef exit = LLVMAppendBasicBlock(func_main, "");
	LLVMPositionBuilderAtEnd(builder, entry);

	LLVMPositionBuilderAtEnd(builder, block);
	bool error = false;

	bool ret = generateValueCodeBlock(ast->block, dibuilder, builder) != NULL;
	LLVMValueRef last_instr = LLVMGetLastInstruction(LLVMGetInsertBlock(builder));
	if (last_instr == NULL || LLVMGetInstructionOpcode(last_instr) != LLVMBr)
	{
		LLVMBuildBr(builder, exit);
	}
	LLVMPositionBuilderAtEnd(builder, entry);
	LLVMBuildBr(builder, block);
	LLVMPositionBuilderAtEnd(builder, exit);

	LLVMBuildRetVoid(builder);

	return ret && !error;
}

void generator_free()
{
}
