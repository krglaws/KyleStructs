#ifndef _KS_TREEMAPNODE_H_
#define _KS_TREEMAPNODE_H_


/* ------------------------------------
 * ks_treemapnode_new():
 * Creates a new ks_treemapnode.
 *
 * Inputs:
 * ks_datacont* key - the key
 * ks_datacont* value - the value
 *
 * Returns:
 * ks_treemapnode* tmn - (NULL) if either of the parameters is NULL.
 *                  - a ks_treemapnode containing 'key' and 'value'.
 */
ks_treemapnode* ks_treemapnode_new(const ks_datacont* key, const ks_datacont* value);


/* ----------------------------------
 * ks_treemapnode_delete():
 * Deletes a ks_treemapnode and its 'key' and 'value' members.
 *
 * Inputs:
 * ks_treemapnode* tmn - the ks_treemapnode to be deleted
 *
 * Returns:
 * void
 */
void ks_treemapnode_delete(ks_treemapnode* tmn);


/* ----------------------------------
 * ks_treemapnode_copy():
 * Creates a copy of a treemapnode* and its ks_datacont*.
 *
 * Inputs:
 * ks_treempanode* tmn - the ks_treemapnode to be copied.
 *
 * Returns:
 * ks_treemapnode* - a copy of the ks_treemapnode*.
 *
 * Notes:
 * ks_treemapnode_copy() only copies the ks_treemapnode itself
 * and its ks_datacont, but not any other connected ks_treemapnodes.
 */
ks_treemapnode* ks_treemapnode_copy(const ks_treemapnode* tmn);


/* -----------------------------------
 * ks_treemapnode_delete_all():
 * Deletes a ks_treemapnode, its 'key' and 'value' members, and recursively
 * deletes its 'right' and 'left' members.
 *
 * Inputs:
 * ks_treemapnode* tmn - the ks_treemapnode being deleted.
 *
 * Returns:
 * void
 */
void ks_treemapnode_delete_all(ks_treemapnode* tmn);


/* ----------------------------------
 * ks_treemapnode_copy_all():
 * Creates a copy of a treemapnode*, its ks_datacont*, and any
 * connected ks_treemapnodes.
 *
 * Inputs:
 * ks_treempanode* tmn - the ks_treemapnode to be copied.
 *
 * Returns:
 * ks_treemapnode* - a copy of the ks_treemapnode*.
 */
ks_treemapnode* ks_treemapnode_copy_all(const ks_treemapnode* tmn);


/* ----------------------------------
 * ks_treemapnode_add():
 * Add a key/value pair to a ks_treemapnode tree.
 *
 * Inputs:
 * ks_treemapnode* tmn - the treemap to be added to
 * ks_datacont* key - the key
 * ks_datacont* value - the value that the key maps to
 *
 * Returns:
 * int result - (-1) if any params are NULL.
 *            - (0) pair added successfully
 *            - (1) already contains pair, old value replaced with new value.
 *
 * Notes:
 * If the key-value pair is successfully added to the ks_treemapnode, the user code
 * must not delete or modify 'key' or 'value', otherwise undefined behavior could
 * ensue. If the pair was not added to the treemap, the user code is responsible for
 * deleting both when they are no longer needed.
 */
int ks_treemapnode_add(ks_treemapnode* tmn, const ks_datacont* key, const ks_datacont* value);


/* ---------------------------
 * ks_treemapnode_remove():
 * Find key/value pair and delete it.
 *
 * Inputs:
 * ks_treemapnode** tmn - the ks_treemapnode to be operated on
 * ks_datacont* key - the key to be removed
 *
 * Returns:
 * int result - (-1) if either param is NULL, or 'key' could not be found.
 *            - (0) pair removed successfully.
 *
 * Notes:
 * Because the key-value pair that is being removed could be located in the root node,
 * 'tmn' must be passed as a nested pointer so that it can be set to a different node,
 * or NULL if there are no nodes left after the removal. Also: 'key' is not consumed by
 * this procedure, it is only used to locate another ks_datacont containing the same data.
 */
int ks_treemapnode_remove(ks_treemapnode** tmn, const ks_datacont* key);


/* ---------------------------
 * ks_treemapnode_get():
 * Get the value from a ks_treemapnode by key.
 *
 * Inputs:
 * ks_treemapnode* tmn - the ks_treemapnode to be operated on.
 * ks_datacont* key - the key used to retrieve a value.
 *
 * Returns:
 * ks_datacont* value - (NULL) if either param is NULL, or if 'key' could not be found.
 *                 - the value mapped to by the key.
 *
 * Notes:
 * The ks_datacont returned by this function is a pointer to the original contained within 
 * the treemap, so it should not be deleted or modified by client code. Also:
 * 'key' is not consumed by this procedure, it is only used to locate another ks_datacont
 * containing the same data.
 */
ks_datacont* ks_treemapnode_get(const ks_treemapnode* tmn, const ks_datacont* key);


/* --------------------------
 * ks_treemapnode_get_key():
 * Retrieves a key located at a specified index within the ks_treemapnode.
 *
 * Inputs:
 * ks_treemapnode* tmn - the ks_treemapnode being retrieved from.
 * int index - the index of the key being retrieved. Negative values
 *             will wrap around.
 *
 * Returns:
 * ks_datacont* key - (NULL) if 'index' is OOB, or if 'tmn' is NULL.
 *               - the key located at 'index'.
 * Notes:
 * The ks_datacont returned by this function is a pointer to the original contained within 
 * the list, so it should not be deleted or modified by client code.
 */
ks_datacont* ks_treemapnode_get_key(const ks_treemapnode* tmn, int index);


/* ----------------------------
 * ks_treemapnode_count():
 * Count the number of key/value pairs stored within a ks_treemapnode.
 *
 * Inputs:
 * ks_treemapnode* tmn - the ks_treemapnode to be operated on.
 *
 * Returns:
 * unsigned int - >= (0) the number of pairs found in the ks_treemapnode, (0) if 'tmn' is NULL.
 */
unsigned int ks_treemapnode_count(const ks_treemapnode* tmn);


/* --------------------------
 * ks_treemapnode_height():
 * Calculate the maximum height of a ks_treemapnode tree.
 *
 * Inputs:
 * ks_treemapnode* tmn - the ks_treemapnode to be operated on.
 *
 * Returns:
 * unsigned int - >= (0) the height of the tree, (0) if 'tmn' is NULL.
 */
unsigned int ks_treemapnode_height(const ks_treemapnode* tmn);


/* --------------------------
 * ks_treemapnode_balance():
 * Balances a ks_treemapnode* tree to ensure optimal performance.
 *
 * Inputs:
 * ks_treemapnode* tmn - the root of the ks_treemapnode being balanced.
 *
 * Returns:
 * ks_treemapnode* - a balanced treemapnode*.
 */
ks_treemapnode* ks_treemapnode_balance(ks_treemapnode* tmn);


#endif
