import { Ast } from "./../parser/ast";

export const isNumber = (str: string): boolean => {
    return str >= '0' && str <= '9';
};

export const isIdentifierBegin = (str: string): boolean => {
    return (str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z') || str === '_';
};

export const isIdentifier = (str: string): boolean => {
    return isIdentifierBegin(str) || isNumber(str);
};

export enum TokenType {
    // special
    EOF = 'EOF',
    ERROR = 'ERROR',
    // debugs
    INLINE_COMMENT = 'INLINE_COMMENT',
    MULTILINE_COMMENT = 'MULTILINE_COMMENT',
    // keywords
    LET = 'LET',
    FN = 'FN',
    IF = 'IF',
    ELSE = 'ELSE',
    RETURN = 'RETURN',
    // literals
    INT = 'INT',
    FLOAT = 'FLOAT',
    STRING = 'STRING',
    TRUE = 'TRUE',
    FALSE = 'FALSE',
    // identifiers
    IDENT = 'IDENT',
    // operators
    ASSIGN = 'ASSIGN', // =
    PLUS = 'PLUS', // +
    MINUS = 'MINUS', // -
    BANG = 'BANG', // !
    QUESTION = 'QUESTION', // ?
    ASTERISK = 'ASTERISK', // *
    SLASH = 'SLASH', // /
    POW = 'POW', // ^
    LT = 'LT', // <
    LTE = 'LTE', // <=
    GT = 'GT', // >
    GTE = 'GTE', // >=
    EQ = 'EQ', // ==
    NEQ = 'NEQ', // !=
    // delimiters
    COMMA = 'COMMA', // ,
    SEMICOLON = 'SEMICOLON', // ;
    LPAREN = 'LPAREN', // (
    RPAREN = 'RPAREN', // )
    LBRACE = 'LBRACE', // {
    RBRACE = 'RBRACE', // }
    LBRACKET = 'LBRACKET', // [
    RBRACKET = 'RBRACKET', // ]
};

export const identifiers = new Map<string, TokenType>([
    ['let', TokenType.LET],
    ['fn', TokenType.FN],
    ['if', TokenType.IF],
    ['else', TokenType.ELSE],
    ['return', TokenType.RETURN],
    ['true', TokenType.TRUE],
    ['false', TokenType.FALSE],
]);

export class TokenLocation {
    line: number;
    column: number;
    pos: number;

    constructor(line: number, column: number, pos: number = -1) {
        this.line = line;
        this.column = column;
        this.pos = pos;
    }

    toString(): string {
        return `line ${this.line}, column ${this.column}`;
    }
};

export class Token {
    type_id: TokenType;
    error_message: string | null;
    value: string | null;

    start_location: TokenLocation;
    end_location: TokenLocation;

    lexme: string | null;

    constructor(start_location: TokenLocation, end_location: TokenLocation, type_id: TokenType, value: string | null = null, errorMessage: string | null = null, lexme: string | null = null) {
        this.type_id = type_id;

        this.value = value;

        this.error_message = errorMessage;

        this.start_location = start_location;
        this.end_location = end_location;

        this.lexme = lexme;
    }

    toString(): string {
        return `Token(type: ${this.type_id}, value: ${this.value}, error: ${this.error_message}, start: ${this.start_location}, end: ${this.end_location})`;
    }
};
