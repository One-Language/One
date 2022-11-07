#include "array.h"

array* array_new() {
    array* a = malloc(sizeof(array));
    a->data = malloc(sizeof(void*) * 8);
    a->size = 0;
    a->capacity = 8;
    return a;
}

void array_push(array* a, void* item) {
    if (a->size == a->capacity) {
        a->capacity *= 2;
        a->data = realloc(a->data, sizeof(void*) * a->capacity);
    }
    a->data[a->size++] = item;
}

void* array_pop(array* a) {
    if (a->size == 0) return NULL;
    return (void*) a->data[--a->size];
}

void* array_get(array* a, int index) {
    if (index < 0 || index >= a->size) return NULL;
    return (void*) a->data[index];
}

void array_set(array* a, int index, void* item) {
    if (index < 0 || index >= a->size) return;
    a->data[index] = item;
}

void array_free(array* a) {
    free(a->data);
    free(a);
}

void array_clear(array* a) {
    a->size = 0;
}

int array_size(array* a) {
    return a->size;
}

void array_resize(array* a, int size) {
    if (size < 0) return;
    if (size > a->capacity) {
        a->capacity = size;
        a->data = realloc(a->data, sizeof(void*) * a->capacity);
    }
    a->size = size;
}

void array_insert(array* a, int index, void* item) {
    if (index < 0 || index > a->size) return;
    if (a->size == a->capacity) {
        a->capacity *= 2;
        a->data = realloc(a->data, sizeof(void*) * a->capacity);
    }
    for (int i = a->size; i > index; i--) {
        a->data[i] = a->data[i - 1];
    }
    a->data[index] = item;
    a->size++;
}

void array_remove(array* a, int index) {
    if (index < 0 || index >= a->size) return;
    for (int i = index; i < a->size - 1; i++) {
        a->data[i] = a->data[i + 1];
    }
    a->size--;
}

void array_remove_range(array* a, int start, int end) {
    if (start < 0 || start >= a->size) return;
    if (end < 0 || end >= a->size) return;
    if (start > end) return;
    for (int i = start; i < end; i++) {
        a->data[i] = a->data[i + 1];
    }
    a->size -= end - start;
}

void array_reverse(array* a) {
    for (int i = 0; i < a->size / 2; i++) {
        void* temp = a->data[i];
        a->data[i] = a->data[a->size - i - 1];
        a->data[a->size - i - 1] = temp;
    }
}

void array_foreach(array* a, void (*callback)(void*)) {
    for (int i = 0; i < a->size; i++) {
        callback(a->data[i]);
    }
}

// void array_sort(array* a, int (*compare)(void*, void*)) {
//     for (int i = 0; i < a->size; i++) {
//         for (int j = i + 1; j < a->size; j++) {
//             if (compare(a->data[i], a->data[j]) > 0) {
//                 void* temp = a->data[i];
//                 a->data[i] = a->data[j];
//                 a->data[j] = temp;
//             }
//         }
//     }
// }
