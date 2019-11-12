
#ifndef _TREEMAPNODE_H_
#define _TREEMAPNODE_H_


#include "listnode.h"
#include "treemapnode.h"


typedef struct treemapnode treemapnode;


struct treemapnode
{
  datacont* key;
  datacont* value;
  treemapnode* left;
  treemapnode* right;
};


/* ------------------------------------
 * treemapnode_new():
 * Returns a pointer to a new treemapnode
 *
 * inputs:
 * datacont* key - the key
 * datacont* value - the value
 *
 * returns:
 * treemapnode*
 * NULL - if one of the parameters is null
 */
treemapnode* treemapnode_new(const datacont* key, const datacont* value);


/* ----------------------------------
 * treemapnode_delete():
 * Deletes a treemapnode and all structs that it contains.
 *
 * inputs:
 * treemapnode* tmn - the treemapnode to be deleted
 *
 * returns:
 * void
 */
void treemapnode_delete(treemapnode* tmn);


/* ----------------------------------
 * treemapnode_add():
 * Add a key/value pair to a treemapnode tree.
 *
 * inputs:
 * treemapnode* tmn - the treemap to be added to
 * datacont* key - the key
 * datacont* value - the value that the key maps to
 *
 * returns:
 * -1 - failed to add pair
 *  0 - pair added successfully
 *  1 - already contains pair, old key/value replaced
 */
int treemapnode_add(treemapnode* tmn, const datacont* key, const datacont* value);


/* ---------------------------
 * treemapnode_remove():
 * Find key/value pair and delete it.
 *
 * inputs:
 * treemapnode** tmn - the treemapnode to be operated on
 * datacont* key - the key to be removed
 *
 * returns:
 * 0 - pair removed successfully
 * 1 - pair not removed (e.g. could not be found)
 */
int treemapnode_remove(treemapnode** tmn, const datacont* key);


/* ---------------------------
 * treemapnode_get():
 * Get the value from a treemapnode by key. The returned
 * value is a copy of the datacont contained
 * within the treemapnode tree, and can be free()'d or
 * otherwise modified.
 *
 * inputs:
 * treemapnode* tmn - the treemapnode to be operated on
 * datacont* key - the key used to retrieve a value
 *
 * returns:
 * datacont* value - the value mapped to by the key
 * NULL - returned when the key could not be found
 */
datacont* treemapnode_get(const treemapnode* tmn, const datacont* key);


/* --------------------------
 * treemapnode_getkeys():
 * Get a linked list of all keys contained within
 * a treemapnode tree. These are copies of the originals
 * in the treemapnode tree, and can be free()'d or
 * otherwise modified.
 *
 * inputs:
 * treemapnode* tmn - the treemapnode to be operated on
 *
 * returns:
 * listnode* - a pointer to a list of datacont*'s
 * NULL - returned if map has no keys
 */
listnode* treemapnode_getkeys(const treemapnode* tmn);


/* --------------------------
 * treemapnode_getvalues():
 * Get a linked list of all values contained within
 * a treemapnode. These are copies of the originals
 * in the treemapnode, and can be free()'d or
 * otherwise modified.
 *
 * inputs:
 * treemapnode* tmn - the treemapnode to be operated on
 *
 * returns:
 * listnode* - a pointer to a list of datacont*'s
 * NULL - returned if map has no keys
 */
listnode* treemapnode_getvalues(const treemapnode* tmn);


/* ----------------------------
 * treemapnode_count():
 * Count the number of key/value pairs stored
 * within a treemapnode.
 *
 * inputs:
 * treemapnode* tmn - the treemapnode to be operated on
 *
 * returns:
 * unsigned int - the number of pairs found in
 * the treemapnode >=0.
 */
unsigned int treemapnode_count(const treemapnode* tmn);


/* --------------------------
 * treemapnode_height():
 * Calculate the maximum height of a treemapnode tree.
 *
 * inputs:
 * treemapnode* tmn - the treemapnode to be operated on
 *
 * returns:
 * unsigned int - the height of the tree >=0.
 */
unsigned int treemapnode_height(const treemapnode* tmn);


#endif

