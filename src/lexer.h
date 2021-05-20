#include <stdio.h>
#include <stdlib.h>

typedef struct lexer {
  // Assembly *assembly;
  char *    f;    // filename (path)
  char *    s;    // source string

  size_t    l;    // line number: default is 1
  size_t    c;    // column number: default is 0
} Lexer;

Lexer* lexer_init(char*, char*);
void lexer_parse(Lexer*);

