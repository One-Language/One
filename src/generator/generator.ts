import { TokenLocation, TokenType } from "../lexer/token";
import {
    AstExpression,
    AstExpressionLiteral,
    AstExpressionBinary,
    AstExpressionUnary,
    AstExpressionTernary,
    AstExpressionFunctionCall,
    AstExpressionVariable,
    AstFunctionArgument,
    AstFunction,
    AstBody,
    Ast,
    AstStatementReturn,
    AstStatement,
    MainAst,
} from "../parser/ast";

export class Generator {
    ast: MainAst;
    functions: AstFunction[] = [];

    libraries: string[] = [
        "#include <stdio.h>",
        "#include <stdlib.h>",
        "#include <string.h>",
        "#include <math.h>",
    ];

    constructor(ast: MainAst) {
        this.ast = ast;
    }

    c(): string {
        let c: string = "";

        c += this.libraries.join("\n") + "\n\n";
        
        c += this.c_functions();

        return c;
    }

    c_functions(): string {
        const functions: AstFunction[] = [];
        for (const ast_item of this.ast.ast) {
            if (ast_item.type === "function") {
                functions.push(ast_item as AstFunction);
            }
        }
        this.functions = functions;

        return functions.map((ast: AstFunction) => {
            return this.c_function(ast);
        }).join("\n\n");
    }

    c_function_argument(ast: AstFunctionArgument): string {
        return ast.datatype + " " + ast.name;
    }

    c_function(ast: AstFunction): string {
        let c: string = "";

        c += "int " + ast.name + "(";
        c += ast.args.map((arg: AstFunctionArgument) => {
            return this.c_function_argument(arg);
        }).join(", ");
        c += ") {\n";

        c += this.c_body(ast.body);

        c += "}\n";

        return c;
    }

    c_expression(ast: AstExpression): string {
        switch (ast.type) {
            case "literal":
                return this.c_expression_literal(ast as AstExpressionLiteral);
            case "binary":
                return this.c_expression_binary(ast as AstExpressionBinary);
            case "unary":
                return this.c_expression_unary(ast as AstExpressionUnary);
            case "ternary":
                return this.c_expression_ternary(ast as AstExpressionTernary);
            case "functionCall":
                return this.c_expression_functionCall(ast as AstExpressionFunctionCall);
            case "variable":
                return this.c_expression_variable(ast as AstExpressionVariable);
            default:
                throw new Error(`Unsupported expression type: ${ast.type}`);
        }
    }

    c_expression_literal(ast: AstExpressionLiteral): string {
        return ast.value.toString();
    }

    c_expression_binary(ast: AstExpressionBinary): string {
        const left = this.c_expression(ast.lhs);
        const right = this.c_expression(ast.rhs);

        switch (ast.operator.type_id) {
            case TokenType.PLUS:
                return `(${left} + ${right})`;
            case TokenType.MINUS:
                return `(${left} - ${right})`;
            case TokenType.ASTERISK:
                return `(${left} * ${right})`;
            case TokenType.SLASH:
                return `(${left} / ${right})`;
            default:
                throw new Error(`Unsupported binary operator: ${ast.operator}`);
        }
    }

    c_expression_unary(ast: AstExpressionUnary): string {
        const operand = this.c_expression(ast.operand);

        switch (ast.operator) {
            case "-":
                return `(-${operand})`;
            default:
                throw new Error(`Unsupported unary operator: ${ast.operator}`);
        }
    }

    c_expression_ternary(ast: AstExpressionTernary): string {
        const clause = this.c_expression(ast.clause);
        const truePath = this.c_expression(ast.true_path);
        const falsePath = this.c_expression(ast.false_path);

        return `(${clause} ? ${truePath} : ${falsePath})`;
    }

    c_expression_functionCall(ast: AstExpressionFunctionCall): string {
        const args = ast.args.map((arg: AstExpression) => this.c_expression(arg)).join(", ");

        return `${ast.functionName}(${args})`;
    }

    c_expression_variable(ast: AstExpressionVariable): string {
        return ast.name;
    }

    c_statement_return(stmt: AstStatementReturn): string {
        if (stmt.value.type === "expression_literal" && (stmt.value as AstExpression).type === "void") return "return;\n";
        else return "return " + this.c_expression(stmt.value) + ";\n";
    }

    c_statement(stmt: AstStatement): string {
        if (stmt.type === "return") {
            return this.c_statement_return(stmt as AstStatementReturn);
        }

        return "";
    }

    c_body(ast: AstBody): string {
        let c: string = "";

        for (const stmt of ast.stmts) {
            c += this.c_statement(stmt);
        }

        return c;
    }
};
