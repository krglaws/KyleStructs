
#include <stdlib.h>

#include "include/datacont.h"
#include "include/listnode.h"
#include "include/treemapnode.h"


treemapnode* treemapnode_new(datacont* key, datacont* value)
{
  if (key == NULL || value == NULL) return NULL;

  treemapnode* tmn = calloc(1, sizeof(treemapnode));
  tmn->key = key;
  tmn->value = value;

  return tmn;
}


void treemapnode_delete(treemapnode* tmn)
{
  if (tmn == NULL) return;
  treemapnode_delete(tmn->left);
  treemapnode_delete(tmn->right);
  datacont_delete(tmn->key);
  datacont_delete(tmn->value);
  free(tmn);
}


int treemapnode_add(treemapnode* tmn, datacont* key, datacont* value)
{
  if (tmn == NULL || key == NULL || value == NULL) return -1;
  
  enum datacontcomp result = datacont_compare(key, tmn->key);
  
  if (result == CANTCOMPARE) return -1;

  if (result == EQUAL)
  {
    datacont_delete(tmn->value);
    tmn->value = value;
    return 1;
  }
  else if (result == LESSTHAN)
  {
    if (tmn->left) return treemapnode_add(tmn->left, key, value);
    else tmn->left = treemapnode_new(key, value);
  }
  else
  {
    if (tmn->right) return treemapnode_add(tmn->right, key, value);
    else tmn->right = treemapnode_new(key, value);
  }
  return 0;
}


int treemapnode_remove(treemapnode** tmn, datacont* key)
{
  if (tmn == NULL || *tmn == NULL || key == NULL) return 1;

  enum datacontcomp result = datacont_compare(key, (*tmn)->key);

  if (result == EQUAL)
  {
    if ((*tmn)->left != NULL && (*tmn)->right != NULL)
    {
      treemapnode** leftmost = &(*tmn)->right;
      while ((*leftmost)->left) leftmost = &(*leftmost)->left;
      datacont_delete((*tmn)->key);
      (*tmn)->key = datacont_copy((*leftmost)->key);
      return treemapnode_remove(leftmost, (*leftmost)->key);
    }
    else if ((*tmn)->left)
    {
      datacont_delete((*tmn)->key);
      datacont_delete((*tmn)->value);
      (*tmn)->key = datacont_copy((*tmn)->left->key);
      (*tmn)->value = datacont_copy((*tmn)->left->value);
      return treemapnode_remove(&(*tmn)->left, (*tmn)->left->key);
    }
    else if ((*tmn)->right)
    {
      datacont_delete((*tmn)->key);
      datacont_delete((*tmn)->value);
      (*tmn)->key = datacont_copy((*tmn)->right->key);
      (*tmn)->value = datacont_copy((*tmn)->right->value);
      return treemapnode_remove(&(*tmn)->right, (*tmn)->right->key);
    }
    else
    {
      treemapnode_delete(*tmn);
      *tmn = NULL;
      return 0;
    }
  }
  else if (result == LESSTHAN)
    return treemapnode_remove(&(*tmn)->left, key);
  else if (result == GREATERTHAN)
    return treemapnode_remove(&(*tmn)->right, key);
  return 1;
}


datacont* treemapnode_get(const treemapnode* tmn, const datacont* key)
{
  if (tmn == NULL || key == NULL) return NULL;

  enum datacontcomp result = datacont_compare(key, tmn->key);

  if (result == EQUAL)
    return datacont_copy(tmn->value);
  else if (result == LESSTHAN)
    return treemapnode_get(tmn->left, key);
  else if (result == GREATERTHAN)
    return treemapnode_get(tmn->right, key);
  return NULL;
}


listnode* treemapnode_getkeys(const treemapnode* tmn)
{
  if (tmn == NULL) return NULL;
  
  listnode* ln = treemapnode_getkeys(tmn->left);
  
  if (ln == NULL)
  {
    ln = listnode_new(datacont_copy(tmn->key));
    ln->next = treemapnode_getkeys(tmn->right);
    ln->next->prev = ln;
    return ln;
  }
  else
  {
    listnode* end = ln;
    while (end->next) end = end->next;
    
    end->next = listnode_new(datacont_copy(tmn->key));
    end->next->prev = end;

    end->next->next = treemapnode_getkeys(tmn->right);
    end->next->next->prev = end->next;
    return ln;
  }
}


listnode* treemapnode_getvalues(const treemapnode* tmn)
{
  if (tmn == NULL) return NULL;

  listnode* ln = treemapnode_getvalues(tmn->left);

  if (ln == NULL)
  {
    ln = listnode_new(datacont_copy(tmn->value));
    ln->next = treemapnode_getvalues(tmn->right);
    ln->next->prev = ln;
    return ln;
  }
  else
  {
    listnode* end = ln;
    while (end->next) end = end->next;

    end->next = listnode_new(datacont_copy(tmn->value));
    end->next->prev = end;

    end->next->next = treemapnode_getvalues(tmn->right);
    end->next->next->prev = end->next;
    return ln;
  }
}

