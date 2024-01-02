#include "string.h"

string_t* string_init() {
    string_t* str = malloc(sizeof(string_t));
    if (str == NULL) {
        printf("Error: Not enough memory to create a string.");
        exit(74);
    }

    str->length = str->capacity = 0;
    str->data = NULL;

    return str;
}

string_t* string_init_size(size_t capacity) {
    string_t* str = malloc(sizeof(string_t));
    if (str == NULL) {
        printf("Error: Not enough memory to create a string.");
        exit(74);
    }

    str->length = 0;
    str->capacity = capacity;
    str->data = calloc(capacity, sizeof(char));
    if (str->data == NULL) {
        printf("Error: Not enough memory to create a string.");
        exit(74);
    }

    return str;
}

size_t string_length(string_t* str)
{
    return str->length;
}

size_t string_capacity(string_t* str)
{
    return str->capacity;
}

void string_append(string_t* str, const char* item)
{
    size_t item_length = strlen(item);

    if (str->length + item_length >= str->capacity) {
        str->capacity = str->length + item_length + 1;
        str->data = realloc(str->data, str->capacity * sizeof(char));
        if (str->data == NULL) {
            printf("Error: Not enough memory to append to the string.");
            exit(74);
        }
    }

    strcat(str->data, item);
    str->length += item_length;
}

void string_append_char(string_t* str, char ch)
{
    if (str->length + 1 >= str->capacity) {
        str->capacity = str->length + 2;
        str->data = realloc(str->data, str->capacity * sizeof(char));
        if (str->data == NULL) {
            printf("Error: Not enough memory to append character to the string.");
            exit(74);
        }
    }

    str->data[str->length] = ch;
    str->length++;
    str->data[str->length] = '\0';
}

char* string_to_array(string_t* str)
{
    return str->data;
}

void string_free(string_t* str)
{
    free(str->data);
    str->length = str->capacity = 0;
    str->data = NULL;
}

char string_char_at(string_t* str, int index)
{
    if (index < 0 || index >= str->length) {
        printf("Error: Index out of bounds.");
        exit(74);
    }

    return str->data[index];
}

void string_set_char_at(string_t* str, int index, char ch)
{
    if (index < 0 || index >= str->length) {
        printf("Error: Index out of bounds.");
        exit(74);
    }

    str->data[index] = ch;
}
