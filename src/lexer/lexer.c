/*
 * Copyright 2021 - Max Base, <maxbasecode@gmail.com>
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

#include "lexer.h"

Token lexer_next(Source *src) {
	Token t = token_new();

	while(*src->data != '\0') {
		t.offset++;
		if(*src->data == '\n') {
			printf("-->NEW LINE\n");
			src->line++;
		}
		else {
			printf("-->%c\n", *src->data);
			if(*src->data >= 'a' && *src->data <= 'z') {
				*src->data++;

				t.tok = 1;
				t.name = "Char";
				return t;
			}
		}
		*src->data++;
	}

	return t;
}

void lexer_scan(Source *src) {
	// printf("%s\n", data);
	Token t;
	while(1) {
		t = lexer_next(src);
		if(t.tok == 0) {
			break;
		}
		printf("-->%s\n", t.name);
	}
}
