import { Token, TokenType } from '../lexer/token';

export abstract class Ast {}

export class MainAst {
    ast: Ast[] = [];
    
    push(ast: Ast) {
        this.ast.push(ast);
    }
};

export class AstBody implements Ast {
    stmts: Ast[] = [];

    constructor(stmts: Ast[]) {
        this.stmts = stmts;
    }
};

export class AstExpression implements Ast {
    type: string = "expression";
    valuetype: string;
    value: any;

    constructor(valuetype: string, value: any) {
        this.valuetype = valuetype;
        this.value = value;
    }
}

export class AstStatementReturn implements Ast {
    type: string = "return";
    value: AstExpression;

    constructor(value: AstExpression) {
        this.value = value;
    }
}

export class AstStatement implements Ast {
    type: string;

    constructor(type: string) {
        this.type = type;
    }
};

export class AstFunctionArgument implements Ast {
    type: string = "function";
    datatype: string; // TODO
    name: string;

    constructor(datatype: string, name: string) {
        this.datatype = datatype;
        this.name = name;
    }
};

export class AstFunction implements Ast {
    type: string = "function";
    name: string;
    args: AstFunctionArgument[];
    body: AstBody;

    constructor(name: string, args: AstFunctionArgument[], body: AstBody) {
        this.name = name;
        this.args = args;
        this.body = body;
    }
};
