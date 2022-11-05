#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_file(char* path);

bool is_dir(char* path);

char* get_file_dir(char* path);

char* get_file_name(char* path);

char* get_file_ext(char* path);

char* get_file_name_no_ext(char* path);

char* get_file_path(char* dir, char* name);

char* get_file_path_ext(char* dir, char* name, char* ext);

char* file_reads(char* file);
