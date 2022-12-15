/**
 The One Programming Language
 File: file.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#ifndef _ONE_FILE_H_
#define _ONE_FILE_H_

#include <stdio.h> // fopen, fclose, FILE
#include <stdlib.h> // malloc, free
#include <stdbool.h> // bool, true, false

typedef struct {
    char* directory;
    char* path;
    char* name;
    char* extension;
    char* content;
    FILE* file;
    size_t size;
    bool exists;
} file_t;

/**
 * @brief Initialize the File object
 * 
 * @param char* path
 * 
 * @return file_t* 
 */
file_t* file_init(char* path);

/**
 * @brief Read the file content
 * 
 * @param file_t* file
 * 
 * @return char*
 */
char* file_read(file_t* file);

/**
 * @brief Free the File object
 * 
 * @param file_t* file
 * 
 * @return void
 */
void file_free(file_t* file);

/**
 * @brief Print the file content
 * 
 * @param file_t* file
 * 
 * @return void
 */
void file_print(file_t* file);

/**
 * @brief Check a file is exists or not
 * 
 * @param file_t* file
 * 
 * @return bool
 */
bool file_exists(file_t* file);

/**
 * @brief Get the file size
 * 
 * @param file_t* file
 * 
 * @return size_t
 */
size_t file_size(file_t* file);

/**
 * @brief Get the file path
 * 
 * @param file_t* file
 * 
 * @return char*
 */
char* file_path(file_t* file);

/**
 * @brief Get the file name
 * 
 * @param file_t* file
 * 
 * @return char*
 */
char* file_name(file_t* file);

/**
 * @brief Get the file extension
 * 
 * @param file_t* file
 * 
 * @return char*
 */
char* file_extension(file_t* file);

/**
 * @brief Get the file directory
 * 
 * @param file_t* file
 * 
 * @return char*
 */
char* file_directory(file_t* file);

#endif
