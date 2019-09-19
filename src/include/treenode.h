
#ifndef _TREENODE_H_
#define _TREENODE_H_

typedef struct treenode treenode;

struct treenode
{
  datacont* dc;
  treenode* right;
  treenode* left;
};

treenode* treenode_new(const datacont* dc);

void treenode_delete(treenode* tn);

int treenode_add(treenode* tn, const datacont* dc);

/* ---------------------------------
 * treenode_remove():
 * Remove a node contained within the
 * treenode* parameter that matches the
 * data container parameter. If you call
 * this function directly (i.e. not through
 * treeset_remove()), you are expected to
 * keep track of the number of remaining
 * nodes on your own. If you remove the last
 * node from the tree, you will have an
 * invalid root pointer. The only clue you
 * will get is a return value of 0 upon
 * successful removal, at which point you
 * can subtract 1 from your own counter if
 * you have one.
 *
 * inputs:
 * treenode* tn - remove treenode from this
 * root node.
 * datacont* dc - remove treenode that contains
 * the same value as this data container
 *
 * returns:
 * 0 - successfully removed node
 * 1 - node not found
 */
int treenode_remove(treenode** tn, const datacont* dc);

int treenode_contains(const treenode* tn, const datacont* dc);

static int _treenode_height(const treenode* tn, unsigned int accum);

unsigned int treenode_height(const treenode* tn);

unsigned int treenode_size(const treenode* tn);

#endif

