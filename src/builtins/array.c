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

/**
 * Push an item to the array.
 * @note This is useful when you want to push an item to the array.
 * 
 * @return void
 * 
 * @param array_t* array
 * 
 * @code
 * array_t* array = array_init();
 * array_push(array, "Hello");
 * array_push(array, "World");
 * @endcode
*/
void array_push(array_t *array, void *item)
{
	if (array->count == array->capacity) {
		// Set size of new array to 4, and double size if it's next...
		array->capacity = array->capacity == 0 ? 4 : 2 * array->capacity;
		array->data = (void **)realloc(array->data, array->capacity * sizeof(void *));
	}

	array->data[array->count] = item;
	array->count++;
}

/**
 * Get the first item of the array.
 * @note This is useful when you want to get the first item of the array.
 * 
 * @return void*
 * 
 * @param array_t* list
 * 
 * @code
 * array_t* array = array_init();
 * array_push(array, "Hello");
 * array_push(array, "World");
 * void* first = array_first(array);
 * printf("%s\n", first); // Hello
 * @endcode
*/
void* array_first(array_t *array)
{
	if (array->count == 0) {
		return NULL;
	}

	return array->data[0];
}

/**
 * Get the first item of the array.
 * @note This is useful when you want to get the last item of the array.
 * 
 * @return void*
 * 
 * @param array_t* list
 * 
 * @code
 * array_t* array = array_init();
 * array_push(array, "Hello");
 * array_push(array, "World");
 * void* last = array_last(array);
 * printf("%s\n", last); // Hello
 * @endcode
*/
void* array_last(array_t *array)
{
	if (array->count == 0) {
		return NULL;
	}

	return array->data[array->count - 1];
}

/**
 * Get the last item of the array.
 * @note This is useful when you want to get the last item of the array.
 * 
 * @return void*
 * 
 * @param array_t* list
 * 
 * @code
 * array_t* array = array_init();
 * array_push(array, "Hello");
 * array_push(array, "World");
 * void* last = array_pop(array);
 * printf("%s\n", last); // World
 * @endcode
*/
void *array_pop(array_t* list)
{
	// debug("array_pop");

	list->count--;
	void *ret = list->data[list->count];
	return ret;
}

/**
 * Free the array.
 * @note This is useful when you want to free the array.
 * 
 * @return void
 * 
 * @param array_t* list
 * 
 * @code
 * array_t* array = array_init();
 * array_free(array);
 * @endcode
*/
void array_free(array_t* list)
{
	// debug("array_free");

	free(list->data); // it's void**
	list->count = list->capacity = 0;
	list->data = NULL;
}

/**
 * Get the item at the index.
 * @note This is useful when you want to get the item at the index.
 * 
 * @return void*
 * 
 * @param array_t* array
 * @param int index
 * 
 * @code
 * array_t* array = array_init();
 * array_push(array, "Hello");
 * array_push(array, "World");
 * void* item = array_getat(array, 0);
 * printf("%s\n", item); // Hello
 * @endcode
*/
void* array_getat(array_t* array, int index)
{
	if (index >= array->count) {
		return NULL;
	}

	return array->data[index];
}