#ifndef _TREEMAP_H_
#define _TREEMAP_H_


#include <ks_datacont.h>
#include <ks_treemapnode.h>
#include <ks_list.h>


typedef struct ks_treemap ks_treemap;


struct ks_treemap
{
  ks_treemapnode* root;
};


/* ------------------------------------
 * ks_treemap_new():
 * Creates a new empty ks_treemap.
 *
 * Inputs:
 * void 
 *
 * Returns:
 * ks_treemap* tm - an empty ks_treemap.
 */
ks_treemap* ks_treemap_new();


/* ----------------------------------
 * ks_treemap_delete():
 * Deletes a ks_treemap and all of its contents.
 *
 * Inputs:
 * ks_treemap* tm - the ks_treemap to be deleted
 *
 * Returns:
 * void
 */
void ks_treemap_delete(ks_treemap* tm);


/* ----------------------------------
 * ks_treemap_add():
 * Add a key/value pair to a ks_treemap.
 *
 * Inputs:
 * ks_treemap* tm - the ks_treemap to be added to
 * ks_datacont* key - the key
 * ks_datacont* value - the value that the key maps to
 *
 * Returns:
 * int result - (-1) if any params are NULL, or if 'key's ks_dataconttype is different from
 *              the other ks_dataconts in the tree.
 *            - (0) pair was added successfully.
 *            - (1) 'key' already present, replaced old 'value'.
 *
 * Notes:
 * If the key-value pair are successfully stored into the ks_treemap, the client code must NOT
 * modify or delete 'key' or 'value', otherwise undefined behavior could ensue. If the pair
 * was not added to the ks_treemap, the client code is responsible for deleting the 'key' and
 * 'value' ks_dataconts when they are no longer needed. If 'value' is replaced by a new value,
 * the 'key' ks_datacont was not stored into the ks_treemap, so it is the client code's responsibility
 * to delete 'key'.
 */
int ks_treemap_add(ks_treemap* tm, const ks_datacont* key, const ks_datacont* value);


/* ---------------------------
 * ks_treemap_remove():
 * Find key/value pair and delete it.
 *
 * Inputs:
 * ks_treemap* tm - the ks_treemap to be operated on
 * ks_datacont* key - the key to be removed
 *
 * Returns:
 * int result - (-1) if either param is NULL, or if 'key' could not be found.
 *            - (0) pair removed successfully.
 *
 * Notes:
 * 'key' is not consumed by this procedure. It is only used to locate another ks_datacont containing
 * the same data.
 */
int ks_treemap_remove(ks_treemap* tm, const ks_datacont* key);


/* ---------------------------
 * ks_treemap_get():
 * Retrieves a value mapped by 'key' from a ks_treemap.
 *
 * Inputs:
 * ks_treemap* tm - the ks_treemap to be operated on
 * ks_datacont* key - the key to use to retrieve a value
 *
 * Returns:
 * ks_datacont* value - (NULL) when the key could not be found.
 *                 - the value mapped to by 'key'.
 *
 * Notes:
 * The ks_datacont returned by this function is a pointer to the original contained within the ks_treemap,
 * so it should not be deleted or modified by client code.
 * See notes on ks_treemap_remove().
 */
ks_datacont* ks_treemap_get(const ks_treemap* tm, const ks_datacont* key);


/* --------------------------
 * ks_treemap_get_key():
 * Retrieves a key located at a specified index within a ks_treemapnode.
 *
 * Inputs:
 * ks_treemap* tm - the ks_treemap being operated on.
 * int index - the index of the key being retrieved. Negative values
 *             will wrap around.
 *
 * Returns:
 * ks_datacont* key - (NULL) if 'index' is OOB, or if 'tm' is NULL.
 *               - the key located at 'index'.
 *
 * Notes:
 * The ks_datacont returned by this function is a pointer to the original contained within the ks_treemap,
 * so it should not be deleted or modified by client code.
 */
ks_datacont* ks_treemap_get_key(const ks_treemap* tm, int index);


/* --------------------------
 * ks_treemap_keys():
 * Get a linked ks_list of all keys contained within a ks_treemap.
 *
 * Inputs:
 * ks_treemap* tm - the ks_treemap to be operated on 
 *
 * Returns:
 * ks_list* ls - (NULL) if 'tm' is NULL or empty.
 *          - a ks_list of keys contained in 'ls'.
 * 
 * Notes:
 * The ks_list returned by this procedure contains copies of the original
 * keys located inside of 'tm', and can be deleted or modified without
 * affecting the originals inside of 'tm'. 
 */
ks_list* ks_treemap_keys(const ks_treemap* tm);


/* --------------------------
 * ks_treemap_values():
 * Get a linked ks_list of all values contained within a ks_treemap.
 *
 * Inputs:
 * ks_treemap* tm - the ks_treemap to be operated on
 *
 * Returns:
 * ks_list* ls - (NULL) if 'tm' is NULL
 *          - a ks_list of the keys contained within 'tm'.
 *
 * Notes:
 * The ks_list returned by this procedure contains copies of the original
 * values located inside of 'tm', and can be deleted or modified without
 * affecting the originals inside of 'tm'. 
 */
ks_list* ks_treemap_values(const ks_treemap* tm);


/* ----------------------------
 * ks_treemap_count():
 * Count the number of key-value pairs stored within a ks_treemap.
 *
 * Inputs:
 * ks_treemap* tm - the ks_treemap to be operated on
 *
 * Returns:
 * unsigned int result - >= (0) the number of pairs found in the ks_treemap, (0) if 'tm' is NULL..
 */
unsigned int ks_treemap_count(const ks_treemap* tm);


/* --------------------------
 * ks_treemap_height():
 * Calculate the maximum height of a ks_treemap.
 *
 * Inputs:
 * ks_treemap* tm - the ks_treemap to be operated on.
 *
 * Returns:
 * unsigned int height - >= (0) the height of the tree (0) if 'tm' is NULL.
 */
unsigned int ks_treemap_height(const ks_treemap* tm);


/* --------------------------
 * ks_treemap_balance():
 * Balances a ks_treemap to ensure optimal performance.
 *
 * Inputs:
 * ks_treemap* tm - the ks_treemap being operated on.
 *
 * Returns:
 * void
 */
void ks_treemap_balance(ks_treemap* tm);


#endif
