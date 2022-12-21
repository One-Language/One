/**
 The One Programming Language
 File: parser.c
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#include "parser.h"

/**
 * @brief Initialize parser with tokens
 * 
 * @param token_list_t* tokens
 * 
 * @return parser_t*
 */
parser_t* parser_init(token_list_t* tokens)
{
    parser_t* parser = (parser_t*)malloc(sizeof(parser_t));
    parser->tokens = tokens;
    parser->current_token = 0;
    parser->ast = ast_init();
    return parser;
}

/**
 * @brief Parser eat a token
 * 
 * @param parser_t* parser
 * 
 * @return token_t*
 */
token_t* parser_eat(parser_t* parser)
{
    token_t* token = parser->tokens->data[parser->current_token];
    parser->current_token++;
    return token;
}

/**
 * @brief Parser go to next token
 * 
 * @param parser_t* parser
 * 
 * @return void
 */
void parser_next(parser_t* parser)
{
    if (parser->current_token < parser->tokens->size) parser->current_token++;
}

/**
 * @brief Parser go to previous token
 * 
 * @param parser_t* parser
 * 
 * @return void
 */
void parser_previous(parser_t* parser)
{
    if (parser->current_token > 0) parser->current_token--;
}

/**
 * @brief Parser peek a token
 * 
 * @param parser_t* parser
 * 
 * @return token_t*
 */
token_t* parser_peek(parser_t* parser)
{
    return parser->tokens->data[parser->current_token];
}

/**
 * @brief Parser peek a token type
 * 
 * @param parser_t* parser
 * 
 * @return token_type_t
 */
token_type_t parser_peek_type(parser_t* parser)
{
    return parser->tokens->data[parser->current_token]->type;
}

/**
 * @brief Parser check if has a token type
 * 
 * @param parser_t* parser
 * @param token_type_t type
 * 
 * @return bool
 */
bool parser_has(parser_t* parser, token_type_t type)
{
    token_t* token = parser->tokens->data[parser->current_token];
    return token->type == type;
}

/**
 * @brief Parser skip a token type
 * 
 * @param parser_t* parser
 * @param token_type_t type
 * 
 * @return bool
 */
bool parser_skip(parser_t* parser, token_type_t type)
{
    if (parser_has(parser, type)) {
        parser->current_token++;
        return true;
    }
    return false;
}

/**
 * @brief Parser expect a token type
 * 
 * @param parser_t* parser
 * @param token_type_t type
 * 
 * @return token_t*
 */
token_t* parser_expect(parser_t* parser, token_type_t type)
{
    token_t* token = parser->tokens->data[parser->current_token];
    if (token->type != type) {
        printf("Unexpected token %s while expecting %s\n", token_name(token->type), token_name(type));
        return NULL;
    }
    parser->current_token++;
    return token;
}

/**
 * @brief Right Associative binding power
 * 
 * @param int priority
 * 
 * @return struct binding_power
 */
struct binding_power RightAssociative(int priority)
{
    struct binding_power bp;
    bp.left_power = priority + 1;
    bp.right_power = priority;
    return bp;
}

/**
 * @brief Left Associative binding power
 * 
 * @param int priority
 * 
 * @return struct binding_power
 */
struct binding_power LeftAssociative(int priority)
{
    struct binding_power bp;
    bp.left_power = priority - 1;
    bp.right_power = priority;
    return bp;
}

/**
 * @brief Parse tokens
 * 
 * @param parser_t* parser
 * 
 * @return void
 */
void parser_parse(parser_t* parser)
{
    while (parser->current_token < parser->tokens->size) {
        token_t* token = parser->tokens->data[parser->current_token];

        if (token->type == TOKEN_EOF) break;
        else if (token->type == TOKEN_FUNC) {
            ast_function_t* function = parser_parse_function(parser);
            if (function != NULL) array_push(parser->ast->functions, function);
        }
        else {
            printf("Unexpected token in parser: %s\n", token_name(token->type));
            parser->current_token++;
        }
    }
}

ast_expr_t* parser_parse_expression_literal(parser_t* parser, ast_block_t* block)
{
    ast_expr_t* expr = malloc(sizeof(ast_expr_t));

    token_t* value = parser_eat(parser);

    expr->type = AST_EXPRESSION_LITERAL;
    expr->expr.literal = malloc(sizeof(ast_expr_literal_t));
    expr->expr.literal->type = AST_VALUE_STRING;
    expr->expr.literal->value.string = value->value;

    return expr;
}

ast_expr_t* parser_parse_expression_sub(parser_t* parser, ast_block_t* block)
{
    parser_expect(parser, TOKEN_LEFT_PAREN);
    ast_expr_t* expression = parser_parse_expression(parser, block, 0);

    if (expression == NULL) {
        printf("Expected expression as sub expression\n");
        // sds message = sdsnew("Expected expression");
        // Error* error = error_init(ERROR_PARSER, ERROR_PARSER_BAD_RULE, message, parser->lexer->main_source, parser_peek(parser)->start, parser_peek(parser)->end);
        // array_push(parser->errors, error);

        return NULL;
    }

    parser_expect(parser, TOKEN_RIGHT_PAREN);

    ast_expr_t* expr = malloc(sizeof(ast_expr_t));
    expr->type = AST_EXPRESSION_SUB_EXPRESSION;
    expr->expr.sub_expression = expression;

    return expr;
}

ast_expr_t* parser_parse_expression_binary(parser_t* parser, ast_block_t* block, ast_expr_t* lhs, int min_bp)
{
    token_t* operator = NULL;
    if (!parser_has(parser, TOKEN_PLUS) &&
        !parser_has(parser, TOKEN_MINUS) &&
        !parser_has(parser, TOKEN_STAR) &&
        !parser_has(parser, TOKEN_SLASH) &&
        //            !parser_has(parser, TOKEN_DIV_INT) &&
        !parser_has(parser, TOKEN_DOT) &&
        // !parser_has(parser, TOKEN_AND) &&
        // !parser_has(parser, TOKEN_ANDAND) &&
        // !parser_has(parser, TOKEN_OR) &&
        // !parser_has(parser, TOKEN_OROR) &&
        !parser_has(parser, TOKEN_EQUAL) &&
        //            !parser_has(parser, TOKEN_BANG_EQUAL) &&
        !parser_has(parser, TOKEN_LESS) &&
        !parser_has(parser, TOKEN_LESS_EQUAL) &&
        !parser_has(parser, TOKEN_GREATER) &&
        !parser_has(parser, TOKEN_GREATER_EQUAL)
    ) {
        printf("Unexpected token %s while expecting binary operator\n", token_name(parser_peek_type(parser)));
        // sds message = sdsnew("Unexpected token ");
        // message = sdscat(message, token_name(parser_peek_type(parser)));
        // Error* error = error_init(ERROR_PARSER, ERROR_PARSER_BAD_RULE, message, parser->lexer->main_source, parser_peek(parser)->start, parser_peek(parser)->end);
        // array_push(parser->errors, error);

        return NULL;
    } else {
        operator = parser_eat(parser);
    }

    ast_expr_t* rhs = parser_parse_expression(parser, block, min_bp);

    ast_expr_t* expr = malloc(sizeof(ast_expr_t));
    expr->type = AST_EXPRESSION_BINARY;
    expr->expr.binary = malloc(sizeof(ast_expr_binary_t));
    expr->expr.binary->left = lhs;
    expr->expr.binary->right = rhs;
    expr->expr.binary->operator = operator->type;

    return expr;
}

ast_expr_t* parser_parse_expression_prefix(parser_t* parser, ast_block_t* block, int min_bp)
{
    token_t* operator;
    if (!parser_has(parser, TOKEN_PLUS) && !parser_has(parser, TOKEN_MINUS)) {
        printf("Unexpected token %s while expecting prefix operator\n", token_name(parser_peek_type(parser)));
        // sds message = sdsnew("Unexpected token ");
        // message = sdscat(message, token_name(parser_peek_type(parser)));
        // Error* error = error_init(ERROR_PARSER, ERROR_PARSER_BAD_RULE, message, parser->lexer->main_source, parser_peek(parser)->start, parser_peek(parser)->end);
        // array_push(parser->errors, error);

        return NULL;
    }

    ast_expr_t* expression = parser_parse_expression(parser, block, min_bp);

    ast_expr_t* expr = malloc(sizeof(ast_expr_t));
    expr->type = AST_EXPRESSION_PREFIX;
    expr->expr.prefix = malloc(sizeof(ast_expr_prefix_t));
    expr->expr.prefix->operator = operator->type;
    expr->expr.prefix->right = expression;

    return expr;
}

int parser_prefix_bp_lookup(token_type_t whichOperator)
{
    switch (whichOperator) {
        case TOKEN_PLUS: return 300;
        case TOKEN_MINUS: return 300;
        default: return 0;
    }
}

array_t* parser_parse_expressions(parser_t* parser, ast_block_t* block)
{
    array_t* expressions = array_init();

    ast_expr_t* lhs = parser_parse_expression(parser, block, 0);
    array_push(expressions, lhs);

//    while (parser_peek_type(parser) != TOKEN_EOF) {
//        ast_expr_t* expr = parser_parse_expression(parser, block, 0);
//        if (expr == NULL) return NULL;
//        array_push(expressions, expr);
//
//        if (parser_has(parser, TOKEN_COMMA)) {
//            advance(parser);
//        } else {
//            break;
//        }
//    }

    return expressions;
}

ast_expr_t* parser_ternary_expression(parser_t* parser, ast_block_t* block, ast_expr_t* clause)
{
    if (!parser_expect(parser, TOKEN_QUESTION)) return NULL;

    ast_expr_t* consequent = parser_parse_expression(parser, block, 0);

    if (!parser_expect(parser, TOKEN_COLON)) return NULL;

    ast_expr_t* alternate = parser_parse_expression(parser, block, 0);

    ast_expr_t* expr = malloc(sizeof(ast_expr_t));
    expr->type = AST_EXPRESSION_TERNARY;
    expr->expr.ternary = malloc(sizeof(ast_expr_ternary_t));
    expr->expr.ternary->condition = clause;
    expr->expr.ternary->true_value = consequent;
    expr->expr.ternary->false_value = alternate;

    return expr;
}

struct binding_power parser_bp_lookup(token_type_t whichOperator)
{
    struct binding_power no_binding_power = {0, 0};

    switch (whichOperator) {
        case TOKEN_LEFT_PAREN: return RightAssociative(997);
        case TOKEN_DOT: return RightAssociative(999);

        // case TOKEN_AND: return LeftAssociative(300);
        // case TOKEN_OR: return LeftAssociative(400);

        // case TOKEN_ANDAND: return LeftAssociative(500);
        // case TOKEN_OROR: return LeftAssociative(600);

        case TOKEN_PLUS: return LeftAssociative(100);
        case TOKEN_MINUS: return LeftAssociative(100);
        case TOKEN_STAR: return LeftAssociative(200);
        case TOKEN_SLASH: return LeftAssociative(200);
//        case TOKEN_DIV_INT: return LeftAssociative(200);
        case TOKEN_EXPONENT: return RightAssociative(99);
        case TOKEN_QUESTION: return RightAssociative(1000);

        case TOKEN_GREATER: return LeftAssociative(50);
        case TOKEN_GREATER_EQUAL: return LeftAssociative(50);
        case TOKEN_LESS: return LeftAssociative(50);
        case TOKEN_LESS_EQUAL: return LeftAssociative(50);
        case TOKEN_EQUAL: return LeftAssociative(50);
    //    case TOKEN_BANG_EQUAL: return LeftAssociative(50);

            // --- Postfix --- (Always Right Associative)
        case TOKEN_BANG: return RightAssociative(400);
            // Note: Postfix operators are always RightAssociative

        default: return no_binding_power;
    }
}

ast_expr_t* parser_parse_expression_postfix(parser_t* parser, ast_block_t* block, ast_expr_t* lhs)
{
    token_t* operator;
    if (parser_has(parser, TOKEN_PLUS) || parser_has(parser, TOKEN_MINUS)) {
        operator = parser_eat(parser);
    } else {
        printf("Unexpected token %s in postfix expression\n", token_name(parser_peek_type(parser)));
        // sds message = sdsnew("Unexpected token ");
        // message = sdscat(message, token_name(parser_peek_type(parser)));
        // Error* error = error_init(ERROR_PARSER, ERROR_PARSER_BAD_RULE, message, parser->lexer->main_source, parser_peek(parser)->start, parser_peek(parser)->end);
        // array_push(parser->errors, error);

        return NULL;
    }

    ast_expr_t* expr = malloc(sizeof(ast_expr_t));
    expr->type = AST_EXPRESSION_POSTFIX;
    expr->expr.postfix = malloc(sizeof(ast_expr_postfix_t));
    expr->expr.postfix->operator = operator->type;
    expr->expr.postfix->operand = lhs;

    return expr;
}

ast_expr_t* parser_parse_expression(parser_t* parser, ast_block_t* block, int binding_power_to_my_right)
{
    ast_expr_t* result = ast_expression_init();

    if (parser_has(parser, TOKEN_IDENTIFIER) ||
        parser_has(parser, TOKEN_NUMBER) ||
        // parser_has(parser, TOKEN_NUMBER_FLOAT ||
        parser_has(parser, TOKEN_STRING) //||
        // parser_has(parser, TOKEN_STRING_SINGLE_QUOTE) ||
        // parser_has(parser, TOKEN_BOOL_TRUE) ||
        // parser_has(parser, TOKEN_BOOL_FALSE) ||
        // parser_has(parser, TOKEN_NULL) ||
        // parser_has(parser, TOKEN_UNDEFINED)
    ) {
        result = parser_parse_expression_literal(parser, block);
    } else if (parser_has(parser, TOKEN_LEFT_PAREN)) {
        result = parser_parse_expression_sub(parser, block);
    } else if (parser_has(parser, TOKEN_PLUS) || parser_has(parser, TOKEN_MINUS)) {
        result = parser_parse_expression_prefix(parser, block,
                                          parser_prefix_bp_lookup(
                                                  parser_peek_type(parser)
                                          )
        );
    } else {
        printf("Unexpected token in expression: %s\n", token_name(parser_peek_type(parser)));
        // sds message = sdsnew("Unexpected token ");
        // message = sdscat(message, token_name(parser_peek_type(parser)));
        // Error* error = error_init(ERROR_PARSER, ERROR_PARSER_BAD_RULE, message, parser->lexer->main_source, parser_peek(parser)->start, parser_peek(parser)->end);
        // array_push(parser->errors, error);

        return NULL;
    }

    if (result == NULL) {
            printf("We should always have either a LHS or Prefix Operator at this point.\n");
        // sds message = sdsnew("We should always have either a LHS or Prefix Operator at this point.");
        // Error* error = error_init(ERROR_PARSER, ERROR_PARSER_BAD_RULE, message, parser->lexer->main_source, parser_peek(parser)->start, parser_peek(parser)->end);
        // array_push(parser->errors, error);

        return NULL;
    }

    while (binding_power_to_my_right < parser_bp_lookup(parser_peek_type(parser)).left_power) {
        // Is it a postfix expression?
        if (parser_has(parser, TOKEN_BANG)) {
            result = parser_parse_expression_postfix(parser, block, result);
        } else if (parser_has(parser, TOKEN_QUESTION)) {
            result = parser_ternary_expression(parser, block, result);
        } else if (parser_skip(parser, TOKEN_LEFT_PAREN)) {
            array_t* args = parser_parse_expressions(parser, block);

            parser_expect(parser, TOKEN_RIGHT_PAREN);

//            result = AstCallExpression(result, args);
        } else {
            // It must be a binary expression
            result = parser_parse_expression_binary(parser, block, result, parser_bp_lookup(parser_peek_type(parser)).right_power);
        }
    }

    if (result == NULL) {
        printf("We should always have either a LHS or Prefix Operator at this point.\n");
        // sds message = sdsnew("We should always have either a LHS or Prefix Operator at this point.");
        // Error* error = error_init(ERROR_PARSER, ERROR_PARSER_BAD_RULE, message, parser->lexer->main_source, parser_peek(parser)->start, parser_peek(parser)->end);
        // array_push(parser->errors, error);

        return NULL;
    }

    return result;
}

/**
 * @brief Parser parse an if statement
 * 
 * @param parser_t* parser
 * 
 * @return ast_if_t*
 */
ast_if_t* parser_parse_if(parser_t* parser)
{
    ast_if_t* stmt_if = ast_statement_if_init();

    if(!parser_expect(parser, TOKEN_IF)) return NULL;

    stmt_if->condition = parser_parse_expression(parser, NULL, 0);

    stmt_if->then = parser_parse_block(parser);

    // Check for else statement
    if (parser_skip(parser, TOKEN_ELSE)) {
        stmt_if->else_ = ast_block_init();

        // Check for else if
        bool is_else = true;
        while (parser_skip(parser, TOKEN_IF)) {
            ast_statement_t* else_ = ast_statement_init();
            else_->type = AST_STATEMENT_IF;
            else_->stmt_if = ast_statement_if_init();

            else_->stmt_if->condition = parser_parse_expression(parser, NULL, 0);
            if (else_->stmt_if->condition == NULL) return NULL;

            else_->stmt_if->then = parser_parse_block(parser);
            if (else_->stmt_if->then == NULL) return NULL;

            array_push(stmt_if->else_->statements, else_);

            if (!parser_skip(parser, TOKEN_ELSE)) {
                is_else = false;
                break;
            }
        }

        // Check for else block
        if (is_else == true) {
            if (parser_has(parser, TOKEN_LEFT_BRACE)) {
                ast_statement_t* else_ = ast_statement_init();
                else_->type = AST_STATEMENT_IF;
                else_->stmt_if = ast_statement_if_init();

                else_->stmt_if->then = parser_parse_block(parser);
                if (else_->stmt_if->then == NULL) return NULL;

                array_push(stmt_if->else_->statements, else_);
            }
            // Unexpected token
            else {
                printf("Unexpected token %s after else\n", token_name(parser_peek_type(parser)));
                return NULL;
            }
        }
    } else {
        stmt_if->else_ = NULL;
    }

    return stmt_if;
}

/**
 * @brief Parser parse a ret statement
 * 
 * @param parser_t* parser
 * 
 * @return ast_ret_t*
 */
ast_ret_t* parser_parse_ret(parser_t* parser)
{
    ast_ret_t* stmt_ret = ast_statement_ret_init();

    if(!parser_expect(parser, TOKEN_RET)) return NULL;

    stmt_ret->expression = parser_parse_expression(parser, NULL, 0);

    return stmt_ret;
}

/**
 * @brief Parser parse a statement
 * 
 * @param parser_t* parser
 * 
 * @return ast_statement_t* 
 */
ast_statement_t* parser_parse_statement(parser_t* parser)
{
    ast_statement_t* statement = ast_statement_init();

    token_t* token = parser_peek(parser);
    switch (token->type) {
        case TOKEN_IF: {
            statement->type = AST_STATEMENT_IF;
            statement->stmt_if = parser_parse_if(parser);
            if (statement->stmt_if == NULL) return NULL;
            break;
        }

        case TOKEN_RET: {
            statement->type = AST_STATEMENT_RET;
            statement->stmt_ret = parser_parse_ret(parser);
            if (statement->stmt_ret == NULL) return NULL;
            break;
        }

        default: {
            printf("Unexpected token in statement: %s\n", token_name(token->type));
            parser_next(parser);
            return NULL;
        }
    }

    return statement;
}

/**
 * @brief Parser parse statements
 * 
 * @param parser_t* parser
 * 
 * @return array_t* (array of ast_statement_t*)
 */
array_t* parser_parse_statements(parser_t* parser)
{
    array_t* statements = array_init();

    while (!parser_has(parser, TOKEN_EOF)) {
        if (parser_has(parser, TOKEN_RIGHT_BRACE)) break;

        ast_statement_t* statement = parser_parse_statement(parser);
        if (statement == NULL) return NULL;

        array_push(statements, statement);
    }

    return statements;
}

/**
 * @brief Parse statements
 * 
 * @param parser_t* parser
 * 
 * @return ast_block_t*
 */
ast_block_t* parser_parse_block(parser_t* parser)
{
    ast_block_t* block = ast_block_init();

    if(!parser_expect(parser, TOKEN_LEFT_BRACE)) return NULL;

    block->statements = parser_parse_statements(parser);
    if (block->statements == NULL) return NULL;

    if(!parser_expect(parser, TOKEN_RIGHT_BRACE)) return NULL;

    return block;
}

/**
 * @brief Parse function
 * 
 * @param parser_t* parser
 * 
 * @return ast_function_t*
 */
ast_function_t* parser_parse_function(parser_t* parser)
{
    ast_function_t* function = ast_function_init();

    if (!parser_expect(parser, TOKEN_FUNC)) return NULL;
    token_t* name = parser_expect(parser, TOKEN_IDENTIFIER);

    if (!parser_expect(parser, TOKEN_LEFT_PAREN)) return NULL;

    while (!parser_has(parser, TOKEN_RIGHT_PAREN)) {
        token_t* type = parser_expect(parser, TOKEN_IDENTIFIER);
        if (type == NULL) return NULL;

        token_t* name = parser_expect(parser, TOKEN_IDENTIFIER);
        if (name == NULL) return NULL;

        ast_argument_t* arg = ast_argument_init();
        arg->type = type->value;
        arg->name = name->value;
        array_push(function->arguments, arg);

        if (parser_has(parser, TOKEN_COMMA)) parser_next(parser);
        else if (!parser_has(parser, TOKEN_RIGHT_PAREN)) {
            printf("Unexpected token %s in function arguments\n", token_name(parser_peek_type(parser)));
            return NULL;
        }
    }

    if (!parser_expect(parser, TOKEN_RIGHT_PAREN)) return NULL;

    if (parser_has(parser, TOKEN_IDENTIFIER)) {
        function->return_type = parser_expect(parser, TOKEN_IDENTIFIER)->value;
    } else {
        function->return_type = NULL;
    }

    function->name = name->value;

    function->block = parser_parse_block(parser);

    if (!function->block) return NULL;

    return function;
}


/**
 * @brief Get AST from parser
 * 
 * @param parser_t* parser
 * 
 * @return ast_t*
 */
ast_t* parser_ast(parser_t* parser)
{
    return parser->ast;
}

/**
 * @brief Free parser
 * 
 * @param parser_t* parser
 */
void parser_free(parser_t* parser)
{
    free(parser);
}
