#ifndef _ONE_PARSER_AST_H_
#define _ONE_PARSER_AST_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {

} ast_t;

ast_t* ast_init();

void ast_free(ast_t* ast);

#endif