import { Lexer } from '../lexer/lexer';
import { Token, TokenType } from '../lexer/token';
import { Ast, MainAst, AstFunction, AstStatement, AstFunctionArgument } from './ast';

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

    parseMainStatement() {
        const first_token = this.lexer.pop();
        if (first_token.type_id === TokenType.EOF) break;

        switch (first_token.type_id) {
            case TokenType.FN: {
                const ast: AstFunction | null = this.parseFunction();
                if (ast !== null) this.ast.push(ast);
            } break;

            default: {
                console.log(" TOKEN ", first_token.type_id);
            } break;
        }
    }

    parseStatement() {
        return new AstStatement(
            "1",
            "2",
        );
    }

    parseBody() {
        const open = this.lexer.match(TokenType.LBRACE);
        if (open.type_id === TokenType.ERROR) {
            const errorMessage = "Wrong token as function body.";
            this.errors.push(errorMessage);
            return null;
        }

        const stmts : Ast[] = [];
        while (! this.lexer.hasAny([TokenType.RBRACE, TokenType.EOF])) {
            const stmt: AstStatement | null = this.parseStatement();
            if (stmt === null) {
                const errorMessage = "Wrong token as statement.";
                this.errors.push(errorMessage);
                return null;
            }

            stmts.push(stmt);
        }

        const close = this.lexer.match(TokenType.RBRACE);
        if (close !== null && close.type_id === TokenType.ERROR) {
            const errorMessage = "Wrong token as function body.";
            this.errors.push(errorMessage);
            return null;
        }

        return new AstBody(
            stmts
        );
    }

    parseFunction() {
        const name = this.lexer.match(TokenType.IDENT);
        if (name.value === null) {
            const errorMessage = "Wrong token as function name.";
            this.errors.push(errorMessage);
            return null;
        }
        const args: AstFunctionArgument[] = [];

        if (this.lexer.skip(TokenType.LBRACE)) { // (
            if (! this.lexer.has(TokenType.RBRACE)) {
                console.log(this.parserFunctionArgument());
            }
            this.lexer.match(TokenType.RBRACE); // )
        }

        const stmts = Ast[] = this.parseBody();

        return new AstFunction(
            name.value,
            args,
            stmts,
        );
    }

    parse() {
        while (true) {
            this.parseMainStatement();
        }
    }
    
    tree(): MainAst {
        return this.ast;
    }
};
