
#ifndef _TREESET_H_
#define _TREESET_H_

typedef struct treeset treeset;

struct treeset 
{
	int num_nodes;
	treenode* root;
};

treeset* treeset_new(const int num_items, const datacont** dclist);

int treeset_add(treeset* ts, const datacont* dc);

int treeset_remove(treeset* ts, const datacont* dc);

int treeset_contains(const treeset* ts, const datacont* dc);

int treeset_height(const treeset* ts);

static void _generate_dotfile(const treenode* tn);

void generate_dotfile(const treenode* tn);

#endif

