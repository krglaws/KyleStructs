#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "datacont.h"
#include "treenode.h"
#include "treeset.h"


treeset* treeset_new()
{
  treeset* ts = (treeset*) malloc(sizeof(treenode));
  ts->num_nodes = 0;
  ts->root = NULL;
  return ts;
}


int treeset_add(treeset* ts, const datacont* dc)
{
  if (ts == NULL || dc == NULL) return -1;
  int retval;
  if (ts->root == NULL)
  {
    ts->root = treenode_new(dc, NULL, NULL);
    retval = treenode_add(ts->root, dc);
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

