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
    generator->ident = 0;
    return generator;
}

char* generator_generate_expression(generator_t* generator, ast_block_t* block, ast_expr_t* expression) {
    string_t *code = string_init();

    switch (expression->type) {
        case AST_EXPRESSION_BINARY: {
            ast_expr_binary_t* binaryExpression = expression->expr.binary;
            char *left = generator_generate_expression(generator, block, binaryExpression->left);
            char *right = generator_generate_expression(generator, block, binaryExpression->right);
            string_append_format(code, "%s %s %s", left, token_name(binaryExpression->operator), right);
            free(left);
            free(right);
        } break;
        case AST_EXPRESSION_UNARY: {
            ast_expr_unary_t* unaryExpression = expression->expr.unary;
            char *value = generator_generate_expression(generator, block, unaryExpression->argument);
            string_append_format(code, "%s %s", token_name(unaryExpression->operator), value);
            free(value);
        } break;
        case AST_EXPRESSION_SUB_EXPRESSION: {
            string_append_format(code, "(");
            string_append(code, generator_generate_expression(generator, block, expression->expr.sub_expression));
            string_append(code, ")");
        } break;
        case AST_EXPRESSION_LITERAL: {
            ast_expr_literal_t * literalExpression = expression->expr.literal;
            string_append_format(code, "%s", literalExpression->value);
        } break;
        default: {
            return "Unknown expression type";
        }
    }

    return code->value;
}

char* generator_generate_if(generator_t* generator, ast_block_t* block, ast_if_t* if_stmt, bool is_else) {
    string_t *code = string_init();

    if (is_else == false) string_append(code, char_repeat('\t', generator->ident));
    string_append(code, "if (");

        string_append(code, generator_generate_expression(generator, block, if_stmt->condition));

    string_append(code, ") ");

    string_append(code, generator_generate_block(generator, NULL, if_stmt->then, false));

    if (if_stmt->else_) {
        for (int i = 0; i < if_stmt->else_->statements->size; i++) {
            ast_statement_t* stmt = if_stmt->else_->statements->data[i];
            if (stmt->type == AST_STATEMENT_IF) {
                ast_if_t* if_stmt = (ast_if_t*)stmt->stmt_if;

                string_append(code, char_repeat('\t', generator->ident));
                string_append(code, "else ");

                if (if_stmt->condition == NULL) {
                    string_append(code, generator_generate_block(generator, NULL, if_stmt->then, false));
                } else {
                    string_append(code, generator_generate_if(generator, block, if_stmt, true));
                }

            }
        }
    }

    return code->value;
}

char* generator_generate_ret(generator_t* generator, ast_block_t* block, ast_ret_t * ret_statement)
{
    string_t* code = string_init();

    string_append(code, char_repeat('\t', generator->ident));
    string_append(code, "return(");

        string_append(code, generator_generate_expression(generator, block, ret_statement->expression));

    string_append(code, ");\n");

    return code->value;
}

char* generator_generate_statement(generator_t* generator, ast_block_t* block, ast_statement_t* statement)
{
    switch (statement->type) {
        case AST_STATEMENT_IF:
            return generator_generate_if(generator, block, statement->stmt_if, false);
            break;
        case AST_STATEMENT_RET:
            return generator_generate_ret(generator, block, statement->stmt_ret);
            break;
        default:
            return "// Unknown statement type\n";
            break;
    }
}

char* generator_generate_block(generator_t* generator, void* parent, ast_block_t* block, bool need_ident)
{
    string_t* code = string_init();

    if (need_ident) string_append(code, char_repeat('\t', generator->ident));

    if (block->statements->size == 0) {
        string_append(code, "{}\n");
        return code->value;
    } else {
        string_append(code, "{\n");
    }

    generator->ident++;

        for (int i = 0; i < block->statements->size; i++) {
            ast_statement_t* statement = block->statements->data[i];
            string_append(code, generator_generate_statement(generator, block, statement));
        }

    generator->ident--;

    string_append(code, char_repeat('\t', generator->ident));
    string_append(code, "}\n");

    return code->value;
}

/**
 * @brief Generate the code of a function from AST
 * 
 * @param generator_t* generator
 * @param ast_function_t* function
 * 
 * @return char* 
 */
char* generator_generate_function(generator_t* generator, ast_function_t* function)
{
    string_t* code = string_init();
    string_append_format(code, "int %s()", function->name);

    if (function->block->statements->size == 0) string_append(code, " ");
    else string_append(code, "\n");

    string_append(code, generator_generate_block(generator, function, function->block, true));

    return code->value;
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
    string_append(generator->code, "#include <stdio.h>\n");
    string_append(generator->code, "#include <stdlib.h>\n");
    string_append(generator->code, "#include <stdbool.h>\n");
    string_append(generator->code, "#include <inttypes.h>\n");
    string_append(generator->code, "\n");

    for (int i = 0; i < generator->ast->functions->size; i++) {
        ast_function_t* function = (ast_function_t*)array_get(generator->ast->functions, i);
        string_append(generator->code, generator_generate_function(generator, function));
    }

    string_append(generator->code, "int _start()\n{\n\treturn(0);\n}\n");
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
