#ifndef _KS_ITERATOR_H_
#define _KS_ITERATOR_H_

#include <stdbool.h>


/* -------------------
 * ks_iterator_new():
 * Creates an iterator for a kylestructs object.
 *
 * Inputs:
 * void* ks_obj - the kylestructs object for which to create an iterator.
 * enum ks_datatype type - the type of 'ks_obj'
 *
 * Returns:
 * ks_iterator* - an iterator for 'ks_obj'
 *
 * Notes:
 * The 'type' parameter can only be KS_LIST, KS_TREESET, KS_HASHSET,
 * KS_TREEMAP, or KS_HASHMAP.
 */
ks_iterator* ks_iterator_new(const void* ks_obj, enum ks_datatype type);


/* -------------------
 * ks_iterator_delete():
 * deletes a ks_iterator.
 *
 * Inputs:
 * ks_iterator* iter - the iterator to be deleted
 *
 * Returns:
 * void
 */
void ks_iterator_delete(ks_iterator* iter);


/* -------------------
 * ks_iterator_next():
 * Retreives the current ks_datacont from an iterator, and
 * advances to the next.
 *
 * Inputs:
 * ks_iterator* iter - the iterator being operated on.
 *
 * Returns:
 * ks_datacont* - the current ks_datacont being pointed to by 'iter'.
 */
const ks_datacont* ks_iterator_next(ks_iterator* iter);


/* -------------------
 * ks_iterator_end():
 * Determines if ks_iterator has reached the end.
 * 
 * Inputs:
 * ks_iterator* iter - the iterator being operated on.
 *
 * Returns:
 * bool - (true) if 'iter' is at the end, (false) otherwise.
 */
bool ks_iterator_end(const ks_iterator* iter);

#endif
