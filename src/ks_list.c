#include <stdlib.h>

#include <ks_datacont.h>
#include <ks_listnode.h>
#include <ks_list.h>


ks_list* ks_list_new()
{
  return calloc(1, sizeof(ks_list));
}


void ks_list_delete(ks_list* ls)
{
  if (ls == NULL) return;

  ks_listnode_delete_all(ls->head);

  free(ls);
}


int ks_list_add(ks_list* ls, const ks_datacont* dc)
{
  if (ls == NULL || dc == NULL) return -1;

  if (ls->head) return ks_listnode_add(ls->head, dc);

  ls->head = ks_listnode_new(dc);

  return 0;
}


int ks_list_remove_by(ks_list* ls, const ks_datacont* dc)
{
  if (ls == NULL || dc == NULL) return -1;

  return ks_listnode_remove_by(&(ls->head), dc);
}


int ks_list_remove_at(ks_list* ls, int index)
{
  if (ls == NULL) return -1;
  
  return ks_listnode_remove_at(&(ls->head), index); 
}


int ks_list_remove_all(ks_list* ls, const ks_datacont* dc)
{
  if (ls == NULL || dc == NULL) return -1;

  return ks_listnode_remove_all(&(ls->head), dc);
}


int ks_list_replace_by(ks_list* ls, const ks_datacont* old_dc, const ks_datacont* new_dc)
{
  if (ls == NULL || old_dc == NULL || new_dc == NULL) return -1;

  return ks_listnode_replace_by(ls->head, old_dc, new_dc);
}


int ks_list_replace_at(ks_list* ls, const ks_datacont* dc, int index)
{
  if (ls == NULL || dc == NULL) return -1;

  return ks_listnode_replace_at(ls->head, dc, index);
}


int ks_list_replace_all(ks_list* ls, const ks_datacont* old_dc, const ks_datacont* new_dc)
{
  if (ls == NULL || old_dc == NULL || new_dc == NULL) return -1;

  return ks_listnode_replace_all(ls->head, old_dc, new_dc);
}


int ks_list_insert(ks_list* ls, const ks_datacont* dc, int index)
{
  if (ls == NULL || dc == NULL) return -1;

  return ks_listnode_insert(&(ls->head), dc, index);
}


int ks_list_index(const ks_list* ls, const ks_datacont* dc)
{
  if (ls == NULL || dc == NULL) return -1;

  return ks_listnode_index(ls->head, dc);
}


ks_datacont* ks_list_get(const ks_list* ls, int index)
{
  if (ls == NULL) return NULL;

  return ks_listnode_get(ls->head, index);
}


unsigned int ks_list_count(const ks_list* ls, const ks_datacont* dc)
{
  if (ls == NULL || dc == NULL) return -1;

  return ks_listnode_count(ls->head, dc);
}


unsigned int ks_list_length(const ks_list* ls)
{
  if (ls == NULL) return 0;

  return ks_listnode_length(ls->head);
}
