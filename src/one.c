/**
 File: one.c
  _        _ 
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021

 **/

#include "one.h"
#include "lexer.h"

void error(char*message)
{
  fprintf(stderr, message);
}

void help(void)
{
  puts("$ One filename.one");
  puts("One version: " ONE_VERSION);
}

char* file_read(char*filename)
{
  FILE * onefile = fopen(filename, "rb");
  if (onefile == NULL) {
    return NULL;
  }
  fseek(onefile, 0L, SEEK_END);
  size_t onefilesize = ftell(onefile);
  rewind(onefile);
  char* onebuffer = (char*)malloc(onefilesize + 1);
  if (onebuffer == NULL) {
    error("error malloc onebuffer\n");
    return NULL;
  }
  size_t onebytesread = fread(onebuffer, 1, onefilesize, onefile);
  if (onebytesread < onefilesize) {
    free(onebuffer);
    error("Could not read file.one\n");
    return NULL;
  }
  onebuffer[onebytesread] = '\0';
  fclose(onefile);
  return onebuffer;
}

void file_parse(char* filename)
{
  char* input = file_read(filename);
  Lexer* l = lexer_init(filename, input);
  lexer_parse(&l);
}

int main(int argc, char** argv)
{
  if (argc <= 1)
    help();
  else
    file_parse(argv[1]);
  return 0;
}