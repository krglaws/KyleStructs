
#include <stdlib.h>


treemap* treemap_new()
{
  return calloc(1, sizeof(treemap));
}


void treemap_delete(treemap* tm)
{
  treemapnode_delete(tm->root);
  free(tm);
}


int treemap_add(treemap* tm, const datacont* key, const datacont* value)
{
  if (tm == NULL || key == NULL || value == NULL) return -1;
  if (tm->root == NULL)
  {
    tm->root = treemapnode_new(key, value);
    return 0;
  }
  else return treemapnode_add(tm->root, key, value);
}


/* ---------------------------
 * treemap_remove():
 * Find key/value pare and delete it.
 *
 * inputs:
 * treemap* tm - the treemap to be operated on
 * datacont* key - the key to be removed
 *
 * returns:
 * 0 - pair removed successfully
 * 1 - pair not removed (e.g. could not be found)
 */
int treemap_remove(treemap* tm, const datacont* key);


/* ---------------------------
 * treemap_get():
 * Get the value from a treemap by key. The returned
 * value is a copy of the datacont contained
 * within the treemap, and can be free()'d or
 * otherwise modified.
 *
 * inputs:
 * treemap* tm - the treemap to be operated on
 * datacont* key - the key to use to retrieve a value
 *
 * returns:
 * datacont* value - the value mapped to by the key
 * NULL - returned when the key could not be found
 */
datacont* treemap_get(const treemap* tm, const datacont* key);


/* --------------------------
 * treemap_getkeys():
 * Get a linked list of all keys contained within
 * a treemap. These are copies of the originals
 * in the treemap, and can be free()'d or 
 * otherwise modified.
 *
 * inputs:
 * treemap* tm - the treemap to be operated on
 *
 * returns:
 * listnode* - a pointer to a list of datacont*'s
 * NULL - returned if map has no keys
 */
listnode* treemap_getkeys(const treemap* tm);


/* --------------------------
 * treemap_getvals():
 * Get a linked list of all values contained within
 * a treemap. These are copies of the originals
 * in the treemap, and can be free()'d or
 * otherwise modified.
 *
 * inputs:
 * treemap* tm - the treemap to be operated on
 *
 * returns:
 * listnode* - a pointer to a list of datacont*'s
 * NULL - returned if map has no keys
 */
listnode* treemap_getvalues(const treemap* tm);


/* ----------------------------
 * treemap_count():
 * Count the number of key/value pairs stored
 * within a treemap.
 *
 * inputs:
 * treemap* tm - the treemap to be operated on
 *
 * returns:
 * unsigned int - the number of pairs found in 
 * the treemap >=0.
 */
unsigned int treemap_count(const treemap* tm);


/* --------------------------
 * treemap_height():
 * Calculate the maximum height of a treemap.
 *
 * inputs:
 * treemap* tm - the treemap to be operated on
 *
 * returns:
 * unsigned int - the height of the tree >=0.
 */
unsigned int treemap_height(const treemap* tm);

#endif

