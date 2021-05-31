/**
 The One Programming Language

 File: token.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "token.h"
#include "lexer.h"

void token_init() {

}

// TODO: inline function
bool token_is_freespace(char c) {
    if (c == ' ')
        return true;
    else if (c == '\t')
        return true;
    return false;
}

// TODO: inline function
bool token_is_freeline(char c) {
    if (c == '\n')
        return true;
    else if (c == '\r')
        return true;
    return false;
}

bool token_is_line(char c) {
    if (c == '\n')
        return true;
    return false;
}

bool token_is_space(char c) {
    if (c == ' ')
        return true;
    return false;
}

bool token_is_free(char c) {
    return token_is_freeline(c) || token_is_freespace(c);
}

bool token_is_alphaasci(char c) {
    if (c >= 'a' && c <= 'z')
        return true;
    else if (c >= 'A' && c <= 'Z')
        return true;
    return false;
}

bool token_is_alpha(char c) {
    if (token_is_alphaasci(c))
        return true;
    else if (c == '_')
        return true;
    return false;
}

bool token_is_number(char c) {
    if (c >= '0' && c <= '9')
        return true;
    return false;
}

bool token_is_digit(char c) {
    if (token_is_number(c) == true)
        return true;
    else if (c == '.')
        return true;
    return false;
}

bool token_is_ident(char c) {
    if (token_is_alpha(c) == true) {
        return true;
    } else if (token_is_number(c) == true) {
        return true;
    }
    return false;
}

bool token_is_eof(char c) {
    // EOF is -1
    return (c == EOF || c == '\0') ? true : false;
}

bool tokenEOF(Lexer *lex) {
    return token_is_eof(*lex->source);
}

void tokenNextChar(Lexer *lex) {
    lex->source++;
}

void tokenPrevChar(Lexer *lex) {
    lex->source--;
}

Token *tokenNext(Lexer *lex) {
    Token *t = malloc(sizeof(Token));
    t->vstring = NULL;

    // skip the free space
    while (token_is_free(*lex->source) == true) {
        tokenNextChar(lex);
    }

    // end if it's EOF
    if (tokenEOF(lex) == true) {
        t->type = TOKEN_EOF;
        return t;
    }

        // single-line comment
        // multi-line comment
        // DIVIDE operator
    else if (*lex->source == '/') { // it's single-line comment or divide operator!
        tokenNextChar(lex);
        if (*lex->source == '/') { // it's single-line comment
            while (token_is_eof(*lex->source) == false && token_is_line(*lex->source) == false) {
                tokenNextChar(lex);
            }
            return tokenNext(lex);
        } else if (*lex->source == '*') { // it's multi-line comment
            // Going to next characters while looking for `*/`
            while (token_is_eof(*lex->source) == false) { // Going next while it's still not END of the source!
                char c1 = *lex->source; // get current char and store it at `c1`
                tokenNextChar(lex); // go to next char
                if (token_is_eof(*lex->source) == true) { // again check and make sure it's not END of the source!
                    // Error: EOF without complete close multi-line comment
                    // TODO: ErrorAppend(...)
                    break; // break loop and stop looking for `*/`.
                }

                char c2 = *lex->source; // get current token, it may be second part of `*/`
                if (c1 == '*' && c2 ==
                                 '/') { // if first char was * and second was /, so we have to close multi-line comment and stop this loop!
                    tokenNextChar(lex); // Skip the `/` character and go to next character
                    break; // END multi-line comment and looking loop!
                } else {
                    // Why we not need to go back to prevChar? Since we still not call the tokenNextChar function...
                    // If you write: tokenPrevChar(lex);, this will stop at a unlimit LOOP, so we not need to call this function, since we still not called `tokenNextChar(lex)` yet!
                    // continue;
                }
            }

            return tokenNext(lex);
        } else {
            t->type = TOKEN_OPERATOR_DIV;
            return t;
        }
    }

        // identifier
    else if (token_is_alpha(*lex->source) ==
             true) { // check if current char is a-z or A-Z or `_`, if it's so it's a user defined identifier or a compiler registered IDENTIFIER
        t->vstring = malloc(sizeof(char) * 200 +
                            1); // malloc and create a string, since we need to store and save identifier name at token struct.

        size_t length = 0;
        while (token_is_ident(*lex->source) == true) { // if current char is a-z OR A-Z or 0-9 or `_`
            t->vstring[length++] = *lex->source; // append and store current char at `->vstring`
            tokenNextChar(lex); // go to next char, and loop will repeat and going up!
        }
        t->vstring[length] = '\0'; // In C, we need to define end of the string, so it will be useful for future functionality with this string

        t->type = TOKEN_VALUE_IDENTIFIER; // defaultly a identifier is user-defined. We check at next line it's a registered compiler Keywords or no. so it's the default value.

        // A test to make sure identifier is COMPILER word registered or a user defined identifier
        // Check identifier is equal to compiler registered Words by filtereing to it's LENGTH.
        for (int i = 0; keywords[i].identifier != NULL; i++) { // loop to check all registerd Keywords
            if (length == keywords[i].length &&
                // check if user-defined identifier length is equal to current registered Keyword
                memcmp(t->vstring, keywords[i].identifier, length) ==
                0) { // check if user-defined identifier equal to current registered Keyword
                t->type = keywords[i].type; // set type of current token to
                break; // break and stop loop
            }
        }

        if (t->type !=
            TOKEN_VALUE_IDENTIFIER) { // if it's not a user-defined identifier, so we not need `vstring` value.
            free(t->vstring); // free char*
            t->vstring = NULL;
        }

        return t;
    }

        // number value
    else if (token_is_number(*lex->source) == true || *lex->source == '.') { // a number token start with [0-9] or '.'
        bool isFloat = false;
        size_t i = 0;

        // maximum length of a number is 100, i think it's enought for our work!
        t->vstring = malloc(sizeof(char) * 100 + 1);

        if (*lex->source == '.') { // it's dot character
            isFloat = true; // we set `isFloat` to true, so we will not accept any `.` character anymore.
            t->vstring[i++] = '0'; // put zero at first item of array (automaticly)

            // put '.' character at second item of array
            t->vstring[i++] = '.';// '.' equal to *lex->source;
        } else { // it's a number [0-9]
            t->vstring[i++] = *lex->source; // put first character at first item of array
        }

        tokenNextChar(lex); // go to next chat, remember we already have prev char at `digits` array.

        // Length if `digits` array maybe is 1 or 2.

        // check it's a HEX Number or no
        // Hex number format: '0' 'x' *****
        if (isFloat == true && t->vstring[0] == '0' && *lex->source ==
                                                   'x') { // We will accept a HEX Number, if we not has `.` character at before, and we has `0` at prev char and current char is `x`.
            // TODO: lex hex numbers!
        } else { // otherwise, it's not a HEX Number, so we except a number digits. maybe it's decimal or float.
            // Remember: Maybe current sutiation was already a float number, it's why we need to check `isFloat` value again.
            // Why? `.4` is equal to `0.4`

            // iterate character and accept [0-9] digits or
            while (token_is_number(*lex->source) == true ||
                   (isFloat == false && *lex->source ==
                                        '.')) { // or it's `.` character while we is not float number yet and we are in decimal state! (isFloat == false means we are in decimal state)
                // TODO: check length of number and validate OS maximum number digits
                // if(length > 100) { /*ErrorAppend(...)*/ }

                if (*lex->source == '.') { // if current char is `.` so we change `isFloat` to true..
                    isFloat = true; // set `isFloat` to true, remember it was `float` before.
                    t->vstring[i++] = '.'; // adding float point to queue char list!
                } else { // it's a digit, [0-9]
                    t->vstring[i++] = *lex->source; // add current number to queue char list!
                }
                tokenNextChar(lex); // go to next char, we need to iterate at this loop
            }
            t->vstring[i] = '\0'; // adding \0 to digits char array to set this DONE OF STRING!

            t->type = TOKEN_VALUE_NUMBER; // set type of current token
            return t;
        }
    }

        // Operator +
        // Operator ++
    else if (*lex->source == '+') { // if current char is starts with `+`
        tokenNextChar(lex);
        if (*lex->source == '+') { // So It's `++` token
            tokenNextChar(lex); // go to next char and skip second part of `++`
            t->type = TOKEN_OPERATOR_PLUSPLUS;
            return t;
        } else {
            t->type = TOKEN_OPERATOR_PLUS;
            return t;
        }
    }

        // Operator -
        // Operator --
    else if (*lex->source == '-') { // if current char is starts with `-`
        tokenNextChar(lex);
        if (*lex->source == '-') { // So It's `--` token
            tokenNextChar(lex); // go to next char and skip second part of `--`
            t->type = TOKEN_OPERATOR_MINUSMINUS;
            return t;
        } else {
            t->type = TOKEN_OPERATOR_MINUS;
            return t;
        }
    }

        // Operator *
        // Operator **
    else if (*lex->source == '*') { // if current char is starts with `*`
        tokenNextChar(lex);
        if (*lex->source == '*') { // So It's `**` token
            tokenNextChar(lex); // go to next char and skip second part of `**`
            t->type = TOKEN_OPERATOR_POW;
            return t;
        } else {
            t->type = TOKEN_OPERATOR_MUL;
            return t;
        }
    }

        // Operator /
        // Operator //
    else if (*lex->source == '/') { // if current char is starts with `/`
        tokenNextChar(lex);
        if (*lex->source == '/') { // So It's `//` token
            tokenNextChar(lex); // go to next char and skip second part of `//`
            t->type = TOKEN_OPERATOR_DIVINT;
            return t;
        } else { // it's `/` token
            t->type = TOKEN_OPERATOR_DIV;
            return t;
        }
    }

        // operator section {
    else if(*lex->source == '{') {
        t->type = TOKEN_SECTION_OPEN;
        tokenNextChar(lex); // go to next character
        return t;
    }

        // operator section }
    else if(*lex->source == '}') {
        t->type = TOKEN_SECTION_CLOSE;
        tokenNextChar(lex); // go to next character
        return t;
    }

        // operator bracket (
    else if(*lex->source == '(') {
        t->type = TOKEN_BRACKET_OPEN;
        tokenNextChar(lex); // go to next character
        return t;
    }

        // operator bracket )
    else if(*lex->source == ')') {
        t->type = TOKEN_BRACKET_CLOSE;
        tokenNextChar(lex); // go to next character
        return t;
    }

        // operator square [
    else if(*lex->source == '[') {
        t->type = TOKEN_SQUARE_OPEN;
        tokenNextChar(lex); // go to next character
        return t;
    }

        // operator square ]
    else if(*lex->source == ']') {
        t->type = TOKEN_SQUARE_CLOSE;
        tokenNextChar(lex); // go to next character
        return t;
    }

        // operator ;
    else if(*lex->source == ';') {
        t->type = TOKEN_OPERATOR_SEMICOLON;
        tokenNextChar(lex); // go to next character
        return t;
    }


        // operator ,
    else if(*lex->source == ',') {
        t->type = TOKEN_OPERATOR_VIRGOOL;
        tokenNextChar(lex); // go to next character
        return t;
    }
        // operator :
        // operator ::
    else if (*lex->source == ':') { // if current char is starts with `:`
        tokenNextChar(lex);
        if (*lex->source == ':') { // So It's `::` token
            tokenNextChar(lex); // go to next char and skip second part of `::`
            t->type = TOKEN_OPERATOR_COLONCOLON;
            return t;
        } else { // it's : token
            t->type = TOKEN_OPERATOR_COLONCOLON;
            return t;
        }
    }

        // operator  .
        // operator ..
        // operator ...
    else if(*lex->source == '.') { // it's . or .. or ... token
        tokenNextChar(lex); // go to next character
        if(*lex->source == '.') { // maybe it's .. or ...
            tokenNextChar(lex); // go to next character
            if(*lex->source == '.') { // it's ...
                t->type = TOKEN_OPERATOR_DOTDOTDOT;
                tokenNextChar(lex); // go to next character
                return t;
            } else { // it's ..
                t->type = TOKEN_OPERATOR_DOTDOT;
                return t;
            }
        } else { // it's . token
            t->type = TOKEN_OPERATOR_DOT;
            return t;
        }
    }


        // operator  ==
        // operator ==
        // operator ===
        // TODO: operator +=
        // TODO: operator -=
        // TODO: operator *=
        // TODO: operator /=
        // TODO: operator **=
        // TODO: operator |=
    else if(*lex->source == '=') { // it's = or == or === token
        tokenNextChar(lex); // go to next character
        if(*lex->source == '=') { // maybe it's == or ===
            tokenNextChar(lex); // go to next character
            if(*lex->source == '=') { // it's ===
                t->type = TOKEN_OPERATOR_EQUALEQUALEQUAL;
                tokenNextChar(lex); // go to next character
                return t;
            } else { // it's ==
                t->type = TOKEN_OPERATOR_EQUALEQUAL;
                return t;
            }
        } else { // it's = token
            t->type = TOKEN_OPERATOR_EQUAL;
            return t;
        }
    }

    // string
    else if(*lex->source == '\"') { // it's first character of string block-value
        tokenNextChar(lex); // go to next char of the source
        size_t i=0;
        t->vstring = malloc(sizeof(char) * 1024); // TODO: we set max 1024 size, but we have to realloc this size at next steps!
        while (token_is_eof(*lex->source) == false && *lex->source != '\"') {
            t->vstring[i++] = *lex->source;
            tokenNextChar(lex); // skip current character and go to next char of the source
        }
        if(*lex->source == '\"') { // we except " character to know this string finished.
            tokenNextChar(lex); // skip current character and go to next char of the source
            t->vstring[i] = '\0';
            t->type = TOKEN_VALUE_STRING;
            return t;
        } else {
            // TODO: raise a error, since maybe user forget to finish a string and we face to EOF of the source!
            t->type = TOKEN_UNKNOWM;
            return t;
        }
    }

    // Otherwise: unknowm token
    t->type = TOKEN_UNKNOWM;
    return t;
}

char *tokenName(TokenType type) {
    switch (type) {
        case TOKEN_EOF:
            return "EOF";

        case TOKEN_VALUE_NUMBER:
            return "VALUE_NUMBER";
        case TOKEN_VALUE_STRING:
            return "VALUE_STRING";
        case TOKEN_VALUE_BOOL:
            return "VALUE_BOOL";

        case TOKEN_IF:
            return "IF";
        case TOKEN_ELSE:
            return "ELSE";
        case TOKEN_DO:
            return "DO";
        case TOKEN_WHILE:
            return "WHILE";
        case TOKEN_FOR:
            return "FOR";
        case TOKEN_SWTICH:
            return "SWITCH";

        case TOKEN_BREAK:
            return "BREAK";
        case TOKEN_CONTINUE:
            return "CONTINUE;";
        case TOKEN_PACKAGE:
            return "PACKAGE";
        case TOKEN_IMPORT:
            return "IMPORT";

        case TOKEN_IN:
            return "IN";
        case TOKEN_AS:
            return "AS";
        case TOKEN_IS:
            return "IS";

        case TOKEN_NULL:
            return "NULL";

        case TOKEN_RETURN:
            return "RETURN";
        case TOKEN_STATIC:
            return "STATIC";

        case TOKEN_THIS:
            return "THIS";

        case TOKEN_SUPER:
            return "SUPER";

        case TOKEN_FALSE:
            return "FALSE";

        case TOKEN_TRUE:
            return "TRUE";

        case TOKEN_VALUE_IDENTIFIER:
            return "IDENTIFIER";

        case TOKEN_OPERATOR_PLUS:
            return "OPERATOR_PLUS";
        case TOKEN_OPERATOR_PLUSPLUS:
            return "OPERATOR_PLUSPLUS";

        case TOKEN_OPERATOR_MINUS:
            return "OPERATOR_MINUS";
        case TOKEN_OPERATOR_MINUSMINUS:
            return "OPERATOR_MINUSMINUS";

        case TOKEN_OPERATOR_MUL:
            return "OPERATOR_MUL";
        case TOKEN_OPERATOR_POW:
            return "OPERATOR_POW";

        case TOKEN_OPERATOR_DIV:
            return "OPERATOR_DIV";
        case TOKEN_OPERATOR_DIVINT:
            return "OPERATOR_DIVINT";

        case TOKEN_OPERATOR_EQUAL:
            return "OPERATOR_EQUAL";
        case TOKEN_OPERATOR_EQUALEQUAL:
            return "OPERATOR_EQUAL";
        case TOKEN_OPERATOR_EQUALEQUALEQUAL:
            return "OPERATOR_EQUAL";

        case TOKEN_SECTION_OPEN:
            return "SECTION_OPEN";
        case TOKEN_SECTION_CLOSE:
            return "SECTION_CLOSE";

        case TOKEN_BRACKET_OPEN:
            return "BRACKET_OPEN";
        case TOKEN_BRACKET_CLOSE:
            return "BRACKET_CLOSE";

            // data types
        case TOKEN_TYPE_I8:
            return "TYPE_I8";
        case TOKEN_TYPE_I16:
            return "TYPE_I16";
        case TOKEN_TYPE_I32:
            return "TYPE_I32";
        case TOKEN_TYPE_I64:
            return "TYPE_I64";
        case TOKEN_TYPE_I128:
            return "TYPE_I128";

        case TOKEN_TYPE_U8:
            return "TYPE_U8";
        case TOKEN_TYPE_U16:
            return "TYPE_U16";
        case TOKEN_TYPE_U32:
            return "TYPE_U32";
        case TOKEN_TYPE_U64:
            return "TYPE_U64";
        case TOKEN_TYPE_U128:
            return "TYPE_U128";

        case TOKEN_TYPE_F32:
            return "TYPE_F32";
        case TOKEN_TYPE_F64:
            return "TYPE_F64";
        case TOKEN_TYPE_BOOL:
            return "TYPE_BOOL";
        case TOKEN_TYPE_STRING:
            return "TYPE_STRING";
        case TOKEN_TYPE_CHAR:
            return "TYPE_CHAR";

        case TOKEN_OPERATOR_BIT_AND:
            return "OPERATOR_BIT_AND";
        case TOKEN_OPERATOR_AND:
            return "OPERATOR_AND";

        case TOKEN_OPERATOR_BIT_OR:
            return "OPERATOR_BIT_OR";
        case TOKEN_OPERATOR_OR:
            return "OPERATOR_OR";

        case TOKEN_OPERATOR_DOT:
            return "DOT";
        case TOKEN_OPERATOR_DOTDOT:
            return "DOTDOT";
        case TOKEN_OPERATOR_DOTDOTDOT:
            return "DOTDOTDOT";

        case TOKEN_OPERATOR_COLON:
            return "OPERATOR_COLON";
        case TOKEN_OPERATOR_COLONCOLON:
            return "OPERATOR_COLONCOLON";
        case TOKEN_OPERATOR_SEMICOLON:
            return "OPERATOR_SEMICOLON";
        case TOKEN_OPERATOR_VIRGOOL:
            return "OPERATOR_VIRGOOL";

        case TOKEN_SQUARE_OPEN:
            return "SQUARE_OPEN";
        case TOKEN_SQUARE_CLOSE:
            return "SQUARE_CLOSE";

        case TOKEN_PRINT:
            return "PRINT";
        case TOKEN_PRINTNL:
            return "PRINTNL";
        case TOKEN_PRINTDB:
            return "PRINTDB";
        case TOKEN_PRINTNLDB:
            return "PRINTNLDB";

        case TOKEN_UNKNOWM:
            return "UNKNOWM";
        default:
            return "UNKNOWM";
    }
}