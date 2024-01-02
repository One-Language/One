import { TokenType, identifiers, isNumber, isIdentifierBegin, isIdentifier, Token, TokenLocation } from './token';

export class Lexer {
    tokens: Token[];
    index: number;

    state: {
        prev_column: number;

        start_pos: number;
        start_line: number;
        start_column: number;

        pos: number;
        line: number;
        column: number;
    } = {
        prev_column: 0,

        start_pos: 0,
        start_line: 1,
        start_column: 0,

        pos: 0,
        line: 1,
        column: 0,
    };

    private readString(input: string): Token {
        let i = this.state.pos + 1;
        while (i < input.length && input[i] !== '"') i++;
        
        if (i === input.length) {
            this.state.pos = i;
            this.state.line = this.state.start_line;
            this.state.column = this.state.start_column;
            return new Token(
                new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
                new TokenLocation(this.state.line, this.state.column, this.state.pos),
                TokenType.ERROR,
                input.substring(this.state.start_pos, this.state.pos),
                null,
                "Unterminated string"
            );
        }
    
        const lexeme = input.substring(this.state.pos, i + 1);
        const value = lexeme.substring(1, lexeme.length - 1);

        this.state.pos = i;
        this.state.line = this.state.start_line;
        this.state.column = this.state.start_column;
        return new Token(
            new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
            new TokenLocation(this.state.line, this.state.column, this.state.pos),
            TokenType.STRING,
            lexeme,
            value
        );
    }

    private readNumber(input: string): Token {
        let i: number = this.state.pos;
        let tmp: string = '';
        let foundE: boolean = false;
        
        while (i < input.length && isNumber(input[i])) {
            tmp += input[i];
            i++;
        }
    
        if (tmp.length === 0) {
            tmp += '0';
        }
    
        if (i < input.length && input[i] === '.') {
            tmp += input[i];
        }
    
        if (i < input.length && (input[i] === 'e' || input[i] === 'E')) {
            if (foundE) {
                this.state.pos = i;
                this.state.line = this.state.start_line;
                this.state.column = this.state.start_column;
                return new Token(
                    new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
                    new TokenLocation(this.state.line, this.state.column, this.state.pos),
                    TokenType.ERROR,
                    input.substring(this.state.start_pos, this.state.pos),
                    null,
                    "Invalid number format: Multiple 'e' characters"
                );
            }

            foundE = true;
        }
    
        const tokenType = tmp.includes('.') || foundE
            ? TokenType.FLOAT
            : TokenType.INT;
        
        this.state.pos = i;
        this.state.line = this.state.start_line;
        this.state.column = this.state.start_column;
        return new Token(
            new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
            new TokenLocation(this.state.line, this.state.column, this.state.pos),
            tokenType,
            tmp
        );
    }

    private readIdentifier(input: string): Token {
        let i: number = this.state.pos;
        let lexeme: string = '';
    
        while (i < input.length && isIdentifier(input[i])) {
            lexeme += input[i];
            i++;
        }
    
        const tokenType = identifiers.get(lexeme) || TokenType.IDENT;

        this.state.pos = i;
        this.state.line = this.state.start_line;
        this.state.column = this.state.start_column;
        return new Token(
            new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
            new TokenLocation(this.state.line, this.state.column, this.state.pos),
            tokenType,
            lexeme
        );
    }
    
    constructor(input: string) {
        this.tokens = [];
        this.index = 0;

        while (this.state.pos < input.length) {
            // Remove whitespace
            while ((this.state.pos < input.length) && ((input[this.state.pos] === " ") || (input[this.state.pos] === "\t"))) this.state.pos++;
            
            this.state.column = this.state.pos - this.state.prev_column;
            this.state.start_pos = this.state.pos;
            this.state.start_line = this.state.line;
            this.state.start_column = this.state.column;

            switch (input[this.state.pos]) {
                case '+': {
                    const token = new Token(
                        new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
                        new TokenLocation(this.state.line, this.state.column, this.state.pos),
                        TokenType.PLUS,
                        '+'
                    );
                    this.tokens.push(token);
                    this.state.pos++;
                } break;

                case '-': {
                    const token = new Token(
                        new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
                        new TokenLocation(this.state.line, this.state.column, this.state.pos),
                        TokenType.MINUS,
                        '-'
                    );
                    this.tokens.push(token);
                    this.state.pos++;
                } break;

                case '*': {
                    const token = new Token(
                        new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
                        new TokenLocation(this.state.line, this.state.column, this.state.pos),
                        TokenType.ASTERISK,
                        '*'
                    );
                    this.tokens.push(token);
                    this.state.pos++;
                } break;

                case '/': {
                    const token = new Token(
                        new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
                        new TokenLocation(this.state.line, this.state.column, this.state.pos),
                        TokenType.SLASH,
                        '/'
                    );
                    this.tokens.push(token);
                    this.state.pos++;
                } break;

                case '(': {
                    const token = new Token(
                        new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
                        new TokenLocation(this.state.line, this.state.column, this.state.pos),
                        TokenType.LPAREN,
                        '('
                    );
                    this.tokens.push(token);
                    this.state.pos++;
                } break;

                case ')': {
                    const token = new Token(
                        new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
                        new TokenLocation(this.state.line, this.state.column, this.state.pos),
                        TokenType.RPAREN,
                        ')'
                    );
                    this.tokens.push(token);
                    this.state.pos++;
                } break;

                case '{': {
                    const token = new Token(
                        new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
                        new TokenLocation(this.state.line, this.state.column, this.state.pos),
                        TokenType.LBRACE,
                        '{'
                    );
                    this.tokens.push(token);
                    this.state.pos++;
                } break;

                case '}': {
                    const token = new Token(
                        new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
                        new TokenLocation(this.state.line, this.state.column, this.state.pos),
                        TokenType.RBRACE,
                        '}'
                    );
                    this.tokens.push(token);
                    this.state.pos++;
                } break;

                case '[': {
                    const token = new Token(
                        new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
                        new TokenLocation(this.state.line, this.state.column, this.state.pos),
                        TokenType.LBRACKET,
                        '['
                    );
                    this.tokens.push(token);
                    this.state.pos++;
                } break;

                case ']': {
                    const token = new Token(
                        new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
                        new TokenLocation(this.state.line, this.state.column, this.state.pos),
                        TokenType.RBRACKET,
                        ']'
                    );
                    this.tokens.push(token);
                    this.state.pos++;
                } break;

                case ',': {
                    const token = new Token(
                        new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
                        new TokenLocation(this.state.line, this.state.column, this.state.pos),
                        TokenType.COMMA,
                        ','
                    );
                    this.tokens.push(token);
                    this.state.pos++;
                } break;

                case ';': {
                    const token = new Token(
                        new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
                        new TokenLocation(this.state.line, this.state.column, this.state.pos),
                        TokenType.SEMICOLON,
                        ';'
                    );
                    this.tokens.push(token);
                    this.state.pos++;
                } break;

                case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': {
                    const token = this.readNumber(input);
                    this.tokens.push(token);
                } break;

                case '"': {
                    const token = this.readString(input);
                    this.tokens.push(token);
                } break;

                case '\n': {
                    this.state.line++;
                    this.state.prev_column = this.state.column;
                    this.state.column = 0;
                    this.state.pos++;
                } break;

                case '\r': case '\a': case '\b': case '\f': case '\v': {
                    this.state.pos++;
                } break;

                default: {
                    if (isIdentifierBegin(input[this.state.pos])) {
                        const token = this.readIdentifier(input);
                        this.tokens.push(token);
                    } else {
                        const errorMessage = `${input[this.state.pos]} is not a valid character`;
                        const token = new Token(
                            new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
                            new TokenLocation(this.state.line, this.state.column, this.state.pos),
                            TokenType.ERROR,
                            input[this.state.pos],
                            errorMessage
                        );
                        this.tokens.push(token);
                        this.state.pos++;
                    }
                } break;
            }
        }

        const token = new Token(
            new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
            new TokenLocation(this.state.line, this.state.column, this.state.pos),
            TokenType.EOF,
            ''
        );
        this.tokens.push(token);
    }

    pop(): Token {
        const result = this.tokens[this.index];
        this.index += 1;
        return result;
    }

    peek(lookingFor: TokenType): boolean {
        return (this.tokens[this.index].type_id == lookingFor);
    }

    front(): TokenType {
        return this.tokens[this.index].type_id;
    }
}
