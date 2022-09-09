//
// Created by Max on 9/9/2022.
//
#include "../parser/parser.h"
#include "../../builtins/str.h"

typedef struct {
    Parser* parser;
    sds code;
} Generator;

Generator* generator_init(Parser* parser);

void generator_generate(Generator* generator);

char* generator_block(Generator* generator, AstBlock* block);

char* generator_statement(Generator* generator, AstBlock* block, AstStatement* stmt);

char* generator_function(Generator* generator, AstBlock* block, AstFunction* function);
