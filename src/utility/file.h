#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
=======
#include <string.h>
>>>>>>> 4bba61f59a96590c2d3c6ec13246954197f7e842
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
