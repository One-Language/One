import { Ast, AstBody, AstFunction, AstFunctionArgument, MainAst } from "../parser/ast";

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

    c_body(ast: AstBody): string {
        return "";
    }
};
