#ifndef _TREEMAP_H_
#define _TREEMAP_H_


#include "treemapnode.h"
#include "list.h"


typedef struct treemap treemap;


struct treemap
{
  treemapnode* root;
};


/* ------------------------------------
 * treemap_new():
 * Creates a new empty treemap.
 *
 * Inputs:
 * void 
 *
 * Returns:
 * treemap* tm - an empty treemap.
 */
treemap* treemap_new();


/* ----------------------------------
 * treemap_delete():
 * Deletes a treemap and all of its contents.
 *
 * Inputs:
 * treemap* tm - the treemap to be deleted
 *
 * Returns:
 * void
 */
void treemap_delete(treemap* tm);


/* ----------------------------------
 * treemap_add():
 * Add a key/value pair to a treemap.
 *
 * Inputs:
 * treemap* tm - the treemap to be added to
 * datacont* key - the key
 * datacont* value - the value that the key maps to
 *
 * Returns:
 * int result - (-1) if any params are NULL, or if 'key's dataconttype is different from
 *              the other dataconts in the tree.
 *            - (0) pair was added successfully.
 *            - (1) 'key' already present, replaced old 'value'.
 *
 * Notes:
 * If the key-value pair are successfully stored into the treemap, the client code must NOT
 * modify or delete 'key' or 'value', otherwise undefined behavior could ensue. If the pair
 * was not added to the treemap, the client code is responsible for deleting the 'key' and
 * 'value' dataconts when they are no longer needed. If 'value' is replaced by a new value,
 * the 'key' datacont was not stored into the treemap, so it is the client code's responsibility
 * to delete 'key'.
 */
int treemap_add(treemap* tm, const datacont* key, const datacont* value);


/* ---------------------------
 * treemap_remove():
 * Find key/value pair and delete it.
 *
 * Inputs:
 * treemap* tm - the treemap to be operated on
 * datacont* key - the key to be removed
 *
 * Returns:
 * int result - (-1) if either param is NULL, or if 'key' could not be found.
 *            - (0) pair removed successfully.
 *
 * Notes:
 * 'key' is not consumed by this procedure. It is only used to locate another datacont containing
 * the same data.
 */
int treemap_remove(treemap* tm, const datacont* key);


/* ---------------------------
 * treemap_get():
 * Retrieves a value mapped by 'key' from a treemap.
 *
 * Inputs:
 * treemap* tm - the treemap to be operated on
 * datacont* key - the key to use to retrieve a value
 *
 * Returns:
 * datacont* value - (NULL) when the key could not be found.
 *                 - the value mapped to by 'key'.
 *
 * Notes:
 * The datacont returned by this function is a pointer to the original contained within the treemap,
 * so it should not be deleted or modified by client code.
 * See notes on treemap_remove().
 */
datacont* treemap_get(const treemap* tm, const datacont* key);


/* --------------------------
 * treemap_get_key():
 * Retrieves a key located at a specified index within a treemapnode.
 *
 * Inputs:
 * treemap* tm - the treemap being operated on.
 * int index - the index of the key being retrieved. Negative values
 *             will wrap around.
 *
 * Returns:
 * datacont* key - (NULL) if 'index' is OOB, or if 'tm' is NULL.
 *               - the key located at 'index'.
 *
 * Notes:
 * The datacont returned by this function is a pointer to the original contained within the treemap,
 * so it should not be deleted or modified by client code.
 */
datacont* treemap_get_key(const treemap* tm, int index);


/* --------------------------
 * treemap_keys():
 * Get a linked list of all keys contained within a treemap.
 *
 * Inputs:
 * treemap* tm - the treemap to be operated on 
 *
 * Returns:
 * list* ls - (NULL) if 'tm' is NULL or empty.
 *          - a list of keys contained in 'ls'.
 * 
 * Notes:
 * The list returned by this procedure contains copies of the original
 * keys located inside of 'tm', and can be deleted or modified without
 * affecting the originals inside of 'tm'. 
 */
list* treemap_keys(const treemap* tm);


/* --------------------------
 * treemap_values():
 * Get a linked list of all values contained within a treemap.
 *
 * Inputs:
 * treemap* tm - the treemap to be operated on
 *
 * Returns:
 * list* ls - (NULL) if 'tm' is NULL
 *          - a list of the keys contained within 'tm'.
 *
 * Notes:
 * The list returned by this procedure contains copies of the original
 * values located inside of 'tm', and can be deleted or modified without
 * affecting the originals inside of 'tm'. 
 */
list* treemap_values(const treemap* tm);


/* ----------------------------
 * treemap_count():
 * Count the number of key-value pairs stored within a treemap.
 *
 * Inputs:
 * treemap* tm - the treemap to be operated on
 *
 * Returns:
 * unsigned int result - >= (0) the number of pairs found in the treemap, (0) if 'tm' is NULL..
 */
unsigned int treemap_count(const treemap* tm);


/* --------------------------
 * treemap_height():
 * Calculate the maximum height of a treemap.
 *
 * Inputs:
 * treemap* tm - the treemap to be operated on.
 *
 * Returns:
 * unsigned int height - >= (0) the height of the tree (0) if 'tm' is NULL.
 */
unsigned int treemap_height(const treemap* tm);


/* --------------------------
 * treemap_balance():
 * Balances a treemap to ensure optimal performance.
 *
 * Inputs:
 * treemap* tm - the treemap being operated on.
 *
 * Returns:
 * void
 */
void treemap_balance(treemap* tm);


#endif
