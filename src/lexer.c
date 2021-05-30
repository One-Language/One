/**
 The One Programming Language

 File: lexer.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "lexer.h"

Lexer *lexerInit(char *filename, char *input, ErrorsContainer *errors) {
    Lexer *lex = malloc(sizeof(Lexer));
    lex->filename = filename;
    lex->source = input;
    lex->location.line = 0;
    lex->location.column = 0;
    return lex;
}

int lexerParse(Lexer *lexer, ErrorsContainer *errors) {
    return EXIT_SUCCESS;
}

void lexerFree(Lexer *lexer) {

}
