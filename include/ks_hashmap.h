#ifndef _KS_HASHMAP_H_
#define _KS_HASHMAP_H_


/* ------------------------------------
 * ks_hashmap_new():
 * Creates a new empty ks_hashmap.
 *
 * Inputs:
 * unsigned int num_buckets - the number of buckets this ks_hashmap should contain.
 * enum ks_datatype type - the ks_datacont type this ks_hashmap will store.
 *
 * Returns:
 * ks_hashmap* hm - a new empty ks_hashmap.
 */
ks_hashmap* ks_hashmap_new(const enum ks_datatype type, const unsigned int num_buckets);


/* ----------------------------------
 * ks_hashmap_delete():
 * Deletes a ks_hashmap and all of its contents.
 *
 * Inputs:
 * ks_hashmap* hm - the ks_hashmap to be deleted.
 *
 * Returns:
 * void
 */
void ks_hashmap_delete(ks_hashmap* hm);


/* ----------------------------------
 * ks_hashmap_copy():
 * Creates a copy of a ks_hashmap and all its contents.
 *
 * Inputs:
 * ks_hashmap* hm - the ks_hashmap to be copied.
 *
 * Returns:
 * ks_hashmap* - a copy of 'hm'.
 */
ks_hashmap* ks_hashmap_copy(const ks_hashmap* hm);


/* ----------------------------------
 * ks_hashmap_add():
 * Add a key/value pair to a ks_hashmap.
 *
 * Inputs:
 * ks_hashmap* hm - the ks_hashmap to be added to
 * ks_datacont* key - the key
 * ks_datacont* value - the value that the key maps to
 *
 * Returns:
 * int result - (-1) if any param is NULL, or if 'key's type does not match 'hm's type.
 *            - (0) pair was added successfully.
 *            - (1) pair added successfully, old key replaced.
 *
 * Notes:
 * If this procedure returns -1, the key-value pair was not stored in 'hm', and
 * so it is the responsibility of the client code to delete 'key' and 'value' when
 * they are no longer needed. If 0 is returned, the client code should not delete or modify
 * 'key' or 'value', as this could cause behavioral issues with 'hm'. If 1 is returned,
 * 'key' was already present, and only 'value' has been placed into 'hm', while 'key'
 * will have to be deleted by the client code.
 */
int ks_hashmap_add(ks_hashmap* hm, const ks_datacont* key, const ks_datacont* value);


/* ---------------------------
 * ks_hashmap_remove():
 * Find key/value pare and delete it.
 *
 * Inputs:
 * ks_hashmap* hm - the ks_hashmap to be operated on
 * ks_datacont* key - the key to be removed
 *
 * Returns:
 * int result - (-1) if either param is NULL, or if 'key' could not be found. 
 *            - (0) pair removed successfully.
 *
 * Notes:
 * this procedure does not consume 'key'. It is the client code's responsibility
 * to delete 'key' when it is no longer needed.
 */
int ks_hashmap_remove(ks_hashmap* hm, const ks_datacont* key);


/* ---------------------------
 * ks_hashmap_get():
 * Gets a value from a ks_hashmap by key.
 * 
 * Inputs:
 * ks_hashmap* hm - the ks_hashmap to be operated on
 * ks_datacont* key - the key to use to retrieve a value
 *
 * Returns:
 * ks_datacont* value - (NULL) when the key could not be found.
 *                 - the value mapped to by the key.
 *
 * Notes:
 * The ks_datacont returned by this function is a pointer to the original contained within the ks_hashmap,
 * so it should not be deleted or modified by client code.
 * See notes on ks_hashmap_remove().
 */
ks_datacont* ks_hashmap_get(const ks_hashmap* hm, const ks_datacont* key);


/* --------------------------
 * ks_hashmap_keys():
 * Get a ks_list of all keys contained within a ks_hashmap. 
 *
 * Inputs:
 * ks_hashmap* hm - the ks_hashmap to be operated on
 *
 * Returns:
 * ks_list* ls - (NULL) if 'hm' is NULL, or if 'hm' is empty.
 *          - a ks_list of the keys contained within 'hm'.
 *
 * Notes:
 * The ks_dataconts in the returned ks_list are copies of the originals in the ks_hashmap, 
 * and can be deleted or otherwise modified.
 */
ks_list* ks_hashmap_keys(const ks_hashmap* hm);


/* --------------------------
 * ks_hashmap_values():
 * Get a linked ks_list of all values contained within
 * a ks_hashmap. These are copies of the originals
 * in the ks_hashmap, and can be free()'d or
 * otherwise modified.
 *
 * Inputs:
 * ks_hashmap* hm - the ks_hashmap to be operated on
 *
 * Returns:
 * ks_list* ls - (NULL) if 'hm' is NULL or empty.
 *          - a ks_list of the values contained in 'hm'.
 *
 * Notes:
 * See notes on ks_hashmap_keys().
 */
ks_list* ks_hashmap_values(const ks_hashmap* hm);


/* ---------------------------------
 * ks_hashmap_count():
 * Count the number of key/value pairs stored within
 * a ks_hashmap.
 *
 * Inputs:
 * ks_hashmap* hm - the ks_hashmap to be operated on
 *
 * Returns:
 * unsigned int count - >= (0) the number of pairs found in the ks_hashmap, (0) if 'hm' is NULL.
 */
unsigned int ks_hashmap_count(const ks_hashmap* hm);


/* ----------------------------
 * ks_hashmap_optimize():
 * Balances all of the ks_treemap buckets in a ks_hashmap to ensure O(log(N)) search time.
 *
 * Inputs:
 * ks_hashmap* hm - the ks_hashmap being optimized.
 *
 * Returns:
 * void
 */
void ks_hashmap_optimize(ks_hashmap* hm);


#endif
