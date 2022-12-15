/**
 The One Programming Language
 File: token.c
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#include "token.h"

/**
 * @brief Get the token name
 * 
 * @param type 
 * @return char* 
 */
char* token_name(token_type_t type)
{
    switch (type) {
        case TOKEN_ERROR: return "error";
        case TOKEN_IF: return "if";
        case TOKEN_ELSE: return "else";
        case TOKEN_RET: return "ret";
        case TOKEN_NUMBER: return "number";
        case TOKEN_EOF: return "eof";
        default: return "unknown";
    }
}
