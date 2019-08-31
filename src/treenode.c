
#include <stdlib.h>

#include "include/datacont.h"
#include "include/treenode.h"


treenode* treenode_new(const datacont* dc, const treenode* left, const treenode* right)
{
  if (dc == NULL) return NULL;
  treenode* tn = (treenode*) malloc(sizeof(treenode));
  tn->dc = (datacont*) dc;
  tn->left = (treenode*) left;
  tn->right = (treenode*) right;
  return tn;
}


void treenode_delete(treenode* tn)
{
  if (tn == NULL) return;
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
    else tn->left = treenode_new(dc, NULL, NULL);
  }
  else
  {
    if (tn->right) return treenode_add(tn->right, dc);
    else tn->right = treenode_new(dc, NULL, NULL);
  }
  return 0;
}


int treenode_remove(treenode* tn, const datacont* dc)
{
  // this is gon' be tricky
  return 0;
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
