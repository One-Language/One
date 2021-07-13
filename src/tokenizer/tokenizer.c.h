/**
 The One Programming Language

 File: tokenizer/tokenizer.h
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef _ONE_TOKENIZER_TOKENIZER_H_
#define _ONE_TOKENIZER_TOKENIZER_H_

#include "../builtins/string.h"

#include "token.h"

/*
 * @function: tokenizer_file
 * @description: Create a array of tokens from a filepath
 * @inputs: char* of a one' pathfile
 * @return: Array of Token
 */
Token* tokenizer_file(char* filepath);

/*
 * @function: tokenizer_string
 * @description: Create a array of tokens from a one program source-code char*
 * @inputs: char* of a One program source-code
 * @return: Array of Token
 */
Token* tokenizer_string(char* data);

#endif // _ONE_TOKENIZER_TOKENIZER_H_
