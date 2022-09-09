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

void generator_generate(Generator* generator)
{
    AstProgram* ast = generator->parser->ast;
    generator->code = sdscat(generator->code, "int main() { return 0; }\n");
}
