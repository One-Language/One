import { Ast, AstBody, AstExpression, AstFunction, AstFunctionArgument, AstStatement, AstStatementReturn, MainAst } from "../parser/ast";

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
        switch (ast.valuetype) {
            case "int": {
                return ast.value;
            } break;
            case "string": {
                return `"${ast.value}"`;
            } break;
            case "float": {
                return ast.value;
            } break;
        }
        return "";
    }

    c_statement_return(stmt: AstStatementReturn): string {
        if (stmt.value === null || stmt.value.valuetype === "void") return "return;\n";
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
