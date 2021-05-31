/**
 The One Programming Language

 File: lexer.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "token.h"
#include "error.h"
#include "lexer.h"

Lexer *lexerInit(char *filename, char *input, ErrorsContainer *errors) {
    Lexer *lex = malloc(sizeof(Lexer));
    lex->filename = filename;
    lex->source = input;
    lex->location.line = 0;
    lex->location.column = 0;
    return lex;
}

int lexerParse(Lexer *lex, ErrorsContainer *errors) {
    token_init(lex);
    printf("=============== Source ===============\n");
    printf("%s\n", lex->source);
    printf("=============== Tokenizer ===============\n");

    Token *t;
    while (tokenEOF(lex) == false) {
//        printf("%c\n", *lex->source);
//        tokenNextChar(lex);
        t = tokenNext(lex);
        if(t->type == TOKEN_UNKNOWM)
            break;
        printf("==>%s\n", tokenName(t->type));
        if(t->type == TOKEN_VALUE_IDENTIFIER || t->type == TOKEN_VALUE_STRING || t->type == TOKEN_VALUE_NUMBER)
            printf("\t%s\n", t->vstring);
    }
    return EXIT_SUCCESS;
}

void lexerFree(Lexer *lexer) {

}
