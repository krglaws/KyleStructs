#ifndef _KS_DATACONT_H_
#define _KS_DATACONT_H_

#include <stddef.h>
#include <stdint.h>

#include "ks_types.h"


/* ---------------------------
 * ks_datacont_new():
 * Creates a new ks_datacont* containing the data pointed to by 'data'.
 *
 * Inputs:
 * void* data - THE data being stored within the ks_datacont.
 * enum ks_datatype dct - the type of the data being stored. See the enum defined
 *                         above to review supported types.
 * size_t count - the number of bytes that 'data' points to.
 * 
 * Returns:
 * ks_datacont* dc - (NULL) if 'data' is NULL or 'count'== 0.
 *                 - a ks_datacont* containing the data specified.
 *
 * Notes:
 * The data pointed to by 'data' is copied into the new ks_datacont structure. This gives
 * the user code the ability to allocate data onto the stack, create a ks_datacont for it,
 * and return it.
 *
 * When the new ks_datacont is to be of type CHARP, a null terminating character '\0' is
 * appended to the end of the string so that calls like strlen(dc->cp) won't cause a seg fault.
 * 
 * The types KS_VOIDP, KS_LIST, KS_TREESET, KS_HASHSET,
 * KS_TREEMAP, and KS_HASHMAP will always be treated as
 * single items (i.e. they should only point to one object
 * in memory). Consequently, the 'size' member of the ks_datacont
 * struct is not used in these cases, although it may be used
 * by user code for its own purposes.
 */
ks_datacont* ks_datacont_new(const void* data, enum ks_datatype type, size_t size);


/* ---------------------------
 * ks_datacont_delete():
 * Deletes a ks_datacont struct along with any data it contains.
 *
 * Inputs:
 * ks_datacont* dc - the ks_datacont being deleted.
 *
 * Returns:
 * void
 * 
 * Notes:
 * ks_datacont_delete() will not call free() on the pointer in KS_VOIDP type
 * as it does on the other pointer types. The user code is expected to handle
 * whatever memory management is necessary in that case.
 */
void ks_datacont_delete(ks_datacont* dc);


/* ---------------------------
 * ks_datacont_copy():
 * Creates an identical copy of a ks_datacont* struct, including all of the data
 * that the original contains.
 *
 * Inputs:
 * ks_datacont* dc - the ks_datacont being copied.
 *
 * Returns:
 * ks_datacont* copy - (NULL) if 'dc' is NULL.
 *                   - a copy of 'dc'.
 *
 * Notes:
 * ks_datacont_copy() will always do deep copies (i.e. it will make a copy of
 * the ks_datacont struct itself, as well as any data it points to),
 * except on KS_VOIDP types.
 */
ks_datacont* ks_datacont_copy(const ks_datacont* dc);


/* ---------------------------
 * ks_datacont_compare():
 * Compares two ks_datacont structs and returns an enum type that specifies the
 * result of the comparison.
 *
 * Inputs:
 * ks_datacont* dca - one of the ks_datacont structs being compared.
 * ks_datacont* dcb - the other ks_datacont being compared.
 *
 * Returns:
 * enum ks_comparison result - see the enum ks_comparison definition at the top of this
 *                            header for details. 
 * 
 * Notes:
 * When used on any pointer type, ks_datacont_compare() will only compare the values
 * of the pointers themselves.
 */
enum ks_comparison ks_datacont_compare(const ks_datacont* dca, const ks_datacont* dcb);


/* ---------------------------
 * ks_datacont_hash():
 * Hashes the data contained within a ks_datacont and returns the result as an unsigned
 * 32-bit integer.
 * 
 * Inputs:
 * ks_datacont* dc - the ks_datacont being hashed.
 *
 * Returns:
 * uint32_t hash - the hash of the data contained in the ks_datacont.
 * 
 * Notes:
 * When used on any pointer type, ks_datacont_hash() will only hash the value of the
 * pointer itself.
 */
uint32_t ks_datacont_hash(const ks_datacont* dc);


#endif
