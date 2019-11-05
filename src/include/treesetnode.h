
#ifndef _TREESETNODE_H_
#define _TREESETNODE_H_


typedef struct treesetnode treesetnode;


struct treesetnode
{
  datacont* dc;
  treesetnode* right;
  treesetnode* left;
};


/* ------------------
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
 * The 'right' and 'left' treesetnode members are NULL by default.
 */
treesetnode* treesetnode_new(const datacont* dc);


/* ------------------
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
 *              dataconts in 'tsn' (e.g. if 'dc' is of type CHAR and the others are 'INT').
 *            - (0) on success.
 */
int treesetnode_add(treesetnode* tsn, const datacont* dc);


/* ---------------------------------
 * treesetnode_remove():
 * Remove a node contained within the treesetnode* parameter that matches the
 * datacont* parameter.
 *
 * Inputs:
 * treesetnode* tsn - remove treesetnode from this root node.
 * datacont* dc - remove treesetnode that contains the same value 
 *                as this data container.
 *
 * Returns:
 * int result - (-1) if 'dc' could not be found, or if either param
 *              is empty.
 *            - (0) on success.
 */
int treesetnode_remove(treesetnode** tn, const datacont* dc);


/* --------------------------
 * treesetnode_contains():
 * Searches for a treesetnode that contains a value matching 'dc'.
 *
 * Inputs:
 * treesetnode* tsn - the treesetnode* being operated on.
 * datacont* dc - the datacont value to look for within 'tsn'.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - (0) if 'dc' could not be found.
 *            - (1) if 'dc' was found.
 */
int treesetnode_contains(const treesetnode* tn, const datacont* dc);

datacont* treesetnode_get_nth(const treesetnode* tn, int n);

unsigned int treesetnode_height(const treesetnode* tn);

unsigned int treesetnode_size(const treesetnode* tn);

#endif

