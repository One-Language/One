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
  if (c >= '0' && c <= '9') return TRUE;
  return FALSE;
}

bool token_is_digit(char c)
{
  if(token_is_number(c) == TRUE) return TRUE;
  else if(c == '.') return TRUE;
  return FALSE;
}

bool token_is_ident(char c)
{
  if (token_is_alpha(c) == TRUE) {
    return TRUE;
  }
  else if (token_is_number(c) == TRUE) {
    return TRUE;
  }
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
  if(token_is_alpha(*lex->s) == TRUE) {
    t->vstring = sdsnew( (char[]){*lex->s} );
    token_nextchar(lex); // eat first char

    while(token_is_ident(*lex->s) == TRUE) {
      t->vstring = sdscat(t->vstring, (char[]){*lex->s} );
      token_nextchar(lex);
    }

    t->vstring = sdscat(t->vstring, (char[]){'\0'} ); // put EOF for string!

    #ifdef DEBUG
      // printf("[string] %s\n", t->vstring);
    #endif

    // sdsfree(t->vstring);
    // printf("==>%s\n", t->vstring);

    if(strcmp(t->vstring, "def") == 0) {
      t->type = tok_def;
      return t;
    }
    else if(strcmp(t->vstring, "extern") == 0) {
      t->type = tok_extern;
      return t;
    }

    t->type = tok_identifier;
    return t;
  }

  // Get number
  if(token_is_digit(*lex->s) == TRUE) {
    sds NumStr = sdsnew( (char[]){*lex->s} );
    token_nextchar(lex); // eat first digit

    while(token_is_digit(*lex->s) == TRUE) {
      NumStr = sdscat(NumStr, (char[]){*lex->s} );
      token_nextchar(lex); // eat next digits...
    }

    t->type = tok_number;
    t->vint = strtod(NumStr, 0);

    sdsfree(NumStr);
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
    else if(*lex->s == '/') {
      t->type = 500;
      return t;
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

char* token_name(Token* t)
{
  switch(t->type) {
    case '/':
      return "OPERATOR_DIV";
    break;

    case tok_div_int: // '//'
      return "OPERATOR_DIV_int";
    break;

    case '+':
      return "OPERATOR_ADD";
    break;

    case '-':
      return "OPERATOR_MIN";
    break;

    case '*':
      return "OPERATOR_MUL";
    break;

    case '=':
      return "OPERATOR_DEFINE";
    break;

    case tok_define: // '=='
      return "OPERATOR_EQUAL";
    break;

    case '{':
      return "SECTION_OPEN";
    break;

    case '}':
      return "SECTION_CLOSE";
    break;

    case '(':
      return "BRACKET_OPEN";
    break;

    case ')':
      return "BRACKET_CLOSE";
    break;

    case tok_identifier:
      return "IDENTIFIER";
    break;

    case tok_string:
      return "STRING";
    break;

    case tok_number:
      return "NUMBER";
    break;

    case tok_def:
      return "DEF";
    break;

    case tok_extern:
      return "EXTERN";
    break;

    default:
      return "UNKNOWN";
    break;
  }
}

void tok_log(Token* t)
{
    printf("[token] %s", token_name(t));

    if(t->type == tok_string || t->type == tok_identifier)
      printf(" = %s", t->vstring);
    else if(t->type == tok_number)
      printf(" = %d", t->vint);

    printf("\n");
}
