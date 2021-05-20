#include "one.h"
#include "lexer.h"
#include "token.h"

void token_init()
{

}

bool token_end(Lexer* l)
{
  // if (*l->s)
  #ifdef DEBUG
    printf("-->%c\n", *(l->s));
  #endif
}
