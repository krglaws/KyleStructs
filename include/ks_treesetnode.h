#ifndef _KS_TREESETNODE_H_
#define _KS_TREESETNODE_H_


#include "ks_datacont.h"


typedef struct ks_treesetnode ks_treesetnode;


struct ks_treesetnode
{
  ks_datacont* dc;
  ks_treesetnode* right;
  ks_treesetnode* left;
};


/* ---------------------
 * ks_treesetnode_new():
 * Creates a new ks_treesetnode* containing a specified ks_datacont value.
 *
 * Inputs:
 * ks_datacont* dc - the ks_datacont to be contained by the new ks_treesetnode*.
 *
 * Returns:
 * ks_treesetnode* tsn - NULL if 'dc' is NULL.
 *                  - a ks_treesetnode* containing 'dc'.
 *
 * Notes:
 * The 'right' and 'left' ks_treesetnode members will be NULL.
 */
ks_treesetnode* ks_treesetnode_new(const ks_datacont* dc);


/* -----------------------
 * ks_treesetnode_delete():
 * Deletes a ks_treesetnode and its ks_datacont* value.
 *
 * Inputs:
 * ks_treesetnode* tsn - the ks_treesetnode being deleted.
 *
 * Returns:
 * void
 *
 * Notes:
 * This function does not delete the 'left' and 'right' nodes
 * that might be connected to 'tsn'.
 */
void ks_treesetnode_delete(ks_treesetnode* tsn);


/* --------------------------
 * ks_treesetnode_delete_all():
 * Deletes a ks_treesetnode and all nodes connected to it.
 *
 * Inputs:
 * ks_treesetnode* tsn - the ks_treesetnode being deleted.
 *
 * Returns:
 * void
 */
void ks_treesetnode_delete_all(ks_treesetnode* tsn);


/* -----------------------
 * ks_treesetnode_add():
 * Adds a ks_datacont* to a collection of other ks_treesetnodes. The ks_datacont is
 * compared with the ks_dataconts contained within the linked ks_treesetnodes, and is placed 
 * in a new ks_treesetnode* based on the ks_datacont value that it contains.
 *
 * Inputs:
 * ks_treesetnode* tsn - the ks_treesetnode being added to.
 * ks_datacont* dc - the ks_datacont being added to 'tsn'.
 *
 * Returns:
 * int result - (-1) if either param is NULL, or if 'dc' is not comparable to the other
 *              ks_dataconts in 'tsn' (e.g. if 'dc' is of type CHAR and the others are INT).
 *            - (0) 'dc' was successfully added to 'tsn'.
 *            - (1) 'dc' is already present in the ks_treesetnode and was not added.
 *
 * Notes:
 * If 'dc' is succefully stored into the set, 'dc' should not be deleted by the user code,
 * as it will be directly stored into the tree. Otherwise a seg fault is likely to occur.
 * In the event that a value matching 'dc' is already present in the treeset, 'dc' is not 
 * stored in the set. Because of this, it is up to the user code to delete 'dc' if necessary.
 */
int ks_treesetnode_add(ks_treesetnode* tsn, const ks_datacont* dc);


/* ----------------------------
 * ks_treesetnode_remove_by():
 * Remove a node contained within the ks_treesetnode* parameter that matches the
 * ks_datacont* parameter.
 *
 * Inputs:
 * ks_treesetnode** tsn - remove ks_treesetnode from this root node.
 * ks_datacont* dc - remove ks_treesetnode that contains the same value 
 *                as this data container.
 *
 * Returns:
 * int result - (-1) if 'dc' could not be found, or if either param is NULL.
 *            - (0) on success.
 *
 * Notes:
 * Because the ks_datacont that is being removed might be located in the root node,
 * 'tsn' must be passed as a nested pointer so that it can be set to a different
 * node, or NULL if there are no nodes left after the removal.
 */
int ks_treesetnode_remove_by(ks_treesetnode** tsn, const ks_datacont* dc);


/* ---------------------------
 * ks_treesetnode_remove_at():
 * Remove a ks_datacont* located at a specified index within the set.
 *
 * Inputs:
 * ks_treesetnode** tsn - the ks_treesetnode from which to remove a  ks_datacont
 * int index - the index of the ks_datacont to be removed from 'tsn'. Negative
 *             values will wrap around.
 *
 * Returns:
 * int result - (-1) if 'index' is OOB, or if 'tsn' is NULL.
 *            - (0) on success.
 * 
 * Notes:
 * See notes for ks_treesetnode_remove_by().
 */
int ks_treesetnode_remove_at(ks_treesetnode** tsn, const int index);


/* -------------------------
 * ks_treesetnode_index():
 * Returns the index of a given ks_datacont value.
 *
 * Inputs:
 * ks_treesetnode* tsn - the ks_treesetnode being searched.
 * ks_datacont* dc - the ks_datacont to search for within 'tsn'.
 *
 * Returns:
 * int index - (-1) if 'dc' could not be found, or if either param is NULL.
 *           - >= (0) the index of 'dc'.
 *
 * Notes:
 * This function should not be used to determine if a ks_datacont is present within
 * a ks_treesetnode*. Instead ks_treesetnode_contains() should be used as it is a much faster
 * operation than ks_treesetnode_index().
 */
int ks_treesetnode_index(const ks_treesetnode* tsn, const ks_datacont* dc);


/* --------------------------
 * ks_treesetnode_contains():
 * Searches for a ks_treesetnode that contains a value matching 'dc'.
 *
 * Inputs:
 * ks_treesetnode* tsn - the ks_treesetnode* being operated on.
 * ks_datacont* dc - the ks_datacont value to look for within 'tsn'.
 *
 * Returns:
 * unsigned int result - (0) if 'dc' could not be found, or if either param is NULL.
 *                     - (1) if 'dc' was found.
 */
unsigned int ks_treesetnode_contains(const ks_treesetnode* tsn, const ks_datacont* dc);


/* ---------------------------
 * ks_treesetnode_get():
 * Returns a ks_datacont located at a specified index within the set.
 *
 * Inputs:
 * ks_treesetnode* tsn - the ks_treesetnode* being operated on.
 * int index - the index of the ks_datacont to being retrieved. Negative values
 *             will wrap around.
 *
 * Returns:
 * ks_datacont* dc - (NULL) if 'index' is OOB, or if 'tsn' is NULL.
 *              - the ks_datacont located at 'index'.
 * Notes:
 * The ks_datacont returned by this function is a pointer to the original contained within 
 * the treeset, so it should not be deleted or modified by client code.
 */
ks_datacont* ks_treesetnode_get(const ks_treesetnode* tsn, const int index);


/* -------------------------
 * ks_treesetnode_count():
 * Returns the number of nodes connected to a ks_treesetnode* (including itself).
 *
 * Inputs:
 * ks_treesetnode* tsn - the ks_treesetnode being operated on.
 *
 * Returns:
 * unsigned int count - >= (0) the number of nodes in 'tsn', (0) when 'tsn' is NULL.
 */
unsigned int ks_treesetnode_count(const ks_treesetnode* tsn);


/* --------------------------
 * ks_treesetnode_height():
 * Calculates the height of the ks_treesetnode and all connected nodes.
 *
 * Inputs:
 * ks_treesetnode* tsn - the ks_treesetnode being operated on.
 *
 * Returns:
 * unsigned int height - >= (0) the height of the ks_treesetnode, (0) when 'tsn' is NULL. 
 */
unsigned int ks_treesetnode_height(const ks_treesetnode* tsn);


/* --------------------------
 * ks_treesetnode_balance():
 * Balances a ks_treesetnode* tree to ensure optimal performance.
 *
 * Inputs:
 * ks_treesetnode* tsn - the root of the ks_treesetnode being balanced.
 *
 * Returns:
 * void
 */
void ks_treesetnode_balance(ks_treesetnode** tsn);


#endif
