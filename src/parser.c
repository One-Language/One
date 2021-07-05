/**
 The One Programming Language

 File: parser.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "lexer.h"
#include "token.h"
#include "array.h"
#include "one.h"
#include "ast.h"
#include "tree.h"
#include "generator.h"

#include "parser.h"

// Global variable(s)
Parser parser;
Array tokens;

// macro
#define PARSER_HAS(want_type) ((*parser.tokens)->type == want_type)

#define PARSER_CURRENT \
	(*parser.tokens)

#define PARSER_CURRENT_LOG                              \
	debug_parser(                                       \
		 "Current Token is %s (%d)%s%s",                \
		 token_name((*parser.tokens)->type),            \
		 (*parser.tokens)->type,                        \
		 ((*parser.tokens)->value != NULL) ? ": " : "", \
		 ((*parser.tokens)->value != NULL) ? (*parser.tokens)->value : "");

void parser_init()
{
	debug_parser("parser_init");

	parser.package = NULL;
	parser.tokens = NULL;
	parser.tokens_count = 0;
	array_init(&tokens);
	// array_init((Array*) parser.tokens);
}

void parser_push(Token *t)
{
	array_push(&tokens, t);
	// array_push((Array*) parser.tokens, t);
}

Precedence precedence_get(TokenType type)
{
	// cpp: 1
	// cpp: 2, a++   a--
	if (type == TOKEN_OPERATOR_PLUSPLUS || type == TOKEN_OPERATOR_MINUSMINUS || type == TOKEN_OPERATOR_DOT)
		return 160;

	// cpp: 3, ++a  --a  +a  -a  !a   ~a   *a   &a
	//	if (type == TOKEN_OPERATOR_AND || type == TOKEN_OPERATOR_STAR) // TODO:
	//		return 150;

	// cpp: 4
	// cpp: 5, a*b   a/b   a%b
	if (type == TOKEN_OPERATOR_STAR || type == TOKEN_OPERATOR_SLASH || type == TOKEN_OPERATOR_SLASH_INT || type == TOKEN_OPERATOR_REMAINDER)
		return 140;

	// cpp: 6
	if (type == TOKEN_OPERATOR_PLUS || type == TOKEN_OPERATOR_MINUS)
		return 130;

	// cpp: 7
	if (type == TOKEN_OPERATOR_SHIFT_LEFT || type == TOKEN_OPERATOR_SHIFT_RIGHT)
		return 120;

	// cpp: 8
	if (type == TOKEN_OPERATOR_EQUAL_THREE)
		return 110;

	// cpp: 9
	if (type == TOKEN_OPERATOR_GREATER || type == TOKEN_OPERATOR_GREATER || type == TOKEN_OPERATOR_LESS || type == TOKEN_OPERATOR_LESS_EQUAL)
		return 100;

	// cpp: 10
	if (type == TOKEN_OPERATOR_EQUAL_EQUAL || type == TOKEN_OPERATOR_EQUAL_BANG)
		return 90;
	// cpp: 11
	if (type == TOKEN_OPERATOR_BITWISE_AND)
		return 80;
	// cpp: 12
	if (type == TOKEN_OPERATOR_BITWISE_XOR)
		return 70;
	// cpp: 13
	if (type == TOKEN_OPERATOR_BITWISE_OR)
		return 60;
	// cpp: 14
	if (type == TOKEN_OPERATOR_AND)
		return 50;
	// cpp: 15
	if (type == TOKEN_OPERATOR_OR)
		return 40;
	// cpp: 16
	if (type == TOKEN_OPERATOR_QUESTION || type == TOKEN_OPERATOR_EQUAL || type == TOKEN_OPERATOR_EQUAL_MINUS ||
		 type == TOKEN_OPERATOR_EQUAL_PLUS || type == TOKEN_OPERATOR_EQUAL_STAR || type == TOKEN_OPERATOR_EQUAL_SLASH ||
		 type == TOKEN_OPERATOR_EQUAL_SLASH_INT || type == TOKEN_OPERATOR_EQUAL_SHIFT_RIGHT || type == TOKEN_OPERATOR_EQUAL_SHIFT_LEFT ||
		 type == TOKEN_OPERATOR_EQUAL_OR || type == TOKEN_OPERATOR_EQUAL_BITWISE_OR || type == TOKEN_OPERATOR_EQUAL_AND ||
		 type == TOKEN_OPERATOR_EQUAL_BITWISE_AND || type == TOKEN_OPERATOR_EQUAL_REMAINDER)
		return 30;
	// cpp: 170
	return -1;
}

/*
char *precedence_name(Precedence type)
{
	switch (type)
	{
		case PREC_ASSIGNMENT: // =
			return "PREC_ASSIGNMETN";
			break;
		case PREC_OR: // or
			return "PREC_OR";
			break;
		case PREC_AND: // and
			return "PREC_AND";
			break;
		case PREC_EQUALITY: // == !=
			return "PREC_EQUALITY";
			break;
		case PREC_COMPARISON: // < > <= >=
			return "PREC_COMPARISON";
			break;
		case PREC_TERM: // + -
			return "PREC_TERM";
			break;
		case PREC_FACTOR: // * /
			return "PREC_FACTOR";
			break;
		case PREC_UNARY: // ! -
			return "PREC_UNARY";
			break;
		case PREC_CALL: // . ()
			return "PREC_CALL";
			break;
		case PREC_PRIMARY:
			return "PREC_PRIMARY";
			break;
		case PREC_NONE: // non operators!
			return "PREC_NONE";
			break;
		default:
			return "PREC_NONE";
			break;
	}
}
*/

void parser_scan()
{
	debug_parser("parser_scan");

	Token *t;
	for (;;)
	{
		t = lexer_scan();
		parser_push(t);
		debug_parser("parser_scan: print_token %s", token_name(t->type));
		if (t->type == TOKEN_ERROR)
		{
			printf("Error: %s\n", t->value);
			break;
		}
		else if (t->type == TOKEN_EOF)
			break;
	}
}

void parser_preapre()
{
	parser.tokens = (Token **)tokens.data;
	parser.tokens_count = tokens.count;
}
void parser_start()
{
	debug_parser("parser_start");

	parser_preapre();

	parser_tokens_log();

	AstRoot *root = parser_check();

	tree_show(stdout, root);

	generator_init(root);
	generator_free();

	ast_free(&root);
}

void parser_tokens_log()
{
	debug_parser("parser_tokens_log");

	for (size_t i = 0; i < parser.tokens_count; i++)
	{
		info_parser("Token[%zu] is %s (%s)", i, token_name(parser.tokens[i]->type), parser.tokens[i]->value == NULL ? "Null" : parser.tokens[i]->value);
	}
}

AstRoot *parser_check()
{
	debug_parser("parser_check");

	Token *t;
	AstRoot *root = (AstRoot *)malloc(sizeof(AstRoot));
	AstGlobalStatenent *stmt;
	AstFunctions fns;

	//	Array vars;
	//	Array structs;
	//	Array enums;
	//	Array types;

	array_init(&fns);
	//	array_init(&vars);
	//	array_init(&structs);
	//	array_init(&enums);
	//	array_init(&types);

	while ((*parser.tokens)->type != TOKEN_EOF)
	{
		t = *parser.tokens;
		debug_parser("parser_check: print_token %d <-> %s", t->type, token_name(t->type));
		if (t->type == TOKEN_ERROR)
		{
			debug_parser("parser_check: print_token_error %s", t->value);
			error_token(t->value);
			break;
		}

		stmt = parser_parse();
		if (stmt != NULL)
		{
			if (stmt->type == AST_GLOBAL_STATEMENT_FN)
			{
				array_push(&fns, (void *)stmt->fn);
			}
			//			else if (stmt->type == AST_GLOBAL_STATEMENT_VAR)
			//			{
			//				array_push(&vars, stmt->var);
			//			}
			//			else if (stmt->type == AST_GLOBAL_STATEMENT_TYPE)
			//			{
			//				array_push(&vars, stmt->type);
			//			}
			//			else if (stmt->type == AST_GLOBAL_STATEMENT_STRUCT)
			//			{
			//				array_push(&structs, stmt->struct);
			//			}
			//			else if (stmt->type == AST_GLOBAL_STATEMENT_ENUM)
			//			{
			//				array_push(&enums, stmt->enum);
			//			}
		}

		// parser_next();
		// parser.tokens++;
	}

	root->package = (char *)parser.package;
	root->functions = fns;

	//	printf("==>%d\n", fns.count);
	//	printf("==>%d\n", root->functions.count);

	//	root->vars = &vars;
	//	root->types = &types;
	//	root->strucs = &structs;
	//	root->enums = &enums;

	//	array_free(&fns);
	//	array_free(&vars);
	//	array_free(&types);
	//	array_free(&structs);
	//	array_free(&enums);

	return root;
}

void parser_next()
{
	debug_parser("parser_next");

	parser.tokens_index++;
	parser.tokens++;
}

void parser_prev()
{
	debug_parser("parser_prev");

	parser.tokens_index--;
	parser.tokens--;
}

AstGlobalStatenent *parser_parse()
{
	debug_parser("parser_parse");

	AstGlobalStatenent *stmt = (AstGlobalStatenent *)malloc(sizeof(AstGlobalStatenent));
	AstFunction *fn;

	size_t i = parser.tokens_index;

	if (parser.tokens_index == 0 && PARSER_CURRENT->type != TOKEN_PACKAGE && parser.package == NULL)
	{
		info_parser("User not defined a package name, so we set it to '%s' as default.", ONE_PACKAGE_DEFAULT);
		parser.package = ONE_PACKAGE_DEFAULT;
	}

	if (PARSER_CURRENT->type == TOKEN_PACKAGE)
	{
		parser_parse_package();
		return NULL;
	}
	else if (PARSER_CURRENT->type == TOKEN_IMPORT)
	{
		parser_parse_import();
		return NULL;
	}
	else if (PARSER_CURRENT->type == TOKEN_TYPE)
	{
		parser_parse_type();
		return NULL;
	}
	else if (PARSER_CURRENT->type == TOKEN_STRUCT)
	{
		parser_parse_struct();
		return NULL;
	}

	else if (PARSER_CURRENT->type == TOKEN_FN)
	{
		fn = parser_parse_fn();
		stmt->type = AST_GLOBAL_STATEMENT_FN;
		stmt->fn = fn;
		return stmt;
	}

	if (PARSER_CURRENT->type == TOKEN_EOF)
		return NULL;
	else if (parser.tokens_index == i)
	{
		printf("==>%s\n", PARSER_CURRENT->value);
		error_parser("Cannot parse this kind of statement, we face to %s token!", token_name(PARSER_CURRENT->type));
	}

	return stmt;
}

AstImport *parser_parse_import()
{
	debug_parser("parser_parse_import");

	Token *ident;

	parser_expect(TOKEN_IMPORT);
	ident = PARSER_CURRENT;
	parser_expect(TOKEN_VALUE_IDENTIFIER);

	return NULL;
}

AstTypeDef *parser_parse_type()
{
	debug_parser("parser_parse_type");

	parser_expect(TOKEN_TYPE);
	return NULL;
}

AstStruct *parser_parse_struct()
{
	debug_parser("parser_parse_struct");

	Token *ident;

	parser_expect(TOKEN_STRUCT);
	ident = PARSER_CURRENT;
	parser_expect(TOKEN_VALUE_IDENTIFIER);

	while (PARSER_CURRENT->type != TOKEN_OPERATOR_BRACKET_CURLY_RIGHT)
	{
		parser_next();
	}

	parser_expect(TOKEN_OPERATOR_BRACKET_CURLY_RIGHT);

	return NULL;
}

AstFunction *parser_parse_fn()
{
	debug_parser("parser_parse_fn");

	AstFunction *fn; // = (AstFunction*) malloc(sizeof(AstFunction));
	AstBlock *block;
	Token *ident;

	AstArguments args;
	array_init(&args);

	parser_expect(TOKEN_FN);
	ident = PARSER_CURRENT;
	parser_expect(TOKEN_VALUE_IDENTIFIER);

	info_parser("Define function = %s", ident->value);
	block = parser_parse_block();

	fn = ast_make_function((char *)ident->value, args, block);

	//	fn->arguments = args;
	// 	array_free(&args);
	//	fn->name = (char*)ident->value;
	//	fn->block = block;

	return fn;
}

AstBlock *parser_parse_block()
{
	debug_parser("parser_parse_block");

	parser_expect(TOKEN_OPERATOR_BRACKET_CURLY_LEFT);
	AstBlock *block = parser_parse_statements();
	parser_expect(TOKEN_OPERATOR_BRACKET_CURLY_RIGHT);
	return block;
}

AstBlock *parser_parse_statements()
{
	debug_parser("parser_parse_statements");

	AstStatement *stmt;
	AstStatements stmts;
	array_init(&stmts);

	while (PARSER_CURRENT->type != TOKEN_OPERATOR_BRACKET_CURLY_RIGHT)
	{
		stmt = parser_parse_statement();
		//		printf("STMT TYPE ===>%s\n", ast_statement_name(stmt->type));
		array_push(&stmts, (void *)stmt);
	}

	AstBlock *block = ast_make_block(stmts);
	//	array_free(&stmts); // TODO

	return block;
}

AstStatement *parser_parse_statement()
{
	debug_parser("parser_parse_statement");

	AstStatement *stmt;

	info_parser("statement type = %s", token_name(PARSER_CURRENT->type));

	if (PARSER_CURRENT->type == TOKEN_PRINT || PARSER_CURRENT->type == TOKEN_PRINTNL || PARSER_CURRENT->type == TOKEN_PRINTDB || PARSER_CURRENT->type == TOKEN_PRINTDBNL)
	{
		stmt = parser_parse_statement_prints();
		return stmt;
	}
	else if (PARSER_CURRENT->type == TOKEN_IF)
	{
	}
	else if (PARSER_CURRENT->type == TOKEN_WHILE)
	{
	}
	else if (PARSER_CURRENT->type == TOKEN_DO)
	{
	}
	else if (PARSER_CURRENT->type == TOKEN_MATCH)
	{
	}
	else if (PARSER_CURRENT->type == TOKEN_SWITCH)
	{
	}
	else
	{
		error_parser("We face to %s as a unknown type of token at print statement!", token_name(PARSER_CURRENT->type));
		return NULL;
	}
	return NULL;
}

AstStatement *parser_parse_statement_prints()
{
	debug_parser("parser_parse_statement_prints");

	if (PARSER_CURRENT->type == TOKEN_PRINT)
	{
		return parser_parse_statement_print();
	}
	else if (PARSER_CURRENT->type == TOKEN_PRINTNL)
	{
		return parser_parse_statement_printnl();
	}
	else if (PARSER_CURRENT->type == TOKEN_PRINTDB)
	{
		return parser_parse_statement_printdb();
	}
	else if (PARSER_CURRENT->type == TOKEN_PRINTDBNL)
	{
		return parser_parse_statement_printdbnl();
	}
	else
	{
		error_parser("We expect a print statement but we face to a %s token!", token_name(PARSER_CURRENT->type));
		return NULL;
	}
}

AstStatement *parser_parse_statement_print()
{
	debug_parser("parser_parse_statement_print");

	AstStatement *stmt = ast_make_statement(AST_STATEMENT_PRINT);

	parser_expect(TOKEN_PRINT);

	//	printf("====::::: current token is %s\n", token_name(PARSER_CURRENT->type));

	stmt->expressions = parser_parse_expressions();

	return stmt;
}

AstStatement *parser_parse_statement_printnl()
{
	debug_parser("parser_parse_statement_printnl");

	AstStatement *stmt = ast_make_statement(AST_STATEMENT_PRINTNL);

	parser_expect(TOKEN_PRINTNL);
	stmt->expressions = parser_parse_expressions();

	return stmt;
}

AstStatement *parser_parse_statement_printdb()
{
	debug_parser("parser_parse_statement_printdb");

	AstStatement *stmt = ast_make_statement(AST_STATEMENT_PRINTDB);

	parser_expect(TOKEN_PRINTDB);
	stmt->expressions = parser_parse_expressions();

	return stmt;
}

AstStatement *parser_parse_statement_printdbnl()
{
	debug_parser("parser_parse_statement_printdbnl");

	AstStatement *stmt = ast_make_statement(AST_STATEMENT_PRINTDBNL);

	parser_expect(TOKEN_PRINTDBNL);
	stmt->expressions = parser_parse_expressions();

	return stmt;
}

AstExpressions parser_parse_expressions()
{
	debug_parser("parser_parse_expressions");

	AstExpression *expr;
	AstExpressions exprs;
	array_init(&exprs);

	bool is_first = true;

	do {
		if (is_first == false) parser_expect(TOKEN_OPERATOR_COMMA);
		//		printf("1/at exprs parser ====::::: current token is %s - %s\n", token_name(PARSER_CURRENT->type), PARSER_CURRENT->value);
		expr = parser_parse_expression();
		//		printf("2/at exprs parser ====::::: current token is %s\n", token_name(PARSER_CURRENT->type));
		array_push(&exprs, expr);
		if (is_first == true) is_first = false;
	} while (PARSER_CURRENT->type == TOKEN_OPERATOR_COMMA);

	//	printf("SOOOO at bottom of exprs parser ====::::: current token is %s\n", token_name(PARSER_CURRENT->type));

	//	for (;;)
	//	{
	//		expr = parser_parse_expression();
	//		array_push(&exprs, (void*)expr);
	//
	//		printf("::::: current token is %s\n", token_name(PARSER_CURRENT->type));
	//
	//		if (parser_has(TOKEN_OPERATOR_COMMA))
	//		{
	//			parser_expect(TOKEN_OPERATOR_COMMA);
	//		}
	//		else
	//		{
	//			break;
	//		}
	//	}

	return exprs;
}

AstExpression *parser_parse_expression_primary()
{
	debug_parser("parser_parse_expression_primary");

	AstType t;
	AstExpression *expr = (AstExpression *)malloc(sizeof(AstExpression));

	//	printf("1/at expr parser====::::: current token is %s - %s\n", token_name(PARSER_CURRENT->type), PARSER_CURRENT->value);

	if (PARSER_CURRENT->type == TOKEN_VALUE_STRING)
	{
		expr->operator= TOKEN_OPERATOR_NONE;
		t.type = AST_TYPE_STRING;
		t.hasArray = false;
		expr->type = t;
		expr->vstring = (char *)PARSER_CURRENT->value;
		info_parser("parser_parse_expression: string value is '%s'", expr->vstring);

		parser_next();
	}
	else if (PARSER_CURRENT->type == TOKEN_VALUE_NUMBER)
	{
		expr->operator= TOKEN_OPERATOR_NONE;
		t.type = AST_TYPE_I32;
		t.hasArray = false;
		expr->type = t;
		expr->vstring = (char *)PARSER_CURRENT->value;
		info_parser("parser_parse_expression: number value is '%s'", expr->vstring);

		parser_next();
	}
	else
	{
		error_parser("Bad token as expression, we face to a %s token!", token_name(PARSER_CURRENT->type));
	}
	return expr;
}

AstExpression *parser_parse_expression_factor()
{
	debug_parser("parser_parse_expression_factor");

	AstExpression *expr;
	if (PARSER_CURRENT->type == TOKEN_OPERATOR_BRACKET_ROUND_LEFT)
	{
		parser_expect(TOKEN_OPERATOR_BRACKET_ROUND_LEFT);
		expr = parser_parse_expression();
		parser_expect(TOKEN_OPERATOR_BRACKET_ROUND_RIGHT);
	}
	else if (PARSER_CURRENT->type == TOKEN_OPERATOR_MINUS || PARSER_CURRENT->type == TOKEN_OPERATOR_PLUS || PARSER_CURRENT->type == TOKEN_OPERATOR_BANG)
	{
		TokenType op = PARSER_CURRENT->type;
		parser_next();
		expr = ast_make_expression_unary(op, parser_parse_expression_primary());
	}
	else
	{
		expr = parser_parse_expression_primary();
	}
	return expr;
}

// 5 of the cpp op tables
AstExpression *parser_parse_expression_term()
{
	debug_parser("parser_parse_expression_term");

	AstExpression *expr = parser_parse_expression_factor();
	while (PARSER_CURRENT->type == TOKEN_OPERATOR_STAR || PARSER_CURRENT->type == TOKEN_OPERATOR_SLASH || PARSER_CURRENT->type == TOKEN_OPERATOR_SLASH_INT || PARSER_CURRENT->type == TOKEN_OPERATOR_REMAINDER)
	{
		TokenType op = PARSER_CURRENT->type;
		parser_next();
		expr = ast_make_expression_2(op, -1, expr, parser_parse_expression_factor());
	}
	return expr;
}

// 6 of the cpp op tables
AstExpression *parser_parse_expression()
{
	debug_parser("parser_parse_expression");

	AstExpression *expr = parser_parse_expression_term();
	while (PARSER_CURRENT->type == TOKEN_OPERATOR_PLUS || PARSER_CURRENT->type == TOKEN_OPERATOR_MINUS)
	{
		TokenType op = PARSER_CURRENT->type;
		parser_next();
		expr = ast_make_expression_2(op, -1, expr, parser_parse_expression_term());
	}
	return expr;

	//	return parser_parse_expression_precedence();
	//	return parser_parse_expression_primary();
}

//
//ParseRule rules[] = {
//	 [TOKEN_OPERATOR_BRACKET_ROUND_RIGHT] = {NULL, NULL, PREC_NONE},
//	 [TOKEN_OPERATOR_BRACKET_SQUARE_LEFT] = {NULL, NULL, PREC_NONE}, // [big]
//	 [TOKEN_OPERATOR_BRACKET_SQUARE_RIGHT] = {NULL, NULL, PREC_NONE},
//	 [TOKEN_OPERATOR_COMMA] = {NULL, NULL, PREC_NONE},
//
////	 [TOKEN_OPERATOR_DOT] = {NULL, dot, PREC_CALL},
//
//	 [TOKEN_OPERATOR_MINUS] = {unary, binary, PREC_TERM},
//	 [TOKEN_OPERATOR_PLUS] = {NULL, binary, PREC_TERM},
//	 [TOKEN_SEMICOLON] = {NULL, NULL, PREC_NONE},
//	 [TOKEN_OPERATOR_SLASH] = {NULL, binary, PREC_FACTOR},
//	 [TOKEN_OPERATOR_STAR] = {NULL, binary, PREC_FACTOR},
//
//	 [TOKEN_OPERATOR_BANG] = {unary, NULL, PREC_NONE},
//
//	 [TOKEN_OPERATOR_EQUAL_BANG] = {NULL, binary, PREC_EQUALITY},
//	 [TOKEN_OPERATOR_EQUAL] = {NULL, NULL, PREC_NONE},
//
//	 [TOKEN_OPERATOR_EQUAL_EQUAL] = {NULL, binary, PREC_EQUALITY},
//	 [TOKEN_OPERATOR_GREATER] = {NULL, binary, PREC_COMPARISON},
//	 [TOKEN_OPERATOR_GREATER_EQUAL] = {NULL, binary, PREC_COMPARISON},
//	 [TOKEN_OPERATOR_LESS] = {NULL, binary, PREC_COMPARISON},
//	 [TOKEN_OPERATOR_LESS_EQUAL] = {NULL, binary, PREC_COMPARISON},
//
//	 [TOKEN_VALUE_IDENTIFIER] = {variable, NULL, PREC_NONE},
//	 [TOKEN_VALUE_STRING] = {string, NULL, PREC_NONE},
//	 [TOKEN_VALUE_NUMBER] = {number, NULL, PREC_NONE},
//	 [TOKEN_OPERATOR_AND] = {NULL, and_, PREC_AND},
//	 [TOKEN_ELSE] = {NULL, NULL, PREC_NONE},
//
//	 [TOKEN_] = {literal, NULL, PREC_NONE},
//
//	 [TOKEN_FOR] = {NULL, NULL, PREC_NONE},
//	 [TOKEN_FN] = {NULL, NULL, PREC_NONE},
//	 [TOKEN_IF] = {NULL, NULL, PREC_NONE},
//
//	 [TOKEN_OR] = {NULL, or_, PREC_OR},
//	 [TOKEN_PRINT] = {NULL, NULL, PREC_NONE},
//	 [TOKEN_PRINTNL] = {NULL, NULL, PREC_NONE},
//	 [TOKEN_RETURN] = {NULL, NULL, PREC_NONE},
//	 [TOKEN_SUPER] = {super_, NULL, PREC_NONE},
//
//	 [TOKEN_] = {this_, NULL, PREC_NONE},
//	 [TOKEN_TRUE] = {literal, NULL, PREC_NONE},
//	 [TOKEN_VAR] = {NULL, NULL, PREC_NONE},
//	 [TOKEN_WHILE] = {NULL, NULL, PREC_NONE},
//	 [TOKEN_ERROR] = {NULL, NULL, PREC_NONE},
//	 [TOKEN_EOF] = {NULL, NULL, PREC_NONE},
//};
//
//static ParseRule* getRule(TokenType type)
//{
//	return &rules[type];
//}
//
//AstExpression* parser_parse_expression_precedence(Precedence precedence)
//{
//	advance();
//	ParseFn prefixRule = getRule(parser.previous.type)->prefix;
//	if (prefixRule == NULL)
//	{
//		error("Expect expression.");
//		return;
//	}
//
//	bool canAssign = precedence <= PREC_ASSIGNMENT;
//	prefixRule(canAssign);
//
//	while (precedence <= getRule(parser.current.type)->precedence)
//	{
//		advance();
//		ParseFn infixRule = getRule(parser.previous.type)->infix;
//
//		infixRule(canAssign);
//	}
//
//	if (canAssign && match(TOKEN_EQUAL))
//	{
//		error("Invalid assignment target.");
//	}
//}

//AstExpression *parseExpression_1()
//{
//	// TODO: Adding ++
//	// TODO: Adding --
//	// TODO: Adding []
//	// TODO: Adding ()
//	// TODO: Adding .
//	// TODO: Adding ->
//
//	AstExpression *expr;
//
//	if (parserHasToken(pars, TOKEN_BRACKET_OPEN, errors) == true) // current token is (
//	{
//		parserNextToken(); // SKIP ( TOKEN
//		expr = parseExpression();
//		parserExceptTokenGo(pars, TOKEN_BRACKET_CLOSE, errors); // we except ) and skip it
//	}
//	else
//	{
//		expr = parseExpressionPrimitive();
//	}
//	return expr;
//}
//
//AstExpression *parseExpression_2()
//{
//	// TODO: type casting...
//
//	AstExpression *expr;
//	if (parserHasToken(pars, TOKEN_OPERATOR_PLUS, errors) == true) // current token is +
//	{
//		parserNextToken(); // SKIP + TOKEN
//		expr = parseExpression_1(); // parser expr-value after + operator
//		expr = astExpression(TOKEN_OPERATOR_PLUS, 10, 0, "", false, expr, NULL);
//	}
//	else if (parserHasToken(pars, TOKEN_OPERATOR_MINUS, errors) == true) // current token is -
//	{
//		parserNextToken(); // SKIP - TOKEN
//		expr = parseExpression_1(); // parser expr-value after - operator
//		expr = astExpression(TOKEN_OPERATOR_MINUS, 10, 0, "", false, expr, NULL);
//	}
//	else
//	{
//		expr = parseExpression_1(); // parser expr-value
//	}
//	return expr;
//}
//
//AstExpression *parseExpression_3()
//{
//	printf("---------- parseExpression_3\n");
//	AstExpression *expr = parseExpression_2();
//
//	if (parserHasToken(pars, TOKEN_OPERATOR_MUL, errors) == true) // current token is *
//	{
//		parserNextToken(); // SKIP * TOKEN
//		expr = astExpression(TOKEN_OPERATOR_MUL, 10, 0, "", false, expr, parseExpression());
//	}
//	else if (parserHasToken(pars, TOKEN_OPERATOR_DIV, errors) == true) // current token is /
//	{
//		parserNextToken(); // SKIP / TOKEN
//		expr = astExpression(TOKEN_OPERATOR_DIV, 10, 0, "", false, expr, parseExpression());
//	}
//	else if (parserHasToken(pars, TOKEN_OPERATOR_DIVINT, errors) == true) // current token is //
//	{
//		parserNextToken(); // SKIP // TOKEN
//		expr = astExpression(TOKEN_OPERATOR_DIVINT, 10, 0, "", false, expr, parseExpression());
//	}
//	else if (parserHasToken(pars, TOKEN_OPERATOR_REM, errors) == true) // current token is %
//	{
//		parserNextToken(); // SKIP % TOKEN
//		expr = astExpression(TOKEN_OPERATOR_REM, 10, 0, "", false, expr, parseExpression());
//	}
//
//	return expr;
//}
//
//AstExpression *parseExpression_4()
//{
//	printf("---------- parseExpression_4\n");
//	AstExpression *expr = parseExpression_3();
//
//	if (parserHasToken(pars, TOKEN_OPERATOR_PLUS, errors) == true) // current token is +
//	{
//		parserNextToken(); // SKIP + TOKEN
//		expr = astExpression(TOKEN_OPERATOR_PLUS, 10, 0, "", false, expr, parseExpression());
//	}
//	else if (parserHasToken(pars, TOKEN_OPERATOR_MINUS, errors) == true) // current token is -
//	{
//		parserNextToken(); // SKIP - TOKEN
//		expr = astExpression(TOKEN_OPERATOR_MINUS, 10, 0, "", false, expr, parseExpression());
//	}
//
//	return expr;
//}
//
//AstExpression *parseExpression_5()
//{
//	printf("---------- parseExpression_5\n");
//	AstExpression *expr = parseExpression_4();
//
//	if (parserHasToken(pars, TOKEN_OPERATOR_SHIFT_LEFT, errors) == true) // current token is >>
//	{
//		parserNextToken(); // SKIP >> TOKEN
//		expr = astExpression(TOKEN_OPERATOR_SHIFT_LEFT, 10, 0, "", false, expr, parseExpression());
//	}
//	else if (parserHasToken(pars, TOKEN_OPERATOR_SHIFT_RIGHT, errors) == true) // current token is <<
//	{
//		parserNextToken(); // SKIP << TOKEN
//		expr = astExpression(TOKEN_OPERATOR_SHIFT_RIGHT, 10, 0, "", false, expr, parseExpression());
//	}
//
//	return expr;
//}
//
//AstExpression *parseExpression_6()
//{
//	printf("---------- parseExpression_6\n");
//	AstExpression *expr = parseExpression_5();
//
//	if (parserHasToken(pars, TOKEN_OPERATOR_GE, errors) == true) // current token is >=
//	{
//		parserNextToken(); // SKIP >= TOKEN
//		expr = astExpression(TOKEN_OPERATOR_GE, 10, 0, "", false, expr, parseExpression());
//	}
//	else if (parserHasToken(pars, TOKEN_OPERATOR_G, errors) == true) // current token is >
//	{
//		parserNextToken(); // SKIP > TOKEN
//		expr = astExpression(TOKEN_OPERATOR_G, 10, 0, "", false, expr, parseExpression());
//	}
//	else if (parserHasToken(pars, TOKEN_OPERATOR_L, errors) == true) // current token is <
//	{
//		parserNextToken(); // SKIP < TOKEN
//		expr = astExpression(TOKEN_OPERATOR_L, 10, 0, "", false, expr, parseExpression());
//	}
//	else if (parserHasToken(pars, TOKEN_OPERATOR_LE, errors) == true) // current token is <=
//	{
//		parserNextToken(); // SKIP <= TOKEN
//		expr = astExpression(TOKEN_OPERATOR_LE, 10, 0, "", false, expr, parseExpression());
//	}
//
//	return expr;
//}
//
//AstExpression *parseExpression_7()
//{
//	printf("---------- parseExpression_7\n");
//	AstExpression *expr = parseExpression_6();
//
//	if (parserHasToken(pars, TOKEN_OPERATOR_EQUALEQUAL, errors) == true) // current token is ==
//	{
//		parserNextToken(); // SKIP == TOKEN
//		expr = astExpression(TOKEN_OPERATOR_EQUALEQUAL, 10, 0, "", false, expr, parseExpression());
//	}
//	else if (parserHasToken(pars, TOKEN_OPERATOR_EQUALEQUALEQUAL, errors) == true) // current token is ===
//	{
//		parserNextToken(); // SKIP === TOKEN
//		expr = astExpression(TOKEN_OPERATOR_EQUALEQUALEQUAL, 10, 0, "", false, expr, parseExpression());
//	}
//	else if (parserHasToken(pars, TOKEN_OPERATOR_NOTEQUALEQUAL, errors) == true) // current token is !==
//	{
//		parserNextToken(); // SKIP !== TOKEN
//		expr = astExpression(TOKEN_OPERATOR_NOTEQUALEQUAL, 10, 0, "", false, expr, parseExpression());
//	}
//	else if (parserHasToken(pars, TOKEN_OPERATOR_NOTEQUAL, errors) == true) // current token is !=
//	{
//		parserNextToken(); // SKIP != TOKEN
//		expr = astExpression(TOKEN_OPERATOR_NOTEQUAL, 10, 0, "", false, expr, parseExpression());
//	}
//
//	return expr;
//}
//
//AstExpression *parseExpression_8()
//{
//	printf("---------- parseExpression_8\n");
//	AstExpression *expr = parseExpression_7();
//
//	if (parserHasToken(pars, TOKEN_OPERATOR_BIT_AND, errors) == true) // current token is &
//	{
//		parserNextToken(); // SKIP & TOKEN
//		expr = astExpression(TOKEN_OPERATOR_BIT_AND, 10, 0, "", false, expr, parseExpression());
//	}
//
//	return expr;
//}
//
//AstExpression *parseExpression_9()
//{
//	printf("---------- parseExpression_9\n");
//	AstExpression *expr = parseExpression_8();
//
//	if (parserHasToken(pars, TOKEN_OPERATOR_BIT_XOR, errors) == true) // current token is ^
//	{
//		parserNextToken(); // SKIP ^ TOKEN
//		expr = astExpression(TOKEN_OPERATOR_BIT_XOR, 10, 0, "", false, expr, parseExpression());
//	}
//
//	return expr;
//}
//
//AstExpression *parseExpression_10()
//{
//	printf("---------- parseExpression_10\n");
//	AstExpression *expr = parseExpression_9();
//
//	if (parserHasToken(pars, TOKEN_OPERATOR_BIT_OR, errors) == true) // current token is |
//	{
//		parserNextToken(); // SKIP | TOKEN
//		expr = astExpression(TOKEN_OPERATOR_BIT_OR, 10, 0, "", false, expr, parseExpression());
//	}
//
//	return expr;
//}
//
//AstExpression *parseExpression_11()
//{
//	printf("---------- parseExpression_11\n");
//	AstExpression *expr = parseExpression_10();
//
//	if (parserHasToken(pars, TOKEN_OPERATOR_AND, errors) == true) // current token is &&
//	{
//		parserNextToken(); // SKIP && TOKEN
//		expr = astExpression(TOKEN_OPERATOR_AND, 10, 0, "", false, expr, parseExpression());
//	}
//
//	return expr;
//}
//
//AstExpression *parseExpression_12()
//{
//	printf("---------- parseExpression_12\n");
//	AstExpression *expr = parseExpression_11();
//
//	if (parserHasToken(pars, TOKEN_OPERATOR_OR, errors) == true) // current token is ||
//	{
//		parserNextToken(); // SKIP || TOKEN
//		expr = astExpression(TOKEN_OPERATOR_OR, 10, 0, "", false, expr, parseExpression());
//	}
//
//	return expr;
//}
//
//AstExpression *parseExpression_13()
//{
//	printf("---------- parseExpression_13\n");
//	printf("[TEST]==>%s\n", tokenName((*pars->lex->tokens)->type));
//	AstExpression *expr = parseExpression_12();
//
//	printf("[TEST]==>%s\n", tokenName((*pars->lex->tokens)->type));
//	if (parserHasToken(pars, TOKEN_OPERATOR_QUESTION, errors) == true) // current token is ?
//	{
//		parserNextToken(); // SKIP ? TOKEN
//		AstExpression *expr_true = parseExpression();
//		parserExceptTokenGo(pars, TOKEN_OPERATOR_COLON, errors); // we except : token and skip it...
//		AstExpression *expr_false = parseExpression();
//		expr = astExpression3(TOKEN_OPERATOR_IF, 10, 0, "", false, expr, expr_true, expr_false);
//	}
//	else if (parserHasToken(pars, TOKEN_OPERATOR_QUESTIONQUESTION, errors) == true) // current token is ??
//	{
//		parserNextToken(); // SKIP ?? TOKEN
//		AstExpression *expr_false = parseExpression();
//		expr = astExpression(TOKEN_OPERATOR_IFIF, 10, 0, "", false, expr, expr_false);
//	}
//
//	return expr;
//}
//
//AstExpression *parseExpression_14()
//{
//	printf("---------- parseExpression_14\n");
//	printf("[TEST]==>%s\n", tokenName((*pars->lex->tokens)->type));
//	AstExpression *expr = parseExpression_13();
//
//	printf("[TEST]==>%s\n", tokenName((*pars->lex->tokens)->type));
//	if (parserHasToken(pars, TOKEN_OPERATOR_EQUAL, errors) == true) // current token is =
//	{
//		parserNextToken(); // SKIP = TOKEN
//		AstExpression *right = parseExpression();
//		expr = astExpression(TOKEN_OPERATOR_EQUAL, 10, 0, "", false, expr, right);
//	}
//
//	return expr;
//}

void parser_parse_package()
{
	debug_parser("parser_parse_package");

	Token *t;
	if (parser.tokens_index == 0)
	{
		parser_expect(TOKEN_PACKAGE);
		if (PARSER_HAS(TOKEN_VALUE_IDENTIFIER))
		{
			PARSER_CURRENT_LOG
			t = PARSER_CURRENT;
			parser_expect(TOKEN_VALUE_IDENTIFIER);
		}
		else if (PARSER_HAS(TOKEN_VALUE_STRING))
		{
			PARSER_CURRENT_LOG
			t = PARSER_CURRENT;
			parser_expect(TOKEN_VALUE_STRING);
		}
		else
		{
			error_parser("You cannot set package name as %s token, you have to write this in two general forms:\n\t1- Identifier: `package yourname`\n\t2- String: `package \"your-name\"`", token_name(PARSER_CURRENT->type));
			return;
		}
	}
	else
	{
		error_parser("You are unable to define package name at middle or end of the file and you have to set package name at top!");
		return;
	}

	info_parser("SET PACKAGE = \"%s\"", t->value);
	parser.package = (char *)t->value;
}

bool parser_expect(TokenType expected)
{
	debug_parser("parser_expect");

	if (PARSER_CURRENT->type == expected)
	{
		parser_next();
		return true;
	}
	else
	{
		error_parser("We expected %s but we find %s", token_name(expected), token_name(PARSER_CURRENT->type));
	}
	return false;
}

bool parser_has(TokenType expected)
{
	debug_parser("parser_has");

	if (PARSER_CURRENT->type == expected)
	{
		return true;
	}
	return false;
}

void parser_free()
{
	debug_parser("parser_free");

	// TODO
}
