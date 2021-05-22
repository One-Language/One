#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "error.h"

static const char* error_level[] = {
    [ERROR]   = "\e[31;1merror\e[m",
    [WARNING] = "\e[35;1mwarning\e[m",
    [NOTE]    = "\e[36;1mnote\e[m",
};

void initErrorContext(ErrorContext* context)
{
  context->error_capacity = 0;
  context->error_count = 0;
  context->errors = NULL;
}

void freeErrorContext(ErrorContext* context)
{
  for (int e = 0; e < context->error_count; e++) {
    free(context->errors[e].message);
  }

  free(context->errors);
  initErrorContext(context);
}

void addError(ErrorContext* context, const char* message, Position position, ErrorLevel level)
{
  if(context != NULL) {
    if (context->error_capacity == context->error_count) {
      context->error_capacity = context->error_capacity * 2 + 4;
      context->errors = (Error*)realloc(context->errors, sizeof(Error) * context->error_capacity);
    }
    int len = strlen(message);
    char* msg = (char*)malloc(len + 1);
    memcpy(msg, message, len + 1);
    context->errors[context->error_count].message = msg;
    context->errors[context->error_count].position = position;
    context->errors[context->error_count].level = level;
    context->error_count++;
  }
}

void printErrors(FILE* file, ErrorContext* context, FileSet* file_set)
{
  for (int i = 0; i < context->error_count; i++) {
      if (context->errors[i].position != NOPOS) {
          LineInfo info = positionToLineInfo(file_set, context->errors[i].position);
          fprintf(file, "%s: %s:%i:%i: %s\n", error_level[context->errors[i].level], info.file->filename, info.line, info.column, context->errors[i].message);
          int printed = fprintf(file, "%5i", info.line);
          char* line = getLineCopyFromFile(info.file, info.line);
          fprintf(file, " | %s", line);
          free(line);

          for (int j = 0; j < printed; j++) {
              putc(' ', file);
          }

          fprintf(file, " |");

          for (int j = 0; j < info.column; j++) {
              putc(' ', file);
          }

          fprintf(file, "\e[31m^\e[m\n");
      } else {
          fprintf(file, "%s: %s\n", error_level[context->errors[i].level], context->errors[i].message);
      }
  }
}

int getErrorCount(ErrorContext* context)
{
  int ret = 0;
  for (int i = 0; i < context->error_count; i++) {
    if (context->errors[i].level == ERROR) {
        ret++;
    }
  }
  return ret;
}

void addErrorf(ErrorContext* context, Position position, ErrorLevel level, const char* format, ...)
{
  char msg[MAX_ERROR_FORMAT];
  va_list varargs;
  va_start(varargs, format);
  vsnprintf(msg, MAX_ERROR_FORMAT, format, varargs);
  va_end(varargs);
  addError(context, msg, position, level);
}
