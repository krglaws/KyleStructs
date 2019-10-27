
#include <stdlib.h>

#include "include/datacont.h"
#include "include/treesetnode.h"
#include "include/treeset.h"
#include "include/hashset.h"


hashset* hashset_new(const unsigned int size, const unsigned long long seed)
{
  hashset* hs = (hashset*) calloc(1, sizeof(hashset));

  if (size > 0)
    hs->buckets = (treeset**) calloc(size, sizeof(treeset*));
  else
    hs->buckets = NULL;

  hs->num_buckets = size;
  hs->seed = seed;
  return hs;
}


void hashset_delete(hashset* hs)
{
  if (hs == NULL) return;

  for (int i = 0; i < hs->num_buckets; i++)
    treeset_delete(hs->buckets[i]);

  free(hs);
}


int hashset_add(hashset* hs, const datacont* dc)
{
  const unsigned long long hashval = datacont_hash(hs->seed, dc);

  if (hs->buckets[hashval % hs->num_buckets] == NULL)
    hs->buckets[hashval % hs->num_buckets] = treeset_new();

  return treeset_add(hs->buckets[hashval % hs->num_buckets], dc);
}


int hashset_remove(hashset* hs, const datacont* dc)
{
  const unsigned long long hashval = datacont_hash(hs->seed, dc);

  return treeset_remove(hs->buckets[hashval % hs->num_buckets], dc);
}


int hashset_contains(const hashset* hs, const datacont* dc)
{
  if (hs == NULL || dc == NULL)
    return 0;

  const unsigned long long hashval = datacont_hash(hs->seed, dc);

  if (hs->buckets[hashval % hs->num_buckets] == NULL)
    return 0;

  return treeset_contains(hs->buckets[hashval % hs->num_buckets], dc);
}
