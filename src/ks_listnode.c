#include <stdlib.h>

#include <ks_types.h>
#include <ks_datacont.h>
#include <ks_listnode.h>


ks_listnode* ks_listnode_new(const ks_datacont* dc)
{
  if (dc == NULL) return NULL;

  ks_listnode* ln = calloc(1, sizeof(ks_listnode));

  ln->dc = (ks_datacont*) dc;

  return ln;
}


void ks_listnode_delete(ks_listnode* ln)
{
  if (ln == NULL) return;

  if (ln->dc) ks_datacont_delete(ln->dc);
  
  free(ln);
}


ks_listnode* ks_listnode_copy(const ks_listnode* ln)
{
  if (ln == NULL) return NULL;

  ks_datacont* dc = ks_datacont_copy(ln->dc);

  return ks_listnode_new(dc);
}


void ks_listnode_delete_all(ks_listnode* ln)
{
  if (ln == NULL) return;

  ks_listnode_delete_all(ln->next);

  ks_listnode_delete(ln);
}


ks_listnode* ks_listnode_copy_all(const ks_listnode* ln)
{
  if (ln == NULL) return NULL;

  ks_listnode* ln_copy = ks_listnode_copy(ln);

  ln_copy->next = ks_listnode_copy_all(ln->next);

  return ln_copy;
}


int ks_listnode_add(ks_listnode* ln, const ks_datacont* dc)
{
  if (ln == NULL || dc == NULL) return -1;

  if (ln->next) return ks_listnode_add(ln->next, dc);

  ln->next = ks_listnode_new(dc);

  return 0;
}


ks_listnode* ks_listnode_merge(ks_listnode* lna, ks_listnode* lnb)
{
  if (lna == NULL || lnb == NULL) return lna ? lna : lnb;

  ks_listnode* iter = lna;

  while (iter->next != NULL)
    iter = iter->next;

  iter->next = lnb;

  return lna;
}


int ks_listnode_remove_by(ks_listnode** ln, const ks_datacont* dc)
{
  if (ln == NULL || *ln == NULL || dc == NULL) return -1;

  if (ks_datacont_compare(dc, (*ln)->dc) == KS_EQUAL)
  {
    ks_listnode* temp = (*ln)->next;
    ks_listnode_delete(*ln);
    *ln = temp;
    return 1;
  }

  if ((*ln)->next) 
    return ks_listnode_remove_by(&((*ln)->next), dc);
  return 0;
}


int ks_listnode_remove_at(ks_listnode** ln, int index)
{
  if (ln == NULL || *ln == NULL || 
      (index < 0 && (index = ks_listnode_length(*ln) + index) < 0))
    return -1;

  if (index == 0)
  {
    ks_listnode* temp = (*ln)->next;
    ks_listnode_delete(*ln);
    *ln = temp;
    return 0;
  }

  if ((*ln)->next)
    return ks_listnode_remove_at(&((*ln)->next), index-1);
  return -1;
}


int ks_listnode_remove_all(ks_listnode** ln, const ks_datacont* dc)
{
  if (ln == NULL || *ln == NULL || dc == NULL) return -1;

  if (ks_datacont_compare(dc, (*ln)->dc) == KS_EQUAL)
  {
    ks_listnode* temp = (*ln)->next;
    ks_listnode_delete(*ln);
    *ln = temp;
    if ((*ln) && (*ln)->next)
      return 1 + ks_listnode_remove_all(&((*ln)->next), dc);
    return 1;
  }
  
  if ((*ln)->next)
    return ks_listnode_remove_all(&(*ln)->next, dc);
  return 0;
}


int ks_listnode_replace_by(ks_listnode* ln, const ks_datacont* old_dc, const ks_datacont* new_dc)
{
  if (ln == NULL || old_dc == NULL || new_dc == NULL) return -1;

  if (ks_datacont_compare(old_dc, ln->dc) == KS_EQUAL)
  {
    ks_datacont_delete(ln->dc);
    ln->dc = (ks_datacont*) new_dc;
    return 0;
  }

  return ks_listnode_replace_by(ln->next, old_dc, new_dc);
}


int ks_listnode_replace_at(ks_listnode* ln, const ks_datacont* dc, int index)
{
  if (ln == NULL || dc == NULL ||
      (index < 0 && (index = ks_listnode_length(ln) + index) < 0))
    return -1;

  if (index == 0)
  {
    ks_datacont_delete(ln->dc);
    ln->dc = (ks_datacont*) dc;
    return 0;
  }

  return ks_listnode_replace_at(ln->next, dc, index-1);
}


int ks_listnode_replace_all(ks_listnode* ln, const ks_datacont* old_dc, const ks_datacont* new_dc)
{
  if (ln == NULL || old_dc == NULL || new_dc == NULL)
    return -1;

  if (ks_datacont_compare(old_dc, ln->dc) == KS_EQUAL)
  {
    ks_datacont_delete(ln->dc);
    ln->dc = (ks_datacont*) new_dc;
    
    if (ln->next)
    { 
      ks_datacont* copy = ks_datacont_copy(new_dc);
      int result = ks_listnode_replace_all(ln->next, old_dc, copy);
      if (result == 0) ks_datacont_delete(copy);
      return 1 + result; 
    }
    return 1;
  }

  else if (ln->next)
    return ks_listnode_replace_all(ln->next, old_dc, new_dc);
  return 0;
}


int ks_listnode_insert(ks_listnode** ln, const ks_datacont* dc, int index)
{
  if (ln == NULL || dc == NULL ||
      (index < 0 && (index = ks_listnode_length(*ln) + index) < 0))
    return -1;

  if (index == 0)
  {
    ks_listnode* new_node = ks_listnode_new(dc);
    new_node->next = *ln;
    *ln = new_node;
    return 0;
  }

  else if (*ln == NULL)
    return -1;

  return ks_listnode_insert(&((*ln)->next), dc, index-1);
}


static int __ks_listnode_index(const ks_listnode* ln, const ks_datacont* dc, int curr_index)
{
  if (ln == NULL || dc == NULL) return -1;

  if (ks_datacont_compare(dc, ln->dc) == KS_EQUAL)
    return curr_index;

  return __ks_listnode_index(ln->next, dc, curr_index+1);
}

int ks_listnode_index(const ks_listnode* ln, const ks_datacont* dc)
{
  return __ks_listnode_index(ln, dc, 0); 
}


ks_datacont* ks_listnode_get(const ks_listnode* ln, int index)
{
  if (ln == NULL || 
      (index < 0 && (index = ks_listnode_length(ln) + index) < 0))
    return NULL;

  if (index == 0) return ln->dc;
  
  return ks_listnode_get(ln->next, index-1);
}


unsigned int ks_listnode_count(const ks_listnode* ln, const ks_datacont* dc)
{
  if (ln == NULL || dc == NULL) return -1;

  if (ks_datacont_compare(dc, ln->dc) == KS_EQUAL)
  {
    if (ln->next)
      return 1 + ks_listnode_count(ln->next, dc);
    return 1;
  }

  if (ln->next)
    return ks_listnode_count(ln->next, dc);
  return 0;
}


unsigned int ks_listnode_length(const ks_listnode* ln)
{
  if (ln == NULL) return 0;
  
  return 1 + ks_listnode_length(ln->next); 
}
