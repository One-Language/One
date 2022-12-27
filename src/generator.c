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

/**
 * @brief Get symbol alias of a operator token
 * 
 * @param char* left 
 * @param token_type_t op
 * @param char* right
 * @return char*
 */
char* operator_symbol(char* left, token_type_t op, char* right)
{
    string_t* code = string_init();

    // unary operators
    if (left == NULL) {
        switch (op) {
            case TOKEN_INCREMENT: string_append_format(code, "++%s", right); break;
            case TOKEN_DECREMENT: string_append_format(code, "--%s", right); break;
            case TOKEN_BANG: string_append_format(code, "! %s", right); break;
            default: string_append_format(code, "unknown operator"); break;
        }
    } else if (right == NULL) {
        switch (op) {
            case TOKEN_INCREMENT: string_append_format(code, "%s++", left); break;
            case TOKEN_DECREMENT: string_append_format(code, "%s--", left); break;
            default: string_append_format(code, "unknown operator"); break;
        }
    }
    // binary operators
    } else {
        switch (op) {
            case TOKEN_EQUAL_EQUAL: string_append_format(code, "%s == %s", left, right); break;
            case TOKEN_LESS_EQUAL: string_append_format(code, "%s < %s", left, right); break;
            case TOKEN_LESS: string_append_format(code, "%s <= %s", left, right); break;
            case TOKEN_GREATER_EQUAL: string_append_format(code, "%s > %s", left, right); break;
            case TOKEN_GREATER: string_append_format(code, "%s >= %s", left, right); break;
            case TOKEN_PLUS: string_append_format(code, "%s + %s", left, right); break;
            case TOKEN_MINUS: string_append_format(code, "%s - %s", left, right); break;
            case TOKEN_STAR: string_append_format(code, "%s * %s", left, right); break;
            case TOKEN_EXPONENT: string_append_format(code, "pow(%s, %s)", left, right); break;
            case TOKEN_SLASH: string_append_format(code, "%s / %s", left, right); break;
            case TOKEN_DOT: string_append_format(code, "concat(%s, %s)", left, right); break;
            case TOKEN_BANG_EQUAL: string_append_format(code, "%s != %s", left, right); break;

            // case TOKEN_LEFT_PAREN: return "left_paren";
            // case TOKEN_RIGHT_PAREN: return "right_paren";

            // case TOKEN_LEFT_BRACE: return "left_brace";
            // case TOKEN_RIGHT_BRACE: return "right_brace";

            // case TOKEN_LEFT_BRACKET: return "left_bracket";
            // case TOKEN_RIGHT_BRACKET: return "right_bracket";

            default: string_append_format(code, "unknown operator"); break;
        }

        // case TOKEN_QUESTION: return "question";
    }

    return code->value;
}

/**
 * @brief Generate the code of a expression from AST
 *
 * @param ast_generator_t* generator
 * @param ast_block_t* block
 * @param ast_expr_t* expression
 *
 * @return
 */
char* generator_generate_expression(generator_t* generator, ast_block_t* block, ast_expr_t* expression)
{
    string_t *code = string_init();

    switch (expression->type) {
        case AST_EXPRESSION_BINARY: {
            ast_expr_binary_t* binaryExpression = expression->expr.binary;
            char *left = generator_generate_expression(generator, block, binaryExpression->left);
            char *right = generator_generate_expression(generator, block, binaryExpression->right);

            // string_append_format(code, "%s %s %s", left, token_name(binaryExpression->operator), right);
            string_append_format(code, "%s", operator_symbol(left, binaryExpression->operator, right));

            free(left);
            free(right);
        } break;
        case AST_EXPRESSION_UNARY: {
            ast_expr_unary_t* unaryExpression = expression->expr.unary;
            char *value = generator_generate_expression(generator, block, unaryExpression->argument);

            // string_append_format(code, "%s %s", token_name(unaryExpression->operator), value);
            string_append_format(code, "%s", operator_symbol(NULL, unaryExpression->operator, value));

            free(value);
        } break;
        case AST_EXPRESSION_SUB_EXPRESSION: {
            string_append_format(code, "(");
            string_append(code, generator_generate_expression(generator, block, expression->expr.sub_expression));
            string_append(code, ")");
        } break;
        case AST_EXPRESSION_LITERAL: {
            ast_expr_literal_t* literalExpression = expression->expr.literal;
            value_t* value = literalExpression->value;

            switch (value->type) {
                case VALUE_TYPE_INT: {
                    string_append_format(code, "%d", value->value.int_value);
                } break;
                case VALUE_TYPE_FLOAT: {
                    string_append_format(code, "%f", value->value.float_value);
                } break;
                case VALUE_TYPE_STR: {
                    string_append_format(code, "%s", value->value.str_value);
                } break;
                case VALUE_TYPE_BOOL: {
                    string_append_format(code, "%s", value->value.bool_value ? "true" : "false");
                } break;
                default: {
                    string_append(code, "unknown");
                } break;
            }
        } break;
        default: {
            return "Unknown expression type";
        }
    }

    return code->value;
}

/**
 * @brief Generate the code of a IF statement from AST
 *
 * @param generator_t* generator
 * @param block_t* block
 * @param ast_if_t* if_stmt
 * @param bool is_else
 *
 * @return char*
 */
char* generator_generate_if(generator_t* generator, ast_block_t* block, ast_if_t* if_stmt, bool is_else)
{
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

/**
 * @brief Generate the code of a RET statement from AST
 *
 * @param generator_t* generator
 * @param block_t* block
 * @param ast_ret_t* ret_statement
 *
 * @return char*
 */
char* generator_generate_ret(generator_t* generator, ast_block_t* block, ast_ret_t * ret_statement)
{
    string_t* code = string_init();

    string_append(code, char_repeat('\t', generator->ident));
    string_append(code, "return(");

        string_append(code, generator_generate_expression(generator, block, ret_statement->expression));

    string_append(code, ");\n");

    return code->value;
}

/**
 * @brief Generate the code of a statement from AST
 *
 * @param generator_t* generator
 * @param block_t* block
 * @param ast_statement_t* statement
 *
 * @return char*
 */
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

/**
 * @brief Generate the code of a block from AST
 *
 * @param generator_t* generator
 * @param block_t* block
 * @param bool need_ident
 *
 * @return char*
 */
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

    // Return type
    string_append(code, function->return_type == NULL ? "void" : function->return_type);

    // Function name
    string_append_format(code, " %s(", function->name);

    // Arguments
    for (int i = 0; i < function->arguments->size; i++) {
        ast_argument_t* arg = function->arguments->data[i];
        string_append_format(code, "%s %s", arg->type, arg->name);

        if (i != function->arguments->size - 1) string_append(code, ", ");
    }

    string_append(code, ")");

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

    // string_append(generator->code, "int _start()\n{\n\treturn(0);\n}\n");
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
