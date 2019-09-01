
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

int treenode_remove(treenode* tn, const datacont* dc);

int treenode_contains(const treenode* tn, const datacont* dc);

static int _treenode_height(const treenode* tn, unsigned int accum);

unsigned int treenode_height(const treenode* tn);

#endif
