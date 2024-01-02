import { TokenType, identifiers, isNumber, isIdentifierBegin, isIdentifier, Token, TokenLocation } from './token';

export class Lexer {
    input: string;
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

    private readString(): Token {
        // Opening "
        this.state.pos++;
        this.state.column++;

        while (this.state.pos < this.input.length && this.input[this.state.pos] !== '"') {
            this.state.pos++;

            if (this.input[this.state.pos] === "\n") this.state.column = 0;
            else this.state.column++;
        }
        
        if (this.state.pos === this.input.length) { // EOF
            const errorMessage = "Unterminated string";
            return this.generateToken(TokenType.ERROR, null, errorMessage);
        }

        // Closing "
        this.state.pos++;
        this.state.column++;
    
        const value = this.input.substring(this.state.start_pos + 1, this.state.pos - 1);
        return this.generateToken(TokenType.STRING, value);
    }

    private readNumber(): Token {
        let tmp: string = '';
        let foundE: boolean = false;
        let foundENoDigit: boolean = false;
        
        while (this.state.pos < this.input.length && isNumber(this.input[this.state.pos])) {
            tmp += this.input[this.state.pos];
            this.state.pos++;
            this.state.column++;
        }
    
        if (tmp.length === 0) {
            foundENoDigit = true;
            tmp += '0';
        }
    
        if (this.state.pos < this.input.length && this.input[this.state.pos] === '.') {
            tmp += this.input[this.state.pos];
            this.state.pos++;
            this.state.column++;

            if (foundENoDigit && this.state.pos < this.input.length && !isNumber(this.input[this.state.pos])) {
                const errorMessage = "This token is not a number it should be a DOT operator!";
                return this.generateToken(TokenType.ERROR, null, errorMessage);
            }

            while (this.state.pos < this.input.length) {
                if (isNumber(this.input[this.state.pos])) {
                    tmp += this.input[this.state.pos];
                    this.state.pos++;
                    this.state.column++;
                }
                else if (this.input[this.state.pos] === 'e' || this.input[this.state.pos] === 'E') {
                    this.state.pos++;
                    this.state.column++;
                    
                    if (foundE) {
                        const errorMessage = "Invalid number format: Multiple 'e' characters";
                        return this.generateToken(TokenType.ERROR, null, errorMessage);
                    }

                    foundE = true;
                }
            }
        }
    
        const tokenType = tmp.includes('.') || foundE
            ? TokenType.FLOAT
            : TokenType.INT;
        return this.generateToken(tokenType, tmp);
    }

    private readIdentifier(): Token {
        let tmp: string = '';
    
        while (this.state.pos < this.input.length && isIdentifier(this.input[this.state.pos])) {
            tmp += this.input[this.state.pos];
            this.state.pos++;
            this.state.column++;
        }
    
        const tokenType = identifiers.get(tmp) || TokenType.IDENT;
        return this.generateToken(tokenType, tmp);
    }

    private generateToken(token_id: TokenType, value: string | null, errorMessage: string | null = null): Token {
        const lexme = this.input.substr(this.state.start_pos, this.state.pos - this.state.start_pos);
        return new Token(
            new TokenLocation(this.state.start_line, this.state.start_column, this.state.start_pos),
            new TokenLocation(this.state.line, this.state.column, this.state.pos),
            token_id,
            value,
            errorMessage,
            lexme
        );
    }

    constructor(input: string) {
        this.input = input;
        this.tokens = [];
        this.index = 0;

        while (this.state.pos < this.input.length) {
            // Remove whitespace
            while ((this.state.pos < this.input.length) && ((this.input[this.state.pos] === " ") || (this.input[this.state.pos] === "\t"))) this.state.pos++;
            
            this.state.column = this.state.pos - this.state.prev_column;
            this.state.start_pos = this.state.pos;
            this.state.start_line = this.state.line;
            this.state.start_column = this.state.column;

            switch (this.input[this.state.pos]) {
                case '+': {
                    this.state.pos++;
                    this.state.column++;
                    const token = this.generateToken(TokenType.PLUS, '+');
                    this.tokens.push(token);
                } break;

                case '-': {
                    this.state.pos++;
                    this.state.column++;
                    const token = this.generateToken(TokenType.MINUS, '-');
                    this.tokens.push(token);
                } break;

                case '*': {
                    this.state.pos++;
                    this.state.column++;
                    const token = this.generateToken(TokenType.ASTERISK, '*');
                    this.tokens.push(token);
                } break;

                case '/': {
                    this.state.pos++;
                    this.state.column++;
                    const token = this.generateToken(TokenType.SLASH, '/');
                    this.tokens.push(token);
                } break;

                case '(': {
                    this.state.pos++;
                    this.state.column++;
                    const token = this.generateToken(TokenType.LPAREN, '(');
                    this.tokens.push(token);
                } break;

                case ')': {
                    this.state.pos++;
                    this.state.column++;
                    const token = this.generateToken(TokenType.RPAREN, ')');
                    this.tokens.push(token);
                } break;

                case '{': {
                    this.state.pos++;
                    this.state.column++;
                    const token = this.generateToken(TokenType.LBRACE, '{');
                    this.tokens.push(token);
                } break;

                case '}': {
                    this.state.pos++;
                    this.state.column++;
                    const token = this.generateToken(TokenType.RBRACE, '}');
                    this.tokens.push(token);
                } break;

                case '[': {
                    this.state.pos++;
                    this.state.column++;
                    const token = this.generateToken(TokenType.LBRACKET, '[');
                    this.tokens.push(token);
                } break;

                case ']': {
                    this.state.pos++;
                    this.state.column++;
                    const token = this.generateToken(TokenType.RBRACKET, ']');
                    this.tokens.push(token);
                } break;

                case ',': {
                    const token = this.generateToken(TokenType.COMMA, ',');
                    this.tokens.push(token);
                    this.state.pos++;
                } break;

                case ';': {
                    this.state.pos++;
                    this.state.column++;
                    const token = this.generateToken(TokenType.SEMICOLON, ';');
                    this.tokens.push(token);
                } break;

                case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': {
                    const token = this.readNumber();
                    this.tokens.push(token);
                } break;

                case '"': {
                    const token = this.readString();
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
                    this.state.column++;
                } break;

                default: {
                    if (isIdentifierBegin(this.input[this.state.pos])) {
                        const token = this.readIdentifier();
                        this.tokens.push(token);
                    } else {
                        this.state.pos++;
                        this.state.column++;

                        const errorMessage = `${this.input[this.state.pos]} is not a valid character`;
                        const token = this.generateToken(TokenType.ERROR, null, errorMessage);
                        this.tokens.push(token);
                    }
                } break;
            }
        }

        const token = this.generateToken(TokenType.EOF, null);
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
