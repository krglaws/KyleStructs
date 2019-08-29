
#include "include/hash.h"

unsigned long long hash(unsigned long long seed, const void* data, const unsigned int size)
{
  for (int i = 0; i < size; i++)
  {
	  unsigned char byte = *((unsigned char*) data + i);
	  seed = ((seed + byte) << 4) + ((seed * byte) >> 4);
  }
  return seed;
}

