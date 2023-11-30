#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

/**
 * Check if a file exists.
 * 
 * @return bool
 * @param char* filepath
 * @note If the file does not exist, it returns false.
 * @note If the file is not readable, it returns false.
 * @note If the file is not a file, it returns false.
 * @note If the file is a directory, it returns false.
 * @note If the file is a file, it returns true.
*/
bool file_exists(char* filepath);

/**
 * Read a file.
 * 
 * @return char* or NULL
 * @param char* filepath
 * @note You must free the returned pointer.
 * @note If the file does not exist, it returns NULL.
 * @note If the file is not readable, it returns NULL.
 * @note If the file is not a file, it returns NULL.
 * @note If the file is a directory, it returns NULL.
*/
char* file_reads(char* filepath);
