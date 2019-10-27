
#ifndef _TREESETNODE_H_
#define _TREESETNODE_H_

typedef struct treesetnode treesetnode;

struct treesetnode
{
  datacont* dc;
  treesetnode* right;
  treesetnode* left;
};

treesetnode* treesetnode_new(const datacont* dc);

void treesetnode_delete(treesetnode* tn);

int treesetnode_add(treesetnode* tn, const datacont* dc);

/* ---------------------------------
 * treesetnode_remove():
 * Remove a node contained within the
 * treesetnode* parameter that matches the
 * datacont* parameter.
 *
 * inputs:
 * treesetnode* tn - remove treesetnode from this
 * root node.
 * datacont* dc - remove treesetnode that contains
 * the same value as this data container
 *
 * returns:
 * 0 - successfully removed node
 * 1 - node not found/received empty parameter
 */
int treesetnode_remove(treesetnode** tn, const datacont* dc);

int treesetnode_contains(const treesetnode* tn, const datacont* dc);

static datacont* _treesetnode_get_nth(const treesetnode* tn, int n, int* index);

datacont* treesetnode_get_nth(const treesetnode* tn, int n);

static int _treesetnode_height(const treesetnode* tn, unsigned int accum);

unsigned int treesetnode_height(const treesetnode* tn);

unsigned int treesetnode_size(const treesetnode* tn);

#endif

