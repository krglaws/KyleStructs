
#ifndef _TREESETNODE_H_
#define _TREESETNODE_H_


#include "datacont.h"


typedef struct treesetnode treesetnode;


struct treesetnode
{
  datacont* dc;
  treesetnode* right;
  treesetnode* left;
};


/* ---------------------
 * treesetnode_new():
 * Creates a new treesetnode* containing a specified datacont value.
 *
 * Inputs:
 * datacont* dc - the datacont to be contained by the new treesetnode*.
 *
 * Returns:
 * treesetnode* tsn - NULL if 'dc' is NULL.
 *                  - a treesetnode* containing 'dc'.
 *
 * Notes:
 * The 'right' and 'left' treesetnode members will be NULL.
 */
treesetnode* treesetnode_new(const datacont* dc);


/* -----------------------
 * treesetnode_delete():
 * Deletes a treesetnode and its datacont* value.
 *
 * Inputs:
 * treesetnode* tsn - the treesetnode being deleted.
 *
 * Returns:
 * void
 *
 * Notes:
 * This function does not delete the 'left' and 'right' nodes
 * that might be connected to 'tsn'.
 */
void treesetnode_delete(treesetnode* tsn);


/* --------------------------
 * treesetnode_delete_all():
 * Deletes a treesetnode and all nodes connected to it.
 *
 * Inputs:
 * treesetnode* tsn - the treesetnode being deleted.
 *
 * Returns:
 * void
 */
void treesetnode_delete_all(treesetnode* tsn);


/* -----------------------
 * treesetnode_add():
 * Adds a datacont* to a collection of other treesetnodes. The datacont is
 * compared with the dataconts contained within the linked treesetnodes, and is placed 
 * in a new treesetnode* based on the datacont value that it contains.
 *
 * Inputs:
 * treesetnode* tsn - the treesetnode being added to.
 * datacont* dc - the datacont being added to 'tsn'.
 *
 * Returns:
 * int result - (-1) if either param is NULL, or if 'dc' is not comparable to the other
 *              dataconts in 'tsn' (e.g. if 'dc' is of type CHAR and the others are INT).
 *            - (0) 'dc' was successfully added to 'tsn'.
 *            - (1) 'dc' is already present in the treesetnode and was not added.
 *
 * Notes:
 * If 'dc' is succefully stored into the set, 'dc' should not be deleted by the user code,
 * as it will be directly stored into the tree. Otherwise a seg fault is likely to occur.
 * In the event that a value matching 'dc' is already present in the treeset, 'dc' is not 
 * stored in the set. Because of this, it is up to the user code to delete 'dc' if necessary.
 */
int treesetnode_add(treesetnode* tsn, const datacont* dc);


/* ----------------------------
 * treesetnode_remove_by():
 * Remove a node contained within the treesetnode* parameter that matches the
 * datacont* parameter.
 *
 * Inputs:
 * treesetnode** tsn - remove treesetnode from this root node.
 * datacont* dc - remove treesetnode that contains the same value 
 *                as this data container.
 *
 * Returns:
 * int result - (-1) if 'dc' could not be found, or if either param is NULL.
 *            - (0) on success.
 *
 * Notes:
 * Because the datacont that is being removed might be located in the root node,
 * 'tsn' must be passed as a nested pointer so that it can be set to a different
 * node, or NULL if there are no nodes left after the removal.
 */
int treesetnode_remove_by(treesetnode** tsn, const datacont* dc);


/* ---------------------------
 * treesetnode_remove_at():
 * Remove a datacont* located at a specified index within the set.
 *
 * Inputs:
 * treesetnode** tsn - the treesetnode from which to remove a  datacont
 * int index - the index of the datacont to be removed from 'tsn'. Negative
 *             values will wrap around.
 *
 * Returns:
 * int result - (-1) if 'index' is OOB, or if 'tsn' is NULL.
 *            - (0) on success.
 * 
 * Notes:
 * See notes for treesetnode_remove_by().
 */
int treesetnode_remove_at(treesetnode** tsn, const int index);


/* -------------------------
 * treesetnode_index():
 * Returns the index of a given datacont value.
 *
 * Inputs:
 * treesetnode* tsn - the treesetnode being searched.
 * datacont* dc - the datacont to search for within 'tsn'.
 *
 * Returns:
 * int index - (-1) if 'dc' could not be found, or if either param is NULL.
 *           - >= (0) the index of 'dc'.
 *
 * Notes:
 * This function should not be used to determine if a datacont is present within
 * a treesetnode*. Instead treesetnode_contains() should be used as it is a much faster
 * operation than treesetnode_index().
 */
int treesetnode_index(const treesetnode* tsn, const datacont* dc);


/* --------------------------
 * treesetnode_contains():
 * Searches for a treesetnode that contains a value matching 'dc'.
 *
 * Inputs:
 * treesetnode* tsn - the treesetnode* being operated on.
 * datacont* dc - the datacont value to look for within 'tsn'.
 *
 * Returns:
 * unsigned int result - (0) if 'dc' could not be found, or if either param is NULL.
 *                     - (1) if 'dc' was found.
 */
unsigned int treesetnode_contains(const treesetnode* tsn, const datacont* dc);


/* ---------------------------
 * treesetnode_get():
 * Returns a datacont located at a specified index within the set.
 *
 * Inputs:
 * treesetnode* tsn - the treesetnode* being operated on.
 * int index - the index of the datacont to being retrieved. Negative values
 *             will wrap around.
 *
 * Returns:
 * datacont* dc - (NULL) if 'index' is OOB, or if 'tsn' is NULL.
 *              - the datacont located at 'index'.
 */
datacont* treesetnode_get(const treesetnode* tsn, const int index);


/* -------------------------
 * treesetnode_count():
 * Returns the number of nodes connected to a treesetnode* (including itself).
 *
 * Inputs:
 * treesetnode* tsn - the treesetnode being operated on.
 *
 * Returns:
 * unsigned int count - >= (0) the number of nodes in 'tsn', (0) when 'tsn' is NULL.
 */
unsigned int treesetnode_count(const treesetnode* tsn);


/* --------------------------
 * treesetnode_height():
 * Calculates the height of the treesetnode and all connected nodes.
 *
 * Inputs:
 * treesetnode* tsn - the treesetnode being operated on.
 *
 * Returns:
 * unsigned int height - >= (0) the height of the treesetnode, (0) when 'tsn' is NULL. 
 */
unsigned int treesetnode_height(const treesetnode* tsn);


/* --------------------------
 * treesetnode_balance():
 * Balances a treesetnode* tree to ensure optimal performance.
 *
 * Inputs:
 * treesetnode* tsn - the root of the treesetnode being balanced.
 *
 * Returns:
 * void
 */
void treesetnode_balance(treesetnode** tsn);


#endif

