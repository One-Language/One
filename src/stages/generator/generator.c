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
    return "( soon )";
}

char* generator_expressions(Generator* generator, AstBlock* block, Array* expressions, int ident)
{
    return "( ...soon... )";
}

char* generator_ret(Generator* generator, AstBlock* block, AstStatement* stmt, int ident)
{
    sds code = sdsnew("");

    char* tab = string_repeat("\t", ident);

    code = sdscatprintf(code, "%sreturn ", tab);
    code = sdscatprintf(code, "%s;\n", generator_expression(generator, block, stmt->stmt.ret->expressions, ident));

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
