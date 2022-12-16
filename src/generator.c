/**
 The One Programming Language
 File: generator.c
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#include "generator.h"

/**
 * @brief Initialize the generator object
 * 
 * @param ast_t* ast
 * 
 * @return generator_t* 
 */
generator_t* generator_init(ast_t* ast)
{
    generator_t* generator = (generator_t*)malloc(sizeof(generator_t));
    generator->ast = ast;
    generator->code = string_init();
    return generator;
}

/**
 * @brief Generate the code from AST
 * 
 * @param generator_t* generator
 * 
 * @return void
 */
void generator_generate(generator_t* generator)
{
    string_append(generator->code, "int main() { return 0; }");
}

/**
 * @brief Get the code from generator
 * 
 * @param generator_t* generator
 * 
 * @return char* 
 */
char* generator_code(generator_t* generator)
{
    return generator->code->value;
}

/**
 * @brief Free the generator object
 * 
 * @param generator_t* generator
 * 
 * @return void
 */
void generator_free(generator_t* generator)
{
    if (generator->code)
        free(generator->code);
    free(generator);
}
