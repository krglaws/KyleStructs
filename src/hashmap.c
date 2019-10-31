
#include <stdlib.h>

#include "include/datacont.h"
#include "include/listnode.h"
#include "include/treemapnode.h"
#include "include/treemap.h"
#include "include/hashmap.h"


hashmap* hashmap_new(const unsigned int num_buckets, const unsigned long long seed)
{
  hashmap* hm = calloc(1, sizeof(hashmap));
  hm->seed = seed;
  hm->num_buckets = num_buckets;
  
  if (num_buckets > 0)
    hm->buckets = calloc(num_buckets, sizeof(treemap*));

  return hm;
}


void hashmap_delete(hashmap* hm)
{
  if (hm == NULL) return;
  for (int i = 0; i < hm->num_buckets; i++)
    treemap_delete(hm->buckets[i]);
  free(hm->buckets);
  free(hm);
}


int hashmap_add(hashmap* hm, const datacont* key, const datacont* value)
{
  if (hm == NULL || key == NULL || value == NULL)
    return -1;

  unsigned long long hashval = datacont_hash(hm->seed, key);

  if (hm->buckets[hashval % hm->num_buckets] == NULL)
    hm->buckets[hashval % hm->num_buckets] = treemap_new();

  return treemap_add(hm->buckets[hashval % hm->num_buckets], key, value);
}


int hashmap_remove(hashmap* hm, const datacont* key)
{
  if (hm == NULL || hm->buckets == NULL || key == NULL) 
    return 1;

  unsigned long long hashval = datacont_hash(hm->seed, key);

  if (hm->buckets[hashval % hm->num_buckets] == NULL)
    return 1;

  return treemap_remove(hm->buckets[hashval % hm->num_buckets], key);
}


datacont* hashmap_get(const hashmap* hm, const datacont* key)
{
  if (hm == NULL || key == NULL)
    return NULL;

  unsigned long long hashval = datacont_hash(hm->seed, key);

  return treemap_get(hm->buckets[hashval % hm->num_buckets], key);
}


listnode* hashmap_getkeys(const hashmap* hm)
{
  if (hm == NULL || hm->buckets == NULL || hm->num_buckets == 0)
    return NULL;

  listnode* ln = NULL;

  for (int i = 0; i < hm->num_buckets; i++)
  {
    listnode* temp = treemap_getkeys(hm->buckets[i]);

    if (temp == NULL) continue;

    if (ln == NULL) ln = temp;
    else {
      listnode* end = ln;
      while(end->next) end = end->next;
      end->next = temp;
    }
  }
  return ln;
}


listnode* hashmap_getvalues(const hashmap* hm)
{
  if (hm == NULL || hm->buckets == NULL || hm->num_buckets == 0)
    return NULL;

  listnode* ln = NULL;

  for (int i = 0; i < hm->num_buckets; i++)
  {
    listnode* temp = treemap_getvalues(hm->buckets[i]);

    if (temp == NULL) continue;

    if (ln == NULL) ln = temp;
    else {
      listnode* end = ln;
      while(end->next) end = end->next;
      end->next = temp;
    }
  }
  return ln;
}


unsigned int hashmap_count(const hashmap* hm)
{
  if (hm == NULL) return 0;
  unsigned int sum = 0;
  for (int i = 0; i < hm->num_buckets; i++)
    sum += treemap_count(hm->buckets[i]);
  return sum;
}

