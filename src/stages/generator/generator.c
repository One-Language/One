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

char* generator_function(Generator* generator, AstBlock* block, AstFunction* function)
{
    sds code = sdsnew("");
    code = sdscatprintf(code, "function %s(", function->name);
    for (int i = 0; i < function->arguments->count; i++) {
        AstFunctionArgument* argument = function->arguments->data[i];
        code = sdscatprintf(code, "%s %s", argument->type, argument->name);
        if (i != function->arguments->count - 1) {
            code = sdscatprintf(code, ", ");
        }
    }
    code = sdscatprintf(code, ") {\n");
    code = sdscatprintf(code, "%s", generator_block(generator, function->block));
    code = sdscatprintf(code, "}\n");
    return code;
}

char* generator_statement(Generator* generator, AstBlock* block, AstStatement* stmt)
{
    switch (stmt->type) {
        case STATEMENT_FUNCTION:
            return generator_function(generator, block, stmt->stmt.function);
        default:
            return sdsnew("Unknown statement type");
    }
}

char* generator_block(Generator* generator, AstBlock* block)
{
    sds temp = sdsnew("");

    for (int i = 0; i < block->statements->count; ++i) {
        AstStatement* stmt = block->statements->data[i];
        temp = sdscat(temp, generator_statement(generator, block, stmt));
    }

    return temp;
}

void generator_generate(Generator* generator)
{
    AstProgram* ast = generator->parser->ast;
    for (int i = 0; i < ast->statements->count; i++) {
        AstStatement* stmt = ast->statements->data[i];
        switch (stmt->type) {
            case STATEMENT_FUNCTION:
                generator->code = sdscatprintf(generator->code, "function %s(", stmt->stmt.function->name);
                for (int j = 0; j < stmt->stmt.function->arguments->count; j++) {
                    AstFunctionArgument* arg = stmt->stmt.function->arguments->data[j];
                    generator->code = sdscatprintf(generator->code, "%s %s", arg->type, arg->name);
                    if (j < stmt->stmt.function->arguments->count - 1) {
                        generator->code = sdscat(generator->code, ", ");
                    }
                }
                generator->code = sdscat(generator->code, ") {\n");
                generator->code = sdscat(generator->code, generator_block(generator, stmt->stmt.function->block));
                generator->code = sdscat(generator->code, "}\n");
                break;
            default:
                break;
        }
    }
//    generator->code = sdscat(generator->code, "int main() { return 0; }\n");
}
