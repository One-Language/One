import { Lexer } from '../lexer/lexer';
import { Ast } from './ast';

export class Parser {
    ast: Ast | null = null;
    lexer: Lexer;

    constructor(lexer: Lexer) {
        this.lexer = lexer;
    }
    
    tree(): Ast | null {
        return this.ast;
    }
};
