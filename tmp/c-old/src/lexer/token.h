/*
 * Copyright 2021; One Language Contributors - Max Base, <maxbasecode [@] gmail {dot} com>
 * This file is part of One Programming Language.
 *
 * one-language is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * one-language is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with one-language.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _TOKEN_H_
#define _TOKEN_H_

typedef struct
{
	// LOG
	int line;
	int offset;

	// DATA
	unsigned int tok;
	char *name;
	char *value;
} Token;

#include "../one.h"

enum one_token
{
	TOK_START = 255
#define DEF(id, str) , id
#include "tokens.h"
#undef DEF
};

Token token_new(void);

#endif
