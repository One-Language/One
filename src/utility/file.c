#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool is_file(char* path) {
	FILE* file = fopen(path, "r");
	if (file) {
		fclose(file);
		return true;
	}
	return false;
}

bool is_dir(char* path) {
	FILE* file = fopen(path, "r");
	if (file) {
		fclose(file);
		return false;
	}
	return true;
}

char* get_file_dir(char* path) {
	char* dir = malloc(strlen(path) + 1);
	strcpy(dir, path);
	for (int i = strlen(dir) - 1; i >= 0; i--) {
		if (dir[i] == '/') {
			dir[i] = '\0';
			break;
		}
	}
	return dir;
}

char* get_file_name(char* path) {
	char* name = malloc(strlen(path) + 1);
	strcpy(name, path);
	for (int i = strlen(name) - 1; i >= 0; i--) {
		if (name[i] == '/') {
			name = &name[i + 1];
			break;
		}
	}
	return name;
}

char* get_file_ext(char* path) {
	char* ext = malloc(strlen(path) + 1);
	strcpy(ext, path);
	for (int i = strlen(ext) - 1; i >= 0; i--) {
		if (ext[i] == '.') {
			ext = &ext[i + 1];
			break;
		}
	}
	return ext;
}

char* get_file_name_no_ext(char* path) {
	char* name = malloc(strlen(path) + 1);
	strcpy(name, path);
	for (int i = strlen(name) - 1; i >= 0; i--) {
		if (name[i] == '.') {
			name[i] = '\0';
			break;
		}
	}
	for (int i = strlen(name) - 1; i >= 0; i--) {
		if (name[i] == '/') {
			name = &name[i + 1];
			break;
		}
	}
	return name;
}

char* get_file_path(char* dir, char* name) {
	char* path = malloc(strlen(dir) + strlen(name) + 2);
	strcpy(path, dir);
	strcat(path, "/");
	strcat(path, name);
	return path;
}

char* get_file_path_ext(char* dir, char* name, char* ext) {
	char* path = malloc(strlen(dir) + strlen(name) + strlen(ext) + 3);
	strcpy(path, dir);
	strcat(path, "/");
	strcat(path, name);
	strcat(path, ".");
	strcat(path, ext);
	return path;
}

char* file_reads(char* filepath) {
	if (filepath == NULL) return NULL;

	FILE* file = fopen(filepath, "rb");
	if (file == NULL) {
		printf("Could not open file \"%s\".", filepath);
		return NULL;
	}

	fseek(file, 0L, SEEK_END);
	size_t fileSize = ftell(file);
	rewind(file);

	char* buffer = (char*)malloc(fileSize + 1);
	if (buffer == NULL) {
		printf("Not enough memory to read \"%s\".", filepath);
		return NULL;
	}

	size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
	if (bytesRead < fileSize) {
		printf("Could not read the \"%s\".", filepath);
		return NULL;
	}

	buffer[bytesRead] = '\0';

	fclose(file);
	return buffer;
}
