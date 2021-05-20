#include "one.h"
#include "lexer.h"
#include "token.h"

Lexer* lexer_init(char *filename, char *input)
{
  Lexer* lex = malloc(sizeof(Lexer));
  lex->f = filename;
  lex->s = input;
  // #ifdef DEBUG
  //   printf("-->%s\n", lex->f);
  //   printf("-->%s\n", lex->s);
  // #endif
  return lex;
}

void lexer_parse(Lexer* lex)
{
  #ifdef DEBUG
    printf("-->%s\n", lex->f);
    printf("-->%s\n", lex->s);
  #endif
  token_end(lex);
  *lex->s++;
  token_end(lex);
  *lex->s++;
  token_end(lex);
}
