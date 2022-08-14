/**
The One Programming Language

File: utils/file.c
 _        _
/ \ |\ | |_    Max Base
\_/ | \| |_    Copyright 2021; One Language Contributors

**/

#include "file.h"

char* file_read_contents(const char* file_path)
{
    FILE* file = fopen(file_path, "r");
    if(file == NULL) {
        printf("Error: file not found!\n");
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    char* data = (char*) malloc(sizeof(char) * (file_size + 1));
    if (data == NULL) {
        printf("Error: memory allocation failed!\n");
        return NULL;
    }
    fread(data, file_size, 1, file);
    data[file_size] = '\0';
    
    fclose(file);
    
    return data;
}
