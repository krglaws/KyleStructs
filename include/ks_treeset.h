#ifndef _KS_TREESET_H_
#define _KS_TREESET_H_


#include <ks_datacont.h>
#include <ks_treesetnode.h>


typedef struct ks_treeset ks_treeset;


struct ks_treeset
{
  ks_treesetnode* root;
};


/* ---------------------
 * ks_treeset_new():
 * Creates a new empty ks_treeset.
 *
 * Inputs:
 * void
 *
 * Returns:
 * ks_treeset* ts - an empty ks_treeset.
 */
ks_treeset* ks_treeset_new();


/* ----------------------
 * ks_treeset_delete():
 * Deletes a ks_treeset and all of its contents.
 *
 * Inputs:
 * ks_treeset* ts - the ks_treeset to be deleted.
 *
 * Returns:
 * void
 */
void ks_treeset_delete(ks_treeset* ts);


/* ----------------------
 * ks_treeset_add():
 * Adds a ks_datacont to a ks_treeset.
 *
 * Inputs:
 * ks_treeset* ts - the ks_treeset being added to.
 * ks_datacont* dc - the ks_datacont being added to the ks_treeset.
 *
 * Returns:
 * int result - (-1) if either param is NULL, or if 'dc' is not comparable to the other 
 *              ks_dataconts in the ks_treeset (e.g. if 'dc' is of type CHAR and the others are INT).
 *            - (0) 'dc' was successfully added to 'ts'.
 *            - (1) 'dc' is already present in the ks_treeset and was not added.
 * 
 * Notes:
 * If 'dc' is successfully stored into the set, 'dc' should not be deleted by the user code,
 * as it will be directly stored into the tree. Otherwise a seg fault is likely to occur.
 * In the event that a value matching 'dc' is already present in the ks_treeset, 'dc' will not
 * be stored, and 'dc' must be deleted by the user code.
 */
int ks_treeset_add(ks_treeset* ts, const ks_datacont* dc);


/* ------------------------------
 * ks_treeset_remove_by():
 * Remove a ks_datacont from a ks_treeset that contains a value matching the value of the 'dc'
 * argument.
 *
 * Inputs:
 * ks_treeset* ts - the ks_treeset being removed from.
 * ks_datacont* dc - the ks_datacont value to remove from the ks_treeset.
 *
 * Returns:
 * int result - (-1) if either param is NULL, or if 'dc' could not be found.
 *            - (0) on success.
 */
int ks_treeset_remove_by(ks_treeset* ts, const ks_datacont* dc);


/* ----------------------------
 * ks_treeset_remove_at():
 * Remove a ks_datacont from a ks_treeset at a specified index.
 *
 * Inputs:
 * ks_treeset* ts - the ks_treeset being removed from.
 * int index - the index of the ks_datacont to be removed.
 *
 * Returns:
 * int result - (-1) if 'index' is OOB or if 'ts' is NULL.
 *            - >= (0) on success.
 */
int ks_treeset_remove_at(ks_treeset* ts, const int index);


/* ---------------------------
 * ks_treeset_index():
 * Returns the index of a given ks_datacont value.
 *
 * Inputs:
 * ks_treeset* ts - the ks_treeset being searched.
 * ks_datacont* dc - the ks_datacont to search for within 'ts'.
 *
 * Returns:
 * int index - (-1) if 'dc' could not be found, or if either param is NULL.
 *           - >= (0) the index of 'dc'. Negative values will wrap around.
 *
 * Notes:
 * This function should not be used to determine if a ks_datacont is present within
 * a ks_treeset*. Instead ks_treeset_contains() should be used as it is a much faster
 * operation than ks_treeset_index().
 */
int ks_treeset_index(const ks_treeset* ts, const ks_datacont* dc);


/* -----------------------------
 * ks_treeset_contains():
 * Searches for a specified ks_datacont value within a ks_treeset.
 *
 * Inputs:
 * ks_treeset* ts - the ks_treeset being searched.
 * ks_datacont* dc - the ks_datacont to search for within 'ts'.
 *
 * Returns:
 * unsigned int result - (0) if 'dc' could not be found, or if either param is NULL.
 *                    - (1) if 'dc' was found.
 */
unsigned int ks_treeset_contains(const ks_treeset* ts, const ks_datacont* dc);


/* ---------------------------
 * ks_treeset_get():
 * Returns a ks_datacont located at a specified index within a ks_treeset.
 *
 * Inputs:
 * ks_treeset* ts - the ks_treeset* being operated on.
 * int index - the index of the ks_datacont to being retrieved. Negative values
 *             will wrap around.
 *
 * Returns:
 * ks_datacont* dc - (NULL) if 'index' is OOB, or if 'tsn' is NULL.
 *              - the ks_datacont located at 'index'.
 *
 * Notes:
 * The ks_datacont returned by this function is a pointer to the original contained within the ks_treeset,
 * so it should not be deleted or modified by client code.
 */
ks_datacont* ks_treeset_get(const ks_treeset* tsn, const int index);


/* -------------------------
 * ks_treeset_count():
 * Returns the number of ks_dataconts stored in a ks_treeset.
 *
 * Inputs:
 * ks_treeset* ts - the ks_treeset being operated on.
 *
 * Returns:
 * unsigned int count - >= (0) the number of nodes in 'ts', (0) when 'ts' is NULL.
 */
unsigned int ks_treeset_count(const ks_treeset* ts);


/* --------------------------
 * ks_treeset_height():
 * Calculates the height of the ks_treeset and all connected nodes.
 *
 * Inputs:
 * ks_treeset* ts - the ks_treeset being operated on.
 *
 * Returns:
 * unsigned int height - >= (0) the height of the ks_treeset, (0) when 'ts' is NULL. 
 */
unsigned int ks_treeset_height(const ks_treeset* ts);


/* --------------------------
 * ks_treeset_balance():
 * Balances a ks_treeset tree to ensure optimal performance.
 *
 * Inputs:
 * ks_treeset* tsn - the ks_treeset being balanced.
 *
 * Returns:
 * void
 */
void ks_treeset_balance(ks_treeset* ts);


#endif
