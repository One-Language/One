#include <stdio.h>
#include <stdlib.h>

#include "test.h"

int main()
{
	bool res;
	size_t rows;
	size_t columns;

	const char* input = "\n!!!hello!!!!\n";
	int index = 10;
	res = file_convert_index_to_rc(input, index, &rows, &columns);

	printf("==>%d, %zu:%zu\n", res == true ? 1 : 0, rows, columns);
	return 0;
}
