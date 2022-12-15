/**
 The One Programming Language
 File: file.h
  _        _
 / \ |\ | |_    Max Base <maxbasecode@gmail.com>
 \_/ | \| |_    Copyright 2023; One Language Contributors
 **/

#include "file.h"

/**
 * @brief Initialize the File object
 * 
 * @param char* path
 * 
 * @return file_t* 
 */
file_t* file_init(char* path)
{
    file_t* file = (file_t*)malloc(sizeof(file_t));
    file->path = path;
    file->content = NULL;
    file->size = 0;
    file->exists = false;
    return file;
}

/**
 * @brief Read the file content
 * 
 * @param file_t* file
 * 
 * @return char*
 */
char* file_read(file_t* file)
{
    file->file = fopen(file->path, "r");
    if (file->file == NULL) {
        file->exists = false;
        return NULL;
    }
    file->exists = true;

	fseek(file->file, 0L, SEEK_END);
	file->size = ftell(file->file);
	rewind(file->file);

    file->content = (char*)malloc(file->size + 1);
	if (file->content == NULL) {
		printf("Not enough memory to read \"%s\".\n", file->path);
		exit(74);
        return NULL;
	}

	size_t bytesRead = fread(file->content, sizeof(char), file->size, file->file);
	if (bytesRead < file->size) {
		printf("Could not read the \"%s\".\n", file->path);
		exit(74);
        return NULL;
	}

	file->content[bytesRead] = '\0';

	fclose(file->file);

    return file->content;
}

/**
 * @brief Free the File object
 * 
 * @param file_t* file
 * 
 * @return void
 */
void file_free(file_t* file)
{
    free(file->content);
    free(file);
}

/**
 * @brief Print the file content
 * 
 * @param file_t* file
 * 
 * @return void
 */
void file_print(file_t* file)
{
    if (file->exists == false || file->content == NULL) return;

    printf("%s", file->content);
}

/**
 * @brief Check a file is exist or not
 * 
 * @param file_t* file
 * 
 * @return bool
 */
bool file_exist(file_t* file)
{
    return file->exists;
}

/**
 * @brief Get the file size
 * 
 * @param file_t* file
 * 
 * @return size_t
 */
size_t file_size(file_t* file)
{
    if (file->exists == false) return -1;

    return file->size;
}

/**
 * @brief Get the file path
 * 
 * @param file_t* file
 * 
 * @return char*
 */
char* file_path(file_t* file)
{
    return file->path;
}

/**
 * @brief Get the file name
 * 
 * @param file_t* file
 * 
 * @return char*
 */
char* file_name(file_t* file)
{
    return file->name;
}

/**
 * @brief Get the file extension
 * 
 * @param file_t* file
 * 
 * @return char*
 */
char* file_extension(file_t* file)
{
    return file->extension;
}

/**
 * @brief Get the file directory
 * 
 * @param file_t* file
 * 
 * @return char*
 */
char* file_directory(file_t* file)
{
    return file->directory;
}
