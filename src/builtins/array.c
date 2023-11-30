#include "array.h"

/**
 * Initialize an array.
 * @note This is useful when you want to create an array and don't know the size and capacity. so it starts from 0.
 * 
 * @return array_t*
 * 
 * @code
 * array_t* array = array_init();
 * @endcode
*/
array_t* array_init()
{
    array_t *array = malloc(sizeof(array_t));
    if (array == NULL) {
        printf("Error: Not enough memory to create an array.");
        exit(74);
    }

    array->count = array->capacity = 0;
    array->data = NULL;

    return array;
}

/**
 * Initialize an array with a size and capacity.
 * @note This is useful when you want to create an array with a specific size and capacity.

 * @return array_t*
 * 
 * @param size_t size
 * @param size_t capacity
 * 
 * @code
 * array_t* array = array_init_size(0, 0);
 * @endcode
 * 
*/
array_t* array_init_size(size_t size, size_t capacity)
{
    array_t *array = malloc(sizeof(array_t));
    if (array == NULL) {
        printf("Error: Not enough memory to create an array.");
        exit(74);
    }

    array->count = array->capacity = 0;
    array->data = NULL;

    return array;
}

/**
 * Get the size of the array.
 * @note This is the size of the allocated memory.
 * @note This is not the number of data inside the array.
 * 
 * @return size_t
 * 
 * @param array_t* array
 */
size_t array_size(array_t* array)
{
    return array->count;
}

/**
 * Get the count of the array.
 * @note This is the number of data inside the array.
 * @note This is not the size of the allocated memory.
 * 
 * @return size_t
 * 
 * @param array_t* array
 * 
*/
size_t array_count(array_t* array)
{
    return array->count;
}

void array_push(array_t *array, void *item)
{
	if (array->count == array->capacity) {
		// Set size of new array to 4, and double size if it's next...
		array->capacity = array->capacity == 0 ? 4 : 2 * array->size;
		array->data = (void **)realloc(array->data, array->size * sizeof(void *));
	}

	array->data[array->count] = item;
	array->count++;
}

void *array_pop(array_t* list)
{
	// debug("array_pop");

	list->count--;
	void *ret = list->data[list->count];
	return ret;
}

void array_free(array_t* list)
{
	// debug("array_free");

	free(list->data); // it's void**
	list->count = list->capacity = 0;
	list->data = NULL;
}
