
#ifndef _TREESET_H_
#define _TREESET_H_

typedef struct treeset treeset;

struct treeset
{
	int num_nodes;
	treenode* root;
};

treeset* treeset_new();

static void _treeset_delete(treenode* tn);

void treeset_delete(treeset* ts);

int treeset_add(treeset* ts, const datacont* dc);

int treeset_remove(treeset* ts, const datacont* dc);

int treeset_contains(const treeset* ts, const datacont* dc);

unsigned int treeset_height(const treeset* ts);

#endif
