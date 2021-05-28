/*
 * Copyright 2021 - Max Base, <maxbasecode [@] gmail {dot} com>
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

#include "../one.h"

#ifndef _SOURCE_H_
#define _SOURCE_H_

typedef struct {
  // if path equal to NULL, so current location
  char *path;

  // probably like to `input.one`
  char *filename;

  // content string
  char *data;

  // line number of current token
  int line;

  // column number of current token
  int column; // TODO: start_column, and end_column
} Source;

Source source_new(void);
Source source_new_data(char *data);

#endif
