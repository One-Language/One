/**
 File: token.c
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "one.h"
#include "lexer.h"
#include "token.h"

void token_init(Lexer* lex)
{

}

bool token_is_space(char c)
{
  if (c == ' ') return TRUE;
  else if (c == '\t') return TRUE;
  else if (c == '\n') return TRUE;
  else if (c == '\r') return TRUE;
  return FALSE;
}

bool token_is_alpha(char c)
{
  if (c >= 'a' && c <= 'z') return TRUE;
  else if (c >= 'A' && c <= 'Z') return TRUE;
  else if (c == '_') return TRUE;
  return FALSE;
}

bool token_is_number(char c)
{
  if (c >= '0' && c <= 'z') return TRUE;
  return FALSE;
}

bool token_is_digit(char c)
{
  if(token_is_number(c)) return TRUE;
  else if(c == '.') return TRUE;
  return FALSE;
}

bool token_is_ident(char c)
{
  if (token_is_alpha(c)) return TRUE;
  else if (token_is_number(c)) return TRUE;
  return FALSE;
}

Token* token_next(Lexer* lex)
{
  // #ifdef DEBUG
  //   printf("[token_next] %c\n", *lex->s);
  // #endif

  Token* t = malloc(sizeof(Token));

  while(token_is_space(*lex->s) == TRUE) {
    token_nextchar(lex);
  }

  // Get identifier
  if(token_is_alpha(*lex->s)) {
    sds IdentifierStr = sdsnew( (char[]){*lex->s} );
    token_nextchar(lex);

    while(token_is_ident(*lex->s)) {
      IdentifierStr = sdscat(IdentifierStr, (char[]){*lex->s} );
      token_nextchar(lex);
    }

    IdentifierStr = sdscat(IdentifierStr, (char[]){'\0'} ); // put EOF for string!

    #ifdef DEBUG
      printf("[string] %s\n", IdentifierStr);
    #endif

    t->vstring = IdentifierStr;
    // sdsfree(IdentifierStr);
    // printf("==>%s\n", t->vstring);

    if(strcmp(IdentifierStr, "def") == 0) {
      t->type = tok_def;
      return t;
    }
    else if(strcmp(IdentifierStr, "extern") == 0) {
      t->type = tok_extern;
      return t;
    }

    t->type = tok_identifier;
    return t;
  }


  // Get number
  if(token_is_digit(*lex->s)) {
    sds NumStr = sdsnew( (char[]){*lex->s} );
    token_nextchar(lex);

    do {
      NumStr = sdscat(NumStr, (char[]){*lex->s} );
      token_nextchar(lex);
    } while(token_is_digit(*lex->s));

    t->type = tok_number;
    t->vint = strtod(NumStr, 0);
    return t;
  }

  // operators
  if(*lex->s == '{') {
    token_nextchar(lex);
    t->type = '{';
    return t;
  }
  else if(*lex->s == '}') {
    token_nextchar(lex);
    t->type = '}';
    return t;
  }
  else if(*lex->s == '(') {
    token_nextchar(lex);
    t->type = '(';
    return t;
  }
  else if(*lex->s == ')') {
    token_nextchar(lex);
    t->type = ')';
    return t;
  }
  else if(*lex->s == '=') {
    token_nextchar(lex);
    t->type = '=';
    return t;
  }

  // Skip less than a single-line comments
  if(*lex->s == '#') {
    do {
      token_nextchar(lex); // eat '#' at first and other chars at next...
    } while(*lex->s != EOF && *lex->s != '\n' && *lex->s != '\r' && *lex->s != '#');

    if(*lex->s != EOF) {
      return token_next(lex);
    }
  }

  // '/' operator
  if(*lex->s == '/') {
    token_nextchar(lex); // eat '/'

    // Skip single-line comments
    if(*lex->s == '/') {

      do {
        token_nextchar(lex); // eat '/' at first and other chars at next...
      } while(*lex->s != EOF && *lex->s != '\n' && *lex->s == '\r');

      if(*lex->s != EOF) {
        return token_next(lex);
      }
    }
    // Skip multi-line comments
    else if(*lex->s == '*') {
      token_nextchar(lex); // eat '*'

      while(TRUE) {
        char c1 = *lex->s;
        if(c1 == '\0') break;
        token_nextchar(lex); // eat first-part

        char c2 = *lex->s;
        if(c2 == '\0') break;
        token_nextchar(lex); // eat second-part

        if(c1 == '*' && c2 == '/') {
          break;
        }
        // else repeat
      }

      if(*lex->s != EOF) {
        return token_next(lex);
      }      
    }
    else {
      t->type = '/';
      return t;
    }
  }

}

Token* token_prev(Lexer* lex)
{

}

char token_nextchar(Lexer* lex)
{
  if(*lex->s == '\n') {
    lex->l++;
    lex->c = 1;
  }
  else {
    lex->c++;
  }
  *lex->s++;
  return *lex->s;
}

char token_prevchar(Lexer* lex)
{
  *lex->s--;
}

bool token_is_end(Lexer* lex)
{
  if (*lex->s == '\0') {
    #ifdef DEBUG
      printf("[token_end] %c\n", *lex->s);
    #endif
    return TRUE;
  }
  return FALSE;
}

void token_free(Token* t)
{
  sdsfree(t->vstring);
}
