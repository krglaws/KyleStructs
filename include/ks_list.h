#ifndef _KS_LIST_H_
#define _KS_LIST_H_


#include <ks_datacont.h>
#include <ks_listnode.h>


typedef struct ks_list ks_list;


struct ks_list
{
  ks_listnode* head;
};


/* -------------------
 * ks_list_new():
 * Creates a new empty ks_list*.
 *
 * Inputs:
 * void
 *
 * Returns:
 * ks_list* ls - a ks_list*
 */
ks_list* ks_list_new();


/* --------------------
 * ks_list_delete(ks_list* ln):
 * Deletes a ks_list and all of its contents.
 *
 * Inputs:
 * ks_list* ls - the ks_list* being deleted.
 *
 * Returns:
 * void
 */
void ks_list_delete(ks_list* ls);


/* --------------------
 * ks_list_add():
 * Append a ks_datacont* to a ks_list.
 *
 * Inputs:
 * ks_list* ls - the ks_list to be added to.
 * ks_datacont* dc - the ks_datacont being added to the ks_list.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - (0) on success.
 */
int ks_list_add(ks_list* ls, const ks_datacont* dc);


/* -----------------------
 * ks_list_remove_by():
 * Removes the first occurrence of a ks_datacont found within a ks_list.
 *
 * Inputs:
 * ks_list* ls - the ks_list being operated on.
 * ks_datacont* dc - the ks_datacont to be removed from the ks_list.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - (0) if the ks_datacont was not found.
 *            - (1) if the ks_datacont was successfully removed.
 */
int ks_list_remove_by(ks_list* ls, const ks_datacont* dc);


/* -----------------------------
 * ks_list_remove_at():
 * Removes a ks_datacont at a specified location within a ks_list.
 *
 * Inputs:
 * ks_list* ls - the ks_list being operated on.
 * int index - the index at which the removal will take place. Negative
 *             values will wrap around.
 *
 * Returns:
 * int result - (-1) when 'ls' is NULL, or when 'index' is OOB.
 *            - (0) on success.
 */
int ks_list_remove_at(ks_list* ls, int index);


/* ------------------------
 * ks_list_remove_all():
 * Removes all occurrences of a specified ks_datacont value within a ks_list.
 *
 * Inputs:
 * ks_list* ls - the ks_list being operated on.
 * ks_datacont* dc - the ks_datacont being removed from the ks_list.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - >= (0) the number of items removed from the ks_list.
 */
int ks_list_remove_all(ks_list* ls, const ks_datacont* dc);


/* -----------------------------
 * ks_list_replace_by():
 * Replaces the first occurrence of a specified ks_datacont value with a new ks_datacont value.
 *
 * Inputs:
 * ks_list* ls - the ks_list being operated on.
 * ks_datacont* old_dc - the original ks_datacont to be replaced.
 * ks_datacont* new_dc - the new ks_datacont replacing the original.
 *
 * Returns:
 * int result - (-1) when any param is NULL, or when 'old_dc' could not be found.
 *            - (0) on success.
 */
int ks_list_replace_by(ks_list* ls, const ks_datacont* old_dc, const ks_datacont* new_dc);


/* -----------------------------
 * ks_list_replace_at():
 * Replaces a ks_datacont at a specified location within a ks_list.
 *
 * Inputs:
 * ks_list* ls - the ks_list being operated on.
 * ks_datacont* dc - the new ks_datacont being added to the ks_list.
 * int index - the index at which the replacement will take place. Negative
 *             values will wrap around.
 *
 * Returns:
 * int result - (-1) when either 'ls' or 'dc' are NULL, or when 'index' is OOB.
 *            - (0) on success.
 */
int ks_list_replace_at(ks_list* ls, const ks_datacont* dc, int index);


/* ------------------------------
 * ks_list_replace_all():
 * Replaces all occurrences of a specified ks_datacont value with a new ks_datacont value.
 *
 * Inputs:
 * ks_list* ls - the ks_list being operated on.
 * ks_datacont* old_dc - the original ks_datacont to be replaced.
 * ks_datacont* new_dc - the new ks_datacont replacing the orignal.
 *
 * Returns:
 * int result - (-1) when any of the params is NULL.
 *            - >= (0) the number of replacements that occurred.
 */
int ks_list_replace_all(ks_list* ls, const ks_datacont* old_dc, const ks_datacont* new_dc);


/* -------------------------
 * ks_list_insert():
 * Inserts a ks_datacont* at a location specified within a ks_list.
 *
 * Inputs:
 * ks_list* ls - the ks_list being operated on.
 * ks_datacont* dc - the ks_datacont being inserted.
 * int index - the location to insert the ks_datacont. Negative values
 *             will wrap around.
 *
 * Returns:
 * int result - (-1) when either parameter is NULL, or when 'index' is OOB.
 *            - (0) on success.
 */
int ks_list_insert(ks_list* ls, const ks_datacont* dc, int index);


/* ---------------------------
 * ks_list_index():
 * Returns the index of the first ks_datacont that matches the ks_datacont 'dc' param located within a ks_list.
 *
 * Inputs:
 * ks_list* ls - the ks_list being searched through.
 * ks_datacont* dc - the ks_datacont to search for within the ks_list.
 *
 * Returns:
 * int index - (-1) if the ks_datacont could not be found, or either param is NULL.
 *           - >= (0) the index of the ks_datacont.
 *
 * Notes:
 * This function can also serve as a 'ks_list_contains' function. Example:
 * if (ks_list_index(ls, dc) >= 0) puts("Found it!");
 */
int ks_list_index(const ks_list* ls, const ks_datacont* dc);


/* -------------------------
 * ks_list_get():
 * Returns a pointer to a ks_datacont contained within a ks_list that is located at 'index'.
 *
 * Inputs:
 * ks_list* ls - the ks_list being operated on.
 * int index - the index used to locate the desired ks_datacont. Negative
 *             values will wrap around.
 *
 * Returns:
 * ks_datacont* dc - (NULL) if the 'index' is OOB, or if either param is NULL.
 *              - a copy of the ks_datacont located at 'index'.
 *
 * Notes:
 * The ks_datacont returned by this function is a pointer to the original contained within the ks_list, so it should not
 * be deleted or modified by client code.
 */
ks_datacont* ks_list_get(const ks_list* ls, int index);


/* ----------------------------
 * ks_list_count():
 * Returns the number of occurrences of a specified ks_datacont value within a ks_list.
 *
 * Inputs:
 * ks_list* ls - the ks_list being operated on.
 * ks_datacont* dc - the ks_datacont to look for within the ks_list.
 *
 * Returns:
 * unsigned int num - (-1) when either param is NULL.
 *                  - >= (0) the number of occurrences of the value contained in 'dc'.
 */
unsigned int ks_list_count(const ks_list* ls, const ks_datacont* dc);


/* ----------------------------
 * ks_list_length():
 * Returns the length of the ks_list.
 *
 * Inputs:
 * ks_list* ls - the ks_list be operated on.
 *
 * Returns:
 * unsigned int length - >= (0) the length of the ks_list. (0) when 'ls' is NULL.
 */
unsigned int ks_list_length(const ks_list* ls);


#endif
