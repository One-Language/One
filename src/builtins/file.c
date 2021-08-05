/**
 The One Programming Language

 File: builtins/array.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "file.h"

/*
 * @function: file_reads
 * @description: read whole of a filepath
 * @arguments: const char* filepath
 * @return: char*
 */
char* file_reads(const char* filepath)
{
	debug("file_reads");
	debug("file_reads: %s", filepath);

	FILE* file = fopen(filepath, "rb");
	if (file == NULL)
	{
		error_panic("Could not open file \"%s\".", filepath);
		exit(74);
	}

	fseek(file, 0L, SEEK_END);
	size_t fileSize = ftell(file);
	debug("file_reads: fileSize is %zu", fileSize);
	rewind(file);

	char* buffer = (char*)malloc(fileSize + 1);
	if (buffer == NULL)
	{
		error_panic("Not enough memory to read \"%s\".", filepath);
		exit(74);
	}

	size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
	debug("file_reads: bytesRead is %zu", bytesRead);
	if (bytesRead < fileSize)
	{
		error_panic("Could not read the \"%s\".", filepath);
		exit(74);
	}

	buffer[bytesRead] = '\0';

	fclose(file);
	return buffer;
}

/*
 * @function: file_convert_index_to_rc
 * @description: We get index of a position and point in string and looking to find its rows and column number and we will pass new value throw argument
 * @arguments: const char* input, int index, size_t* rows, size_t* columns
 * @return: bool / True or False; does that index exists or no. maybe current index is out of the file and filelength is less that `index` value!
 */
bool file_convert_index_to_rc(const char* input, int index, size_t* rows, size_t* columns)
{
	int row = 1, col = 0;

	for (int i = 0; i < index; i++)
	{
		char ch = input[i];
		// printf("-->%d,'%c'\n", i, ch);

		if (ch == '\0') return false; // Stop loop and return false as function return-value

		if (ch == '\r')
		{
			// Skip the optional \n
			if (i + 1 < index && input[i + 1] == '\n')
			{
				i++;
			}

			row++;
			col = 0;
		}
		else if (ch == '\n')
		{
			row++;
			col = 0;
		}
		else
		{
			col++;
		}
	}

	*rows = row;
	*columns = col;

	return true;
}

// TODO
char* file_get_parent(const char* path)
{
    int parentLen;
	char* parent = malloc(sizeof(path));
    char* last = strrchr(path, '/');

    if (last != NULL) {

        parentLen = strlen(path) - strlen(last + 1);
        strncpy(parent, path, parentLen);
    }

    return parent;
}
