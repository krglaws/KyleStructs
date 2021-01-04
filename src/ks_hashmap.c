#include <stdlib.h>
#include <stdint.h>

#include <ks_types.h>
#include <ks_datacont.h>
#include <ks_listnode.h>
#include <ks_list.h>
#include <ks_treemapnode.h>
#include <ks_treemap.h>
#include <ks_hashmap.h>


ks_hashmap* ks_hashmap_new(const enum ks_datatype type, const unsigned int num_buckets)
{
  if (num_buckets == 0) return NULL;

  ks_hashmap* hm = calloc(1, sizeof(ks_hashmap));

  hm->type = type;

  hm->buckets = calloc(num_buckets, sizeof(ks_treemap*));
 
  hm->num_buckets = num_buckets;
  
  return hm;
}


void ks_hashmap_delete(ks_hashmap* hm)
{
  if (hm == NULL) return;

  for (int i = 0; i < hm->num_buckets; i++)
    ks_treemap_delete(hm->buckets[i]);

  free(hm->buckets);
  free(hm);
}


ks_hashmap* ks_hashmap_copy(const ks_hashmap* hm)
{
  if (hm == NULL) return NULL;

  ks_hashmap* hm_copy = ks_hashmap_new(hm->type, hm->num_buckets);

  for (int i = 0; i < hm->num_buckets; i++)
  {
    hm_copy->buckets[i] = ks_treemap_copy(hm->buckets[i]);
  }

  return hm_copy;
}


int ks_hashmap_add(ks_hashmap* hm, const ks_datacont* key, const ks_datacont* value)
{
  if (hm == NULL || key == NULL || value == NULL
      || key->type != hm->type)
    return -1;

  uint32_t hash = ks_datacont_hash(key);

  if (hm->buckets[hash % hm->num_buckets] == NULL)
    hm->buckets[hash % hm->num_buckets] = ks_treemap_new();

  return ks_treemap_add(hm->buckets[hash % hm->num_buckets], key, value);
}


int ks_hashmap_remove(ks_hashmap* hm, const ks_datacont* key)
{
  if (hm == NULL || hm->buckets == NULL || key == NULL
      || key->type != hm->type) 
    return -1;

  uint32_t hash = ks_datacont_hash(key);

  return ks_treemap_remove(hm->buckets[hash % hm->num_buckets], key);
}


ks_datacont* ks_hashmap_get(const ks_hashmap* hm, const ks_datacont* key)
{
  if (hm == NULL || key == NULL
      || key->type != hm->type)
    return NULL;

  uint32_t hash = ks_datacont_hash(key);

  return ks_treemap_get(hm->buckets[hash % hm->num_buckets], key);
}


ks_datacont* ks_hashmap_get_key(const ks_hashmap* hm, int index)
{
  if (hm == NULL) return NULL;

  int start = index < 0 ? hm->num_buckets - 1 : 0;
  int end = index < 0 ? -1 : hm->num_buckets;
  int dir = index < 0 ? -1 : 1;

  for (; start != end; start += dir)
  {
    ks_treemap* tm = hm->buckets[start];

    ks_datacont* dc = ks_treemap_get_key(tm, index);

    if (dc != NULL)
      return dc;

    index -= (dir * ks_treemap_count(tm));
  }

  return NULL;
}


unsigned int ks_hashmap_count(const ks_hashmap* hm)
{
  if (hm == NULL) return 0;

  int count = 0;
 
  for (int i = 0; i < hm->num_buckets; i++)
    count += ks_treemap_count(hm->buckets[i]);

  return count;
}


void ks_hashmap_optimize(ks_hashmap* hm)
{
  if (hm == NULL) return;

  for (int i = 0; i < hm->num_buckets; i++)
    ks_treemap_balance(hm->buckets[i]);
}
