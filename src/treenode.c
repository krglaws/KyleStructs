
#include <stdlib.h>

#include "include/datacont.h"
#include "include/treenode.h"


treenode* treenode_new(const datacont* dc)
{
  if (dc == NULL) return NULL;
  treenode* tn = (treenode*) malloc(sizeof(treenode));
  tn->dc = (datacont*) dc;
  tn->left = tn->right = NULL;
  return tn;
}


void treenode_delete(treenode* tn)
{
  if (tn == NULL) return;
  if (tn->right != NULL) treenode_delete(tn->right);
  if (tn->left != NULL) treenode_delete(tn->left);
  datacont_delete((datacont*) tn->dc);
  free(tn);
}


int treenode_add(treenode* tn, const datacont* dc)
{
  if (tn == NULL || dc == NULL) return -1;

  enum datacontcomp result = datacont_compare(dc, tn->dc);
  if (result == EQUAL) return 1;
  if (result == CANTCOMPARE) return -1;

  else if (result == LESSTHAN)
  {
    if (tn->left) return treenode_add(tn->left, dc);
    else tn->left = treenode_new(dc);
  }
  else
  {
    if (tn->right) return treenode_add(tn->right, dc);
    else tn->right = treenode_new(dc);
  }
  return 0;
}


int treenode_remove(treenode** tn, const datacont* dc)
{
  if (tn == NULL || *tn == NULL || dc == NULL) return 1;
  
  enum datacontcomp result = datacont_compare(dc, (*tn)->dc);

  if (result == EQUAL)
  {
    if ((*tn)->left != NULL && (*tn)->right != NULL)
    {
      treenode** leftmost = &(*tn)->right;
      while ((*leftmost)->left) leftmost = &(*leftmost)->left;
      datacont_delete((*tn)->dc);
      (*tn)->dc = datacont_copy((*leftmost)->dc);
      return treenode_remove(leftmost, (*leftmost)->dc);
    }
    else if ((*tn)->left)
    {
      datacont_delete((*tn)->dc);
      (*tn)->dc = datacont_copy((*tn)->left->dc);
      return treenode_remove(&(*tn)->left, (*tn)->left->dc);
    }
    else if ((*tn)->right)
    {
      datacont_delete((*tn)->dc);
      (*tn)->dc = datacont_copy((*tn)->right->dc);
      return treenode_remove(&(*tn)->right, (*tn)->right->dc);
    }
    else
    {
      treenode_delete(*tn);
      *tn = NULL;
      return 0;
    }
  }
  else if (result == LESSTHAN) 
    return treenode_remove(&(*tn)->left, dc);
  else if (result == GREATERTHAN)
    return treenode_remove(&(*tn)->right, dc);
  return 1;
}


int treenode_contains(const treenode* tn, const datacont* dc)
{
  if (tn == NULL || dc == NULL) return 0;
  enum datacontcomp result = datacont_compare(dc, tn->dc);
  if (result == EQUAL) return 1;
  if (result == GREATERTHAN) return treenode_contains(tn->right, dc);
  return treenode_contains(tn->left, dc);
}


static int _treenode_height(const treenode* tn, unsigned int accum)
{
  if (tn != NULL)
  {
    accum++;
    int left_height = _treenode_height(tn->left, accum);
    int right_height = _treenode_height(tn->right, accum);
    return left_height > right_height ? left_height : right_height;
  }
  return accum;
}


unsigned int treenode_height(const treenode* tn)
{
  return _treenode_height(tn, 0);
}
