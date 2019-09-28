
#include <stdlib.h>

#include "include/datacont.h"
#include "include/treesetnode.h"


treesetnode* treesetnode_new(const datacont* dc)
{
  if (dc == NULL) return NULL;
  treesetnode* tn = (treesetnode*) malloc(sizeof(treesetnode));
  tn->dc = (datacont*) dc;
  tn->left = tn->right = NULL;
  return tn;
}


void treesetnode_delete(treesetnode* tn)
{
  if (tn == NULL) return;
  if (tn->right != NULL) treesetnode_delete(tn->right);
  if (tn->left != NULL) treesetnode_delete(tn->left);
  datacont_delete((datacont*) tn->dc);
  free(tn);
}


int treesetnode_add(treesetnode* tn, const datacont* dc)
{
  if (tn == NULL || dc == NULL) return -1;

  enum datacontcomp result = datacont_compare(dc, tn->dc);
  if (result == EQUAL) return 1;
  if (result == CANTCOMPARE) return -1;

  else if (result == LESSTHAN)
  {
    if (tn->left) return treesetnode_add(tn->left, dc);
    else tn->left = treesetnode_new(dc);
  }
  else
  {
    if (tn->right) return treesetnode_add(tn->right, dc);
    else tn->right = treesetnode_new(dc);
  }
  return 0;
}


int treesetnode_remove(treesetnode** tn, const datacont* dc)
{
  if (tn == NULL || *tn == NULL || dc == NULL) return 1;
  
  enum datacontcomp result = datacont_compare(dc, (*tn)->dc);

  if (result == EQUAL)
  {
    if ((*tn)->left != NULL && (*tn)->right != NULL)
    {
      treesetnode** leftmost = &(*tn)->right;
      while ((*leftmost)->left) leftmost = &(*leftmost)->left;
      datacont_delete((*tn)->dc);
      (*tn)->dc = datacont_copy((*leftmost)->dc);
      return treesetnode_remove(leftmost, (*leftmost)->dc);
    }
    else if ((*tn)->left)
    {
      datacont_delete((*tn)->dc);
      (*tn)->dc = datacont_copy((*tn)->left->dc);
      return treesetnode_remove(&(*tn)->left, (*tn)->left->dc);
    }
    else if ((*tn)->right)
    {
      datacont_delete((*tn)->dc);
      (*tn)->dc = datacont_copy((*tn)->right->dc);
      return treesetnode_remove(&(*tn)->right, (*tn)->right->dc);
    }
    else
    {
      treesetnode_delete(*tn);
      *tn = NULL;
      return 0;
    }
  }
  else if (result == LESSTHAN) 
    return treesetnode_remove(&(*tn)->left, dc);
  else if (result == GREATERTHAN)
    return treesetnode_remove(&(*tn)->right, dc);
  return 1;
}


int treesetnode_contains(const treesetnode* tn, const datacont* dc)
{
  if (tn == NULL || dc == NULL) return 0;
  enum datacontcomp result = datacont_compare(dc, tn->dc);
  if (result == EQUAL) return 1;
  if (result == GREATERTHAN) return treesetnode_contains(tn->right, dc);
  return treesetnode_contains(tn->left, dc);
}


static int _treesetnode_height(const treesetnode* tn, unsigned int accum)
{
  if (tn != NULL)
  {
    accum++;
    int left_height = _treesetnode_height(tn->left, accum);
    int right_height = _treesetnode_height(tn->right, accum);
    return left_height > right_height ? left_height : right_height;
  }
  return accum;
}


unsigned int treesetnode_height(const treesetnode* tn)
{
  return _treesetnode_height(tn, 0);
}
