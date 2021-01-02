#include <stdlib.h>
#include <stdint.h>

#include <ks_types.h>
#include <ks_datacont.h>
#include <ks_listnode.h>
#include <ks_list.h>
#include <ks_treesetnode.h>
#include <ks_treeset.h>
#include <ks_hashset.h>


ks_hashset* ks_hashset_new(const enum ks_datatype type, const unsigned int num_buckets)
{
  if (num_buckets == 0) return NULL;

  ks_hashset* hs = calloc(1, sizeof(ks_hashset));

  hs->type = type;

  hs->buckets = calloc(num_buckets, sizeof(ks_treeset*));

  hs->num_buckets = num_buckets;

  return hs;
}


void ks_hashset_delete(ks_hashset* hs)
{
  if (hs == NULL) return;

  for (int i = 0; i < hs->num_buckets; i++)
    ks_treeset_delete(hs->buckets[i]);

  free(hs->buckets);
  free(hs);
}


ks_hashset* ks_hashset_copy(const ks_hashset* hs)
{
  if (hs == NULL) return NULL;

  ks_hashset* hs_copy = ks_hashset_new(hs->type, hs->num_buckets);

  for (int i = 0; i < hs->num_buckets; i++)
  {
    hs_copy->buckets[i] = ks_treeset_copy(hs->buckets[i]);
  }

  return hs_copy;
}


int ks_hashset_add(ks_hashset* hs, const ks_datacont* dc)
{
  if (hs == NULL || dc == NULL 
      || dc->type != hs->type) return -1;

  uint32_t hash = ks_datacont_hash(dc);

  if (hs->buckets[hash % hs->num_buckets] == NULL)
    hs->buckets[hash % hs->num_buckets] = ks_treeset_new();

  return ks_treeset_add(hs->buckets[hash % hs->num_buckets], dc);
}


int ks_hashset_remove(ks_hashset* hs, const ks_datacont* dc)
{
  if (hs == NULL || dc == NULL
      || dc->type != hs->type) return -1;

  uint32_t hash = ks_datacont_hash(dc);

  return ks_treeset_remove_by(hs->buckets[hash % hs->num_buckets], dc);
}


unsigned int ks_hashset_contains(const ks_hashset* hs, const ks_datacont* dc)
{
  if (hs == NULL || dc == NULL
      || dc->type != hs->type) return 0;

  uint32_t hash = ks_datacont_hash(dc);

  if (hs->buckets[hash % hs->num_buckets] == NULL) return 0;

  return ks_treeset_contains(hs->buckets[hash % hs->num_buckets], dc);
}


unsigned int ks_hashset_count(const ks_hashset* hs)
{
  if (hs == NULL) return 0;

  int count = 0;

  for (int i = 0; i < hs->num_buckets; i++)
    count += ks_treeset_count(hs->buckets[i]);

  return count;
}


ks_list* ks_hashset_to_list(const ks_hashset* hs)
{
  if (hs == NULL) return NULL;

  ks_list* ls = ks_list_new();

  for (int i = 0, j = 0; i < hs->num_buckets; i++, j = 0)
    while (ks_list_add(ls, ks_datacont_copy(ks_treeset_get(hs->buckets[i], j++))) != -1);

  return ls;
}


void ks_hashset_optimize(ks_hashset* hs)
{
  if (hs == NULL) return;

  for (int i = 0; i < hs->num_buckets; i++)
    ks_treeset_balance(hs->buckets[i]);
}
