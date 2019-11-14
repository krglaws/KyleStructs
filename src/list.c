
#include "include/list.h"


list* list_new()
{
  return calloc(1, sizeof(list));
}


void list_delete(list* ls)
{
  if (ls == NULL) return;

  listnode_delete_all(ls->head);

  free(ls);
}


int list_add(list* ls, const datacont* dc)
{
  if (ls == NULL || dc == NULL) return -1;

  if (ls->head) return listnode_add(ls->head, dc);

  ls->head = listnode_new(dc);

  return 0;
}


int list_remove_by(list* ls, const datacont* dc)
{
  if (ls == NULL || dc == NULL) return -1;

  return listnode_remove_by(&(ls->head), dc);
}


int list_remove_at(list* ls, int index)
{
  if (ls == NULL) return -1;
  
  return listnode_remove_at(&(ls->head), index); 
}


int list_remove_all(list* ls, const datacont* dc)
{
  if (ls == NULL || dc == NULL) return -1;

  return listnode_remove_all(&(ls->head), dc);
}


int list_replace_by(list* ls, const datacont* old_dc, const datacont* new_dc)
{
  if (ls == NULL || old_dc == NULL || new_dc == NULL) return -1;

  return listnode_replace_by(ls->head, old_dc, new_dc);
}


int list_replace_at(list* ls, const datacont* dc, int index)
{
  if (ls == NULL || dc == NULL) return -1;

  return listnode_replace_at(ls->head, dc, index);
}


int list_replace_all(list* ls, const datacont* old_dc, const datacont* new_dc)
{
  if (ls == NULL || old_dc == NULL || new_dc == NULL) return -1;

  return listnode_replace_all(ls->head, old_dc, new_dc);
}


int list_insert(list* ls, const datacont* dc, int index)
{
  if (ls == NULL || dc == NULL) return -1;

  return listnode_insert(&(ls->head), dc, index);
}


int list_index(const list* ls, const datacont* dc)
{
  if (ls == NULL || dc == NULL) return -1;

  return listnode_index(ls->head, dc);
}


datacont* list_get(const list* ls, int index)
{
  if (ls == NULL) return NULL;

  return listnode_get(ls->head, index);
}


unsigned int list_count(const list* ls, const datacont* dc)
{
  if (ls == NULL || dc == NULL) return -1;

  return listnode_count(ls->head, dc);
}


unsigned int list_length(const list* ls)
{
  if (ls == NULL) return 0;

  return listnode_length(ls->head);
}


