#include "ks_treeset.h"

#include <stdlib.h>

#include "ks_datacont.h"
#include "ks_hashset.h"
#include "ks_treesetnode.h"
#include "ks_types.h"

ks_treeset* ks_treeset_new() { return calloc(1, sizeof(ks_treesetnode)); }

void ks_treeset_delete(ks_treeset* ts) {
  if (ts == NULL) return;

  ks_treesetnode_delete_all(ts->root);

  free(ts);
}

ks_treeset* ks_treeset_copy(const ks_treeset* ts) {
  if (ts == NULL) return NULL;

  ks_treeset* ts_copy = ks_treeset_new();

  ts_copy->root = ks_treesetnode_copy_all(ts->root);

  return ts_copy;
}

int ks_treeset_add(ks_treeset* ts, const ks_datacont* dc) {
  if (ts == NULL || dc == NULL) return -1;

  if (ts->root == NULL) {
    ts->root = ks_treesetnode_new(dc);
    return 0;
  }
  return ks_treesetnode_add(ts->root, dc);
}

int ks_treeset_remove_by(ks_treeset* ts, const ks_datacont* dc) {
  if (ts == NULL || dc == NULL) return -1;

  return ks_treesetnode_remove_by(&ts->root, dc);
}

int ks_treeset_remove_at(ks_treeset* ts, int index) {
  if (ts == NULL) return -1;

  return ks_treesetnode_remove_at(&ts->root, index);
}

int ks_treeset_index(const ks_treeset* ts, const ks_datacont* dc) {
  if (ts == NULL || dc == NULL) return -1;

  return ks_treesetnode_index(ts->root, dc);
}

unsigned int ks_treeset_contains(const ks_treeset* ts, const ks_datacont* dc) {
  if (ts == NULL || dc == NULL) return 0;

  return ks_treesetnode_contains(ts->root, dc);
}

const ks_datacont* ks_treeset_get(const ks_treeset* ts, int index) {
  if (ts == NULL) return NULL;

  return ks_treesetnode_get(ts->root, index);
}

unsigned int ks_treeset_count(const ks_treeset* ts) {
  if (ts == NULL) return 0;

  return ks_treesetnode_count(ts->root);
}

unsigned int ks_treeset_height(const ks_treeset* ts) {
  if (ts == NULL) return 0;

  return ks_treesetnode_height(ts->root);
}

void ks_treeset_balance(ks_treeset* ts) {
  if (ts == NULL) return;

  ts->root = ks_treesetnode_balance(ts->root);
}
