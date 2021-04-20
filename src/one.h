#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define printf printf
#define print printf
#define VERSION "0.3.0"
#define ARCH "linux/amd64"

void main_help(void);
void main_badcommand(int argc, char *argv[]);
void main_badparam(void);
void main_badflag(void);
void main_version(int argc);
void main_parse(int argc, char *argv[]);
int main(int argc, char *argv[]);

