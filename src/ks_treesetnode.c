#include <stdlib.h>

#include <ks_datacont.h>
#include <ks_treesetnode.h>


ks_treesetnode* ks_treesetnode_new(const ks_datacont* dc)
{
  if (dc == NULL) return NULL;

  ks_treesetnode* tsn = calloc(1, sizeof(ks_treesetnode));

  tsn->dc = (ks_datacont*) dc;

  return tsn;
}


void ks_treesetnode_delete(ks_treesetnode* tsn)
{
  if (tsn == NULL) return;

  ks_datacont_delete(tsn->dc);

  free(tsn);
}


void ks_treesetnode_delete_all(ks_treesetnode* tsn)
{
  if (tsn == NULL) return;

  ks_treesetnode_delete_all(tsn->left);

  ks_treesetnode_delete_all(tsn->right);

  ks_treesetnode_delete(tsn);
}


int ks_treesetnode_add(ks_treesetnode* tsn, const ks_datacont* dc)
{
  if (tsn == NULL || dc == NULL) return -1;

  enum ks_comparison result = ks_datacont_compare(dc, tsn->dc);

  if (result == KS_EQUAL) return 1;
  if (result == KS_CANTCOMPARE) return -1;

  else if (result == KS_LESSTHAN)
  {
    if (tsn->left) return ks_treesetnode_add(tsn->left, dc);
    else tsn->left = ks_treesetnode_new(dc);
  }
  else
  {
    if (tsn->right) return ks_treesetnode_add(tsn->right, dc);
    else tsn->right = ks_treesetnode_new(dc);
  }
  return 0;
}


int ks_treesetnode_remove_by(ks_treesetnode** tsn, const ks_datacont* dc)
{
  if (tsn == NULL || *tsn == NULL || dc == NULL) return -1;
  
  enum ks_comparison result = ks_datacont_compare(dc, (*tsn)->dc);

  if (result == KS_EQUAL)
  {
    if ((*tsn)->left != NULL && (*tsn)->right != NULL)
    {
      ks_treesetnode** leftmost = &(*tsn)->right;
      while ((*leftmost)->left) leftmost = &(*leftmost)->left;
      ks_datacont_delete((*tsn)->dc);
      (*tsn)->dc = ks_datacont_copy((*leftmost)->dc);
      return ks_treesetnode_remove_by(leftmost, (*leftmost)->dc);
    }
    else if ((*tsn)->left)
    {
      ks_datacont_delete((*tsn)->dc);
      (*tsn)->dc = ks_datacont_copy((*tsn)->left->dc);
      return ks_treesetnode_remove_by(&(*tsn)->left, (*tsn)->left->dc);
    }
    else if ((*tsn)->right)
    {
      ks_datacont_delete((*tsn)->dc);
      (*tsn)->dc = ks_datacont_copy((*tsn)->right->dc);
      return ks_treesetnode_remove_by(&(*tsn)->right, (*tsn)->right->dc);
    }
    else
    {
      ks_treesetnode_delete(*tsn);
      *tsn = NULL;
      return 0;
    }
  }
  else if (result == KS_LESSTHAN) 
    return ks_treesetnode_remove_by(&(*tsn)->left, dc);
  else if (result == KS_GREATERTHAN)
    return ks_treesetnode_remove_by(&(*tsn)->right, dc);
  return -1;
}


static int __ks_treesetnode_remove_at(ks_treesetnode** tsn, const int index, int* curr_index)
{
  if (tsn == NULL || *tsn == NULL) return -1;

  if (index < 0 &&
        (__ks_treesetnode_remove_at(&(*tsn)->right, index, curr_index) == 0))
    return 0;

  else if (__ks_treesetnode_remove_at(&(*tsn)->left, index, curr_index) == 0)
    return 0;

  if (*curr_index == index)
    return ks_treesetnode_remove_by(tsn, (*tsn)->dc);

  index < 0 ? (*curr_index)-- : (*curr_index)++;

  if (index < 0)
    return __ks_treesetnode_remove_at(&(*tsn)->left, index, curr_index);

  return __ks_treesetnode_remove_at(&(*tsn)->right, index, curr_index);
}


int ks_treesetnode_remove_at(ks_treesetnode** tsn, const int index)
{
  int curr_index;
 
  if (index < 0) curr_index = -1;
  else curr_index = 0;

  return __ks_treesetnode_remove_at(tsn, index, &curr_index);
}


static int __ks_treesetnode_index(const ks_treesetnode* tsn, const ks_datacont* dc, int* curr_index)
{
  if (tsn == NULL) return -1;

  int index;
  if ((index = __ks_treesetnode_index(tsn->left, dc, curr_index)) > -1)
    return index;

  if (ks_datacont_compare(dc, tsn->dc) == KS_EQUAL)
    return *curr_index;

  (*curr_index)++;

  return __ks_treesetnode_index(tsn->right, dc, curr_index);
}


int ks_treesetnode_index(const ks_treesetnode* tsn, const ks_datacont* dc)
{
  int curr_index = 0;

  return __ks_treesetnode_index(tsn, dc, &curr_index);
}
 

unsigned int ks_treesetnode_contains(const ks_treesetnode* tsn, const ks_datacont* dc)
{
  if (tsn == NULL || dc == NULL) return 0;

  enum ks_comparison result = ks_datacont_compare(dc, tsn->dc);
 
  if (result == KS_EQUAL) return 1;

  if (result == KS_GREATERTHAN) return ks_treesetnode_contains(tsn->right, dc);
 
  return ks_treesetnode_contains(tsn->left, dc);
}


static ks_datacont* __ks_treesetnode_get(const ks_treesetnode* tsn, const int index, int* curr_index)
{
  if (tsn == NULL) return NULL;

  ks_datacont* dc;

  if (index < 0 &&
        (dc = __ks_treesetnode_get(tsn->right, index, curr_index)) != NULL)
    return dc;

  else if ((dc = __ks_treesetnode_get(tsn->left, index, curr_index)) != NULL)
    return dc;

  if (*curr_index == index)
    return tsn->dc;

  index < 0 ? (*curr_index)-- : (*curr_index)++;

  if (index < 0)
    return __ks_treesetnode_get(tsn->left, index, curr_index);

  return __ks_treesetnode_get(tsn->right, index, curr_index);
}


ks_datacont* ks_treesetnode_get(const ks_treesetnode* tsn, const int index)
{
  int curr_index = index < 0 ? -1 : 0;

  return __ks_treesetnode_get(tsn, index, &curr_index);
}


unsigned int ks_treesetnode_count(const ks_treesetnode* tsn)
{
  if (tsn == NULL) return 0;

  return 1 + ks_treesetnode_count(tsn->left) + 
    ks_treesetnode_count(tsn->right);
}


unsigned int ks_treesetnode_height(const ks_treesetnode* tsn)
{
  if (tsn == NULL) return 0;

  unsigned int left_height = ks_treesetnode_height(tsn->left);

  unsigned int right_height = ks_treesetnode_height(tsn->right);

  return 1 + (left_height > right_height ? left_height : right_height);
}


void ks_treesetnode_balance(ks_treesetnode** tsn)
{
  if (tsn == NULL || *tsn == NULL) return;

  int count = ks_treesetnode_count(*tsn);

  if (count < 3) return;

  int temp = count, rowlen = 2, nrows = 1, fulltree = 1;
  while (temp /= 2)
  {
    nrows++;
    fulltree += rowlen;
    rowlen *= 2;
  }

  int rootindex = fulltree / 2;
  ks_treesetnode* new_tree = ks_treesetnode_new(
                            ks_datacont_copy(
                              ks_treesetnode_get(*tsn, rootindex)));

  rowlen = 2; 
  int added = 1;
  float prev = 0.5, curr = 0.25;

  for (int i = 1; i < nrows && added < count; i++)
  {
    for (int j = 0; j < rowlen && added < count; j++)
    {
      int index = (int) (fulltree * (curr + (j * prev)));

      if (index < count)
      {
        ks_datacont* curr_dc = ks_datacont_copy(ks_treesetnode_get(*tsn, index));
        ks_treesetnode_add(new_tree, curr_dc);
        added++;
      }
    }

    prev = curr;
    curr /= 2;
    rowlen *= 2;
  }

  ks_treesetnode_delete_all(*tsn);
  *tsn = new_tree;
}
