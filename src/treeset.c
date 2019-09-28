
#include <stdlib.h>

#include "include/datacont.h"
#include "include/treesetnode.h"
#include "include/treeset.h"


treeset* treeset_new()
{
  treeset* ts = (treeset*) malloc(sizeof(treesetnode));
  ts->num_nodes = 0;
  ts->root = NULL;
  return ts;
}


void treeset_delete(treeset* ts)
{
  if (ts == NULL) return;
  treesetnode_delete(ts->root);
  free(ts);
}


int treeset_add(treeset* ts, const datacont* dc)
{
  if (ts == NULL || dc == NULL) return -1;

  int retval;

  if (ts->root == NULL)
  {
    ts->root = treesetnode_new(dc);
    retval = 0;
  }
  else retval = treesetnode_add(ts->root, dc);

  if (retval == 0) ts->num_nodes++;

  return retval;
}


int treeset_remove(treeset* ts, const datacont* dc)
{
  if (ts == NULL) return 1;
  int retval = treesetnode_remove(&ts->root, dc);

  if (retval == 0)
    ts->num_nodes--;

  if (ts->num_nodes < 1)
    ts->root = NULL;

  return retval;
}


int treeset_contains(const treeset* ts, const datacont* dc)
{
  if (ts == NULL || dc == NULL) return 0;
  return treesetnode_contains(ts->root, dc);
}


unsigned int treeset_height(const treeset* ts)
{
  if (ts == NULL) return 0;
  return treesetnode_height(ts->root);
}

