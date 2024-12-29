#ifndef _KS_HASHSET_H_
#define _KS_HASHSET_H_

#include <stddef.h>

#include "ks_types.h"

/* ----------------------------------
 * ks_hashset_new():
 * Creates a new empty ks_hashset.
 *
 * Inputs:
 * unsigned int buckets - the number of buckets that the new ks_hashset should contain.
 *
 * Returns:
 * ks_hashset* hs - a new empty ks_hashset.
 */
ks_hashset* ks_hashset_new(enum ks_datatype type, size_t num_buckets);

/* ---------------------------------
 * ks_hashset_delete():
 * Deletes a ks_hashset and all of its contents.
 *
 * Inputs:
 * ks_hashset* hs - the ks_hashset being deleted.
 *
 * Returns:
 * void
 */
void ks_hashset_delete(ks_hashset* hs);

/* -------------------------------
 * ks_hashset_copy():
 * Creates a copy of a ks_hashset and all of its contents.
 *
 * Inputs:
 * ks_hashset* hs - the ks_hashset being delete.
 *
 * Returns:
 * ks_hashset* - a copy of 'hs'.
 */
ks_hashset* ks_hashset_copy(const ks_hashset* hs);

/* --------------------------------
 * ks_hashset_add():
 * Adds a ks_datacont to a hashaset.
 *
 * Inputs:
 * ks_hashset* hs - the ks_hashset being added to.
 * ks_datacont* dc - the ks_datacont being added to 'hs'.
 *
 * Returns:
 * int result - (-1) if either param is NULL, or if the ks_datatype of 'dc' does not
 *              match the other ks_dataconts within the ks_hashset.
 *            - (0) 'dc' was successfully added to the ks_hashset. 
 *            - (1) 'dc' is already stored in the ks_hashset.
 *
 * Notes:
 * If 'dc' is successfully stored into the set, 'dc' should not be deleted by the user code,
 * as it will be directly stored into the tree. Otherwise a seg fault is likely to occur.
 * In the event that a value matching 'dc' is already present, or if 'hs' is NULL, 'dc' will
 * not be stored into the set, and 'dc' must be deleted by the user code.
 */
int ks_hashset_add(ks_hashset* hs, const ks_datacont* dc);

/* -------------------------
 * ks_hashset_remove():
 * Remove a ks_datacont from a ks_hashset.
 *
 * Inputs:
 * ks_hashset* hs - the ks_hashset being removed from.
 * ks_datacont* dc - the ks_datacont to be removed from 'hs'.
 *
 * Returns:
 * int result - (-1) if either param is NULL, or if 'dc' could not be found.
 *            - (0) on success.
 */
int ks_hashset_remove(ks_hashset* hs, const ks_datacont* dc);

/* ------------------------
 * ks_hashset_contains():
 * Searches for a specified ks_datacont value within a ks_hashset.
 *
 * Inputs:
 * ks_hashset* hs - the ks_hashset being searched.
 * ks_datacont* dc - the ks_datacont being searched for.
 *
 * Returns:
 * unsigned int result - (0) if 'dc' could not be found, or if either param is NULL.
 *                     - (1) 'hs' contains 'dc'.
 */
unsigned int ks_hashset_contains(const ks_hashset* hs, const ks_datacont* dc);

/* ------------------------
 * ks_hashset_count():
 * Counts the number of ks_dataconts contained within a ks_hashset.
 *
 * Inputs:
 * ks_hashset* hs - the ks_hashset being operated on.
 *
 * Returns:
 * unsigned int count - >= (0) the number of ks_dataconts within 'hs', (0) when 'hs' is NULL.
 */
unsigned int ks_hashset_count(const ks_hashset* hs);

/* --------------------
 * ks_hashset_get():
 * Retrieves a ks_datacont located at a specified index within a ks_hashset.
 *
 * Inputs:
 * ks_hashet* hs - the ks_hashset being operated on.
 * int index - the index from which to retrieve a ks_datacont. (supports negative indexing)
 *
 * Notes:
 * Negative values for 'index' are allowed.
 */
const ks_datacont* ks_hashset_get(const ks_hashset* hs, int index);

/* --------------------
 * ks_hashset_optimize():
 * Balances all of the ks_treeset buckets in a ks_hashset to ensure O(log(N)) search
 * time.
 *
 * Inputs:
 * ks_hashset* hs - the ks_hashset being operated on.
 *
 * Returns:
 * void
 */
void ks_hashset_optimize(ks_hashset* hs);

#endif
