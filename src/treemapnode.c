#include <treemapnode.h>


treemapnode* treemapnode_new(const datacont* key, const datacont* value)
{
  if (key == NULL || value == NULL) return NULL;

  treemapnode* tmn = calloc(1, sizeof(treemapnode));

  tmn->key = (datacont*) key;

  tmn->value = (datacont*) value;

  return tmn;
}


void treemapnode_delete(treemapnode* tmn)
{
  if (tmn == NULL) return;

  datacont_delete(tmn->key);
 
  datacont_delete(tmn->value);
  
  free(tmn);
}


void treemapnode_delete_all(treemapnode* tmn)
{
  if (tmn == NULL) return;

  treemapnode_delete_all(tmn->left);

  treemapnode_delete_all(tmn->right);

  treemapnode_delete(tmn);
}


int treemapnode_add(treemapnode* tmn, const datacont* key, const datacont* value)
{
  if (tmn == NULL || key == NULL || value == NULL) return -1;
 
  enum datacontcomp result = datacont_compare(key, tmn->key);
 
  if (result == CANTCOMPARE) return -1;

  if (result == EQUAL)
  {
    datacont_delete(tmn->value);
    tmn->value = (datacont*) value;
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


int treemapnode_remove(treemapnode** tmn, const datacont* key)
{
  if (tmn == NULL || *tmn == NULL || key == NULL) return -1;

  enum datacontcomp result = datacont_compare(key, (*tmn)->key);

  if (result == EQUAL)
  {
    if ((*tmn)->left != NULL && (*tmn)->right != NULL)
    {
      treemapnode** leftmost = &(*tmn)->right;
      while ((*leftmost)->left) leftmost = &(*leftmost)->left;
      datacont_delete((*tmn)->key);
      datacont_delete((*tmn)->value);
      (*tmn)->key = datacont_copy((*leftmost)->key);
      (*tmn)->value = datacont_copy((*leftmost)->value);
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
    return tmn->value;

  else if (result == LESSTHAN)
    return treemapnode_get(tmn->left, key);

  else if (result == GREATERTHAN)
    return treemapnode_get(tmn->right, key);

  return NULL;
}


static datacont* __treemapnode_get_key(const treemapnode* tmn, int index, int* curr_index)
{
  if (tmn == NULL) return NULL;

  datacont* dc;

  if (index < 0 &&
        (dc = __treemapnode_get_key(tmn->right, index, curr_index)) != NULL)
    return dc;

  else if ((dc = __treemapnode_get_key(tmn->left, index, curr_index)) != NULL)
    return dc;

  if (*curr_index == index)
    return tmn->key;

  index < 0 ? (*curr_index)-- : (*curr_index)++;

  if (index < 0)
    return __treemapnode_get_key(tmn->left, index, curr_index);

  return __treemapnode_get_key(tmn->right, index, curr_index);
}


datacont* treemapnode_get_key(const treemapnode* tmn, int index)
{
  int curr_index = index < 0 ? -1 : 0;

  return __treemapnode_get_key(tmn, index, &curr_index);
}


listnode* treemapnode_keys(const treemapnode* tmn)
{
  if (tmn == NULL) return NULL;
 
  listnode* lsn = treemapnode_keys(tmn->left);
 
  if (lsn == NULL)
  {
    lsn = listnode_new(datacont_copy(tmn->key));
    lsn->next = treemapnode_keys(tmn->right);
    return lsn;
  }
  else
  {
    listnode* end = lsn;
    while (end->next) end = end->next;
    end->next = listnode_new(datacont_copy(tmn->key));
    end->next->next = treemapnode_keys(tmn->right);
    return lsn;
  }
}


listnode* treemapnode_values(const treemapnode* tmn)
{
  if (tmn == NULL) return NULL;

  listnode* lsn = treemapnode_values(tmn->left);

  if (lsn == NULL)
  {
    lsn = listnode_new(datacont_copy(tmn->value));
    lsn->next = treemapnode_values(tmn->right);
    return lsn;
  }
  else
  {
    listnode* end = lsn;
    while (end->next) end = end->next;
    end->next = listnode_new(datacont_copy(tmn->value));
    end->next->next = treemapnode_values(tmn->right);
    return lsn;
  }
}


unsigned int treemapnode_count(const treemapnode* tmn)
{
  if (tmn == NULL) return 0;

  return 1 + treemapnode_count(tmn->left) + 
    treemapnode_count(tmn->right);
}


unsigned int treemapnode_height(const treemapnode* tmn)
{
  if (tmn == NULL) return 0;

  unsigned int left_height = treemapnode_height(tmn->left);

  unsigned int right_height = treemapnode_height(tmn->right);

  return 1 + (left_height > right_height ? left_height : right_height);
}


void treemapnode_balance(treemapnode** tmn)
{
  if (tmn == NULL || *tmn == NULL) return;

  int count = treemapnode_count(*tmn);

  if (count < 3) return;

  int temp = count, rowlen = 2, nrows = 1, fulltree = 1;
  while (temp /= 2)
  {
    nrows++;
    fulltree += rowlen;
    rowlen *= 2;
  }

  int rootindex = fulltree / 2;
  datacont* key = datacont_copy(treemapnode_get_key(*tmn, rootindex));
  datacont* value = datacont_copy(treemapnode_get(*tmn, key));
  treemapnode* new_tree = treemapnode_new(key, value);

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
        key = datacont_copy(treemapnode_get_key(*tmn, index));
        value = datacont_copy(treemapnode_get(*tmn, key));
        treemapnode_add(new_tree, key, value);
        added++;
      }

      prev = curr;
      curr /= 2;
      rowlen *= 2;
    }
  }

  treemapnode_delete_all(*tmn);
  *tmn = new_tree;
}
