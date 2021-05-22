/*
 * Max Base
 * 2021
 * https://github.com/basemax/MyLang
 */

// Why hh and not h? It's cpp and c.

// llvm libs
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/ExecutionEngine/Orc/ThreadSafeModule.h"

using namespace llvm;
using namespace llvm::orc;

// c libs
#include <cctype>
#include <cstdio>
#include <cstdlib>

// cpp libs
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <algorithm>

// "unknown tokens" are represented by their ASCII code.
enum Token {
	tok_eof = -1,
	tok_def = -2,
	tok_extern = -3,
	tok_identifier = -4,
	tok_number = -5,
	tok_string = -6
};

// lexer variables
static double NumVal;
static std::string StrVal;
static int CurTok; // current token

// parser variables
static std::map<char, int> BinopPrecedence;
static std::string IdentifierStr;

// codegenerator variables
// llvm variables
static std::unique_ptr<LLVMContext> TheContext;
static std::unique_ptr<Module> TheModule;
static std::unique_ptr<IRBuilder<>> Builder;
static std::map<std::string, Value *> NamedValues;
static std::unique_ptr<legacy::FunctionPassManager> TheFPM;

// classes
class ExprAST {
public:
	virtual ~ExprAST() {}

	virtual Value *codegen() = 0;
};

class StringExprAST : public ExprAST {
	std::string Val;
public:
	StringExprAST(std::string v) : Val(v) {}

	Value *codegen() override;
};

class NumberExprAST : public ExprAST {
	double Val;
public:
	NumberExprAST(double v) : Val(v) {}

	virtual Value *codegen() override;
};

class VariableExprAst : public ExprAST {
	std::string Name;
public:
	VariableExprAst(const std::string &Name): Name(Name) {}

	Value *codegen() override;
};

class BinaryExprAST : public ExprAST {
	char Op; // + - * / > < >= <=
	std::unique_ptr<ExprAST> LHS, RHS;

public:
	BinaryExprAST(
		char op,
		std::unique_ptr<ExprAST> LHS,
		std::unique_ptr<ExprAST> RHS
	// ) : Op(op), LHS(LHS), RHS(RHS) {}
	) : Op(op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}

	Value *codegen() override;
};

class CallExprAST : public ExprAST {
	std::string Callee;
	std::vector< std::unique_ptr< ExprAST > > Args;

public:
	CallExprAST(
		const std::string &Callee,
		std::vector< std::unique_ptr<ExprAST> > Args
	) : Callee(Callee), Args(std::move(Args)) {}

	Value *codegen() override;
};

class PrototypeAST {
  std::string Name;
  std::vector<std::string> Args;

public:
  PrototypeAST(const std::string &Name, std::vector<std::string> Args)
      : Name(Name), Args(std::move(Args)) {}

	Function *codegen();

	const std::string &getName() const {
		return Name;
	}
};

class FunctionAST {
	std::unique_ptr< PrototypeAST > Proto;
	std::unique_ptr< ExprAST > Body;

public:
	FunctionAST(
		std::unique_ptr< PrototypeAST > Proto,
		std::unique_ptr< ExprAST > Body
		) : Proto(std::move(Proto)), Body(std::move(Body)) {}

	Function *codegen();
};

// lexer
static int gettok();
static int getNextToken();
// BinopPrecedence - This holds the precedence for each binary operator that is defined.
// static std::map<char, int> BinopPrecedence;

std::unique_ptr<ExprAST> LogError(const char *);

// parser
static std::unique_ptr<ExprAST> ParseNumberExpr();
static std::unique_ptr<ExprAST> ParseStringExpr();
static std::unique_ptr<ExprAST> ParsePrimary();
static std::unique_ptr<ExprAST> ParseExpression();
static std::unique_ptr<ExprAST> ParseIdentifierOrCallExpr();
static std::unique_ptr<ExprAST> ParseParenExpr();
static std::unique_ptr<ExprAST> ParseIdentifierExpr();
static int GetTokPrecedence();
static std::unique_ptr<ExprAST> ParseBinOpRHS(int, std::unique_ptr<ExprAST>);
static std::unique_ptr<PrototypeAST> ParsePrototype();
static std::unique_ptr<PrototypeAST> ParsePrototype();
static std::unique_ptr<FunctionAST> ParseDefinition();
static std::unique_ptr<PrototypeAST> ParseExtern();
static std::unique_ptr<FunctionAST> ParseTopLevelExpr();

// handle
static void HandleDefinition();
static void HandleExtern();
static void HandleTopLevelExpression();
static void MiainLoop();

// next llvm global variables
static std::map<std::string, std::unique_ptr<PrototypeAST>> FunctionProtos;
// static ExitOnError ExitOnErr;

