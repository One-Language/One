//
// Created by Max on 9/4/2022.
//

#ifndef ONE_LEXER_PARSER_H
#define ONE_LEXER_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <str.h>

#include "../../builtins/io.h"
#include "../../builtins/array.h"
#include "../../builtins/str.h"
#include "../../builtins/error.h"

#include "../lexer/lexer.h"

#include "ast.h"

typedef struct {
    Lexer* lexer;
    Token** tokens;
    size_t token_count;

    AstProgram* ast;
    Array* errors;
} Parser;

Parser* parser_init(Lexer* lexer);

void parser_parse(Parser* parser);

char* parser_trace(Parser* parser);

char* parser_trace_block(Parser* parser, AstBlock* block, int ident);

char* parser_trace_statements(Parser* parser, AstBlock* block, Array* statements, int ident);

AstFunctionArgument* parser_fn_argument(Parser* parser);

AstType* parser_type(Parser* parser);

Array* parser_fn_arguments(Parser* parser);

AstStatement* parser_fn(Parser* parser, AstBlock* block);

char* parser_trace_statement(Parser* parser, AstBlock* block, AstStatement* stmt, int ident);

AstStatement* parser_statement(Parser* parser, AstBlock* block);

AstBlock* make_block();

Array* parser_statements(Parser* parser,AstBlock* block);

void parser_parse(Parser* parser);

char* ast_statement_type_name(AstStatementType type);

AstExpression* parser_expression(Parser* parser, AstBlock* block, int binding_power_to_my_right);

void parser_free(Parser* parser);

#endif //ONE_LEXER_PARSER_H
