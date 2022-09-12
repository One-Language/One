//
// Created by Max on 9/9/2022.
//

#include "generator.h"

Generator* generator_init(Parser* parser)
{
    Generator* generator = malloc(sizeof(Generator));

    generator->parser = parser;
    generator->code = sdsnew("");

    return generator;
}

char* generator_type(Generator* generator, AstType* type)
{
    sds code = sdsnew("");

    if (type->isPointer) code = sdscat(code, "Pointer<");
    if (type->isArray) code = sdscat(code, "Array<");

    code = sdscat(code, type->type);

    if (type->isPointer) code = sdscat(code, ">");
    if (type->isArray) code = sdscat(code, ">");

    return code;
}

void generator_free(Generator* generator)
{
    if (generator == NULL) return;

    // TODO
//    if (generator->parser != NULL && generator->parser->lexer != NULL) lexer_free(generator->parser->lexer);
//    if (generator->parser != NULL) parser_free(generator->parser);
    free(generator);
}

char* generator_function(Generator* generator, AstBlock* block, AstFunction* function, int ident)
{
    sds code = sdsnew("");

    char* tab = string_repeat("\t", ident);
    char* returnType = generator_type(generator, function->returnType);

    code = sdscat(code, tab);
    code = sdscat(code, returnType);
    code = sdscatprintf(code, " %s(", function->name);
    for (int i = 0; i < function->arguments->count; i++) {
        AstFunctionArgument* argument = function->arguments->data[i];
        char* type = generator_type(generator, argument->type);
        code = sdscatprintf(code, "%s %s", type, argument->name);
        free(type);
        if (i != function->arguments->count - 1) {
            code = sdscatprintf(code, ", ");
        }
    }
    code = sdscatprintf(code, ") {\n");
    code = sdscatprintf(code, "%s", generator_block(generator, function->block, ident + 1));
    code = sdscatprintf(code, "%s}\n", tab);

//    free(tab);
//    free(returnType);

    return code;
}

char* generator_expression(Generator* generator, AstBlock* block, AstExpression* expression, int ident)
{
    sds code = sdsnew("");
    if (expression == NULL) {
        return code; // TODO
    }

    char* tab = string_repeat("\t", ident);

    switch (expression->type) {
        case AST_EXPRESSION_BINARY: {
            AstBinaryExpression *binaryExpression = expression->expr.binary;
            char *left = generator_expression(generator, block, binaryExpression->left, 0);
            char *right = generator_expression(generator, block, binaryExpression->right, 0);
            code = sdscatprintf(code, "%s%s %s %s", tab, left, token_type_name(binaryExpression->operator), right);
//            free(left);
//            free(right);
        } break;
        case AST_EXPRESSION_UNARY: {
            AstUnaryExpression *unaryExpression = expression->expr.unary;
            char *value = generator_expression(generator, block, unaryExpression->argument, 0);
            code = sdscatprintf(code, "%s%s %s", tab, token_type_name(unaryExpression->operator), value);
//            free(value);
        } break;
        case AST_EXPRESSION_SUB_EXPRESSION: {
            code = sdscatprintf(code, "%s(%s)", tab, generator_expression(generator, block, expression->expr.sub_expression->expression, 0));
        } break;
        case AST_EXPRESSION_LITERAL: {
            AstLiteralExpression *literalExpression = expression->expr.literal;
            code = sdscatprintf(code, "%s%s", tab, literalExpression->value);
        } break;
//        case AST_EXPRESSION_TYPE_VARIABLE: {
//            AstVariableExpression *variableExpression = expression->variableExpression;
//            code = sdscatprintf(code, "%s%s", tab, variableExpression->name);
//            break;
//        }

//        case AST_EXPRESSION_TYPE_CALL: {
//            AstCallExpression *callExpression = expression->callExpression;
//            code = sdscatprintf(code, "%s%s(", tab, callExpression->name);
//            for (int i = 0; i < callExpression->arguments->count; i++) {
//                AstExpression *argument = callExpression->arguments->data[i];
//                char *argumentCode = generator_expression(generator, block, argument, ident);
//                code = sdscatprintf(code, "%s", argumentCode);
//                free(argumentCode);
//                if (i != callExpression->arguments->count - 1) {
//                    code = sdscatprintf(code, ", ");
//                }
//            }
//            code = sdscatprintf(code, ")");
//            break;
//        }

//        case AST_EXPRESSION_TYPE_INDEX: {
//            AstIndexExpression* indexExpression = expression->indexExpression;
//            char* value = generator_expression(generator, block, indexExpression->value, ident);
//            char* index = generator_expression(generator, block, indexExpression->index, ident);
//            code = sdscatprintf(code, "%s%s[%
        default: {
            return "Unknown expression type";
        }
    }

    return code;
}

char* generator_expressions(Generator* generator, AstBlock* block, Array* expressions, int ident)
{
    sds code = sdsnew("");

    code = sdscat(code, string_repeat("\t", ident));

    for (int i = 0; i < expressions->count; i++) {
        AstExpression* expression = expressions->data[i];
        code = sdscatprintf(code, "%s", generator_expression(generator, block, expression, 0));
        if (i != expressions->count - 1) {
            code = sdscatprintf(code, ", ");
        }
    }

    return code;
}

char* generator_ret(Generator* generator, AstBlock* block, AstStatement* stmt, int ident)
{
    sds code = sdsnew("");

    char* tab = string_repeat("\t", ident);

    code = sdscatprintf(code, "%sreturn %s\n", tab, generator_expressions(generator, block, stmt->stmt.ret->expressions, ident));

    return code;
}

char* generator_statement(Generator* generator, AstBlock* block, AstStatement* stmt, int ident)
{
    switch (stmt->type) {
        case STATEMENT_RET:
            return generator_ret(generator, block, stmt, ident);
        case STATEMENT_FUNCTION:
            return generator_function(generator, block, stmt->stmt.function, ident);
        default:
            return sdsnew("Unknown statement type");
    }
}

char* generator_block(Generator* generator, AstBlock* block, int ident)
{
    sds temp = sdsnew("");

    for (int i = 0; i < block->statements->count; ++i) {
        AstStatement* stmt = block->statements->data[i];
        if (stmt != NULL) {
            temp = sdscat(temp, generator_statement(generator, block, stmt, ident));
        }
    }

    return temp;
}

void generator_generate(Generator* generator)
{
    sds temp = sdsnew("");

    AstBlock* block = make_block();
    AstProgram* ast = generator->parser->ast;

    for (int i = 0; i < ast->statements->count; i++) {
        AstStatement* stmt = ast->statements->data[i];
        if (stmt != NULL) {
            temp = sdscat(temp, generator_statement(generator, block, stmt, 0));
        }
    }

    generator->code = temp;
}
