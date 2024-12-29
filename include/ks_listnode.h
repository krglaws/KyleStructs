#ifndef _KS_LISTNODE_H_
#define _KS_LISTNODE_H_

#include "ks_types.h"


/* -------------------
 * ks_listnode_new():
 * Creates a new ks_listnode* containing a ks_datacont*.
 *
 * Inputs:
 * ks_datacont* dc - the ks_datacont* to be held by the ks_listnode.
 *
 * Returns:
 * ks_listnode* ln - a ks_listnode*, (NULL) if 'dc' is NULL.
 */
ks_listnode* ks_listnode_new(const ks_datacont* dc);


/* --------------------
 * ks_listnode_delete():
 * Deletes a ks_listnode and its ks_datacont* member.
 *
 * Inputs:
 * ks_listnode* ln - the ks_listnode* being deleted.
 *
 * Returns:
 * void
 *
 * Notes:
 * This function will not touch the other nodes that 'ln' might be connected to. It is
 * assumed that the user code has or will disconnect any connected nodes.
 */
void ks_listnode_delete(ks_listnode* ln);


/* --------------------
 * ks_listnode_copy():
 * Creates a copy of a ks_listnode and its ks_datacont.
 *
 * Inputs:
 * ks_listnode* ln - the ks_listnode being copied.
 *
 * Returns:
 * ks_listnode* - a copy of the ks_listnode.
 *
 * Notes:
 * ks_listnode_copy() only copies 'ln' and its connected ks_datacont*,
 * but not any other connected ks_listnodes.
 */
ks_listnode* ks_listnode_copy(const ks_listnode* ln);


/* -------------------
 * ks_listnode_delete_all():
 * Deletes a ks_listnode and all other connected nodes.
 *
 * Inputs:
 * ks_listnode* ln - the ks_listnode to be deleted.
 *
 * Returns:
 * void
 *
 * Notes:
 * This function will delete 'ln' and all nodes connected to it. If only part of a
 * list is to be deleted, it will have to be manually isolated, with it's 'next'
 * member set to NULL.
 */
void ks_listnode_delete_all(ks_listnode* ln);


/* ----------------------
 * ks_listnode_copy_all():
 * Creates a copy of a ks_listnode and all of its connected nodes.
 *
 * Inputs:
 * ks_listnode* ln - the ks_listnode to be copied.
 * 
 * Returns:
 * ks_listnode* - a copy of the ks_listnode.
 */
ks_listnode* ks_listnode_copy_all(const ks_listnode* ln);


/* --------------------
 * ks_listnode_add():
 * Append a ks_datacont* to a ks_listnode chain.
 *
 * Inputs:
 * ks_listnode* ln - the ks_listnode to be added to.
 * ks_datacont* dc - the ks_datacont being added to the list.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - (0) on success.
 */
int ks_listnode_add(ks_listnode* ln, const ks_datacont* dc);


/* ---------------------
 * ks_listnode_merge():
 * Merges two ks_listnodes.
 *
 * Inputs:
 * ks_listnode* lna - the left half of new ks_listnode* chain.
 * ks_listnode* lnb - the right half of new ks_listnode* chain.
 *
 * Returns:
 * ks_listnode* - pointer to beginning of ks_listnode chain.
 *
 * Notes:
 * If one of the params is NULL, the non-NULL param will be returned.
 * If both are NULL, NULL will be returned.
 */
ks_listnode* ks_listnode_merge(ks_listnode* lna, ks_listnode* lnb);


/* -----------------------
 * ks_listnode_remove_by():
 * Removes the first occurrence of a ks_datacont found within a chain of ks_listnodes.
 *
 * Inputs:
 * ks_listnode** ln - the ks_listnode being operated on.
 * ks_datacont* dc - the ks_datacont to be removed from the ks_listnode.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - (0) if the ks_datacont was not found.
 *            - (1) if the ks_datacont was successfully removed.
 *
 * Notes:
 * This function may delete the ks_listnode reference passed to 'ln' if it is the node that contains the
 * 'dc' value being deleted. Because of this, a nested pointer must be passed into 'ln' so that
 * it can be set either to the next node in the list, or NULL if there are no remaining nodes. Also,
 * the ks_datacont being passed into this function is assumed to be deleted by the user code. The 'dc'
 * parameter will not be modified in any way by this function.
 */
int ks_listnode_remove_by(ks_listnode** ln, const ks_datacont* dc);


/* -----------------------------
 * ks_listnode_remove_at():
 * Removes a ks_datacont at a specified location within a ks_listnode chain.
 *
 * Inputs:
 * ks_listnode** ln - the ks_listnode being operated on.
 * int index - the index at which the removal will take place. Negative
 *             values will wrap around.
 *
 * Returns:
 * int result - (-1) when 'ln' is NULL, or when 'index' is OOB.
 *            - (0) on success.
 *
 * Notes:
 * See ks_listnode_remove_by() notes, as they apply to this function as well.
 */
int ks_listnode_remove_at(ks_listnode** ln, int index);


/* ------------------------
 * ks_listnode_remove_all():
 * Removes all occurrences of a specified ks_datacont value within a chain of ks_listnodes.
 *
 * Inputs:
 * ks_listnode** ln - the ks_listnode being operated on.
 * ks_datacont* dc - the ks_datacont being removed from the ks_listnode.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - >= (0) the number of nodes removed from the ks_listnode chain.
 *
 * Notes:
 * See ks_listnode_remove_by() notes, as they apply to this function as well.
 */
int ks_listnode_remove_all(ks_listnode** ln, const ks_datacont* dc);


/* -----------------------------
 * ks_listnode_replace_by():
 * Replaces the first occurrence of a specified ks_datacont value with a new ks_datacont value.
 *
 * Inputs:
 * ks_listnode* ln - the ks_listnode being operated on.
 * ks_datacont* old_dc - the original ks_datacont to be replaced.
 * ks_datacont* new_dc - the new ks_datacont replacing the original.
 *
 * Returns:
 * int result - (-1) when any param is NULL, or when 'old_dc' could not be found.
 *            - (0) on success.
 *
 * Notes:
 * The ks_datacont replacement 'new_dc' should not be deleted by the user code
 * UNLESS the replacement fails. It will be stored directly into the list. 
 * The 'old_dc' parameter WILL always need to be deleted by the user code.
 */
int ks_listnode_replace_by(ks_listnode* ln, const ks_datacont* old_dc, const ks_datacont* new_dc);


/* -----------------------------
 * ks_listnode_replace_at():
 * Replaces a ks_datacont at a specified location within a ks_listnode chain.
 *
 * Inputs:
 * ks_listnode* ln - the ks_listnode being operated on.
 * ks_datacont* dc - the new ks_datacont being added to the ks_listnode chain.
 * int index - the index at which the replacement will take place. Negative
 *             values will wrap around.
 *
 * Returns:
 * int result - (-1) when either 'ln' or 'dc' are NULL, or when 'index' is OOB.
 *            - (0) on success.
 *
 * Notes:
 * The ks_datacont replacement 'dc' should not be deleted by the user code. It will
 * be stored directly into the list.
 */
int ks_listnode_replace_at(ks_listnode* ln, const ks_datacont* dc, int index);


/* ------------------------------
 * ks_listnode_replace_all():
 * Replaces all occurrences of a specified ks_datacont value with a new ks_datacont value.
 *
 * Inputs:
 * ks_listnode* ln - the ks_listnode being operated on.
 * ks_datacont* old_dc - the original ks_datacont to be replaced.
 * ks_datacont* new_dc - the new ks_datacont replacing the orignal.
 *
 * Returns:
 * int result - -1 when any of the params is NULL
 *            - >= (0) the number of replacements that occurred.
 *
 * Notes:
 * See notes on ks_listnode_replace_by(). The same applies here.
 */
int ks_listnode_replace_all(ks_listnode* ln, const ks_datacont* old_dc, const ks_datacont* new_dc);


/* -------------------------
 * ks_listnode_insert():
 * Inserts a ks_datacont* at a location specified in a chain of ks_listnodes.
 *
 * Inputs:
 * ks_listnode** ln - the ks_listnode being operated on.
 * ks_datacont* dc - the ks_datacont being inserted.
 * int index - the location to insert the ks_datacont. Negative values
 *             will wrap around.
 *
 * Returns:
 * int result - (-1) when either parameter is NULL, or when 'index' is OOB.
 *            - (0) on success.
 *
 * Notes:
 * In the event that a ks_datacont is being inserted at the beginning of a ks_listnode chain,
 * the reference to 'ln' will have to changed to the new 0th ks_listnode, which is why
 * 'ln' must be passed in as a nested pointer.
 */
int ks_listnode_insert(ks_listnode** ln, const ks_datacont* dc, int index);


/* ---------------------------
 * ks_listnode_index():
 * Returns the index of the first ks_datacont that matches the ks_datacont 'dc' param located within a group of connected ks_listnodes.
 *
 * Inputs:
 * ks_listnode* ln - the ks_listnode being searched through.
 * ks_datacont* dc - the ks_datacont to search for within the connected ks_listnodes.
 *
 * Returns:
 * int index - (-1) if the ks_datacont could not be found, or either param is NULL.
 *           - >= (0) the index of the ks_datacont.
 *
 * Notes:
 * This function can also serve as a 'ks_listnode_contains' function. Example:
 * if (ks_listnode_index(ln, dc) >= 0) puts("Found it!");
 */
int ks_listnode_index(const ks_listnode* ln, const ks_datacont* dc);


/* -------------------------
 * ks_listnode_get():
 * Returns a pointer to a ks_datacont contained within a ks_listnode that is a specified number of nodes down the chain from 'ln'.
 *
 * Inputs:
 * ks_listnode* ln - the ks_listnode being operated on.
 * int index - the index used to locate the desired ks_datacont. Negative
 *             values will wrap around.
 *
 * Returns:
 * ks_datacont* dc - (NULL) if the 'index' is OOB, or if either param is NULL.
 *                 - a pointer to the ks_datacont located at 'index'.
 *
 * Notes:
 * The ks_datacont returned by this function is a pointer to the original contained within the list, so it should not
 * be deleted or modified by client code.
 */
const ks_datacont* ks_listnode_get(const ks_listnode* ln, int index);


/* ----------------------------
 * ks_listnode_count():
 * Returns the number of occurrences of a specified ks_datacont value within a ks_listnode chain.
 *
 * Inputs:
 * ks_listnode* ln - the ks_listnode being operated on.
 * ks_datacont* dc - the ks_datacont to look for within the list.
 *
 * Returns:
 * unsigned int num - (-1) when either param is NULL.
 *                  - >= (0) the number of ks_listnodes that contain the same value as 'dc'.
 */
unsigned int ks_listnode_count(const ks_listnode* ln, const ks_datacont* dc);


/* ----------------------------
 * ks_listnode_length():
 * Returns the length of the list.
 *
 * Inputs:
 * ks_listnode* ln - the ks_listnode be operated on.
 *
 * Returns:
 * unsigned int length - >= (0) the length of the list. (0) when 'ln' is NULL.
 */
unsigned int ks_listnode_length(const ks_listnode* ln);


#endif
