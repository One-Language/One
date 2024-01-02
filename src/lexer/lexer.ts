import { TokenType, identifiers, isNumber, isIdentifierBegin, isIdentifier, Token } from './token';

export class Lexer {
    tokens: Token[];
    index: number;

    private readString(input: string, start_pos: number): Token {
        // match we need to have end string and not eof
        let i = start_pos + 1;
        while((i < input.length) && (input[i] !== '"')) i++;
        if (i === input.length) {
            throw new Error('Unterminated string');
        }
        i++;
        return new Token(TokenType.STRING, input.substring(start_pos, i) );
    }

    private readNumber(input: string, start_pos: number): Token {
        let i: number = start_pos;
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
            i++;
            while (i < input.length && isNumber(input[i])) {
                tmp += input[i];
                i++;
            }
        }
    
        if (i < input.length && (input[i] === 'e' || input[i] === 'E')) {
            if (foundE) {
                throw new Error("Invalid number format: Multiple 'e' characters");
            } else {
                foundE = true;
                tmp += 'e';
                i++;
                if (i < input.length && (input[i] === '+' || input[i] === '-')) {
                    tmp += input[i];
                    i++;
                }
                while (i < input.length && isNumber(input[i])) {
                    tmp += input[i];
                    i++;
                }
            }
        }
    
        const tokenType = tmp.includes('.') || foundE
            ? TokenType.FLOAT
            : TokenType.INT;
    
        return new Token(tokenType, tmp);
    }

    private readIdentifier(input: string, start_pos: number): Token {
        let i: number = start_pos;
        let lexeme: string = '';
        while (i < input.length && isIdentifier(input[i])) {
            lexeme += input[i];
            i++;
        }

        const tokenType = identifiers.get(lexeme) || TokenType.IDENT;

        return new Token(tokenType, lexeme);
    }

    constructor(input: string) {
        this.tokens = [];
        this.index = 0;

        let i = 0;

        while (i < input.length) {
            // Remove whitespace
            while ((i < input.length) && ((input[i] === " ") || (input[i] === "\t"))) i++;

            switch (input[i]) {
                case '+': {
                    this.tokens.push( new Token(TokenType.PLUS, '+') );
                    i++;
                } break;
                case '-': {
                    this.tokens.push( new Token(TokenType.MINUS, '-') );
                    i++;
                } break;
                case '*': {
                    this.tokens.push( new Token(TokenType.ASTERISK, '*') );
                    i++;
                } break;
                case '/': {
                    this.tokens.push( new Token(TokenType.SLASH, '/') );
                    i++;
                } break;
                case '(': {
                    this.tokens.push( new Token(TokenType.LPAREN, '(') );
                    i++;
                } break;
                case ')': {
                    this.tokens.push( new Token(TokenType.RPAREN, ')') );
                    i++;
                } break;
                case '{': {
                    this.tokens.push( new Token(TokenType.LBRACE, '{') );
                    i++;
                } break;
                case '}': {
                    this.tokens.push( new Token(TokenType.RBRACE, '}') );
                    i++;
                } break;
                case '[': {
                    this.tokens.push( new Token(TokenType.LBRACKET, '[') );
                    i++;
                } break;
                case ']': {
                    this.tokens.push( new Token(TokenType.RBRACKET, ']') );
                    i++;
                } break;
                case ',': {
                    this.tokens.push( new Token(TokenType.COMMA, ',') );
                    i++;
                } break;
                case ';': {
                    this.tokens.push( new Token(TokenType.SEMICOLON, ';') );
                    i++;
                } break;

                case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': {
                    try {
                        this.tokens.push(this.readNumber(input, i));
                        i += this.tokens[this.tokens.length - 1].lexeme.length;
                    } catch (e: any) {
                        this.tokens.push(new Token(TokenType.ERROR, input[i], e.message));
                    }
                } break;

                case '"': {
                    try {
                        this.tokens.push(this.readString(input, i));
                        i += this.tokens[this.tokens.length - 1].lexeme.length;
                    } catch (e: any) {
                        this.tokens.push(new Token(TokenType.ERROR, input[i], e.message));
                    }
                } break;

                // identifier & keywords
                default: {
                    if (isIdentifierBegin(input[i])) {
                        try {
                            this.tokens.push(this.readIdentifier(input, i));
                            i += this.tokens[this.tokens.length - 1].lexeme.length;
                        } catch (e: any) {
                            this.tokens.push(new Token(TokenType.ERROR, input[i], e.message));
                        }
                    } else {
                        this.tokens.push(new Token(TokenType.ERROR, input[i]));
                        i++;
                    }
                } break;
            }
        }

        this.tokens.push( new Token(TokenType.EOF, '') );
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
