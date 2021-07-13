/**
 The One Programming Language

 File: builtins/string.c
  _        _
 / \ |\ | |_    Max Base
 \_/ | \| |_    Copyright 2021; One Language Contributors

 **/

#include "string.h"

/*
 * @function: string_new
 * @desctipion: Creates a new string,
 * if there is not enough memory, will return a null pointer instead.
 * @arguments: nothing
 * @return: mallocated string
 */
string* string_new()
{
	// allocate space for the string struct
	string* ss = malloc(sizeof(string));
	// quit if no memory
	if (NULL == ss) goto string_new_fail;

	// allocate space for the string itself
	ss->str = malloc(STRING_SIZE_INIT);
	// quit and cleanup if this failed
	if (NULL == ss->str) goto string_new_fail;

	// set up the other bits of the string string
	ss->end = ss->str;
	*ss->end = '\0';
	ss->size = STRING_SIZE_INIT;

	return ss;
string_new_fail:
	free(ss);
	return NULL;
}

/*
 * @function: string_append
 * @description: Append to a string string, growing the allocated memory if needed
 * on error, will return the longest string possible, which may truncate the
 * suffix.
 * @arguments: string target, char* value want to be added
 * @return: void
 */
void string_append(string* ss, char* suffix)
{
	// iterate through suffix by character. Could be more efficient by using
	// memcopy or similar, but the idea is the same.
	while (*suffix != '\0')
	{
		// Check to see if the string needs to grow or not.
		// also make sure we leave space for the null-termination byte at the end
		if (!((ss->end - ss->str) < (ss->size - 1)))
		{
			// store the offset, since the end ptr will not be valid if realloc
			// moves our memory block
			size_t offset = ss->end - ss->str;
			// allocate bigger space, grows by doubling (good amortization)
			char* newstr = realloc(ss->str, (ss->size * 2));
			// if we're out of memory, we bail out.
			if (NULL == newstr)
			{
				ss->end--;
				break;
			}
			// reset the string string's internal to reflect the new size and
			// possible memory block
			ss->str = newstr;
			ss->size = ss->size * 2;
			ss->end = ss->str + offset;
		}
		//append chars to the string
		*(ss->end) = *suffix;
		suffix++;
		ss->end++;
	}
	// make sure we're always null terminated correctly.
	*(ss->end) = '\0';
}
