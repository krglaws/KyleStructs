#ifndef _LIST_H_
#define _LIST_H_


#include "listnode.h"


typedef struct list list;


struct list
{
  listnode* head;
};


/* -------------------
 * list_new():
 * Creates a new empty list*.
 *
 * Inputs:
 * void
 *
 * Returns:
 * list* ls - a list*
 */
list* list_new();


/* --------------------
 * list_delete(list* ln):
 * Deletes a list and all of its contents.
 *
 * Inputs:
 * list* ls - the list* being deleted.
 *
 * Returns:
 * void
 */
void list_delete(list* ls);


/* --------------------
 * list_add():
 * Append a datacont* to a list.
 *
 * Inputs:
 * list* ls - the list to be added to.
 * datacont* dc - the datacont being added to the list.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - (0) on success.
 */
int list_add(list* ls, const datacont* dc);


/* -----------------------
 * list_remove_by():
 * Removes the first occurrence of a datacont found within a list.
 *
 * Inputs:
 * list* ls - the list being operated on.
 * datacont* dc - the datacont to be removed from the list.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - (0) if the datacont was not found.
 *            - (1) if the datacont was successfully removed.
 */
int list_remove_by(list* ls, const datacont* dc);


/* -----------------------------
 * list_remove_at():
 * Removes a datacont at a specified location within a list.
 *
 * Inputs:
 * list* ls - the list being operated on.
 * int index - the index at which the removal will take place. Negative
 *             values will wrap around.
 *
 * Returns:
 * int result - (-1) when 'ls' is NULL, or when 'index' is OOB.
 *            - (0) on success.
 */
int list_remove_at(list* ls, int index);


/* ------------------------
 * list_remove_all():
 * Removes all occurrences of a specified datacont value within a list.
 *
 * Inputs:
 * list* ls - the list being operated on.
 * datacont* dc - the datacont being removed from the list.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - >= (0) the number of items removed from the list.
 */
int list_remove_all(list* ls, const datacont* dc);


/* -----------------------------
 * list_replace_by():
 * Replaces the first occurrence of a specified datacont value with a new datacont value.
 *
 * Inputs:
 * list* ls - the list being operated on.
 * datacont* old_dc - the original datacont to be replaced.
 * datacont* new_dc - the new datacont replacing the original.
 *
 * Returns:
 * int result - (-1) when any param is NULL, or when 'old_dc' could not be found.
 *            - (0) on success.
 */
int list_replace_by(list* ls, const datacont* old_dc, const datacont* new_dc);


/* -----------------------------
 * list_replace_at():
 * Replaces a datacont at a specified location within a list.
 *
 * Inputs:
 * list* ls - the list being operated on.
 * datacont* dc - the new datacont being added to the list.
 * int index - the index at which the replacement will take place. Negative
 *             values will wrap around.
 *
 * Returns:
 * int result - (-1) when either 'ls' or 'dc' are NULL, or when 'index' is OOB.
 *            - (0) on success.
 */
int list_replace_at(list* ls, const datacont* dc, int index);


/* ------------------------------
 * list_replace_all():
 * Replaces all occurrences of a specified datacont value with a new datacont value.
 *
 * Inputs:
 * list* ls - the list being operated on.
 * datacont* old_dc - the original datacont to be replaced.
 * datacont* new_dc - the new datacont replacing the orignal.
 *
 * Returns:
 * int result - (-1) when any of the params is NULL.
 *            - >= (0) the number of replacements that occurred.
 */
int list_replace_all(list* ls, const datacont* old_dc, const datacont* new_dc);


/* -------------------------
 * list_insert():
 * Inserts a datacont* at a location specified within a list.
 *
 * Inputs:
 * list* ls - the list being operated on.
 * datacont* dc - the datacont being inserted.
 * int index - the location to insert the datacont. Negative values
 *             will wrap around.
 *
 * Returns:
 * int result - (-1) when either parameter is NULL, or when 'index' is OOB.
 *            - (0) on success.
 */
int list_insert(list* ls, const datacont* dc, int index);


/* ---------------------------
 * list_index():
 * Returns the index of the first datacont that matches the datacont 'dc' param located within a list.
 *
 * Inputs:
 * list* ls - the list being searched through.
 * datacont* dc - the datacont to search for within the list.
 *
 * Returns:
 * int index - (-1) if the datacont could not be found, or either param is NULL.
 *           - >= (0) the index of the datacont.
 *
 * Notes:
 * This function can also serve as a 'list_contains' function. Example:
 * if (list_index(ls, dc) >= 0) puts("Found it!");
 */
int list_index(const list* ls, const datacont* dc);


/* -------------------------
 * list_get():
 * Returns a pointer to a datacont contained within a list that is located at 'index'.
 *
 * Inputs:
 * list* ls - the list being operated on.
 * int index - the index used to locate the desired datacont. Negative
 *             values will wrap around.
 *
 * Returns:
 * datacont* dc - (NULL) if the 'index' is OOB, or if either param is NULL.
 *              - a copy of the datacont located at 'index'.
 *
 * Notes:
 * The datacont returned by this function is a pointer to the original contained within the list, so it should not
 * be deleted or modified by client code.
 */
datacont* list_get(const list* ls, int index);


/* ----------------------------
 * list_count():
 * Returns the number of occurrences of a specified datacont value within a list.
 *
 * Inputs:
 * list* ls - the list being operated on.
 * datacont* dc - the datacont to look for within the list.
 *
 * Returns:
 * unsigned int num - (-1) when either param is NULL.
 *                  - >= (0) the number of occurrences of the value contained in 'dc'.
 */
unsigned int list_count(const list* ls, const datacont* dc);


/* ----------------------------
 * list_length():
 * Returns the length of the list.
 *
 * Inputs:
 * list* ls - the list be operated on.
 *
 * Returns:
 * unsigned int length - >= (0) the length of the list. (0) when 'ls' is NULL.
 */
unsigned int list_length(const list* ls);


#endif
