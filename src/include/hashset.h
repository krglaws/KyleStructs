
#ifndef _HASHSET_H_
#define _HASHSET_H_

typedef struct hashset hashset;

struct hashset
{
  const unsigned int num_buckets;
  treeset** buckets;
};

hashset* hashset_new(const unsigned int num_items, const datacont** dclist);

int hashset_add(hashset* hs, const datacont* dc);

int hashset_remove(hashset* hs, const datacont* dc);

int hashset_contains(const hashset* hs, const datacont* dc);

#endif

