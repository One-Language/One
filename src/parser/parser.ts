import { Lexer } from '../lexer/lexer';
import { Token, TokenType } from '../lexer/token';
import { Ast, MainAst, AstStatementReturn, AstExpression, AstBody, AstFunction, AstStatement, AstFunctionArgument } from './ast';

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

        if (type.value === null || name.value === null) {
            const errorMessage = "Wrong token as type/name of function argument.";
            this.errors.push(errorMessage);
            return null;
        }

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

    parseExpression() {
        if (this.lexer.has(TokenType.INT)) {
            const expr = this.lexer.match(TokenType.INT);
            return new AstExpression(
                "int",
                expr.value,
            );
        }
        else if (this.lexer.skip(TokenType.FLOAT)) {
            const expr = this.lexer.match(TokenType.FLOAT);
            return new AstExpression(
                "float",
                expr.value,
            );
        }
        else if (this.lexer.has(TokenType.STRING)) {
            const expr = this.lexer.match(TokenType.STRING);
            return new AstExpression(
                "string",
                expr.value,
            );
        }
        else if (this.lexer.has(TokenType.IDENT)) {
            const expr = this.lexer.match(TokenType.IDENT);
            return new AstExpression(
                "ident",
                expr.value,
            );
        }

        return null;
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
                this.errors.push("Wrong token as expression.");
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

        if (this.lexer.skip(TokenType.LPAREN)) { // (
            if (! this.lexer.has(TokenType.RPAREN)) {
                console.log(this.parserFunctionArgument());
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
