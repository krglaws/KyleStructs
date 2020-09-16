
#include "include/treemap.h"


treemap* treemap_new()
{
  return calloc(1, sizeof(treemap));
}


void treemap_delete(treemap* tm)
{
  if (tm == NULL) return;

  treemapnode_delete_all(tm->root);

  free(tm);
}


int treemap_add(treemap* tm, const datacont* key, const datacont* value)
{
  if (tm == NULL || key == NULL || value == NULL) return -1;

  if (tm->root == NULL)
  {
    tm->root = treemapnode_new(key, value);
    return 0;
  }
  return treemapnode_add(tm->root, key, value);
}


int treemap_remove(treemap* tm, const datacont* key)
{
  if (tm == NULL) return -1;

  return treemapnode_remove(&tm->root, key);
}


datacont* treemap_get(const treemap* tm, const datacont* key)
{
  if (tm == NULL) return NULL;

  return treemapnode_get(tm->root, key);
}


datacont* treemap_get_key(const treemap* tm, int index)
{
  if (tm == NULL) return NULL;

  return treemapnode_get_key(tm->root, index);
}


list* treemap_keys(const treemap* tm)
{
  if (tm == NULL) return NULL;

  list* ls = list_new();

  ls->head = treemapnode_keys(tm->root);

  return ls;
}


list* treemap_values(const treemap* tm)
{
  if (tm == NULL) return NULL;

  list* ls = list_new();

  ls->head = treemapnode_values(tm->root);

  return ls;
}


unsigned int treemap_count(const treemap* tm)
{
  if (tm == NULL) return 0;

  return treemapnode_count(tm->root);
}


unsigned int treemap_height(const treemap* tm)
{
  if (tm == NULL) return 0;

  return treemapnode_height(tm->root);
}


void treemap_balance(treemap* tm)
{
  if (tm == NULL) return;

  treemapnode_balance(&tm->root);
}

