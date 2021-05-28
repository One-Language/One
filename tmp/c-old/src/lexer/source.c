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

#include "source.h"

Source source_new(void) {
  Source s;
  s.data = NULL;
  s.line = 1;
  s.column = 0;
  return s;
}

Source source_new_data(char *data) {
  Source s = source_new();
  s.data = data;
  return s;
}
