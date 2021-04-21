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

#include "io.h"

char *read_file(char *filename) {
  FILE *onefile = fopen(filename, "rb");

  if(onefile == NULL) {
    return NULL;
  }

  fseek(onefile, 0L, SEEK_END);
  size_t onefilesize = ftell(onefile);
  rewind(onefile);
  char *onebuffer = (char *)malloc(onefilesize + 1);

  if(onebuffer == NULL) {
    error("error malloc onebuffer\n");
    return NULL;
  }

  size_t onebytesread = fread(onebuffer, 1, onefilesize, onefile);
  if(onebytesread < onefilesize) {
    free(onebuffer);
    error("Could not read file.one\n");
    return NULL;
  }

  onebuffer[onebytesread] = '\0';

  fclose(onefile);
  return onebuffer;
}
