
#include <stdlib.h>

#include "include/datacont.h"
#include "treemapnode.h"


treemap* treemap_new()
{
  return calloc(1, sizeof(treemap));
}


void treemap_delete(treemap* tm)
{
  treemapnode_delete(tm->root);
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
  else return treemapnode_add(tm->root, key, value);
}


int treemap_remove(treemap* tm, const datacont* key)
{
  if (tm == NULL) return 1;
  return treemapnode_remove(&tm->root, key);
}


datacont* treemap_get(const treemap* tm, const datacont* key)
{
  if (tm == NULL) return NULL;
  return treemapnode_get(tm->root, key);
}


listnode* treemap_getkeys(const treemap* tm)
{
  if (tm == NULL) return NULL;
  return treemapnode_getkeys(tm->root);
}


listnode* treemap_getvalues(const treemap* tm)
{
  if (tm == NULL) return NULL;
  return treemapnode_getvalues(tm->root);
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

