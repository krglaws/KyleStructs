#ifndef _HASHSET_H_
#define _HASHSET_H_


#include "treeset.h"
#include "list.h"


/* -----------------------
 * notes: 
 *
 * hashsets, unlike its inherited types treeset and treesetnode, are required to have the type defined
 * within the struct itself. This is to prevent two dataconts of non-comparable types to be added into 
 * two separate buckets without error. treesets and treesetnodes on the other hand have their types
 * determined by the first datacont that is passed into them.
 *
 * Since hashsets are not iterable the way a treeset is, hashset_to_list() provides a means for iterating
 * over the contents of a hashset.
 */
typedef struct hashset hashset;


struct hashset
{
  enum dataconttype type;

  unsigned int num_buckets;

  treeset** buckets;
};


/* ----------------------------------
 * hashset_new():
 * Creates a new empty hashset.
 *
 * Inputs:
 * unsigned int buckets - the number of buckets that the new hashset should contain.
 *
 * Returns:
 * hashset* hs - a new empty hashset.
 */
hashset* hashset_new(const enum dataconttype type, const unsigned int num_buckets);


/* ---------------------------------
 * hashset_delete():
 * Deletes a hashset and all of its contents.
 *
 * Inputs:
 * hashset* hs - the hashset being deleted.
 *
 * Returns:
 * void
 */
void hashset_delete(hashset* hs);


/* --------------------------------
 * hashset_add():
 * Adds a datacont to a hashaset.
 *
 * Inputs:
 * hashset* hs - the hashset being added to.
 * datacont* dc - the datacont being added to 'hs'.
 *
 * Returns:
 * int result - (-1) if either param is NULL, or if the dataconttype of 'dc' does not
 *              match the other dataconts within the hashset.
 *            - (0) 'dc' was successfully added to the hashset. 
 *            - (1) 'dc' is already stored in the hashset.
 *
 * Notes:
 * If 'dc' is successfully stored into the set, 'dc' should not be deleted by the user code,
 * as it will be directly stored into the tree. Otherwise a seg fault is likely to occur.
 * In the event that a value matching 'dc' is already present, or if 'hs' is NULL, 'dc' will
 * not be stored into the set, and 'dc' must be deleted by the user code.
 */
int hashset_add(hashset* hs, const datacont* dc);


/* -------------------------
 * hashset_remove():
 * Remove a datacont from a hashset.
 *
 * Inputs:
 * hashset* hs - the hashset being removed from.
 * datacont* dc - the datacont to be removed from 'hs'.
 *
 * Returns:
 * int result - (-1) if either param is NULL, or if 'dc' could not be found.
 *            - (0) on success.
 */
int hashset_remove(hashset* hs, const datacont* dc);


/* ------------------------
 * hashset_contains():
 * Searches for a specified datacont value within a hashset.
 *
 * Inputs:
 * hashset* hs - the hashset being searched.
 * datacont* dc - the datacont being searched for.
 *
 * Returns:
 * unsigned int result - (0) if 'dc' could not be found, or if either param is NULL.
 *                     - (1) 'hs' contains 'dc'.
 */
unsigned int hashset_contains(const hashset* hs, const datacont* dc);


/* ------------------------
 * hashset_count():
 * Counts the number of dataconts contained within a hashset.
 *
 * Inputs:
 * hashset* hs - the hashset being operated on.
 *
 * Returns:
 * unsigned int count - >= (0) the number of dataconts within 'hs', (0) when 'hs' is NULL.
 */
unsigned int hashset_count(const hashset* hs);


/* ------------------------
 * hashset_to_list():
 * Returns a list of all dataconts within a hashset.
 *
 * Inputs:
 * hashset* hs - the hashset being operated on.
 *
 * Returns:
 * list* ls - (NULL) if 'hs' is NULL.
 *          - a list containing zero or more dataconts.
 *
 * Notes:
 * The dataconts contained within 'ls' are copies of those in 'hs', and can
 * be safely deleted by the user code without affecting the dataconts within
 * 'hs'.
 */
list* hashset_to_list(const hashset* hs);


/* --------------------
 * hashset_optimize():
 * Balances all of the treeset buckets in a hashset to ensure O(log(N)) search
 * time.
 *
 * Inputs:
 * hashset* hs - the hashset being operated on.
 *
 * Returns:
 * void
 */
void hashset_optimize(hashset* hs);


#endif
