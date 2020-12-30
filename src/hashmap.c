#include <hashmap.h>


hashmap* hashmap_new(const enum dataconttype type, const unsigned int num_buckets)
{
  if (num_buckets == 0) return NULL;

  hashmap* hm = calloc(1, sizeof(hashmap));

  hm->type = type;

  hm->buckets = calloc(num_buckets, sizeof(treemap*));
 
  hm->num_buckets = num_buckets;
  
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
  if (hm == NULL || key == NULL || value == NULL
      || key->type != hm->type)
    return -1;

  uint32_t hash = datacont_hash(key);

  if (hm->buckets[hash % hm->num_buckets] == NULL)
    hm->buckets[hash % hm->num_buckets] = treemap_new();

  return treemap_add(hm->buckets[hash % hm->num_buckets], key, value);
}


int hashmap_remove(hashmap* hm, const datacont* key)
{
  if (hm == NULL || hm->buckets == NULL || key == NULL
      || key->type != hm->type) 
    return -1;

  uint32_t hash = datacont_hash(key);

  return treemap_remove(hm->buckets[hash % hm->num_buckets], key);
}


datacont* hashmap_get(const hashmap* hm, const datacont* key)
{
  if (hm == NULL || key == NULL
      || key->type != hm->type)
    return NULL;

  uint32_t hash = datacont_hash(key);

  return treemap_get(hm->buckets[hash % hm->num_buckets], key);
}


list* hashmap_keys(const hashmap* hm)
{
  if (hm == NULL || hm->buckets == NULL)
    return NULL;

  list* ls = list_new();
  list* temp = NULL;
  listnode* end = NULL;

  for (int i = 0; i < hm->num_buckets; i++)
  {
    if ((temp = treemap_keys(hm->buckets[i])) == NULL)
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


list* hashmap_values(const hashmap* hm)
{
  if (hm == NULL || hm->buckets == NULL)
    return NULL;

  list* ls = list_new();
  list* temp = NULL;
  listnode* end = NULL;

  for (int i = 0; i < hm->num_buckets; i++)
  {
    if ((temp = treemap_values(hm->buckets[i])) == NULL)
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


unsigned int hashmap_count(const hashmap* hm)
{
  if (hm == NULL) return 0;
  
  int count = 0;
 
  for (int i = 0; i < hm->num_buckets; i++)
    count += treemap_count(hm->buckets[i]);

  return count;
}


void hashmap_optimize(hashmap* hm)
{
  if (hm == NULL) return;

  for (int i = 0; i < hm->num_buckets; i++)
    treemap_balance(hm->buckets[i]);
}
