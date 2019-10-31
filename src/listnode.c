
#include <stdlib.h>

#include "include/datacont.h"
#include "include/listnode.h"


listnode* listnode_new(const datacont* dc)
{
  if (dc == NULL) return NULL;

  listnode* ln = calloc(1, sizeof(listnode));

  ln->dc = (datacont*) dc;

  return ln;
}


void listnode_delete(listnode* ln)
{
  if (ln == NULL) return;
  
  if (ln->dc) datacont_delete(ln->dc);
  
  free(ln);
}


void listnode_delete_all(listnode* ln)
{
  if (ln == NULL) return;

  listnode_delete_all(ln->next);
  
  listnode_delete(ln);
}


int listnode_add(listnode* ln, const datacont* dc)
{
  if (ln == NULL || dc == NULL) return -1;

  if (ln->next) return listnode_add(ln->next, dc);

  ln->next = listnode_new(dc);
  
  return 0;
}


int listnode_remove_by(listnode** ln, const datacont* dc)
{
  if (ln == NULL || *ln == NULL || dc == NULL) return -1;

  if (datacont_compare(dc, (*ln)->dc) == EQUAL)
  {
    listnode* temp = (*ln)->next;
    listnode_delete(*ln);
    *ln = temp;
    return 1;
  }

  if ((*ln)->next) 
    return listnode_remove_by(&((*ln)->next), dc);
  return 0;
}


int listnode_remove_at(listnode** ln, int index)
{
  if (ln == NULL || *ln == NULL || 
      index < 0 && (index = listnode_length(*ln) + index) < 0)
    return -1;

  if (index == 0)
  {
    listnode* temp = (*ln)->next;
    listnode_delete(*ln);
    *ln = temp;
    return 0;
  }

  if ((*ln)->next)
    return listnode_remove_at(&((*ln)->next), index-1);
  return -1;
}


int listnode_remove_all(listnode** ln, const datacont* dc)
{
  if (ln == NULL || *ln == NULL || dc == NULL) return -1;

  if (datacont_compare(dc, (*ln)->dc) == EQUAL)
  {
    listnode* temp = (*ln)->next;
    listnode_delete(*ln);
    *ln = temp;
    if ((*ln) && (*ln)->next)
      return 1 + listnode_remove_all(&((*ln)->next), dc);
    return 1;
  }
  
  if ((*ln)->next)
    return listnode_remove_all(&(*ln)->next, dc);
  return 0;
}


int listnode_replace_by(listnode* ln, const datacont* old_dc, const datacont* new_dc)
{
  if (ln == NULL || old_dc == NULL || new_dc == NULL) return -1;

  if (datacont_compare(old_dc, ln->dc) == EQUAL)
  {
    datacont_delete(ln->dc);
    ln->dc = (datacont*) new_dc;
    return 0;
  }

  return listnode_replace_by(ln->next, old_dc, new_dc);
}


int listnode_replace_at(listnode* ln, const datacont* dc, int index)
{
  if (ln == NULL || dc == NULL ||
      index < 0 && (index = listnode_length(ln) + index) < 0)
    return -1;

  if (index == 0)
  {
    datacont_delete(ln->dc);
    ln->dc = (datacont*) dc;
    return 0;
  }

  return listnode_replace_at(ln->next, dc, index-1);
}


int listnode_replace_all(listnode* ln, const datacont* old_dc, const datacont* new_dc)
{
  if (ln == NULL || old_dc == NULL || new_dc == NULL)
    return -1;

  if (datacont_compare(old_dc, ln->dc) == EQUAL)
  {
    datacont_delete(ln->dc);
    ln->dc = (datacont*) new_dc;
    
    if (ln->next)
    { 
      datacont* copy = datacont_copy(new_dc);
      int result = listnode_replace_all(ln->next, old_dc, copy);
      if (result == 0) datacont_delete(copy);
      return 1 + result; 
    }
    return 1;
  }

  else if (ln->next)
    return listnode_replace_all(ln->next, old_dc, new_dc);
  return 0;
}


int listnode_insert(listnode** ln, const datacont* dc, int index)
{
  if (ln == NULL || *ln == NULL || dc == NULL ||
      index < 0 && (index = listnode_length(*ln) + index) < 0)
    return -1;

  if (index == 0)
  {
    listnode* new_node = listnode_new(dc);
    new_node->next = *ln;
    *ln = new_node;
    return 0;
  }

  return listnode_insert(&((*ln)->next), dc, index-1);
}


static int __listnode_index(const listnode* ln, const datacont* dc, int curr_index)
{
  if (ln == NULL || dc == NULL) return -1;

  if (datacont_compare(dc, ln->dc) == EQUAL)
    return curr_index;

  return __listnode_index(ln->next, dc, curr_index+1);
}

int listnode_index(const listnode* ln, const datacont* dc)
{
  return __listnode_index(ln, dc, 0); 
}


datacont* listnode_get(const listnode* ln, int index)
{
  if (ln == NULL || 
      index < 0 && (index = listnode_length(ln) + index) < 0)
    return NULL;

  if (index == 0) return datacont_copy(ln->dc);
  
  return listnode_get(ln->next, index-1);
}


unsigned int listnode_count(const listnode* ln, const datacont* dc)
{
  if (ln == NULL || dc == NULL) return -1;

  if (datacont_compare(dc, ln->dc) == EQUAL)
  {
    if (ln->next)
      return 1 + listnode_count(ln->next, dc);
    return 1;
  }

  if (ln->next)
    return listnode_count(ln->next, dc);
  return 0;
}


unsigned int listnode_length(const listnode* ln)
{
  if (ln == NULL) return 0;
  
  return 1 + listnode_length(ln->next); 
}

