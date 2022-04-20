#include "math.h"
#include "../util.h"
#include <string.h>

// Swap two integers around (taking in their addresses)
void swap(int* x, int* y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}
