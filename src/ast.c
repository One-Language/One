/**
 The One Programming Language
 File: ast.c
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#include "ast.h"

/**
 * @brief Initialize AST
 * 
 * @param void
 * 
 * @return ast_t* 
 */
ast_t* ast_init()
{
    ast_t* ast = (ast_t*)malloc(sizeof(ast_t));
    ast->functions = array_init();
    ast->output = string_init();
    ast->ident = 0;
    return ast;
}

/**
 * @brief Initialize a function
 * 
 * @param void
 * 
 * @return ast_functaion_t*
 */
ast_function_t* ast_function_init()
{
    ast_function_t* function = (ast_function_t*)malloc(sizeof(ast_function_t));
    function->arguments = array_init();
    function->return_type = malloc(sizeof(char)*50);
//    function->block = ast_block_init();
    return function;
}

/**
 * @brief Initialize a statement
 *
 * @param void
 *
 * @return ast_statement_t*
 */
ast_argument_t* ast_argument_init()
{
    ast_argument_t* argument = (ast_argument_t*)malloc(sizeof(ast_argument_t));
    argument->name = malloc(sizeof(char) * 100);
    argument->type = malloc(sizeof(char) * 100);
    return argument;
}

/**
 * @brief Initialize a statement
 * 
 * @return ast_statement_t* 
 */
ast_statement_t* ast_statement_init()
{
    ast_statement_t* statement = (ast_statement_t*)malloc(sizeof(ast_statement_t));
    return statement;
}

/**
 * @brief Initialize an expression
 * 
 * @param void
 * 
 * @return ast_expr_t* 
 */
ast_expr_t* ast_expression_init()
{
    ast_expr_t* expr = (ast_expr_t*)malloc(sizeof(ast_expr_t));
    return expr;
}

/**
 * @brief Initialize a block
 * 
 * @param void
 * 
 * @return ast_block_t* 
 */
ast_block_t* ast_block_init()
{
    ast_block_t* block = (ast_block_t*)malloc(sizeof(ast_block_t));
    block->statements = array_init();
    return block;
}

char* ast_print_xml_expression_literal(ast_t* ast, ast_block_t* block, value_t* value)
{
    string_t* str = string_init();

    string_append(str, char_repeat('\t', ast->ident));

    switch (value->type) {
        case VALUE_TYPE_INT: {
            string_append_format(str, "<integer>%d</integer>\n", value->value.int_value);
        } break;
        case VALUE_TYPE_FLOAT: {
            string_append_format(str, "<float>%f</float>\n", value->value.float_value);
        } break;
        case VALUE_TYPE_STR: {
            string_append_format(str, "<string>%s</string>\n", value->value.str_value);
        } break;
        case VALUE_TYPE_BOOL: {
            string_append_format(str, "<boolean>%s</boolean>\n", value->value.bool_value ? "true" : "false");
        } break;
        default: {
            string_append(str, "<unknown></unknown>\n");
        } break;
    }

    return str->value;
}

/**
 * @brief Print XML of a expressions
 *
 * @param ast_t* ast
 * @param ast_block_t* block
 * @param ast_expr_t* expression
 *
 * @return char*
 */
char* ast_print_xml_expression(ast_t* ast, ast_block_t* block, ast_expr_t* expression)
{
    string_t* str = string_init();
    if (expression == NULL) return NULL; // TODO

    switch (expression->type) {
        case AST_EXPRESSION_BINARY: {
            ast_expr_binary_t* binaryExpression = expression->expr.binary;

            string_append(str, char_repeat('\t', ast->ident));
            string_append_format(str, "<expression_binary type=\"%s\">\n", token_name(binaryExpression->operator));
            ast->ident++;

                string_append(str, char_repeat('\t', ast->ident));
                string_append(str, "<left>\n");
                ast->ident++;

                    char *left = ast_print_xml_expression(ast, block, binaryExpression->left);
                    string_append(str, left);
                    // free(left);

                ast->ident--;
                string_append(str, char_repeat('\t', ast->ident));
                string_append(str, "</left>\n");

                ////////////////////////////////////////////////////

                string_append(str, char_repeat('\t', ast->ident));
                string_append(str,
                              "<right>\n");
                ast->ident++;

                    char *right = ast_print_xml_expression(ast, block, binaryExpression->right);
                    string_append(str, right);
                    // free(right);

                ast->ident--;
                string_append(str, char_repeat('\t', ast->ident));
                string_append(str, "</right>\n");

            ast->ident--;
            string_append(str, char_repeat('\t', ast->ident));
            string_append(str, "</expression_binary>\n");
        } break;
        case AST_EXPRESSION_UNARY: {
            ast_expr_unary_t* unaryExpression = expression->expr.unary;

            string_append(str, char_repeat('\t', ast->ident));
            string_append(str, "<expression_unary>\n");

            ast->ident++;
            char *value = ast_print_expression(block, unaryExpression->argument, 0);
            string_append(str, value);
            // free(value);
            ast->ident--;

            string_append(str, char_repeat('\t', ast->ident));
            string_append(str, "</expression_unary>\n");

            // free(value);
        } break;
        case AST_EXPRESSION_SUB_EXPRESSION: {
            // string_append_format(str, "%s(", tab);
            char* value = ast_print_expression(block, expression->expr.sub_expression, 0);
            string_append(str, value);
            free(value);
            // string_append(str, ")");
        } break;
        case AST_EXPRESSION_LITERAL: {
            ast_expr_literal_t * literalExpression = expression->expr.literal;

            string_append(str, char_repeat('\t', ast->ident));
            string_append(str, "<expression_literal>\n");

            ast->ident++;
            string_append_format(str, "%s", ast_print_xml_expression_literal(ast, block, expression->expr.literal->value));
            ast->ident--;

            string_append(str, char_repeat('\t', ast->ident));
            string_append(str, "</expression_literal>\n");
        } break;
//        case AST_EXPRESSION_TYPE_VARIABLE: {
//            AstVariableExpression *variableExpression = expression->variableExpression;
//            str = sdscatprintf(code, "%s%s", tab, variableExpression->name);
//            break;
//        }

//        case AST_EXPRESSION_TYPE_CALL: {
//            AstCallExpression *callExpression = expression->callExpression;
//            str = sdscatprintf(code, "%s%s(", tab, callExpression->name);
//            for (int i = 0; i < callExpression->arguments->size; i++) {
//                ast_expr_t *argument = callExpression->arguments->data[i];
//                char *argumentstr = ast_print_expression(block, argument, ident);
//                str = sdscatprintf(code, "%s", argumentCode);
//                free(argumentCode);
//                if (i != callExpression->arguments->size - 1) {
//                    str = sdscatprintf(code, ", ");
//                }
//            }
//            str = sdscatprintf(code, ")");
//            break;
//        }

//        case AST_EXPRESSION_TYPE_INDEX: {
//            AstIndexExpression* indexExpression = expression->indexExpression;
//            char* value = ast_print_expression(block, indexExpression->value, ident);
//            char* index = ast_print_expression(block, indexExpression->index, ident);
//            str = sdscatprintf(code, "%s%s[%
        default: {
            string_append(str, char_repeat('\t', ast->ident));
            string_append(str, "<expression_unknown/>\n");
        }
    }

    return str->value;
}

/**
 * @brief Print of a expressions
 *
 * @param ast_block_t* block
 * @param ast_expr_t* expression
 * @param int ident
 *
 * @return char*
 */
char* ast_print_expression(ast_block_t* block, ast_expr_t* expression, int ident)
{
    string_t* str = string_init();
    if (expression == NULL) return NULL; // TODO

    char* tab = char_repeat('\t', ident);

    switch (expression->type) {
        case AST_EXPRESSION_BINARY: {
            ast_expr_binary_t* binaryExpression = expression->expr.binary;
            char *left = ast_print_expression(block, binaryExpression->left, 0);
            char *right = ast_print_expression(block, binaryExpression->right, 0);
            string_append_format(str, "%s%s %s %s", tab, left, token_name(binaryExpression->operator), right);
            // free(left);
            // free(right);
        } break;
        case AST_EXPRESSION_UNARY: {
            ast_expr_unary_t* unaryExpression = expression->expr.unary;
            char *value = ast_print_expression(block, unaryExpression->argument, 0);
            string_append_format(str, "%s%s %s", tab, token_name(unaryExpression->operator), value);
            // free(value);
        } break;
        case AST_EXPRESSION_SUB_EXPRESSION: {
            string_append_format(str, "%s(", tab);
            string_append(str, ast_print_expression(block, expression->expr.sub_expression, 0));
            string_append(str, ")");
        } break;
        case AST_EXPRESSION_LITERAL: {
            ast_expr_literal_t * literalExpression = expression->expr.literal;
            string_append_format(str, "%s%s", tab, literalExpression->value);
        } break;
//        case AST_EXPRESSION_TYPE_VARIABLE: {
//            AstVariableExpression *variableExpression = expression->variableExpression;
//            str = sdscatprintf(code, "%s%s", tab, variableExpression->name);
//            break;
//        }

//        case AST_EXPRESSION_TYPE_CALL: {
//            AstCallExpression *callExpression = expression->callExpression;
//            str = sdscatprintf(code, "%s%s(", tab, callExpression->name);
//            for (int i = 0; i < callExpression->arguments->size; i++) {
//                ast_expr_t *argument = callExpression->arguments->data[i];
//                char *argumentstr = ast_print_expression(block, argument, ident);
//                str = sdscatprintf(code, "%s", argumentCode);
//                free(argumentCode);
//                if (i != callExpression->arguments->size - 1) {
//                    str = sdscatprintf(code, ", ");
//                }
//            }
//            str = sdscatprintf(code, ")");
//            break;
//        }

//        case AST_EXPRESSION_TYPE_INDEX: {
//            AstIndexExpression* indexExpression = expression->indexExpression;
//            char* value = ast_print_expression(block, indexExpression->value, ident);
//            char* index = ast_print_expression(block, indexExpression->index, ident);
//            str = sdscatprintf(code, "%s%s[%
        default: {
            return "Unknown expression type";
        }
    }

    return str->value;
}

/**
 * @brief Print of a expressions
 *
 * @param array_t* expressions
 * @param int ident
 *
 * @return char*
 */
char* ast_print_expressions(array_t* expressions, int ident)
{
    string_t* str = string_init();

    string_append(str, char_repeat('\t', ident));

    for (int i = 0; i < expressions->size; i++) {
        ast_expr_t* expression = expressions->data[i];
        string_append(str, ast_print_expression(NULL, expression, 0));
        if (i != expressions->size - 1) string_append(str, ", ");
    }

    return str->value;
}

/**
 * @brief Print XML of a IF statement
 *
 * @param ast_t* ast
 * @param ast_block_t* block
 * @param ast_if_t* statement
 *
 * @return char*
 */
char* ast_print_xml_statement_if(ast_t* ast, ast_block_t* block, ast_if_t* statement)
{
    string_t* str = string_init();

    string_append(str, char_repeat('\t', ast->ident));
    string_append(str, "<if>\n");
    ast->ident++;

    if (statement->condition != NULL) {
        string_append(str, char_repeat('\t', ast->ident));
        string_append(str, "<condition>\n");
        ast->ident++;

        string_append(str, ast_print_xml_expression(ast, NULL, statement->condition));

        ast->ident--;
        string_append(str, char_repeat('\t', ast->ident));
        string_append(str, "</condition>\n");
    } else {
        string_append(str, char_repeat('\t', ast->ident));
        string_append(str, "<condition/>\n");
    }

    //////////////////////

    string_append(str, char_repeat('\t', ast->ident));
    string_append(str, "<then>\n");
    ast->ident++;

    string_append(str, ast_print_xml_block(ast, statement->then));

    ast->ident--;
    string_append(str, char_repeat('\t', ast->ident));
    string_append(str, "</then>\n");

    if (statement->else_ != NULL) {
        string_append(str, char_repeat('\t', ast->ident));
        string_append(str, "<else>\n");
        ast->ident++;

            string_append(str, ast_print_xml_block(ast, statement->else_));

        ast->ident--;
        string_append(str, char_repeat('\t', ast->ident));
        string_append(str, "</else>\n");
    }

    ast->ident--;
    string_append(str, char_repeat('\t', ast->ident));
    string_append(str, "</if>\n");

    return str->value;
}

/**
 * @brief Print XML of a statement
 *
 * @param ast_t* ast
 * @param ast_statement_t* statement
 *
 * @return char*
 */
char* ast_print_xml_statement(ast_t* ast, ast_statement_t* statement)
{
    string_t* str = string_init();

    switch (statement->type) {
        case AST_STATEMENT_IF:
            string_append(str, ast_print_xml_statement_if(ast, NULL, statement->stmt_if));
            break;

        case AST_STATEMENT_RET:
            string_append(str, char_repeat('\t', ast->ident));
            string_append(str, "<return>\n");

            ast->ident++;
            string_append(str, ast_print_xml_expression(ast, NULL, statement->stmt_ret->expression));
            ast->ident--;

            string_append(str, char_repeat('\t', ast->ident));
            string_append(str, "</return>\n");
            break;

            // case AST_STATEMENT_EXPR:
            //     string_append(str, "\t\t\t\tExpression statement\n");
            //     break;

        default:
            string_append(str, char_repeat('\t', ast->ident));
            string_append(str, "<unknown/>\n");
            break;
    }

    return str->value;
}

/**
 * @brief Print of a statement
 *
 * @param ast_statement_t* statement
 *
 * @return char*
 */
char* ast_print_statement(ast_statement_t* statement)
{
    string_t* str = string_init();

    switch (statement->type) {
        case AST_STATEMENT_IF:
            string_append(str, "\t\t\t\tIf statement\n");
            break;

        case AST_STATEMENT_RET:
            string_append(str, "\t\t\t\tReturn statement: ");
            string_append(str, ast_print_expression(NULL, statement->stmt_ret->expression, 0));
            string_append(str, "\n");
            break;

            // case AST_STATEMENT_EXPR:
            //     string_append(str, "\t\t\t\tExpression statement\n");
            //     break;

        default:
            string_append(str, "\t\t\t\tUnknown statement\n");
            break;
    }

    return str->value;
}

/**
 * @brief Print XML of a block
 *
 * @param ast_t* ast
 * @param ast_block_t* block
 *
 * @return char*
 */
char* ast_print_xml_block(ast_t* ast, ast_block_t* block)
{
    string_t* str = string_init();

    string_append(str, char_repeat('\t', ast->ident));
    string_append(str, "<block>\n");
    ast->ident++;

    string_append(str, char_repeat('\t', ast->ident));
    if (block->statements->size == 0) string_append(str, "<statements/>\n");
    else {
        string_append_format(str, "<statements count=\"%zu\">\n", block->statements->size);

        ast->ident++;
        for (int i = 0; i < block->statements->size; i++) {
            ast_statement_t* statement = array_get(block->statements, i);
            string_append(str, ast_print_xml_statement(ast, statement));
        }
        ast->ident--;

        string_append(str, char_repeat('\t', ast->ident));
        string_append_format(str, "</statements>\n");
    }

    ast->ident--;

    string_append(str, char_repeat('\t', ast->ident));
    string_append(str, "</block>\n");

    return str->value;
}

/**
 * @brief Print of a block
 *
 * @param ast_t* ast
 * @param ast_block_t* block
 *
 * @return char*
 */
char* ast_print_block(ast_block_t* block)
{
    string_t* str = string_init();

    string_append_format(str, "\t\tBlock (%d statements)\n", block->statements->size);

    for (int i = 0; i < block->statements->size; i++) {
        ast_statement_t* statement = array_get(block->statements, i);
        string_append(str, ast_print_statement(statement));
    }

    return str->value;
}

/**
 * @brief Print XML of a function
 *
 * @param ast_t* ast
 * @param ast_function_t* function
 *
 * @return char*
 */
char* ast_print_xml_function(ast_t* ast, ast_function_t* function)
{
    string_t* str = string_init();

    string_append(str, char_repeat('\t', ast->ident));
    string_append_format(str, "<function name=\"%s\">\n", function->name);
    ast->ident++;

        string_append(str, char_repeat('\t', ast->ident));
        if (function->arguments->size == 0) string_append(str, "<arguments/>\n");
        else {
            string_append_format(str, "<arguments count=\"%d\">\n", function->arguments->size);
            ast->ident++;

                for (int i = 0; i < function->arguments->size; i++) {
                    ast_argument_t* argument = array_get(function->arguments, i);
                    string_append(str, char_repeat('\t', ast->ident));
                    string_append_format(str, "<argument name=\"%s\" type=\"%s\"/>\n", argument->name, argument->type);
                }

            ast->ident--;
            string_append(str, char_repeat('\t', ast->ident));
            string_append(str, "</arguments>\n");}

        string_append(str, ast_print_xml_block(ast, function->block));

        string_append(str, char_repeat('\t', ast->ident));

        if (function->return_type == NULL) string_append(str, "<return type=\"void\"/>\n");
        else {
            string_append_format(str, "<return type=\"%s\"/>\n", function->return_type);
        }

    ast->ident--;
    string_append(str, char_repeat('\t', ast->ident));
    string_append_format(str, "</function>\n");

    return str->value;
}

/**
 * @brief Print AST of a function
 * 
 * @param ast_function_t* function
 * 
 * @return char*
 */
char* ast_print_function(ast_function_t* function)
{
    string_t* str = string_init();

    string_append_format(str, "\tFunction %s (%d statements)\n", function->name, function->block->statements->size);

    string_append(str, ast_print_block(function->block));

    return str->value;
}

/**
 * @brief Print AST
 * 
 * @param ast_t* ast
 * 
 * @return char*
 */
char* ast_print(ast_t* ast)
{
    string_t* str = string_init();

    if (ast->functions->size == 0) string_append(str, "There are no functions!\n");
    else {
        string_append_format(str, "Functions(%zu):\n", ast->functions->size);
        for (int i = 0; i < ast->functions->size; i++) {
            ast_function_t* function = ast->functions->data[i];
            string_append(str, ast_print_function(function));
        }
    }

    return str->value;
}

/**
 * @brief Initialize an if statement
 * 
 * @param void
 * 
 * @return ast_if_t* 
 */
ast_if_t* ast_statement_if_init()
{
    ast_if_t* st = (ast_if_t*)malloc(sizeof(ast_if_t));
    st->then= NULL;
    st->else_ = NULL;
    return st;
}

/**
 * @brief Initialize a ret statement
 * 
 * @param void
 * 
 * @return ast_ret_t* 
 */
ast_ret_t* ast_statement_ret_init()
{
    ast_ret_t* st = (ast_ret_t*)malloc(sizeof(ast_ret_t));
    return st;
}

/**
 * @brief Print AST in JSON format
 * 
 * @param ast_t* ast
 * 
 * @return char*
 */
char* ast_print_json(ast_t* ast)
{
    string_t* str = string_init();

    string_append(str, "{soon}");

    return str->value;
}

/**
 * @brief Print AST in XML format
 * 
 * @param ast_t* ast
 * 
 * @return char*
 */
char* ast_print_xml(ast_t* ast)
{
    string_t* str = string_init();

    if (ast->functions->size == 0) string_append(str, "<functions/>\n");
    else {
        string_append_format(str, "<functions count=\"%zu\">\n", ast->functions->size);
        ast->ident++;
        for (int i = 0; i < ast->functions->size; i++) {
            ast_function_t* function = ast->functions->data[i];
            string_append(str, ast_print_xml_function(ast, function));
        }
        ast->ident--;
        string_append_format(str, "</functions>\n");
    }

    return str->value;
}
