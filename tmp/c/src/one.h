/**
 File: one.h
  _        _
 / \ |\ | |_    Author: Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#ifndef _ONE_H_
#define _ONE_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arg.h"
#include "sds.h"
#include "vec.h"

// typedef struct Args;

#define DEBUG
#define ONE_VERSION "0.4.0"

#define log(format, params...) printf(format, params...);

void error(char *format, ...);
void help(Args *args);
char *file_read(char *);
void file_parse(char *);

// int main(int argc, const char* const* argv, const char* const* env);
int main(int argc, char **argv, char **env);

// typedef enum {
//     FALSE,
//     TRUE
// } bool;

// enum _bool {
//    false = 0,
//    true = 1
// };
// typedef enum _bool Bool;

#endif
