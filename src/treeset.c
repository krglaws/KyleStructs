#include <treeset.h>


treeset* treeset_new()
{
  return calloc(1, sizeof(treesetnode));
}


void treeset_delete(treeset* ts)
{
  if (ts == NULL) return;

  treesetnode_delete_all(ts->root);

  free(ts);
}


int treeset_add(treeset* ts, const datacont* dc)
{
  if (ts == NULL || dc == NULL) return -1;

  if (ts->root == NULL)
  {
    ts->root = treesetnode_new(dc);
    return 0;
  }
  return treesetnode_add(ts->root, dc);
}


int treeset_remove_by(treeset* ts, const datacont* dc)
{
  if (ts == NULL || dc == NULL) return -1;

  return treesetnode_remove_by(&ts->root, dc);
}


int treeset_remove_at(treeset* ts, const int index)
{
  if (ts == NULL) return -1;

  return treesetnode_remove_at(&ts->root, index);
}


int treeset_index(const treeset* ts, const datacont* dc)
{
  if (ts == NULL || dc == NULL) return -1;

  return treesetnode_index(ts->root, dc);
}


unsigned int treeset_contains(const treeset* ts, const datacont* dc)
{
  if (ts == NULL || dc == NULL) return 0;

  return treesetnode_contains(ts->root, dc);
}


datacont* treeset_get(const treeset* ts, int index)
{
  if (ts == NULL) return NULL;

  return treesetnode_get(ts->root, index);
}


unsigned int treeset_count(const treeset* ts)
{
  if (ts == NULL) return 0;

  return treesetnode_count(ts->root);
}


unsigned int treeset_height(const treeset* ts)
{
  if (ts == NULL) return 0;

  return treesetnode_height(ts->root);
}


void treeset_balance(treeset* ts)
{
  if (ts == NULL) return;

  treesetnode_balance(&ts->root);
}
