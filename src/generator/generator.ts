import { Ast } from "../parser/ast";

export class Generator {
    ast: Ast;

    libraries: string[] = [
        "#include <stdio.h>",
        "#include <stdlib.h>",
        "#include <string.h>",
        "#include <math.h>",
    ];

    constructor(ast: Ast) {
        this.ast = ast;
    }

    c(): string {
        let c: string = "";

        c += this.libraries.join("\n") + "\n\n";

        c += "int main() {\n";
        c += this.c_body(this.ast);
        c += "}";

        return c;
    }

    c_body(ast: Ast): string {
        return "";
    }
};
