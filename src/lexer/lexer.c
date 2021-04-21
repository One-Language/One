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

Token lexer_next(char **data) {
	Token t;
	t.line = 0;
	t.offset = 0;
	t.tok = 0;
	t.name = "None";

	while(**data != '\0') {
		t.offset++;
		if(**data == '\n') {
			printf("-->NEW LINE\n");
			t.line++;
		}
		else {
			// printf("-->%c\n", **data);
			if(**data >= 'a' && **data <= 'z') {
				**data++;

				t.tok = 1;
				t.name = "Char";
				return t;
			}
		}
		**data++;
	}
	return t;
}

void lexer_scan(char *data) {
	// printf("%s\n", data);
	Token t;
	while(1) {
		t = lexer_next(&data);
		if(t.tok == 0) {
			break;
		}
		printf("-->%s\n", t.name);
	}
}
