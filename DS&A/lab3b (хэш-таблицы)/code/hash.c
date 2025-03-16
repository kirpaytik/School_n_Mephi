#include "table.h"

unsigned int hash1(unsigned int key, int msize)
{
	return key % msize;
}


unsigned int hash2(unsigned int key, int msize)
{
	if (msize == 1) {
		return 0;
	}
	return 1 + key % (msize - 1);
}
