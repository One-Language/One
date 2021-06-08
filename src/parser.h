/**
 The One Programming Language

 File: parser.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#ifndef _PARSER_H_
#define _PARSER_H_


typedef struct _token Token;
typedef struct _location Location;
typedef struct _errors ErrorsContainer;
typedef struct _lexer Lexer;
typedef struct _ast_expression AstExpression;


typedef struct _parser
{
	Lexer *lex;
} Parser;

Parser *parserInit(Lexer *, ErrorsContainer *);

int parserCheck(Parser *, ErrorsContainer *);

void parserFree(Parser *);

bool tokenIsUserType(Parser *, ErrorsContainer *);

bool tokenIsPrimaryType(Parser *, ErrorsContainer *);

bool parserExceptTokenGo(Parser *, TokenType, ErrorsContainer *);

bool parserExceptToken(Parser *, TokenType, ErrorsContainer *);

bool parserHasToken(Parser *, TokenType, ErrorsContainer *);


AstExpression *parseExpression_1(Parser *, ErrorsContainer *);
AstExpression *parseExpression_2(Parser *, ErrorsContainer *);
AstExpression *parseExpression_3(Parser *, ErrorsContainer *);
AstExpression *parseExpression_4(Parser *, ErrorsContainer *);
AstExpression *parseExpression_5(Parser *, ErrorsContainer *);
AstExpression *parseExpression_6(Parser *, ErrorsContainer *);
AstExpression *parseExpression_7(Parser *, ErrorsContainer *);
AstExpression *parseExpression_8(Parser *, ErrorsContainer *);
AstExpression *parseExpression_9(Parser *, ErrorsContainer *);
AstExpression *parseExpression_10(Parser *, ErrorsContainer *);
AstExpression *parseExpression_11(Parser *, ErrorsContainer *);
AstExpression *parseExpression_12(Parser *, ErrorsContainer *);
AstExpression *parseExpression_13(Parser *, ErrorsContainer *);
AstExpression *parseExpression(Parser *, ErrorsContainer *);

#endif
