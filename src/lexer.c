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
#include "array.h"

Lexer *lexerInit(char *filename, char *input, ErrorsContainer *errors) {
    Lexer *lex = malloc(sizeof(Lexer));
    lex->tokens = NULL;
    lex->token_count = 0;
    lex->filename = filename;
    lex->source = input;
    lex->location.line = 0;
    lex->location.column = 0;
    return lex;
}

void lexerLog(Lexer *lex) {
    printf("=============== Tokenizer ===============\n");

    Token *t;
    for (size_t i = 0; i < lex->token_count; i++) {
        t = lex->tokens[i];

        printf("==>%s\n", tokenName(t->type));
        if (t->type == TOKEN_VALUE_IDENTIFIER || t->type == TOKEN_VALUE_STRING || t->type == TOKEN_VALUE_NUMBER)
            printf("\t%s\n", t->vstring);
    }
}


int lexerCheck(Lexer *lex, ErrorsContainer *errors) {
    token_init(lex);
    printf("=============== Source ===============\n");
    printf("%s\n", lex->source);

    Array tokens;
    arrayInit(&tokens);

    bool has_error = false; // we need this value to make sure we can add EOF token at end of tokens list or no.
    // for example: Maybe we need to detect we tokenizer whole of the file or no, we face to a error and so we break and not tokiziers whole of the source!

    Token *t;
    while (tokenEOF(lex) == false) {
//        printf("%c\n", *lex->source);
//        tokenNextChar(lex);
        t = tokenNext(lex);
        if (t->type == TOKEN_UNKNOWM) {
            has_error = true; // change error status from false to true...
            // TODO: raise a error via ErrorAppend(...)
            break;
        }

        arrayPush(&tokens, t);
//        printf("==>%s\n", tokenName(t->type));
//        if(t->type == TOKEN_VALUE_IDENTIFIER || t->type == TOKEN_VALUE_STRING || t->type == TOKEN_VALUE_NUMBER)
//            printf("\t%s\n", t->vstring);
    }

    // Why in some case when we put newline and free space at end of file, we not see a EOF token there!
    if(has_error == false) { // if we not have any errors in tokinizering source
        if (tokens.count == 0 || ( // if tokens list is empty
                tokens.count > 0 && ((Token *) tokens.data[tokens.count - 1])->type !=
                                    TOKEN_EOF) // otherwise, if tokens list is not empty and at last item of tokens we not have a EOF token...
                ) {
            Token *t_eof = malloc(sizeof(Token)); // create a token value just for adding EOF token.
            t_eof->type = TOKEN_EOF; // set type of new token as TOKEN_EOF
            arrayPush(&tokens, t_eof); // push and add t-eof token at list of token!
            // free(t_eof); // free t_eof from memory!
        }
    }

    lex->tokens = (Token **) tokens.data;
    lex->token_count = tokens.count;
    return EXIT_SUCCESS;
}

void lexerFree(Lexer *lexer) {

}
