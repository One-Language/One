//
// Created by Max on 9/4/2022.
//

#ifndef ONE_LEXER_IO_H
#define ONE_LEXER_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <str.h>
#include <stdbool.h>

#include "error.h"

/*
 * @function: file_reads
 * @description: read whole of a filepath
 * @arguments: const char* filepath
 * @return: char*
 */
char* file_reads(const char* filepath);

/*
 * @function: file_convert_index_to_rc
 * @description: We get index of a position and point in string and looking to find its rows and column number and we will pass new value throw argument
 * @arguments: const char* input, int index, size_t* rows, size_t* columns
 * @return: bool / True or False; does that index exists or no. maybe current index is out of the file and filelength is less that `index` value!
 */
bool file_convert_index_to_rc(const char* input, int index, size_t* rows, size_t* columns);

/*
 * @function: file_get_parent
 * @description: If you want to get directory path from a full-file path, this function will be useful and can return the directory path for you.
 * @arguments: const char* path
 * @return: char*
 */
char* file_get_parent(const char* path);


char* string_repeat(char* value, size_t repeat);

#endif //ONE_LEXER_IO_H
