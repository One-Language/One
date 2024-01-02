import { Lexer } from '../lexer/lexer';
import { Token, TokenType } from '../lexer/token';
import { Ast, MainAst, AstStatementReturn, AstExpression, AstBody, AstFunction, AstStatement, AstFunctionArgument } from './ast';

interface binding_power { left_power: number; right_power: number; }

export class Parser {
    ast: MainAst = new MainAst();
    lexer: Lexer;
    errors: string[] = [];

    constructor(lexer: Lexer) {
        this.lexer = lexer;
        this.parse();
    }

    // match(lookingFor: TokenType): Token {
    //     const token: Token = this.lexer.match(lookingFor);
    //     if (token.type_id === TokenType.ERROR) {
    //         this.errors.push(token.error_message ?? "Error in match");
    //     }
    //     return token;
    // }

    parserFunctionArgument() {
        const type = this.lexer.match(TokenType.IDENT);
        const name = this.lexer.match(TokenType.IDENT);

        if (type.error_message !== null) {
            this.errors.push(type.error_message);
            return null;
        }
        else if (name.error_message !== null) {
            this.errors.push(name.error_message);
            return null;
        }

        if (type.value === null) return null;
        if (name.value === null) return null;

        return new AstFunctionArgument(
            type.value,
            name.value
        );
    }

    parseMainStatement(): Ast | null | undefined {
        const first_token = this.lexer.pop();
        if (first_token.type_id === TokenType.EOF) return undefined;

        switch (first_token.type_id) {
            case TokenType.FN: {
                const ast: AstFunction | null = this.parseFunction();
                return ast;
            } break;

            default: {
                console.log(" TOKEN ", first_token.type_id);
            } break;
        }

        return null;
    }
    
    prefix_bp_lookup(whichOperator: TokenType): number {
        switch(whichOperator) {
            case TokenType.PLUS: return 300;
            case TokenType.MINUS: return 300;
            default: return 0;
        }
    }

    // *** Helper Functions to manage binding powers ***
    LeftAssociative(priority: number): binding_power {
        return { left_power: (priority - 1), right_power: priority };
    }

    RightAssociative(priority: number): binding_power {
        return { left_power: (priority + 1), right_power: priority };
    }
 
    // Look up the left and right binding power of a given infix or postfix operator.
    bp_lookup(whichOperator: TokenType): binding_power {
        const no_binding_power: binding_power = {left_power: 0, right_power: 0};

        switch (whichOperator) {
            case TokenType.PLUS: return this.LeftAssociative(100);
            case TokenType.MINUS: return this.LeftAssociative(100);
            case TokenType.ASTERISK: return this.LeftAssociative(200);
            case TokenType.SLASH: return this.LeftAssociative(200);
            case TokenType.POW: return this.RightAssociative(99);
            case TokenType.QUESTION: return this.RightAssociative(1000);

            case TokenType.GT: return this.LeftAssociative(50);
            case TokenType.GTE: return this.LeftAssociative(50);
            case TokenType.LT: return this.LeftAssociative(50);
            case TokenType.LTE: return this.LeftAssociative(50);
            case TokenType.EQ: return this.LeftAssociative(50);
            case TokenType.NEQ: return this.LeftAssociative(50);

            // --- Postfix --- (Always Right Associative)
            case TokenType.BANG: return this.RightAssociative(400);
            // Note: Postfix operators are always RightAssociative

            default: return no_binding_power;
        }
    }

    parseExpression(binding_power_to_my_right: number = 0): AstExpression | null {
        let result: AstExpression | null = null;
    
        if (this.lexer.has(TokenType.INT) || this.lexer.has(TokenType.FLOAT)) {
            result = this.Number_Literal();
        }
        else if (this.lexer.has(TokenType.LPAREN)) {
            result = this.Sub_Expression();
        }
        else if (this.lexer.has(TokenType.PLUS) || this.lexer.has(TokenType.MINUS)) {
            result = new Prefix_Expression(this.prefix_bp_lookup(this.lexer.front()));
        }   
        
        if (result === null) {
            return null; // We should always have either a LHS or Prefix Operator at this point.
        }

        while(binding_power_to_my_right < this.bp_lookup(this.lexer.front()).left_power ) {
            if (this.lexer.has(TokenType.BANG)) {
                result = this.Postfix_Expression(result as AstExpression);
            }
            else if (this.lexer.has(TokenType.QUESTION)) {
                result = this.Ternary_Expression(result as AstExpression)
            }
            else {
                result = this.Binary_Expression(result as AstExpression, this.bp_lookup(this.lexer.front()).right_power);
            }
        }
    
        return result;
    }

    parseStatement() {
        if (this.lexer.has(TokenType.RETURN)) {
            this.lexer.skip(TokenType.RETURN);

            if (this.lexer.skip(TokenType.SEMICOLON)) {
                return new AstStatementReturn(
                    new AstExpression(
                        "void",
                        null,
                    ),
                );
            }

            const expr: AstExpression | null = this.parseExpression();
            if (expr === null) {
                this.errors.push("Wrong token as AstExpression.");
                return null;
            }

            return new AstStatementReturn(
                expr,
            );
        }

        return null;
    }

    parseBody() {
        const open = this.lexer.match(TokenType.LBRACE);
        if (open.type_id === TokenType.ERROR && open.error_message !== null) {
            this.errors.push(open.error_message);
            return null;
        }

        const stmts : Ast[] = [];
        while (true) {
            if (this.lexer.has(TokenType.RBRACE)) break;
            if (this.lexer.has(TokenType.EOF)) break;

            const stmt: Ast | null = this.parseStatement();
            if (stmt === null) {
                const errorMessage = "Wrong token as statement.";
                this.errors.push(errorMessage);
                return null;
            }
            stmts.push(stmt);
        }

        const close = this.lexer.match(TokenType.RBRACE);
        if (close.type_id === TokenType.ERROR && close.error_message !== null) {
            this.errors.push(close.error_message);
            return null;
        }

        return new AstBody(
            stmts,
        );
    }

    parseFunction() {
        const name = this.lexer.match(TokenType.IDENT);
        if (name.error_message !== null) {
            this.errors.push(name.error_message);
            return null;
        }
        if (name.value === null) return null;

        const args: AstFunctionArgument[] = [];
    
        if (this.lexer.skip(TokenType.LPAREN) !== null) { // (
            while (!this.lexer.has(TokenType.RPAREN)) {
                const arg = this.parserFunctionArgument();
                if (arg === null) {
                    const errorMessage = "Wrong token as function argument.";
                    this.errors.push(errorMessage);
                    return null;
                }
                args.push(arg);
                if (!this.lexer.has(TokenType.RPAREN) && !this.lexer.skip(TokenType.COMMA)) {
                    const errorMessage = "Expected comma or closing parenthesis in function arguments.";
                    this.errors.push(errorMessage);
                    return null;
                }
            }
            this.lexer.match(TokenType.RPAREN); // )
        }
    
        const body: AstBody | null = this.parseBody();
        if (body === null) {
            const errorMessage = "Wrong token as function body.";
            this.errors.push(errorMessage);
            return null;
        }

        return new AstFunction(
            name.value,
            args,
            body,
        );
    }

    parse() {
        while (true) {
            const ast: Ast | null | undefined = this.parseMainStatement();
            if (ast === undefined) break; // EOF
            else if (ast !== null) this.ast.push(ast);
        }
    }
    
    tree(): MainAst {
        return this.ast;
    }
};
