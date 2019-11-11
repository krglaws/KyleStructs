
#ifndef _HASHMAP_H_
#define _HASHMAP_H_


#include "datacont.h"
#include "treemap.h"
#include "listnode.h"


typedef struct hashmap hashmap;


struct hashmap
{
  unsigned int num_buckets;
  unsigned long long seed;
  treemap** buckets;
};


/* ------------------------------------
 * hashmap_new():
 * Returns a pointer to a new empty hashmap.
 *
 * inputs:
 * const unsigned int num_buckets - the number of buckets 
 * this hashmap should contain
 * const unsigned long long seed - the seed to be used when
 * hashing each new item
 *
 * returns:
 * hashmap*
 */
hashmap* hashmap_new(const unsigned int num_buckets, const unsigned long long seed);


/* ----------------------------------
 * hashmap_delete():
 * Deletes a hashmap and all structs that it contains.
 *
 * inputs:
 * hashmap* hm - the hashmap to be deleted
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
 * -1 - failed to add pair
 *  0 - pair added successfully
 *  1 - pair added successfully, old key replaced
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
 * 0 - pair removed successfully
 * 1 - pair not removed (e.g. could not be found)
 */
int hashmap_remove(hashmap* hm, const datacont* key);


/* ---------------------------
 * hashmap_get():
 * Get the value from a hashmap by key. The returned
 * value is a copy of the datacont contained
 * within the hashmap, and can be free()'d or
 * otherwise modified.
 *
 * inputs:
 * hashmap* hm - the hashmap to be operated on
 * datacont* key - the key to use to retrieve a value
 *
 * returns:
 * datacont* value - the value mapped to by the key
 * NULL - returned when the key could not be found
 */
datacont* hashmap_get(const hashmap* hm, const datacont* key);


/* --------------------------
 * hashmap_getkeys():
 * Get a linked list of all keys contained within
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
listnode* hashmap_getkeys(const hashmap* hm);


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
listnode* hashmap_getvalues(const hashmap* hm);


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
