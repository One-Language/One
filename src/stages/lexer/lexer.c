//
// Created by Max on 9/4/2022.
//

#include "lexer.h"

Lexer* lexer_init(char* source)
{
    Lexer* lexer = malloc(sizeof(Lexer));
    lexer->source = source;
    lexer->position = (Location){0, 1, 0};
    lexer->tokens = malloc(sizeof(Array));
    array_init(lexer->tokens);

    return lexer;
}

Token* token_init(TokenType type, char* value, Location start, Location end)
{
    Token* token = malloc(sizeof(Token));
    token->type = type;
    token->value = value;
    token->start = start;
    token->end = end;
    return token;
}

Token* lexer_lex(Lexer* lexer)
{
    printf("lexer_lex: %c\n", *lexer->source);
    Location start = lexer->position;

    switch (*lexer->source) {
        case '(': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            return token_init(TOKEN_LPAREN, "(", start, lexer->position);
        } break;
        case ')': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            return token_init(TOKEN_RPAREN, ")", start, lexer->position);
        } break;
        case '[': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            return token_init(TOKEN_LBRACKET, "[", start, lexer->position);
        } break;
        case ']': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            return token_init(TOKEN_RBRACKET, "]", start, lexer->position);
        } break;
        case '{': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            return token_init(TOKEN_LBRACE, "{", start, lexer->position);
        } break;
        case '}': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            return token_init(TOKEN_RBRACE, "}", start, lexer->position);
        } break;
        case '\n': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.line++;
            lexer->position.column = 0;

            return lexer_lex(lexer);
        } break;
        case ' ':
        case '\t':
        case '\r': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            return lexer_lex(lexer);
        } break;
        case 'a'...'z': case 'A'...'Z':
        {
            sds temp = sdsnew("");

            // Continue until we find something that isn't a digit, or end of input.
            while(*lexer->source != '\0') {
                if (!isalpha(*lexer->source)) break;
                temp = sdscatprintf(temp, "%c", *lexer->source);

                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;
            }

            switch (temp[0]) {
                case 'f': {
                    if (strcmp(temp, "fn") == 0) {
                        return token_init(TOKEN_FN, temp, start, lexer->position);
                    } else if (strcmp(temp, "for") == 0) {
                        return token_init(TOKEN_FOR, temp, start, lexer->position);
                    }
                } break;
                case 'r': {
                    if (strcmp(temp, "ret") == 0) {
                        return token_init(TOKEN_RET, temp, start, lexer->position);
                    }
                } break;
                case 'i': {
                    if (strcmp(temp, "if") == 0) {
                        return token_init(TOKEN_IF, temp, start, lexer->position);
                    }
                } break;
                case 'e': {
                    if (strcmp(temp, "else") == 0) {
                        return token_init(TOKEN_ELSE, temp, start, lexer->position);
                    }
                } break;
                case 'w': {
                    if (strcmp(temp, "while") == 0) {
                        return token_init(TOKEN_WHILE, temp, start, lexer->position);
                    }
                } break;
            }

            return token_init(TOKEN_IDENTIFIER, temp, start, lexer->position);
        } break;
        case '0'...'9':
        {
            // Save the starting position
            char* start_pos = lexer->source;
            // Continue until we find something that isn't a digit, or end of input.
            while(*lexer->source != '\0') {
                if (!isdigit(*lexer->source)) break;
                lexer->source++;
            }
            return token_init(TOKEN_IDENTIFIER, strndup(start_pos, lexer->source - start_pos), start, lexer->position);
        } break;
        case '\0': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            return token_init(TOKEN_EOF, "", start, lexer->position);
        } break;
        case '>': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            if (*lexer->source == '=') {
                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;

                return token_init(TOKEN_GTE, ">=", start, lexer->position);
            }

            return token_init(TOKEN_GT, ">", start, lexer->position);
        } break;
        case '<': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            if (*lexer->source == '=') {
                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;

                return token_init(TOKEN_LTE, "<=", start, lexer->position);
            }

            return token_init(TOKEN_LT, "<", start, lexer->position);
        } break;
        case '=': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            if (*lexer->source == '=') {
                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;

                return token_init(TOKEN_EQ, "==", start, lexer->position);
            }

            return token_init(TOKEN_ASSIGN, "=", start, lexer->position);
        } break;
        case '!': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            if (*lexer->source == '=') {
                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;

                return token_init(TOKEN_NEQ, "!=", start, lexer->position);
            }

            return token_init(TOKEN_NOT, "!", start, lexer->position);
        } break;
        case '+': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            if (*lexer->source == '+') {
                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;

                return token_init(TOKEN_INC, "++", start, lexer->position);
            } else if (*lexer->source == '=') {
                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;

                return token_init(TOKEN_ADD_ASSIGN, "+=", start, lexer->position);
            }

            return token_init(TOKEN_ADD, "+", start, lexer->position);
        } break;
        case '-': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            if (*lexer->source == '-') {
                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;

                return token_init(TOKEN_DEC, "--", start, lexer->position);
            } else if (*lexer->source == '=') {
                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;

                return token_init(TOKEN_SUB_ASSIGN, "-=", start, lexer->position);
            }

            return token_init(TOKEN_SUB, "-", start, lexer->position);
        } break;
        case '*': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            if (*lexer->source == '=') {
                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;

                return token_init(TOKEN_MUL_ASSIGN, "*=", start, lexer->position);
            }

            return token_init(TOKEN_MUL, "*", start, lexer->position);
        } break;
        case '#': {
            // comment and read until next line or EOF
            while(*lexer->source != '\0') {
                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;
                if (*lexer->source == '\n') {
                    lexer->position.column = 0;
                    lexer->position.line++;
                    break;
                }
            }
            return lexer_lex(lexer);
        } break;
        case '/': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            if (*lexer->source == '=') {
                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;

                return token_init(TOKEN_DIV_ASSIGN, "/=", start, lexer->position);
            }

            return token_init(TOKEN_DIV, "/", start, lexer->position);
        } break;
        case '%': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            if (*lexer->source == '=') {
                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;

                return token_init(TOKEN_MOD_ASSIGN, "%=", start, lexer->position);
            }

            return token_init(TOKEN_MOD, "%", start, lexer->position);
        } break;
        case '^': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            return token_init(TOKEN_POW, "^", start, lexer->position);
        } break;
        case '&': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            if (*lexer->source == '&') {
                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;

                return token_init(TOKEN_ANDAND, "&&", start, lexer->position);
            }

            return token_init(TOKEN_AND, "&", start, lexer->position);
        } break;
        case '|': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            if (*lexer->source == '|') {
                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;

                return token_init(TOKEN_OROR, "||", start, lexer->position);
            }

            return token_init(TOKEN_OR, "|", start, lexer->position);
        } break;
        case '~': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            return token_init(TOKEN_TILDE, "~", start, lexer->position);
        } break;
        case '.': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            if (*lexer->source == '.') {
                lexer->source++;
                lexer->position.offset++;
                lexer->position.column++;

                if (*lexer->source == '.') {
                    lexer->source++;
                    lexer->position.offset++;
                    lexer->position.column++;

                    return token_init(TOKEN_ELLIPSIS, "...", start, lexer->position);
                }

                return token_init(TOKEN_DOTDOT, "..", start, lexer->position);
            }

            return token_init(TOKEN_DOT, ".", start, lexer->position);
        } break;
        case ';': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            return token_init(TOKEN_SEMICOLON, ";", start, lexer->position);
        } break;
        case ',': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            return token_init(TOKEN_COMMA, ",", start, lexer->position);
        } break;
        case ':': {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            return token_init(TOKEN_COLON, ":", start, lexer->position);
        } break;
        default: {
            lexer->source++;
            lexer->position.offset++;
            lexer->position.column++;

            return token_init(TOKEN_ERROR, "Unexpected character", start, lexer->position);
        }
    }
}

void lexer_tokenizer(Lexer* lexer)
{
    Token* t = lexer_lex(lexer);
    do {
        array_push(lexer->tokens, t);
        t = lexer_lex(lexer);
    }
    while (t != NULL && t->type != TOKEN_EOF);

    if (t != NULL && t->type == TOKEN_EOF) {
        array_push(lexer->tokens, t);
    }
}

char* location_string(Location location)
{
    char* str = malloc(sizeof(char) * 100);
    sprintf(str, "%d:%d:%d", location.offset, location.line, location.column);
    return str;
}

char* token_type_name(TokenType type)
{
    printf("%d\n", type);
    switch (type) {
        case TOKEN_EOF:
            return "EOF";
        case TOKEN_ERROR:
            return "ERROR";
        case TOKEN_FN:
            return "FN";
        case TOKEN_IF:
            return "IF";
        case TOKEN_ELSE:
            return "ELSE";
        case TOKEN_WHILE:
            return "WHILE";
        case TOKEN_FOR:
            return "FOR";
        case TOKEN_RET:
            return "RET";

        case TOKEN_IDENTIFIER:
            return "IDENTIFIER";
//        case TOKEN_NUMBER: return "NUMBER";
//        case TOKEN_STRING: return "STRING";
//        case TOKEN_CHAR: return "CHAR";
        case TOKEN_ADD:
            return "PLUS";
        case TOKEN_SUB:
            return "MINUS";
        case TOKEN_MUL:
            return "MUL";
        case TOKEN_DIV:
            return "DIV";
        case TOKEN_MOD:
            return "MOD";
        case TOKEN_POW:
            return "POW";
        case TOKEN_AND:
            return "AND";
        case TOKEN_OR:
            return "OR";
        case TOKEN_TILDE:
            return "TILDE";
        case TOKEN_ANDAND:
            return "ANDAND";
        case TOKEN_OROR:
            return "OROR";
        case TOKEN_NOT:
            return "NOT";
        case TOKEN_ASSIGN:
            return "ASSIGN";
        case TOKEN_ADD_ASSIGN:
            return "ADD_ASSIGN";
        case TOKEN_SUB_ASSIGN:
            return "SUB_ASSIGN";
        case TOKEN_MUL_ASSIGN:
            return "MUL_ASSIGN";
        case TOKEN_DIV_ASSIGN:
            return "DIV_ASSIGN";
        case TOKEN_MOD_ASSIGN:
            return "MOD_ASSIGN";
//        case TOKEN_POW_ASSIGN: return "POW_ASSIGN";
//        case TOKEN_AND_ASSIGN: return "AND_ASSIGN";
//        case TOKEN_OR_ASSIGN: return "OR_ASSIGN";
//        case TOKEN_TILDE_ASSIGN: return "TILDE_ASSIGN";
//        case TOKEN_LSHIFT: return "LSHIFT";
//        case TOKEN_RSHIFT: return "RSHIFT";
//        case TOKEN_LSHIFT_ASSIGN: return "LSHIFT_ASSIGN";
//        case TOKEN_RSHIFT_ASSIGN: return "RSHIFT_ASSIGN";
        case TOKEN_EQ:
            return "EQ";
        case TOKEN_NEQ:
            return "NEQ";
        case TOKEN_LT:
            return "LT";
        case TOKEN_GT:
            return "GT";
        case TOKEN_LTE:
            return "LTE";
        case TOKEN_GTE:
            return "GTE";
        case TOKEN_DOT:
            return "DOT";
        case TOKEN_DOTDOT:
            return "DOTDOT";
        case TOKEN_ELLIPSIS:
            return "ELLIPSIS";
        case TOKEN_LPAREN:
            return "LPAREN";
        case TOKEN_RPAREN:
            return "RPAREN";
        case TOKEN_LBRACE:
            return "LBRACE";
        case TOKEN_RBRACE:
            return "RBRACE";

        default:
            return "UNKNOWN";
    }
}

sds lexer_trace(Lexer* lexer)
{
    printf("lexer_trace\n");
    sds temp = sdsnew("<Lexer>\n");

    for (int i = 0; i < lexer->tokens->count; i++)
    {
        Token* token = lexer->tokens->data[i];
        temp = sdscatprintf(temp, "%s<token id=\"%d\">\n", "\t", i + 1);
            temp = sdscatfmt(temp, "%s<type>%s</type>\n", "\t\t", token_type_name(token->type));
            temp = sdscatfmt(temp, "%s<value>%s</value>\n", "\t\t", token->value);
            temp = sdscatfmt(temp, "%s<start>%s</start>\n", "\t\t", location_string(token->start));
            temp = sdscatfmt(temp, "%s<end>%s</end>\n", "\t\t", location_string(token->end));
        temp = sdscatfmt(temp, "%s</token>\n", "\t");
    }

    temp = sdscat(temp, "</Lexer>");

    return temp;
}
