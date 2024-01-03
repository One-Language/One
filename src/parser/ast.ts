import { Token, TokenType } from '../lexer/token';

export abstract class Ast {
    type: string = "ast";
};

export class MainAst {
    ast: Ast[] = [];
    
    push(ast: Ast) {
        this.ast.push(ast);
    }
};

export class AstBody implements Ast {
    type: string = "body";
    stmts: Ast[] = [];

    constructor(stmts: Ast[]) {
        this.stmts = stmts;
    }
};

export class AstStatementReturn implements Ast {
    type: string = "return";
    value: AstExpression;

    constructor(value: AstExpression) {
        this.value = value;
    }
};

export class AstStatement implements Ast {
    type: string;

    constructor(type: string) {
        this.type = type;
    }
};

export class AstFunctionArgument implements Ast {
    type: string = "function_argument";
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

export abstract class AstExpression implements Ast {
    type: string = "expression";
    // valuetype: string;
    // value: any;

    // constructor(valuetype: string, value: any) {
    //     this.valuetype = valuetype;
    //     this.value = value;
    // }
};

export class AstExpressionSub extends AstExpression {
    type: string = "expression_sub";
    expr: AstExpression;

    constructor(expr: AstExpression) {
        super();
        this.expr = expr;
    }
};

export class AstExpressionTernary extends AstExpression {
    clause: AstExpression;
    true_path: AstExpression;
    false_path: AstExpression;

    constructor(clause: AstExpression, true_path: AstExpression, false_path: AstExpression) {
        super();
        this.clause = clause;
        this.true_path = true_path;
        this.false_path = false_path;
    }
};

export class AstExpressionPostfix extends AstExpression {
    lhs: AstExpression;
    operator: Token;

    constructor(lhs: AstExpression, operator: Token) {
        super();
        this.lhs = lhs;
        this.operator = operator;
    }
};

export class AstExpressionPrefix extends AstExpression {
    type: string = "expression_prefix";
    operator: Token;
    rhs: AstExpression;

    constructor(operator: Token, rhs: AstExpression) {
        super();
        this.operator = operator;
        this.rhs = rhs;
    }
};

// An expression is anything that can be evaluated, A number literal is an expression.
export class AstExpressionLiteral extends AstExpression {
    type: string = "expression_literal";
    valuetype: string;
    value: any;

    constructor(valuetype: string, value: any) {
        super();
        this.value = value;
        this.valuetype = valuetype;
    }
};

export class AstExpressionBinary extends AstExpression {
    type: string = "expression_binary";
    lhs: AstExpression;
    operator: Token;
    rhs: AstExpression;

    constructor(lhs: AstExpression, operator: Token, rhs: AstExpression) {
        super();
        this.lhs = lhs;
        this.operator = operator;
        this.rhs = rhs;
    }
};

export class AstExpressionUnary extends AstExpression {
    type: string = "expression_unary";
    operator: Token;
    operand: AstExpression;

    constructor(operator: Token, operand: AstExpression) {
        super();
        this.operator = operator;
        this.operand = operand;
    }
};

export class AstExpressionFunctionCall extends AstExpression {
    type: string = "expression_function_call";
    functionName: string;
    args: AstExpression[];

    constructor(functionName: string, args: AstExpression[]) {
        super();
        this.functionName = functionName;
        this.args = args;
    }
};

export class AstExpressionVariable extends AstExpression {
    type: string = "expression_variable";
    name: string;

    constructor(name: string) {
        super();
        this.name = name;
    }
};
