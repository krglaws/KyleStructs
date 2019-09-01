
#include <stdlib.h>

#include "include/datacont.h"
#include "include/treenode.h"
#include "include/treeset.h"


treeset* treeset_new()
{
  treeset* ts = (treeset*) malloc(sizeof(treenode));
  ts->num_nodes = 0;
  ts->root = NULL;
  return ts;
}


static void _treeset_delete(treenode* tn)
{
  if (tn == NULL) return;
  if (tn->left != NULL) _treeset_delete(tn->left);
  if (tn->right != NULL) _treeset_delete(tn->right);
  treenode_delete(tn);
}


void treeset_delete(treeset* ts)
{
  if (ts == NULL) return;
  _treeset_delete(ts->root);
  free(ts);
}


int treeset_add(treeset* ts, const datacont* dc)
{
  if (ts == NULL || dc == NULL) return -1;
  int retval;
  if (ts->root == NULL)
  {
    ts->root = treenode_new(dc);
    retval = 0;
  }
  else
  {
    retval = treenode_add(ts->root, dc);
  }
  if (retval == 0) ts->num_nodes++;
  return retval;
}


int treeset_remove(treeset* ts, const datacont* dc)
{
  if (ts == NULL || dc == NULL) return 1;
  return treenode_remove(ts->root, dc);
}


int treeset_contains(const treeset* ts, const datacont* dc)
{
  if (ts == NULL || dc == NULL) return 0;
  return treenode_contains(ts->root, dc);
}


unsigned int treeset_height(const treeset* ts)
{
  if (ts == NULL) return 0;
  return treenode_height(ts->root);
}
