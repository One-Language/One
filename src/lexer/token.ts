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
    ASTERISK = 'ASTERISK', // *
    SLASH = 'SLASH', // /
    LT = 'LT', // <
    GT = 'GT', // >
    EQ = 'EQ', // ==
    NOT_EQ = 'NOT_EQ', // !=
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

export interface Ast {};

export class Token implements Ast {
    type_id: TokenType;
    lexeme: string;
    error_message: string | null;
    value: string | null;

    constructor(type_id: TokenType, lexeme: string, value: string | null = null, errorMessage: string | null = null) {
        this.type_id = type_id;
        this.lexeme = lexeme;
        this.value = value;
        this.error_message = errorMessage;
    }
};
