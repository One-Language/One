#include "file.h"

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
bool file_exists(char* filepath)
{
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        return false;
    }

    // Check is readable
    if (access(filepath, R_OK) != 0) {
        fclose(file);
        return false;
    }

    return true;
}

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
char* file_reads(char* filepath)
{
	// debug("file_reads");
	// debug("file_reads: %s", filepath);

	FILE* file = fopen(filepath, "rb");
	if (file == NULL) {
		printf("Error: Could not open file \"%s\".", filepath);
		exit(74);
	}

	fseek(file, 0L, SEEK_END);
	size_t fileSize = ftell(file);
	// debug("file_reads: fileSize is %zu", fileSize);
	rewind(file);

	char* buffer = (char*)malloc(fileSize + 1);
	if (buffer == NULL) {
		printf("Error: Not enough memory to read \"%s\".", filepath);
		exit(74);
	}

	size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
	// debug("file_reads: bytesRead is %zu", bytesRead);
	if (bytesRead < fileSize) {
		printf("Error: Could not read the \"%s\".", filepath);
		exit(74);
	}

	buffer[bytesRead] = '\0';

	fclose(file);
	return buffer;
}
