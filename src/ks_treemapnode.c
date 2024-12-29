#include "ks_treemapnode.h"

#include <stdlib.h>

#include "ks_datacont.h"
#include "ks_listnode.h"
#include "ks_types.h"

ks_treemapnode* ks_treemapnode_new(const ks_datacont* key,
                                   const ks_datacont* value) {
  if (key == NULL || value == NULL) return NULL;

  ks_treemapnode* tmn = calloc(1, sizeof(ks_treemapnode));

  tmn->key = (ks_datacont*)key;

  tmn->value = (ks_datacont*)value;

  return tmn;
}

void ks_treemapnode_delete(ks_treemapnode* tmn) {
  if (tmn == NULL) return;

  ks_datacont_delete(tmn->key);

  ks_datacont_delete(tmn->value);

  free(tmn);
}

ks_treemapnode* ks_treemapnode_copy(const ks_treemapnode* tmn) {
  if (tmn == NULL) return NULL;

  ks_datacont* key = ks_datacont_copy(tmn->key);
  ks_datacont* val = ks_datacont_copy(tmn->value);

  return ks_treemapnode_new(key, val);
}

void ks_treemapnode_delete_all(ks_treemapnode* tmn) {
  if (tmn == NULL) return;

  ks_treemapnode_delete_all(tmn->left);

  ks_treemapnode_delete_all(tmn->right);

  ks_treemapnode_delete(tmn);
}

ks_treemapnode* ks_treemapnode_copy_all(const ks_treemapnode* tmn) {
  if (tmn == NULL) return NULL;

  ks_treemapnode* tmn_copy = ks_treemapnode_copy(tmn);

  tmn_copy->left = ks_treemapnode_copy_all(tmn->left);
  tmn_copy->right = ks_treemapnode_copy_all(tmn->right);

  return tmn_copy;
}

int ks_treemapnode_add(ks_treemapnode* tmn, const ks_datacont* key,
                       const ks_datacont* value) {
  if (tmn == NULL || key == NULL || value == NULL) return -1;

  enum ks_comparison result = ks_datacont_compare(key, tmn->key);

  if (result == KS_CANTCOMPARE) return -1;

  if (result == KS_EQUAL) {
    ks_datacont_delete(tmn->key);
    ks_datacont_delete(tmn->value);
    tmn->key = (ks_datacont*)key;
    tmn->value = (ks_datacont*)value;
    return 1;
  } else if (result == KS_LESSTHAN) {
    if (tmn->left)
      return ks_treemapnode_add(tmn->left, key, value);
    else
      tmn->left = ks_treemapnode_new(key, value);
  } else {
    if (tmn->right)
      return ks_treemapnode_add(tmn->right, key, value);
    else
      tmn->right = ks_treemapnode_new(key, value);
  }
  return 0;
}

int ks_treemapnode_remove(ks_treemapnode** tmn, const ks_datacont* key) {
  if (tmn == NULL || *tmn == NULL || key == NULL) return -1;

  enum ks_comparison result = ks_datacont_compare(key, (*tmn)->key);

  if (result == KS_EQUAL) {
    if ((*tmn)->left != NULL && (*tmn)->right != NULL) {
      ks_treemapnode** leftmost = &(*tmn)->right;
      while ((*leftmost)->left) leftmost = &(*leftmost)->left;
      ks_datacont_delete((*tmn)->key);
      ks_datacont_delete((*tmn)->value);
      (*tmn)->key = ks_datacont_copy((*leftmost)->key);
      (*tmn)->value = ks_datacont_copy((*leftmost)->value);
      return ks_treemapnode_remove(leftmost, (*leftmost)->key);
    } else if ((*tmn)->left) {
      ks_datacont_delete((*tmn)->key);
      ks_datacont_delete((*tmn)->value);
      (*tmn)->key = ks_datacont_copy((*tmn)->left->key);
      (*tmn)->value = ks_datacont_copy((*tmn)->left->value);
      return ks_treemapnode_remove(&(*tmn)->left, (*tmn)->left->key);
    } else if ((*tmn)->right) {
      ks_datacont_delete((*tmn)->key);
      ks_datacont_delete((*tmn)->value);
      (*tmn)->key = ks_datacont_copy((*tmn)->right->key);
      (*tmn)->value = ks_datacont_copy((*tmn)->right->value);
      return ks_treemapnode_remove(&(*tmn)->right, (*tmn)->right->key);
    } else {
      ks_treemapnode_delete(*tmn);
      *tmn = NULL;
      return 0;
    }
  } else if (result == KS_LESSTHAN)
    return ks_treemapnode_remove(&(*tmn)->left, key);
  else if (result == KS_GREATERTHAN)
    return ks_treemapnode_remove(&(*tmn)->right, key);
  return 1;
}

const ks_datacont* ks_treemapnode_get(const ks_treemapnode* tmn,
                                      const ks_datacont* key) {
  if (tmn == NULL || key == NULL) return NULL;

  enum ks_comparison result = ks_datacont_compare(key, tmn->key);

  if (result == KS_EQUAL)
    return tmn->value;

  else if (result == KS_LESSTHAN)
    return ks_treemapnode_get(tmn->left, key);

  else if (result == KS_GREATERTHAN)
    return ks_treemapnode_get(tmn->right, key);

  return NULL;
}

static ks_datacont* __ks_treemapnode_get_key(const ks_treemapnode* tmn,
                                             int index, int* curr_index) {
  if (tmn == NULL) return NULL;

  ks_treemapnode* first = index < 0 ? tmn->right : tmn->left;
  ks_treemapnode* second = index < 0 ? tmn->left : tmn->right;

  ks_datacont* key;

  if ((key = __ks_treemapnode_get_key(first, index, curr_index)) != NULL)
    return key;

  index < 0 ? (*curr_index)-- : (*curr_index)++;

  if (*curr_index == index) return tmn->key;

  return __ks_treemapnode_get_key(second, index, curr_index);
}

const ks_datacont* ks_treemapnode_get_key(const ks_treemapnode* tmn,
                                          int index) {
  int curr_index = index < 0 ? 0 : -1;

  return __ks_treemapnode_get_key(tmn, index, &curr_index);
}

unsigned int ks_treemapnode_count(const ks_treemapnode* tmn) {
  if (tmn == NULL) return 0;

  return 1 + ks_treemapnode_count(tmn->left) + ks_treemapnode_count(tmn->right);
}

unsigned int ks_treemapnode_height(const ks_treemapnode* tmn) {
  if (tmn == NULL) return 0;

  unsigned int left_height = ks_treemapnode_height(tmn->left);

  unsigned int right_height = ks_treemapnode_height(tmn->right);

  return 1 + (left_height > right_height ? left_height : right_height);
}

static ks_treemapnode* __ks_treemapnode_balance(ks_treemapnode* tmn, int start,
                                                int end) {
  if (start > end) return NULL;

  int mid = (start + end) / 2;

  ks_datacont* key = ks_datacont_copy(ks_treemapnode_get_key(tmn, mid));
  ks_datacont* val = ks_datacont_copy(ks_treemapnode_get(tmn, key));
  ks_treemapnode* root = ks_treemapnode_new(key, val);

  root->left = __ks_treemapnode_balance(tmn, start, mid - 1);
  root->right = __ks_treemapnode_balance(tmn, mid + 1, end);

  return root;
}

ks_treemapnode* ks_treemapnode_balance(ks_treemapnode* root) {
  if (root == NULL) return NULL;

  int count = ks_treemapnode_count(root);

  ks_treemapnode* balanced = __ks_treemapnode_balance(root, 0, count - 1);

  ks_treemapnode_delete_all(root);

  return balanced;
}
