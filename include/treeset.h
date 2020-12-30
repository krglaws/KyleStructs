#ifndef _TREESET_H_
#define _TREESET_H_


#include "treesetnode.h"


typedef struct treeset treeset;


struct treeset
{
  treesetnode* root;
};


/* ---------------------
 * treeset_new():
 * Creates a new empty treeset.
 *
 * Inputs:
 * void
 *
 * Returns:
 * treeset* ts - an empty treeset.
 */
treeset* treeset_new();


/* ----------------------
 * treeset_delete():
 * Deletes a treeset and all of its contents.
 *
 * Inputs:
 * treeset* ts - the treeset to be deleted.
 *
 * Returns:
 * void
 */
void treeset_delete(treeset* ts);


/* ----------------------
 * treeset_add():
 * Adds a datacont to a treeset.
 *
 * Inputs:
 * treeset* ts - the treeset being added to.
 * datacont* dc - the datacont being added to the treeset.
 *
 * Returns:
 * int result - (-1) if either param is NULL, or if 'dc' is not comparable to the other 
 *              dataconts in the treeset (e.g. if 'dc' is of type CHAR and the others are INT).
 *            - (0) 'dc' was successfully added to 'ts'.
 *            - (1) 'dc' is already present in the treeset and was not added.
 * 
 * Notes:
 * If 'dc' is successfully stored into the set, 'dc' should not be deleted by the user code,
 * as it will be directly stored into the tree. Otherwise a seg fault is likely to occur.
 * In the event that a value matching 'dc' is already present in the treeset, 'dc' will not
 * be stored, and 'dc' must be deleted by the user code.
 */
int treeset_add(treeset* ts, const datacont* dc);


/* ------------------------------
 * treeset_remove_by():
 * Remove a datacont from a treeset that contains a value matching the value of the 'dc'
 * argument.
 *
 * Inputs:
 * treeset* ts - the treeset being removed from.
 * datacont* dc - the datacont value to remove from the treeset.
 *
 * Returns:
 * int result - (-1) if either param is NULL, or if 'dc' could not be found.
 *            - (0) on success.
 */
int treeset_remove_by(treeset* ts, const datacont* dc);


/* ----------------------------
 * treeset_remove_at():
 * Remove a datacont from a treeset at a specified index.
 *
 * Inputs:
 * treeset* ts - the treeset being removed from.
 * int index - the index of the datacont to be removed.
 *
 * Returns:
 * int result - (-1) if 'index' is OOB or if 'ts' is NULL.
 *            - >= (0) on success.
 */
int treeset_remove_at(treeset* ts, const int index);


/* ---------------------------
 * treeset_index():
 * Returns the index of a given datacont value.
 *
 * Inputs:
 * treeset* ts - the treeset being searched.
 * datacont* dc - the datacont to search for within 'ts'.
 *
 * Returns:
 * int index - (-1) if 'dc' could not be found, or if either param is NULL.
 *           - >= (0) the index of 'dc'. Negative values will wrap around.
 *
 * Notes:
 * This function should not be used to determine if a datacont is present within
 * a treeset*. Instead treeset_contains() should be used as it is a much faster
 * operation than treeset_index().
 */
int treeset_index(const treeset* ts, const datacont* dc);


/* -----------------------------
 * treeset_contains():
 * Searches for a specified datacont value within a treeset.
 *
 * Inputs:
 * treeset* ts - the treeset being searched.
 * datacont* dc - the datacont to search for within 'ts'.
 *
 * Returns:
 * unsigned int result - (0) if 'dc' could not be found, or if either param is NULL.
 *                    - (1) if 'dc' was found.
 */
unsigned int treeset_contains(const treeset* ts, const datacont* dc);


/* ---------------------------
 * treeset_get():
 * Returns a datacont located at a specified index within a treeset.
 *
 * Inputs:
 * treeset* ts - the treeset* being operated on.
 * int index - the index of the datacont to being retrieved. Negative values
 *             will wrap around.
 *
 * Returns:
 * datacont* dc - (NULL) if 'index' is OOB, or if 'tsn' is NULL.
 *              - the datacont located at 'index'.
 *
 * Notes:
 * The datacont returned by this function is a pointer to the original contained within the treeset,
 * so it should not be deleted or modified by client code.
 */
datacont* treeset_get(const treeset* tsn, const int index);


/* -------------------------
 * treeset_count():
 * Returns the number of dataconts stored in a treeset.
 *
 * Inputs:
 * treeset* ts - the treeset being operated on.
 *
 * Returns:
 * unsigned int count - >= (0) the number of nodes in 'ts', (0) when 'ts' is NULL.
 */
unsigned int treeset_count(const treeset* ts);


/* --------------------------
 * treeset_height():
 * Calculates the height of the treeset and all connected nodes.
 *
 * Inputs:
 * treeset* ts - the treeset being operated on.
 *
 * Returns:
 * unsigned int height - >= (0) the height of the treeset, (0) when 'ts' is NULL. 
 */
unsigned int treeset_height(const treeset* ts);


/* --------------------------
 * treeset_balance():
 * Balances a treeset tree to ensure optimal performance.
 *
 * Inputs:
 * treeset* tsn - the treeset being balanced.
 *
 * Returns:
 * void
 */
void treeset_balance(treeset* ts);


#endif
