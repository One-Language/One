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

#ifndef _ONE_H_
#define _ONE_H_

// glibc, runtime library
#include <stddef.h> // NULL
#include <stdio.h> // printf, fopen, fclose
#include <stdlib.h> // malloc, free
#include <string.h> // strcmp

#define printf printf
#define print printf

// own inside library
#include "io.h"
#include "lexer/lexer.h"
#include "lexer/source.h"
#include "lexer/token.h"

// primary data
#define VERSION "0.3.0"
#define ARCH "linux/amd64"

// functions
void error(char *message);
void main_help(void);
void main_badcommand(int argc, char *argv[]);
void main_badparam(void);
void main_badflag(void);
void main_version(int argc);
void main_parse(int argc, char *argv[]);
int main(int argc, char *argv[]);

#endif
