
#ifndef _HASHSET_H_
#define _HASHSET_H_

typedef struct hashset hashset;

struct hashset
{
  unsigned int num_buckets;
  treeset** buckets;
  unsigned long long seed;
};

hashset* hashset_new(unsigned int size);

void hashset_delete(hashset* hs);

int hashset_add(hashset* hs, const datacont* dc);

int hashset_remove(hashset* hs, const datacont* dc);

int hashset_contains(const hashset* hs, const datacont* dc);

#endif

