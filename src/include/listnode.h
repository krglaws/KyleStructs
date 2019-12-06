
#ifndef _LISTNODE_H_
#define _LISTNODE_H_


#include "datacont.h"


typedef struct listnode listnode;


struct listnode
{
  datacont* dc;
  listnode* next;
};


/* -------------------
 * listnode_new():
 * Creates a new listnode* containing a datacont*.
 *
 * Inputs:
 * datacont* dc - the datacont* to be held by the listnode.
 *
 * Returns:
 * listnode* ln - a listnode*, (NULL) if 'dc' is NULL.
 */
listnode* listnode_new(const datacont* dc);


/* --------------------
 * listnode_delete(listnode* ln):
 * Deletes a listnode and its datacont* member.
 *
 * Inputs:
 * listnode* ln - the listnode* being deleted.
 *
 * Returns:
 * void
 *
 * Notes:
 * This function will not touch the other nodes that 'ln' might be connected to. It is
 * assumed that the user code has or will disconnect any connected nodes.
 */
void listnode_delete(listnode* ln);


/* -------------------
 * listnode_delete_all():
 * Deletes a listnode and all other connected nodes.
 *
 * Inputs:
 * listnode* ln - the listnode to be deleted.
 *
 * Returns:
 * void
 *
 * Notes:
 * This function will delete 'ln' and all nodes connected to it. If only part of a
 * list is to be deleted, it will have to be manually isolated, with it's 'next'
 * member set to NULL.
 */
void listnode_delete_all(listnode* ln);


/* --------------------
 * listnode_add():
 * Append a datacont* to a listnode chain.
 *
 * Inputs:
 * listnode* ln - the listnode to be added to.
 * datacont* dc - the datacont being added to the list.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - (0) on success.
 */
int listnode_add(listnode* ln, const datacont* dc);


/* -----------------------
 * listnode_remove_by():
 * Removes the first occurrence of a datacont found within a chain of listnodes.
 *
 * Inputs:
 * listnode** ln - the listnode being operated on.
 * datacont* dc - the datacont to be removed from the listnode.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - (0) if the datacont was not found.
 *            - (1) if the datacont was successfully removed.
 *
 * Notes:
 * This function may delete the listnode reference passed to 'ln' if it is the node that contains the
 * 'dc' value being deleted. Because of this, a nested pointer must be passed into 'ln' so that
 * it can be set either to the next node in the list, or NULL if there are no remaining nodes. Also,
 * the datacont being passed into this function is assumed to be deleted by the user code. The 'dc'
 * parameter will not be modified in any way by this function.
 */
int listnode_remove_by(listnode** ln, const datacont* dc);


/* -----------------------------
 * listnode_remove_at():
 * Removes a datacont at a specified location within a listnode chain.
 *
 * Inputs:
 * listnode** ln - the listnode being operated on.
 * int index - the index at which the removal will take place. Negative
 *             values will wrap around.
 *
 * Returns:
 * int result - (-1) when 'ln' is NULL, or when 'index' is OOB.
 *            - (0) on success.
 *
 * Notes:
 * See listnode_remove_by() notes, as they apply to this function as well.
 */
int listnode_remove_at(listnode** ln, int index);


/* ------------------------
 * listnode_remove_all():
 * Removes all occurrences of a specified datacont value within a chain of listnodes.
 *
 * Inputs:
 * listnode** ln - the listnode being operated on.
 * datacont* dc - the datacont being removed from the listnode.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - >= (0) the number of nodes removed from the listnode chain.
 *
 * Notes:
 * See listnode_remove_by() notes, as they apply to this function as well.
 */
int listnode_remove_all(listnode** ln, const datacont* dc);


/* -----------------------------
 * listnode_replace_by():
 * Replaces the first occurrence of a specified datacont value with a new datacont value.
 *
 * Inputs:
 * listnode* ln - the listnode being operated on.
 * datacont* old_dc - the original datacont to be replaced.
 * datacont* new_dc - the new datacont replacing the original.
 *
 * Returns:
 * int result - (-1) when any param is NULL, or when 'old_dc' could not be found.
 *            - (0) on success.
 *
 * Notes:
 * The datacont replacement 'new_dc' should not be deleted by the user code
 * UNLESS the replacement fails. It will be stored directly into the list. 
 * The 'old_dc' parameter WILL always need to be deleted by the user code.
 */
int listnode_replace_by(listnode* ln, const datacont* old_dc, const datacont* new_dc);


/* -----------------------------
 * listnode_replace_at():
 * Replaces a datacont at a specified location within a listnode chain.
 *
 * Inputs:
 * listnode* ln - the listnode being operated on.
 * datacont* dc - the new datacont being added to the listnode chain.
 * int index - the index at which the replacement will take place. Negative
 *             values will wrap around.
 *
 * Returns:
 * int result - (-1) when either 'ln' or 'dc' are NULL, or when 'index' is OOB.
 *            - (0) on success.
 *
 * Notes:
 * The datacont replacement 'dc' should not be deleted by the user code. It will
 * be stored directly into the list.
 */
int listnode_replace_at(listnode* ln, const datacont* dc, int index);


/* ------------------------------
 * listnode_replace_all():
 * Replaces all occurrences of a specified datacont value with a new datacont value.
 *
 * Inputs:
 * listnode* ln - the listnode being operated on.
 * datacont* old_dc - the original datacont to be replaced.
 * datacont* new_dc - the new datacont replacing the orignal.
 *
 * Returns:
 * int result - -1 when any of the params is NULL
 *            - >= (0) the number of replacements that occurred.
 *
 * Notes:
 * See notes on listnode_replace_by(). The same applies here.
 */
int listnode_replace_all(listnode* ln, const datacont* old_dc, const datacont* new_dc);


/* -------------------------
 * listnode_insert():
 * Inserts a datacont* at a location specified in a chain of listnodes.
 *
 * Inputs:
 * listnode** ln - the listnode being operated on.
 * datacont* dc - the datacont being inserted.
 * int index - the location to insert the datacont. Negative values
 *             will wrap around.
 *
 * Returns:
 * int result - (-1) when either parameter is NULL, or when 'index' is OOB.
 *            - (0) on success.
 *
 * Notes:
 * In the event that a datacont is being inserted at the beginning of a listnode chain,
 * the reference to 'ln' will have to changed to the new 0th listnode, which is why
 * 'ln' must be passed in as a nested pointer.
 */
int listnode_insert(listnode** ln, const datacont* dc, int index);


/* ---------------------------
 * listnode_index():
 * Returns the index of the first datacont that matches the datacont 'dc' param located within a group of connected listnodes.
 *
 * Inputs:
 * listnode* ln - the listnode being searched through.
 * datacont* dc - the datacont to search for within the connected listnodes.
 *
 * Returns:
 * int index - (-1) if the datacont could not be found, or either param is NULL.
 *           - >= (0) the index of the datacont.
 *
 * Notes:
 * This function can also serve as a 'listnode_contains' function. Example:
 * if (listnode_index(ln, dc) >= 0) puts("Found it!");
 */
int listnode_index(const listnode* ln, const datacont* dc);


/* -------------------------
 * listnode_get():
 * Returns a pointer to a datacont contained within a listnode that is a specified number of nodes down the chain from 'ln'.
 *
 * Inputs:
 * listnode* ln - the listnode being operated on.
 * int index - the index used to locate the desired datacont. Negative
 *             values will wrap around.
 *
 * Returns:
 * datacont* dc - (NULL) if the 'index' is OOB, or if either param is NULL.
 *              - a pointer to the datacont located at 'index'.
 *
 * Notes:
 * The datacont returned by this function is a pointer to the original contained within the list, so it should not
 * be deleted or modified by client code.
 */
datacont* listnode_get(const listnode* ln, int index);


/* ----------------------------
 * listnode_count():
 * Returns the number of occurrences of a specified datacont value within a listnode chain.
 *
 * Inputs:
 * listnode* ln - the listnode being operated on.
 * datacont* dc - the datacont to look for within the list.
 *
 * Returns:
 * unsigned int num - (-1) when either param is NULL.
 *                  - >= (0) the number of listnodes that contain the same value as 'dc'.
 */
unsigned int listnode_count(const listnode* ln, const datacont* dc);


/* ----------------------------
 * listnode_length():
 * Returns the length of the list.
 *
 * Inputs:
 * listnode* ln - the listnode be operated on.
 *
 * Returns:
 * unsigned int length - >= (0) the length of the list. (0) when 'ln' is NULL.
 */
unsigned int listnode_length(const listnode* ln);


#endif
