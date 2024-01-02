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
    type: string;
    value: any;

    constructor(type: string, value: any) {
        this.type = type;
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
    type: string; // TODO
    name: string;

    constructor(type: string, name: string) {
        this.type = type;
        this.name = name;
    }
};

export class AstFunctionArgument implements Ast {
    type: string; // TODO
    name: string;

    constructor(type: string, name: string) {
        this.type = type;
        this.name = name;
    }
};

export class AstFunction implements Ast {
    name: string;
    args: AstFunctionArgument[];
    body: AstBody;

    constructor(name: string, args: AstFunctionArgument[], body: AstBody) {
        this.name = name;
        this.args = args;
        this.body = body;
    }
};
