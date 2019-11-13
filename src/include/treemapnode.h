
#ifndef _TREEMAPNODE_H_
#define _TREEMAPNODE_H_


#include "listnode.h"


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
 * Creates a new treemapnode.
 *
 * Inputs:
 * datacont* key - the key
 * datacont* value - the value
 *
 * Returns:
 * treemapnode* tmn - (NULL) if either of the parameters is NULL.
 *                  - a treemapnode containing 'key' and 'value'.
 */
treemapnode* treemapnode_new(const datacont* key, const datacont* value);


/* ----------------------------------
 * treemapnode_delete():
 * Deletes a treemapnode and its 'key' and 'value' members.
 *
 * Inputs:
 * treemapnode* tmn - the treemapnode to be deleted
 *
 * Returns:
 * void
 */
void treemapnode_delete(treemapnode* tmn);


/* -----------------------------------
 * treemapnode_delete_all():
 * Deletes a treemapnode, its 'key' and 'value' members, and recursively
 * deletes its 'right' and 'left' members.
 *
 * Inputs:
 * treemapnode* tmn - the treemapnode being deleted.
 *
 * Returns:
 * void
 */
void treemapnode_delete_all(treemapnode* tmn);


/* ----------------------------------
 * treemapnode_add():
 * Add a key/value pair to a treemapnode tree.
 *
 * Inputs:
 * treemapnode* tmn - the treemap to be added to
 * datacont* key - the key
 * datacont* value - the value that the key maps to
 *
 * Returns:
 * int result - (-1) if any params are NULL.
 *            - (0) pair added successfully
 *            - (1) already contains pair, old value replaced with new value.
 *
 * Notes:
 * If the key-value pair is successfully added to the treemapnode, the user code
 * must not delete or modify 'key' or 'value', otherwise undefined behavior could
 * ensue. If the pair was not added to the treemap, the user code is responsible for
 * deleting both when they are no longer needed. If 'value' is replaced by a new value,
 * the 'key' is not stored into the treemap, and it is the user code's responsibility
 * to delete the 'key'.
 */
int treemapnode_add(treemapnode* tmn, const datacont* key, const datacont* value);


/* ---------------------------
 * treemapnode_remove():
 * Find key/value pair and delete it.
 *
 * Inputs:
 * treemapnode** tmn - the treemapnode to be operated on
 * datacont* key - the key to be removed
 *
 * Returns:
 * int result - (-1) if either param is NULL, or 'key' could not be found.
 *            - (0) pair removed successfully.
 *
 * Notes:
 * Because the key-value pair that is being removed could be located in the root node,
 * 'tmn' must be passed as a nested pointer so that it can be set to a different node,
 * or NULL if there are no nodes left after the removal. Also: 'key' is not consumed by
 * this procedure, it is only used to locate another datacont containing the same data.
 */
int treemapnode_remove(treemapnode** tmn, const datacont* key);


/* ---------------------------
 * treemapnode_get():
 * Get the value from a treemapnode by key.
 *
 * Inputs:
 * treemapnode* tmn - the treemapnode to be operated on.
 * datacont* key - the key used to retrieve a value.
 *
 * Returns:
 * datacont* value - (NULL) if either param is NULL, or if 'key' could not be found.
 *                 - the value mapped to by the key.
 *
 * Notes:
 * The datacont 'value' returned by this function is a copy of the original which can
 * be safely deleted or modified without affecting the original inside of 'tmn'. Also:
 * 'key' is not consumed by this procedure, it is only used to locate another datacont
 * containing the same data.
 */
datacont* treemapnode_get(const treemapnode* tmn, const datacont* key);


/* --------------------------
 * treemapnode_get_key():
 * Retrieves a key located at a specified index within the treemapnode.
 *
 * Inputs:
 * treemapnode* tmn - the treemapnode being retrieved from.
 * int index - the index of the key being retrieved. Negative values
 *             will wrap around.
 *
 * Returns:
 * datacont* key - (NULL) if 'index' is OOB, or if 'tmn' is NULL.
 *               - the key located at 'index'.
 * Notes:
 * The datacont 'key' returned by this function is a copy of the original which can
 * be safely deleted or modified without affecting the original inside of 'tmn'.
 */
datacont* treemapnode_get_key(const treemapnode* tmn, int index);


/* --------------------------
 * treemapnode_keys():
 * Get a linked list of all keys contained within a treemapnode tree.
 * 
 * Inputs:
 * treemapnode* tmn - the treemapnode to be operated on
 *
 * Returns:
 * listnode* lsn - (NULL) if 'tmn' is NULL, or if 'tmn' is empty.
 *               - a list of the keys contained int 'tmn'.
 *
 * Notes:
 * 'lsn' contains copies of the original 'key' dataconts in 'tmn' which can be
 * safely deleted or modified without affecting the originals inside of 'tmn'.
 */
listnode* treemapnode_keys(const treemapnode* tmn);


/* --------------------------
 * treemapnode_values():
 * Get a linked list of all values contained within a treemapnode.
 *
 * Inputs:
 * treemapnode* tmn - the treemapnode to be operated on
 *
 * Returns:
 * listnode* lsn - (NULL) if 'tmn' is NULL or empty.
 *               - a list of the values contained in 'tmn'.
 *
 * Notes:
 * 'lsn' contains copies of the original 'value' dataconts in 'tmn' which can be
 * safely deleted or modified without affecting the originals inside of 'tmn'.
 */
listnode* treemapnode_values(const treemapnode* tmn);


/* ----------------------------
 * treemapnode_count():
 * Count the number of key/value pairs stored within a treemapnode.
 *
 * Inputs:
 * treemapnode* tmn - the treemapnode to be operated on.
 *
 * Returns:
 * unsigned int - >= (0) the number of pairs found in the treemapnode, (0) if 'tmn' is NULL.
 */
unsigned int treemapnode_count(const treemapnode* tmn);


/* --------------------------
 * treemapnode_height():
 * Calculate the maximum height of a treemapnode tree.
 *
 * Inputs:
 * treemapnode* tmn - the treemapnode to be operated on.
 *
 * Returns:
 * unsigned int - >= (0) the height of the tree, (0) if 'tmn' is NULL.
 */
unsigned int treemapnode_height(const treemapnode* tmn);


/* --------------------------
 * treemapnode_balance():
 * Balances a treemapnode* tree to ensure optimal performance.
 *
 * Inputs:
 * treemapnode** tmn - the root of the treemapnode being balanced.
 *
 * Returns:
 * void
 *
 * Notes:
 * Because the root of 'tmn' may change during the balancing process,
 * a 'tmn' must be passed in as a nested pointer so that it can be set to
 * the new root node when necessary.
 */
void treemapnode_balance(treemapnode** tmn);


#endif

