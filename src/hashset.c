
#include "include/hashset.h"


hashset* hashset_new(const enum dataconttype type, const unsigned int num_buckets)
{
  if (num_buckets == 0) return NULL;

  hashset* hs = calloc(1, sizeof(hashset));

  hs->type = type;

  hs->buckets = calloc(num_buckets, sizeof(treeset*));

  hs->num_buckets = num_buckets;

  return hs;
}


void hashset_delete(hashset* hs)
{
  if (hs == NULL) return;

  for (int i = 0; i < hs->num_buckets; i++)
    treeset_delete(hs->buckets[i]);

  free(hs->buckets);
  free(hs);
}


int hashset_add(hashset* hs, const datacont* dc)
{
  if (hs == NULL || dc == NULL 
      || dc->type != hs->type) return -1;

  uint32_t hash = datacont_hash(dc);

  if (hs->buckets[hash % hs->num_buckets] == NULL)
    hs->buckets[hash % hs->num_buckets] = treeset_new();

  return treeset_add(hs->buckets[hash % hs->num_buckets], dc);
}


int hashset_remove(hashset* hs, const datacont* dc)
{
  if (hs == NULL || dc == NULL
      || dc->type != hs->type) return -1;

  uint32_t hash = datacont_hash(dc);

  return treeset_remove_by(hs->buckets[hash % hs->num_buckets], dc);
}


unsigned int hashset_contains(const hashset* hs, const datacont* dc)
{
  if (hs == NULL || dc == NULL
      || dc->type != hs->type) return 0;

  uint32_t hash = datacont_hash(dc);

  if (hs->buckets[hash % hs->num_buckets] == NULL) return 0;

  return treeset_contains(hs->buckets[hash % hs->num_buckets], dc);
}


unsigned int hashset_count(const hashset* hs)
{
  if (hs == NULL) return 0;

  int count = 0;

  for (int i = 0; i < hs->num_buckets; i++)
    count += treeset_count(hs->buckets[i]);

  return count;
}


list* hashset_to_list(const hashset* hs)
{
  if (hs == NULL) return NULL;

  list* ls = list_new();

  for (int i = 0, j = 0; i < hs->num_buckets; i++, j = 0)
    while (list_add(ls, datacont_copy(treeset_get(hs->buckets[i], j++))) != -1);

  return ls;
}


void hashset_optimize(hashset* hs)
{
  if (hs == NULL) return;

  for (int i = 0; i < hs->num_buckets; i++)
    treeset_balance(hs->buckets[i]);
}

