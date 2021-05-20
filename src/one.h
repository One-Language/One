#include <stdio.h>
#include <stdlib.h>

#define DEBUG
#define ONE_VERSION "0.4.0"

void error(char *message);
void help(void);
char *file_read(char *filename);
void file_parse(char *filename);
int main(int argc, char **argv);

typedef enum {
	FALSE,
	TRUE
} bool;



