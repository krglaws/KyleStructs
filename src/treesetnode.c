
#include "include/treesetnode.h"


treesetnode* treesetnode_new(const datacont* dc)
{
  if (dc == NULL) return NULL;

  treesetnode* tsn = calloc(1, sizeof(treesetnode));

  tsn->dc = (datacont*) dc;

  return tsn;
}


void treesetnode_delete(treesetnode* tsn)
{
  if (tsn == NULL) return;

  datacont_delete(tsn->dc);

  free(tsn);
}


void treesetnode_delete_all(treesetnode* tsn)
{
  if (tsn == NULL) return;

  treesetnode_delete_all(tsn->left);

  treesetnode_delete_all(tsn->right);

  treesetnode_delete(tsn);
}


int treesetnode_add(treesetnode* tsn, const datacont* dc)
{
  if (tsn == NULL || dc == NULL) return -1;

  enum datacontcomp result = datacont_compare(dc, tsn->dc);

  if (result == EQUAL) return 1;
  if (result == CANTCOMPARE) return -1;

  else if (result == LESSTHAN)
  {
    if (tsn->left) return treesetnode_add(tsn->left, dc);
    else tsn->left = treesetnode_new(dc);
  }
  else
  {
    if (tsn->right) return treesetnode_add(tsn->right, dc);
    else tsn->right = treesetnode_new(dc);
  }
  return 0;
}


int treesetnode_remove_by(treesetnode** tsn, const datacont* dc)
{
  if (tsn == NULL || *tsn == NULL || dc == NULL) return -1;
  
  enum datacontcomp result = datacont_compare(dc, (*tsn)->dc);

  if (result == EQUAL)
  {
    if ((*tsn)->left != NULL && (*tsn)->right != NULL)
    {
      treesetnode** leftmost = &(*tsn)->right;
      while ((*leftmost)->left) leftmost = &(*leftmost)->left;
      datacont_delete((*tsn)->dc);
      (*tsn)->dc = datacont_copy((*leftmost)->dc);
      return treesetnode_remove_by(leftmost, (*leftmost)->dc);
    }
    else if ((*tsn)->left)
    {
      datacont_delete((*tsn)->dc);
      (*tsn)->dc = datacont_copy((*tsn)->left->dc);
      return treesetnode_remove_by(&(*tsn)->left, (*tsn)->left->dc);
    }
    else if ((*tsn)->right)
    {
      datacont_delete((*tsn)->dc);
      (*tsn)->dc = datacont_copy((*tsn)->right->dc);
      return treesetnode_remove_by(&(*tsn)->right, (*tsn)->right->dc);
    }
    else
    {
      treesetnode_delete(*tsn);
      *tsn = NULL;
      return 0;
    }
  }
  else if (result == LESSTHAN) 
    return treesetnode_remove_by(&(*tsn)->left, dc);
  else if (result == GREATERTHAN)
    return treesetnode_remove_by(&(*tsn)->right, dc);
  return -1;
}


static int __treesetnode_remove_at(treesetnode** tsn, const int index, int* curr_index)
{
  if (tsn == NULL || *tsn == NULL) return -1;

  if (index < 0 &&
        (__treesetnode_remove_at(&(*tsn)->right, index, curr_index) == 0))
    return 0;

  else if (__treesetnode_remove_at(&(*tsn)->left, index, curr_index) == 0)
    return 0;

  if (*curr_index == index)
    return treesetnode_remove_by(tsn, (*tsn)->dc);

  index < 0 ? (*curr_index)-- : (*curr_index)++;

  if (index < 0)
    return __treesetnode_remove_at(&(*tsn)->left, index, curr_index);

  return __treesetnode_remove_at(&(*tsn)->right, index, curr_index);
}


int treesetnode_remove_at(treesetnode** tsn, const int index)
{
  int curr_index;
 
  if (index < 0) curr_index = -1;
  else curr_index = 0;

  return __treesetnode_remove_at(tsn, index, &curr_index);
}


static int __treesetnode_index(const treesetnode* tsn, const datacont* dc, int* curr_index)
{
  if (tsn == NULL) return -1;

  int index;
  if ((index = __treesetnode_index(tsn->left, dc, curr_index)) > -1)
    return index;

  if (datacont_compare(dc, tsn->dc) == EQUAL)
    return *curr_index;

  (*curr_index)++;

  return __treesetnode_index(tsn->right, dc, curr_index);
}


int treesetnode_index(const treesetnode* tsn, const datacont* dc)
{
  int curr_index = 0;

  return __treesetnode_index(tsn, dc, &curr_index);
}
 

unsigned int treesetnode_contains(const treesetnode* tsn, const datacont* dc)
{
  if (tsn == NULL || dc == NULL) return 0;

  enum datacontcomp result = datacont_compare(dc, tsn->dc);
 
  if (result == EQUAL) return 1;

  if (result == GREATERTHAN) return treesetnode_contains(tsn->right, dc);
 
  return treesetnode_contains(tsn->left, dc);
}


static datacont* __treesetnode_get(const treesetnode* tsn, const int index, int* curr_index)
{
  if (tsn == NULL) return NULL;

  datacont* dc;

  if (index < 0 &&
        (dc = __treesetnode_get(tsn->right, index, curr_index)) != NULL)
    return dc;

  else if ((dc = __treesetnode_get(tsn->left, index, curr_index)) != NULL)
    return dc;

  if (*curr_index == index)
    return datacont_copy(tsn->dc);

  index < 0 ? (*curr_index)-- : (*curr_index)++;

  if (index < 0)
    return __treesetnode_get(tsn->left, index, curr_index);

  return __treesetnode_get(tsn->right, index, curr_index);
}


datacont* treesetnode_get(const treesetnode* tsn, const int index)
{
  int curr_index = index < 0 ? -1 : 0;

  return __treesetnode_get(tsn, index, &curr_index);
}


unsigned int treesetnode_count(const treesetnode* tsn)
{
  if (tsn == NULL) return 0;

  return 1 + treesetnode_count(tsn->left) + 
    treesetnode_count(tsn->right);
}


unsigned int treesetnode_height(const treesetnode* tsn)
{
  if (tsn == NULL) return 0;

  unsigned int left_height = treesetnode_height(tsn->left);
    
  unsigned int right_height = treesetnode_height(tsn->right);
    
  return 1 + (left_height > right_height ? left_height : right_height);
}


void treesetnode_balance(treesetnode** tsn)
{
  if (tsn == NULL || *tsn == NULL) return;

  float prev, curr;
  int count, temp, added, log, rowlen;

  count = temp = treesetnode_count(*tsn);
  added = 0; log = 1; rowlen = 1; prev = 1.0; curr = 0.5;

  treesetnode* new_tree = treesetnode_new(
                            treesetnode_get(*tsn, count/2));
 
  while (temp /= 2) log++;

  for (int i = 0; i < log + 1 && added < count; i++)
  {
    for (int j = 0; j < rowlen && added < count; j++)
    {
      treesetnode_add(new_tree,
        treesetnode_get(*tsn, (int) (count * (curr + (j * prev)))));
      added++;
    }
    prev = curr;
    curr /= 2;
    rowlen *= 2;
  }

  treesetnode_delete_all(*tsn);
  
  *tsn = new_tree;
}

