//
// Created by Max on 9/4/2022.
//

#include "parser.h"
// #include "../lexer/lexer.h"

Parser* parser_init(Lexer* lexer)
{
    Parser* parser = (Parser*)malloc(sizeof(Parser));
    parser->lexer = lexer;

    parser->tokens = (Token**) lexer->tokens->data;
    parser->token_count = lexer->tokens->count;

    parser->ast = (AstProgram*)malloc(sizeof(AstProgram));
    parser->ast->statements = malloc(sizeof(Array));
    array_init(parser->ast->statements);
    parser->ast->errors = malloc(sizeof(Array));
    array_init(parser->ast->errors);

    parser->errors = malloc(sizeof(Array));
    array_init(parser->errors);

    return parser;
}

AstStatement* statement_make(char* name)
{
    AstStatement* statement = (AstStatement*)malloc(sizeof(AstStatement));
    statement->name = strdup(name);

    return statement;
}

void advance(Parser* parser)
{
    *parser->tokens++;
}

void previus(Parser* parser)
{
    *parser->tokens--;
}

bool peekFor(Parser* parser, TokenType type)
{
    if ((*parser->tokens)->type == type) return true;
    return false;
}

bool peekForNext(Parser* parser, TokenType type)
{
    if ((*parser->tokens + 1)->type == type) return true;
    return false;
}

bool peekForPrevius(Parser* parser, TokenType type)
{
    if ((*parser->tokens - 1)->type == type) return true;
    return false;
}

Token* expect(Parser* parser, TokenType type)
{
    if ((*parser->tokens)->type == type) {
        Token* t = *parser->tokens;
        advance(parser);
        return t;
    }
    else {
        sds message = sdsnew("");
        message = sdscatprintf(message, "Expected %s, but got %s", token_type_name(type), token_type_name((*parser->tokens)->type));

        Error* error = error_init(ERROR_PARSER, ERROR_PARSER_BAD_TOKEN, message, parser->lexer->main_source, (*parser->tokens)->start, (*parser->tokens)->end);
        array_push(parser->errors, error);
        return NULL;
    }
}

AstBlock* parse_block(Parser* parser)
{
    AstBlock* block = make_block();
    block->statements = malloc(sizeof(Array));
    array_init(block->statements);

    if (expect(parser, TOKEN_LBRACE) == NULL) return NULL;

    while (!peekFor(parser, TOKEN_RBRACE) && !peekFor(parser, TOKEN_EOF)) {
        array_push(block->statements, parser_statement(parser, block));
    }

    if (expect(parser, TOKEN_RBRACE) == NULL) return NULL;

    return block;
}

void parser_free(Parser* parser)
{
    if (parser == NULL) return;

    // TODO
//    lexer_free(parser->lexer);
    free(parser);
}


char* ast_statement_type_name(AstStatementType type)
{
    switch(type) {
        case STATEMENT_EXPRESSION:
            return "STATEMENT_EXPRESSION";
        case STATEMENT_RETURN:
            return "STATEMENT_RETURN";
        case STATEMENT_FUNCTION:
            return "STATEMENT_FUNCTION";
        case STATEMENT_IF:
            return "STATEMENT_IF";
        case STATEMENT_WHILE:
            return "STATEMENT_WHILE";
        case STATEMENT_FOR:
            return "STATEMENT_FOR";
        default:
            return "STATEMENT_ERROR";
    }
}

AstType* parser_type(Parser* parser)
{
    AstType* type = malloc(sizeof(AstType));
    type->isPointer = false;
    type->isArray = false;

    if (peekFor(parser, TOKEN_MUL)) {
        type->isPointer = true;
        advance(parser);
    }

    Token* t = expect(parser, TOKEN_IDENTIFIER);
    if (t == NULL) return NULL;
    type->type = t->value;

    // []
    if (peekFor(parser, TOKEN_LBRACKET)) {
        advance(parser);
        if (expect(parser, TOKEN_RBRACKET) == NULL) {
            // TODO: Error
            return NULL;
        }
        type->isArray = true;
    }

    return type;
}

AstFunctionArgument* parser_fn_argument(Parser* parser)
{
    AstFunctionArgument* argument = (AstFunctionArgument*)malloc(sizeof(AstFunctionArgument));

    Token* name = expect(parser, TOKEN_IDENTIFIER);
    if (name == NULL) return NULL;
    argument->name = name->value;

    AstType* type = parser_type(parser);
    if (type == NULL) return NULL;
    argument->type = type;

    return argument;
}

Array* parser_fn_arguments(Parser* parser)
{
    Array* arguments = malloc(sizeof(Array));
    array_init(arguments);

    if (expect(parser, TOKEN_LPAREN) == NULL) return NULL;

    while (1) {
        if (peekFor(parser, TOKEN_RPAREN)) break;

        AstFunctionArgument* arg = parser_fn_argument(parser);
        if (arg == NULL) return NULL;
        array_push(arguments, arg);

        if (peekFor(parser, TOKEN_RPAREN)) break;
        if (expect(parser, TOKEN_COMMA) == NULL) return NULL;
    }

    if (expect(parser, TOKEN_RPAREN) == NULL) return NULL;

    return arguments;
}

AstStatement* parser_fn(Parser* parser, AstBlock* block)
{
    AstStatement* statement = malloc(sizeof(AstStatement));

    statement->type = STATEMENT_FUNCTION;
    statement->stmt.function = malloc(sizeof(AstFunction));
    statement->stmt.function->arguments = malloc(sizeof(Array));
    array_init(statement->stmt.function->arguments);

    if (expect(parser, TOKEN_FN) == NULL) return NULL;

    Token* ident = expect(parser, TOKEN_IDENTIFIER);
    if (ident == NULL) return NULL;
    statement->stmt.function->name = ident->value;

    Array* args = parser_fn_arguments(parser);
    if (args == NULL) return NULL;
    statement->stmt.function->arguments = args;

    // :
    if (peekFor(parser, TOKEN_COLON)) {
        advance(parser);

        AstType* type = parser_type(parser);
        if (type == NULL) return NULL;
        statement->stmt.function->returnType = type;
    } else {
        AstType* type = malloc(sizeof(AstType));
        type->type = strdup("void");
        type->isPointer = false;
        type->isArray = false;
        statement->stmt.function->returnType = type;
    }

    statement->stmt.function->block = parse_block(parser);
    if (statement->stmt.function->block == NULL) return NULL;

    array_push(block->functions, statement->stmt.function->name);

    return statement;
}

AstStatement* parser_statement(Parser* parser, AstBlock* block)
{
    switch ((*parser->tokens)->type)
    {
        case TOKEN_FN: {
            return parser_fn(parser, block);
        } break;
//        case TOKEN_IDENTIFIER: {
//            AstStatement* stmt = statement_make((*parser->tokens)->value);
//
//            advance(parser); // eat identifier
//            array_push(block->variables, stmt->name);
//
//            return stmt;
//        } break;
        default: {
            AstExpression *expression = parser_expression(parser, block);
            if (expression == NULL) {
                sds message = sdsnew("Expected expression");
                Error* error = error_init(ERROR_PARSER, ERROR_PARSER_BAD_RULE, message, parser->lexer->main_source, (*parser->tokens)->start, (*parser->tokens)->end);
                array_push(parser->errors, error);
                return NULL;
            }

            AstStatement* stmt = malloc(sizeof(AstStatement));
            stmt->type = STATEMENT_EXPRESSION;
            stmt->stmt.expression = expression;
            return stmt;
        };
    }
}

AstExpression* parser_expression(Parser* parser, AstBlock* block)
{
    AstExpression* result = malloc(sizeof(AstExpression));

    if ((*parser->tokens)->type == TOKEN_IDENTIFIER ||
            (*parser->tokens)->type == TOKEN_NUMBER_INT ||
            (*parser->tokens)->type == TOKEN_NUMBER_FLOAT ||
            (*parser->tokens)->type == TOKEN_STRING_DOUBLE_QUOTE ||
            (*parser->tokens)->type == TOKEN_STRING_SINGLE_QUOTE ||
            (*parser->tokens)->type == TOKEN_BOOL_TRUE ||
            (*parser->tokens)->type == TOKEN_BOOL_FALSE ||
            (*parser->tokens)->type == TOKEN_NULL ||
            (*parser->tokens)->type == TOKEN_UNDEFINED) {
        result = parse_expression_literal();
    } else if ((*parser->tokens)->type === TokenType.T_PARENTHESIS_OPEN) {
        result = this.parseSubExpression();
    } else if (this.has(TokenType.T_OPERATOR_ADD) || this.has(TokenType.T_OPERATOR_SUBTRACT)) {
        result = parsePrefixExpression(this.prefix_bp_lookup(ft));
    } else {
        sds message = sdsnew("Unexpected token ");
        message = sdscat(message, token_type_name(ft));
        Error* error = error_init(ERROR_PARSER, ERROR_PARSER_BAD_RULE, message, parser->lexer->main_source, (*parser->tokens)->start, (*parser->tokens)->end);
        array_push(parser->errors, error);
    }

    advance(parser);
    return NULL;
//    return parser_addition(parser, block);
}

Array* parser_statements(Parser* parser, AstBlock* block)
{
    Array* statements = malloc(sizeof(Array));
    array_init(statements);

    while ((*parser->tokens)->type != TOKEN_EOF)
    {
        AstStatement* statement = parser_statement(parser, block);
        if (statement != NULL)
        {
            array_push(statements, statement);
        }
    }

    return statements;
}

AstBlock* make_block()
{
    AstBlock* block = malloc(sizeof(AstBlock));

    block->variables = malloc(sizeof(Array));
    array_init(block->variables);

    block->functions = malloc(sizeof(Array));
    array_init(block->functions);

    return block;
}

void parser_parse(Parser* parser)
{
    if (parser->lexer->errors->count > 0) {
        return;
    }

    AstBlock* block = make_block();
    parser->ast->statements = (Array*)parser_statements(parser, block);
}

char* parser_trace_type(Parser* parser, AstBlock* block, AstType* type, int ident)
{
    sds code = sdsnew("");

    char* tab = string_repeat("\t", ident);
    char* tab2 = string_repeat("\t", ident + 1);

    code = sdscatprintf(code, "%s<Type is_pointer=\"%s\" is_array=\"%s\">\n", tab, type->isPointer ? "true" : "false", type->isArray ? "true" : "false");
    code = sdscatprintf(code, "%s<Name>%s</Name>\n", tab2, type->type);
    code = sdscatprintf(code, "%s</Type>\n", tab);

    free(tab);
    free(tab2);

    return code;
}

char* parser_trace_statement(Parser* parser, AstBlock* block, AstStatement* stmt, int ident)
{
    sds temp = sdsnew("");

    char* tab = string_repeat("\t", ident);
    char* tab2 = string_repeat("\t", ident + 1);
    char* tab3 = string_repeat("\t", ident + 2);

    switch (stmt->type) {
        case STATEMENT_FUNCTION: {
            temp = sdscatprintf(temp, "%s<StatementFunction name=\"%s\">\n", tab, stmt->stmt.function->name);
            if (stmt->stmt.function->arguments->count == 0) {
                temp = sdscatprintf(temp, "%s<FunctionArguments count=\"%d\" />\n", tab2, stmt->stmt.function->arguments->count);
            } else {
                temp = sdscatprintf(temp, "%s<FunctionArguments count=\"%d\">\n", tab2, stmt->stmt.function->arguments->count);
                // TODO: arguments
                for (int i = 0; i < stmt->stmt.function->arguments->count; i++)
                {
                    AstFunctionArgument* arg = stmt->stmt.function->arguments->data[i];
                    temp = sdscatprintf(temp, "%s<FunctionArgument name=\"%s\">\n", tab3, arg->name);
                    temp = sdscatprintf(temp, "%s", parser_trace_type(parser, block, arg->type, ident + 4));
                    temp = sdscatprintf(temp, "%s</FunctionArgument>\n", tab3);
                }
                temp = sdscatprintf(temp, "%s</FunctionArguments>\n", tab2);

            }

            temp = sdscatprintf(temp, "%s<FunctionBlock>\n", tab2);
            temp = sdscat(temp, parser_trace_block(parser, stmt->stmt.function->block, ident + 2));
            temp = sdscatprintf(temp, "%s</FunctionBlock>\n", tab2);

            temp = sdscatprintf(temp, "%s<FunctionReturn>\n", tab2);
            temp = sdscatprintf(temp, "%s", parser_trace_type(parser, block, stmt->stmt.function->returnType, ident + 2));
            temp = sdscatprintf(temp, "%s</FunctionReturn>\n", tab2);
            temp = sdscatprintf(temp, "%s</StatementFunction>\n", tab);
        } break;
        default: {
            temp = sdscatprintf(temp, "%s<Statement name=\"%s\" />\n", tab, stmt->name);
        } break;
    }

    free(tab);
    free(tab2);
    free(tab3);

    return temp;
}

char* parser_trace_statements(Parser* parser, AstBlock *block, Array* statements, int ident)
{
    sds temp = sdsnew("");

    char* tab = string_repeat("\t", ident);

    if (statements->count == 0) {
        temp = sdscatprintf(temp, "%s<Statements count=\"%d\" />\n", tab, statements->count);
    } else {
        temp = sdscatprintf(temp, "%s<Statements count=\"%d\">\n", tab, statements->count);
        for (int i = 0; i < statements->count; i++) {
            AstStatement* stmt = statements->data[i];
            if (stmt != NULL) {
                temp = sdscat(temp, parser_trace_statement(parser, block, stmt, ident + 1));
            }
        }
        temp = sdscatprintf(temp, "%s</Statements>\n", tab);
    }

    free(tab);

    return temp;
}

char* parser_trace_block(Parser* parser, AstBlock* block, int ident)
{
    sds temp = sdsnew("");

    char* tab = string_repeat("\t", ident);
    char* tab2 = string_repeat("\t", ident + 1);
    char* tab3 = string_repeat("\t", ident + 2);

    temp = sdscatprintf(temp, "%s<Block>\n", tab);

    if (block->variables->count == 0) {
        temp = sdscatprintf(temp, "%s<BlockVariables count=\"%d\" />\n", tab2, block->variables->count);
    } else {
        temp = sdscatprintf(temp, "%s<BlockVariables count=\"%d\">\n", tab2, block->variables->count);
        for (int i = 0; i < block->functions->count; i++) {
            temp = sdscatprintf(temp, "%s<Variable name=\"%s\" />\n", tab3, (char*) block->variables->data[i]);
        }
        temp = sdscatprintf(temp, "%s</BlockVariables>\n", tab2);
    }
    /////////////////////////////////
    if (block->statements->count == 0) {
        temp = sdscatprintf(temp, "%s<BlockFunctions count=\"%d\" />\n", tab2, block->functions->count);
    } else {
        temp = sdscatprintf(temp, "%s<BlockFunctions count=\"%d\">\n", tab2, block->functions->count);
        for (int i = 0; i < block->functions->count; i++) {
            temp = sdscatprintf(temp, "%s<Function name=\"%s\" />\n",tab3, block->functions->data[i]);
        }
        temp = sdscatprintf(temp, "%s</BlockFunctions>\n", tab2);
    }
    /////////////////////////////////
    temp = sdscat(temp, parser_trace_statements(parser, block, block->statements, ident + 1));

    temp = sdscatprintf(temp, "%s</Block>\n", tab);

    free(tab);
    free(tab2);
    free(tab3);

    return temp;
}

char* parser_trace(Parser* parser)
{
    sds temp = sdsnew("<Parser>\n");

    // Create an empty block without any defined variables or functions!
    AstBlock* block = make_block();
    block->statements = parser->ast->statements;
    temp = sdscatprintf(temp, parser_trace_statements(parser, block, block->statements, 1));

    temp = sdscat(temp, "</Parser>");

    return temp;
}
