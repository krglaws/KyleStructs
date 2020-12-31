#include <stdlib.h>
#include <stdint.h>

#include <ks_datacont.h>
#include <ks_list.h>
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


ks_list* ks_hashmap_keys(const ks_hashmap* hm)
{
  if (hm == NULL || hm->buckets == NULL)
    return NULL;

  ks_list* ls = ks_list_new();
  ks_list* temp = NULL;
  ks_listnode* end = NULL;

  for (int i = 0; i < hm->num_buckets; i++)
  {
    if ((temp = ks_treemap_keys(hm->buckets[i])) == NULL)
      continue;

    if (ls->head == NULL)
    {
      ls->head = end = temp->head;
      free(temp);
    }
    else
    {
      while (end->next) end = end->next;
      end->next = temp->head;
    }
  }
  return ls;
}


ks_list* ks_hashmap_values(const ks_hashmap* hm)
{
  if (hm == NULL || hm->buckets == NULL)
    return NULL;

  ks_list* ls = ks_list_new();
  ks_list* temp = NULL;
  ks_listnode* end = NULL;

  for (int i = 0; i < hm->num_buckets; i++)
  {
    if ((temp = ks_treemap_values(hm->buckets[i])) == NULL)
      continue;

    if (ls->head == NULL)
    {
      ls->head = end = temp->head;
      free(temp);
    }
    else
    {
      while (end->next) end = end->next;
      end->next = temp->head;
    }
  }
  return ls;
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
