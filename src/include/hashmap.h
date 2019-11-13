
#ifndef _HASHMAP_H_
#define _HASHMAP_H_


#include "treemap.h"
#include "list.h"


typedef struct hashmap hashmap;


struct hashmap
{
  enum dataconttype type;

  unsigned int num_buckets;
 
  treemap** buckets;
};


/* ------------------------------------
 * hashmap_new():
 * Returns a pointer to a new empty hashmap.
 *
 * inputs:
 * unsigned int num_buckets - the number of buckets this hashmap should contain.
 * enum dataconttype type - the datacont type this hashmap will store.
 *
 * returns:
 * hashmap* hm - a new empty hashmap.
 */
hashmap* hashmap_new(const enum dataconttype type, const unsigned int num_buckets);


/* ----------------------------------
 * hashmap_delete():
 * Deletes a hashmap and all structs that it contains.
 *
 * inputs:
 * hashmap* hm - the hashmap to be deleted.
 *
 * returns:
 * void
 */
void hashmap_delete(hashmap* hm);


/* ----------------------------------
 * hashmap_add():
 * Add a key/value pair to a hashmap.
 *
 * inputs:
 * hashmap* hm - the hashmap to be added to
 * datacont* key - the key
 * datacont* value - the value that the key maps to
 *
 * returns:
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
int hashmap_add(hashmap* hm, const datacont* key, const datacont* value);


/* ---------------------------
 * hashmap_remove():
 * Find key/value pare and delete it.
 *
 * inputs:
 * hashmap* hm - the hashmap to be operated on
 * datacont* key - the key to be removed
 *
 * returns:
 * int result - (0) pair removed successfully
 *            - (1) pair not removed (e.g. could not be found)
 */
int hashmap_remove(hashmap* hm, const datacont* key);


/* ---------------------------
 * hashmap_get():
 * Gets a value from a hashmap by key.
 * 
 * inputs:
 * hashmap* hm - the hashmap to be operated on
 * datacont* key - the key to use to retrieve a value
 *
 * returns:
 * datacont* value - (NULL) when the key could not be found.
 *                 - the value mapped to by the key
 */
datacont* hashmap_get(const hashmap* hm, const datacont* key);


/* --------------------------
 * hashmap_keys():
 * Get a list of all keys contained within a hashmap. 
 *
 * inputs:
 * hashmap* hm - the hashmap to be operated on
 *
 * returns:
 * list* - (NULL) if 'hm' is NULL, or if 'hm' is empty.
 *       - a list of the keys contained within 'hm'.
 *
 * Notes:
 * The dataconts in the returned list are copies of the originals in the hashmap, 
 * and can be deleted or otherwise modified.
 */
list* hashmap_keys(const hashmap* hm);


/* --------------------------
 * hashmap_getvals():
 * Get a linked list of all values contained within
 * a hashmap. These are copies of the originals
 * in the hashmap, and can be free()'d or
 * otherwise modified.
 *
 * inputs:
 * hashmap* hm - the hashmap to be operated on
 *
 * returns:
 * listnode* - a pointer to a list of datacont*'s
 * NULL - returned if map has no keys
 */
listnode* hashmap_values(const hashmap* hm);


/* ---------------------------------
 * hashmap_count():
 * Count the number of key/value pairs stored within
 * a hashmap.
 *
 * inputs:
 * hashmap* hm - the hashmap to be operated on
 *
 * returns:
 * unsigned int - the number of pairs found in the hashmap >=0.
 */
unsigned int hashmap_count(const hashmap* hm);


#endif
