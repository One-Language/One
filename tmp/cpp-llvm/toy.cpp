/*
 * Max Base
 * 2021
 * https://github.com/basemax/MyLang
 */

// Why cc and not cpp? It's shorter.

// clang++ -g -O3 my-lang.cc `llvm-config --cxxflags` -o my
// g++ my-lang.cc -o my `llvm-config --cxxflags`

// clang++ -g -O3 my-lang.cc `llvm-config --cxxflags --ldflags --system-libs --libs core` -o my
// g++ my-lang.cc -o my `llvm-config --cxxflags --ldflags --system-libs --libs core`

// Research: Static single assignment form

#include "toy.hh"

static int gettok() {
	static int LastChar = ' ';

	// Skip whitespaces
	while(isspace(LastChar)) {
		LastChar = getchar();
	}

	// Get identifier
	if(isalpha(LastChar) || LastChar == '_') {
		IdentifierStr = LastChar;
		while(isalnum((LastChar = getchar())) || LastChar == '_') {
			IdentifierStr += LastChar;
		}

		if(IdentifierStr == "def") {
			return tok_def;
		}
		else if(IdentifierStr == "extern") {
			return tok_extern;
		}
		return tok_identifier;
	}

	// Get number
	if(isdigit(LastChar) || LastChar == '.') {
		std::string NumStr;
		do {
			NumStr += LastChar;
			LastChar = getchar();
		} while(isdigit(LastChar) || LastChar == '.');
		NumVal = strtod(NumStr.c_str(), 0);
		return tok_number;
	}

	// Get string
	if(LastChar == '\"') {
		do {
			StrVal += LastChar;
			LastChar = getchar();
		} while(LastChar != '\"');
		LastChar = getchar(); // eat '"'
		return tok_string;
	}

	// Skip single-line comments
	if(LastChar == '#') {
		do {
			LastChar = getchar();
		} while(LastChar != EOF && LastChar != '\n' && LastChar == '\r');

		if(LastChar != EOF) {
			return gettok();
		}
	}

	if(LastChar == EOF) {
		return tok_eof;
	}

	int ThisChar = LastChar;
	LastChar = getchar();
	return ThisChar;
}

static int getNextToken() {
	return CurTok = gettok();
}

std::unique_ptr<ExprAST> LogError(const char *Str) {
	fprintf(stderr, "LogError: %s\n", Str);
	return nullptr;
}

// std::unique_ptr<PrototypeAST> LogErrorp(const char *Str) {
// 	LogError(Str);
// 	return nullptr;
// }

static std::unique_ptr<ExprAST> ParseNumberExpr() {
	auto Result = std::make_unique<NumberExprAST>(NumVal);
	getNextToken();

	return std::move(Result);
}

static std::unique_ptr<ExprAST> ParseStringExpr() {
	auto Result = std::make_unique<StringExprAST>(StrVal);
	getNextToken();

	return std::move(Result);
}

static std::unique_ptr<ExprAST> ParsePrimary() {
	switch(CurTok) {
		case tok_identifier:
			return ParseIdentifierOrCallExpr();
		case tok_number:
			return ParseNumberExpr();
		case tok_string:
			return ParseStringExpr();
		case '(':
			return ParseParenExpr();
		default:
			return LogError("unknown token when expecting an expression");
	}
}

static std::unique_ptr<ExprAST> ParseExpression() {
	auto LHS = ParsePrimary();

	if(LHS) {
		return ParseBinOpRHS(0, std::move(LHS));
	}

	return nullptr;
}

static std::unique_ptr<ExprAST> ParseIdentifierOrCallExpr() {
	std::string IdName = IdentifierStr;
	getNextToken();

	if(CurTok == '(') {
		getNextToken(); // eat '('
		std::vector< std::unique_ptr<ExprAST> > Args;
		while(true) {
			auto Arg = ParseExpression();
			if(Arg) {
				Args.push_back(std::move(Arg));
			} else {
				return nullptr;
			}

			if(CurTok == ')') {
				getNextToken(); // eat ')'
				break;
			}
			else if(CurTok == ',') {
				getNextToken(); // eat ','
			}
			else {
				LogError("Expected ')' or ',' in argument list");
				return nullptr;
			}
		}

		return std::make_unique<CallExprAST>(IdName, std::move(Args));
	}
	else {
		return std::make_unique<VariableExprAst>(IdName);
	}
}

static std::unique_ptr<ExprAST> ParseParenExpr() {
	getNextToken(); // eat '('

	auto V = ParseExpression();
	if(!V) {
		return nullptr;
	}

	if(CurTok == ')') {
		getNextToken(); // eat ')'
		return V;
	} else {
		LogError("expected ')'");
		return nullptr;
	}
}

/// identifierexpr
///   ::= identifier
///   ::= identifier '(' expression* ')'
static std::unique_ptr<ExprAST> ParseIdentifierExpr() {
	std::string IdName = IdentifierStr;
	getNextToken(); // eat identifier.

	if (CurTok == '(') {
		// Call.
		getNextToken(); // eat '('
		std::vector<std::unique_ptr<ExprAST>> Args;

		if(CurTok != ')') {

			while (true) {
				if(auto Arg = ParseExpression()) {
					Args.push_back(std::move(Arg));

					if(CurTok == ')') {
						break;
					}

					if (CurTok != ',') {
						LogError("Expected ')' or ',' in argument list");
						return nullptr;
					}
					getNextToken();
				}
				else {
					return nullptr;
				}
			}
		}

		// Eat the ')'.
		getNextToken();

		return std::make_unique<CallExprAST>(IdName, std::move(Args));

	}
	else {
		// Simple variable ref.
		return std::make_unique<VariableExprAst>(IdName);
	}
}

static int GetTokPrecedence() {
	// if(!isasci(CurTok)) {
	// 	return -1;
	// }

	switch(CurTok) {
		case '<':
		case '>':
			return 10;

		case '+':
		case '-':
			return 20;

		case '*':
		case '/':
			return 20;

		default:
			return -1;
	}
}

static std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec,
	std::unique_ptr<ExprAST> LHS ) {
	while(true) {
		int TokPrec = GetTokPrecedence();

		if(TokPrec < ExprPrec) {
			return LHS;
		}
		else {
			int BinOp = CurTok;
			getNextToken(); // eat binOp

			auto RHS = ParsePrimary();
			if(RHS) {
				int NextPrec = GetTokPrecedence();
				if(TokPrec < NextPrec) {
					RHS = ParseBinOpRHS(TokPrec+1, std::move(RHS));
					if(!RHS) {
						return nullptr;
					}

					LHS = std::make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
				}
			}
			else {
				return nullptr;
			}
		}

	}
}

static std::unique_ptr<PrototypeAST> ParsePrototype() {
	if(CurTok == tok_identifier) {
		std::string FnName = IdentifierStr;
		getNextToken(); // eat identifier

		if (CurTok == '(') {
			std::vector<std::string> ArgNames;

			while (getNextToken() == tok_identifier) {
				ArgNames.push_back(IdentifierStr);
			}
			if (CurTok == ')') {
				getNextToken(); // eat ')'.
				return std::make_unique<PrototypeAST>(FnName, std::move(ArgNames));
			}
			else {
				LogError("Expected ')' in prototype");
				return nullptr;
			}
		}
		else {
			LogError("Expected '(' in prototype");
			return nullptr;
		}

	}
	else {
		LogError("Expected function name in prototype");
		return nullptr;
	}
}

static std::unique_ptr<FunctionAST> ParseDefinition() {
	getNextToken(); //eat def.

	auto Proto = ParsePrototype();
	if(!Proto) {
		return nullptr;
	}

	auto E = ParseExpression();
	if(E) {
		return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
	}
	// else {
	// 	return nullptr;
	// }

	return nullptr;
}

static std::unique_ptr<PrototypeAST> ParseExtern() {
	getNextToken(); // eat extern.
	return ParsePrototype();
}

static std::unique_ptr<FunctionAST> ParseTopLevelExpr() {
	auto E = ParseExpression();

	if(E) {
		auto Proto = std::make_unique<PrototypeAST>("__anon_expr", std::vector< std::string>());
		return std::make_unique<FunctionAST>(std::move(Proto), std::move(E));
	}
	// else {
	// 	return nullptr;
	// }

	return nullptr;
}

static void InitializeModule() {
	// Open a new context and module.
	TheContext = std::make_unique<LLVMContext>();
	TheModule = std::make_unique<Module>("my cool jit", *TheContext);

	// Create a new builder for the module.
	Builder = std::make_unique<IRBuilder<>>(*TheContext);
}

static void HandleDefinition() {
	if(auto FnAST = ParseDefinition()) {
		if(auto *FnIR = FnAST->codegen()) {
			// fprintf(stderr, "Parsed a function definition.\n");
			fprintf(stderr, "Read a function definition.\n");
			FnIR->print(errs());
			fprintf(stderr, "\n");
		}
		// else {}
	}
	else {
		// Skip token for error recovery.
		getNextToken();
	}
}

static void HandleExtern() {
	if(auto ProtoAST = ParseExtern()) {
		if(auto *FnIR = ProtoAST->codegen()) {
			// fprintf(stderr, "Parsed an extern\n");
			fprintf(stderr, "Read an extern\n");
			FnIR->print(errs());
			fprintf(stderr, "\n");
		}
		// else {}
	}
	else {
		// SKip token for error recovery.
		getNextToken();
	}
}

static void HandleTopLevelExpression() {
	// Evaloate a top-level expression into a anonymous function.
	if(auto FnAST = ParseTopLevelExpr()) {
		if(auto *FnIR = FnAST->codegen()) {
			// fprintf(stderr, "Parsed a top-level expr\n");
			fprintf(stderr, "Read a top-level expression\n");
			FnIR->print(errs());
			fprintf(stderr, "\n");
		}
		// else {}			
	}
	else {
		// SKip token for error recovery.
		getNextToken();
	}
}

static void MiainLoop() {
	while(true) {
		fprintf(stderr, "Ready> ");
		switch(CurTok) {
			case tok_eof:
				return;
			case ';':

				getNextToken();
				break;

			case tok_def:
				HandleDefinition();
				break;

			case tok_extern:
				HandleExtern();
				break;

			default:
				HandleTopLevelExpression();
				break;
		}

	}
}

// code generators
Value *NumberExprAST::codegen() {
	return ConstantFP::get(*TheContext, APFloat(Val));
}

Value *StringExprAST::codegen() {
	// Uhh...a global constant array
	return ConstantFP::get(*TheContext, APFloat(0.0)); // TODO: Strings are gonna be a bit more special. You can either keep them as alloca nodes filled with the data, or as global fixed arrays initialised at init 
}

Value *VariableExprAst::codegen() {
	Value *V = NamedValues[Name];

	if(!V) {
		LogError("Unknown variable name");
		// return nullptr;
	}
	return V;
}

Value *BinaryExprAST::codegen() {
	Value *L = LHS->codegen();
	Value *R = RHS->codegen();

	if(!L || !R) {
		return nullptr;
	}

	switch(Op) {
		case '+':
			return Builder->CreateFAdd(L, R, "addtmp");

		case '-':
			return Builder->CreateFAdd(L, R, "subtmp");

		case '*':
			return Builder->CreateFAdd(L, R, "multmp");

		case '/':
			return Builder->CreateFAdd(L, R, "addtmp");

		case '<':
			L = Builder->CreateFCmpULT(L, R, "cmptmp");
			return Builder->CreateUIToFP(L, Type::getDoubleTy(*TheContext), "booltmp");

		default:
			LogError("invalid binary operator");
			return nullptr;
	}
}

Value *CallExprAST::codegen() {
	Function *CalleeF = TheModule->getFunction(Callee);

	if(!CalleeF) {
		LogError("Unknown function referenced");
		return nullptr;
	}

	if(CalleeF->arg_size() != Args.size()) {
		LogError("incorrect # arguments passed");
		return nullptr;
	}

	std::vector<Value *> ArgsV;
	for(unsigned i = 0, e = Args.size(); i != e; ++i) {
		ArgsV.push_back(Args[i]->codegen());
		if(!ArgsV.back()) {
			return nullptr;
		}
	}

	return Builder->CreateCall(CalleeF, ArgsV, "calltmp");
}

Function *PrototypeAST::codegen() {
	std::vector<Type *> Doubles(Args.size(), Type::getDoubleTy(*TheContext));

	FunctionType *FT = FunctionType::get(Type::getDoubleTy(*TheContext), Doubles, false);

	Function *F = Function::Create(FT, Function::ExternalLinkage, Name, TheModule.get());

	// Set names for all arguments.
	unsigned Idx = 0;
	for(auto &Arg : F->args()) {
		Arg.setName(Args[Idx++]);
	}

	return F;
}

Function *FunctionAST::codegen() {
	Function *TheFunction = TheModule->getFunction(Proto->getName());

	if(!TheFunction) {
		TheFunction = Proto->codegen();
	}

	if(!TheFunction) {
		return nullptr;
	}

	if(!TheFunction->empty()) {
		LogError("Function cannot be redefined.");
		return nullptr;
	}

	BasicBlock *BB = BasicBlock::Create(*TheContext, "entry", TheFunction);
	Builder->SetInsertPoint(BB);

	NamedValues.clear();
	for(auto &Arg : TheFunction->args()) {
		NamedValues[std::string(Arg.getName())] = &Arg;
	}

	if (Value *RetVal = Body->codegen()) {
		Builder->CreateRet(RetVal);
		verifyFunction(*TheFunction);

		return TheFunction;
	}
	// else {
	// 	TheFunction->eraseFromParent();
	// 	return nullptr;
	// }

	TheFunction->eraseFromParent();
	return nullptr;
}

int main() {
	// while(true) {
	// 	int tok = gettok();
	// 	std::cout << "\tToken:" << tok << std::endl;
	// }

	fprintf(stderr, "Ready> ");
	getNextToken();

	// Make the module, which holds all the code.
	InitializeModule();

	// Run the main "interpreter loop" now.
	MiainLoop();

	// Print out all of the generated code.
	TheModule->print(errs(), nullptr);
}
