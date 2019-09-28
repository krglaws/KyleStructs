
#ifndef _TREESET_H_
#define _TREESET_H_

typedef struct treeset treeset;

struct treeset
{
	int num_nodes;
	treesetnode* root;
};

treeset* treeset_new();

void treeset_delete(treeset* ts);

int treeset_add(treeset* ts, const datacont* dc);

/* ------------------------------
 * treeset_remove():
 * Remove a node from a treeset that contains a
 * data container matching the value of the 'dc'
 * argument. On successful removal, 1 is subtracted 
 * from the treeset's num_nodes value.
 *
 * inputs:
 * treeset* ts - remove treesetnode from this treeset.
 * datacont* dc - remove treesetnode with matching 
 * datacont value.
 *
 * returns:
 * 0 - successfully removed node
 * 1 - node not found/received empty parameter
 */
int treeset_remove(treeset* ts, const datacont* dc);

int treeset_contains(const treeset* ts, const datacont* dc);

unsigned int treeset_height(const treeset* ts);

#endif

