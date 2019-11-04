
#ifndef _LIST_H_
#define _LIST_H_


typedef struct list list;


struct list
{
  int length;
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
 * list* ln - a list*
 */
list* list_new();


/* --------------------
 * list_delete(list* ln):
 * Deletes a list and all of its contents.
 *
 * Inputs:
 * list* ln - the list* being deleted.
 *
 * Returns:
 * void
 *
 * Notes:
 * This function will not touch the other nodes that 'ln' might be connected to. It is
 * assumed that the user code has or will disconnect any connected nodes.
 */
void list_delete(list* ln);


/* -------------------
 * list_delete_all():
 * Deletes a list and all other connected nodes.
 *
 * Inputs:
 * list* ln - the list to be deleted.
 *
 * Returns:
 * void
 *
 * Notes:
 * This function will delete 'ln' and all nodes connected to it. If only part of a
 * list is to be deleted, it will have to be manually isolated, with it's 'next'
 * member set to NULL.
 */
void list_delete_all(list* ln);


/* --------------------
 * list_add():
 * Append a datacont* to a list chain.
 *
 * Inputs:
 * list* ln - the list to be added to.
 * datacont* dc - the datacont being added to the list.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - (0) on success.
 */
int list_add(list* ln, const datacont* dc);


/* -----------------------
 * list_remove_by():
 * Removes the first occurrence of a datacont found within a chain of lists.
 *
 * Inputs:
 * list** ln - the list being operated on.
 * datacont* dc - the datacont to be removed from the list.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - (0) if the datacont was not found.
 *            - (1) if the datacont was successfully removed.
 *
 * Notes:
 * This function may delete the list reference passed to 'ln' if it is the node that contains the
 * 'dc' value being deleted. Because of this, a nested pointer must be passed into 'ln' so that
 * it can be set either to the next node in the list, or NULL if there are no remaining nodes. Also,
 * the datacont being passed into this function is assumed to be deleted by the user code. The 'dc'
 * parameter will not be modified in any way by this function.
 */
int list_remove_by(list** ln, const datacont* dc);


/* -----------------------------
 * list_remove_at():
 * Removes a datacont at a specified location within a list chain.
 *
 * Inputs:
 * list** ln - the list being operated on.
 * int index - the index at which the removal will take place. Negative
 *             values will wrap around.
 *
 * Returns:
 * int result - (-1) when 'ln' is NULL, or when 'index' is OOB.
 *            - (0) on success.
 *
 * Notes:
 * See list_remove_by() notes, as they apply to this function as well.
 */
int list_remove_at(list** ln, int index);


/* ------------------------
 * list_remove_all():
 * Removes all occurrences of a specified datacont value within a chain of lists.
 *
 * Inputs:
 * list** ln - the list being operated on.
 * datacont* dc - the datacont being removed from the list.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - >= (0) the number of nodes removed from the list chain.
 *
 * Notes:
 * See list_remove_by() notes, as they apply to this function as well.
 */
int list_remove_all(list** ln, const datacont* dc);


/* -----------------------------
 * list_replace_by():
 * Replaces the first occurrence of a specified datacont value with a new datacont value.
 *
 * Inputs:
 * list* ln - the list being operated on.
 * datacont* old_dc - the original datacont to be replaced.
 * datacont* new_dc - the new datacont replacing the original.
 *
 * Returns:
 * int result - (-1) when any param is NULL, or when 'old_dc' could not be found.
 *            - (0) on success.
 *
 * Notes:
 * The datacont replacement 'new_dc' should not be deleted by the user code
 * UNLESS the replacement fails. It will be stored directly into the list. 
 * The 'old_dc' parameter WILL always need to be deleted by the user code.
 */
int list_replace_by(list* ln, const datacont* old_dc, const datacont* new_dc);


/* -----------------------------
 * list_replace_at():
 * Replaces a datacont at a specified location within a list chain.
 *
 * Inputs:
 * list* ln - the list being operated on.
 * datacont* dc - the new datacont being added to the list chain.
 * int index - the index at which the replacement will take place. Negative
 *             values will wrap around.
 *
 * Returns:
 * int result - (-1) when either 'ln' or 'dc' are NULL, or when 'index' is OOB.
 *            - (0) on success.
 *
 * Notes:
 * The datacont replacement 'dc' should not be deleted by the user code. It will
 * be stored directly into the list.
 */
int list_replace_at(list* ln, const datacont* dc, int index);


/* ------------------------------
 * list_replace_all():
 * Replaces all occurrences of a specified datacont value with a new datacont value.
 *
 * Inputs:
 * list* ln - the list being operated on.
 * datacont* old_dc - the original datacont to be replaced.
 * datacont* new_dc - the new datacont replacing the orignal.
 *
 * Returns:
 * int result - -1 when any of the params is NULL
 *            - >= (0) the number of replacements that occurred.
 *
 * Notes:
 * See notes on list_replace_by(). The same applies here.
 */
int list_replace_all(list* ln, const datacont* old_dc, const datacont* new_dc);


/* -------------------------
 * list_insert():
 * Inserts a datacont* at a location specified in a chain of lists.
 *
 * Inputs:
 * list** ln - the list being operated on.
 * datacont* dc - the datacont being inserted.
 * int index - the location to insert the datacont. Negative values
 *             will wrap around.
 *
 * Returns:
 * int result - (-1) when either parameter is NULL, or when 'index' is OOB.
 *            - (0) on success.
 *
 * Notes:
 * In the event that a datacont is being inserted at the beginning of a list chain,
 * the reference to 'ln' will have to changed to the new 0th list, which is why
 * 'ln' must be passed in as a nested pointer.
 */
int list_insert(list** ln, const datacont* dc, int index);


/* ---------------------------
 * list_index():
 * Returns the index of the first datacont that matches the datacont 'dc' param located within a group of connected lists.
 *
 * Inputs:
 * list* ln - the list being searched through.
 * datacont* dc - the datacont to search for within the connected lists.
 *
 * Returns:
 * int index - (-1) if the datacont could not be found, or either param is NULL.
 *           - >= (0) the index of the datacont.
 *
 * Notes:
 * This function can also serve as a 'list_contains' function. Example:
 * if (list_index(ln, dc) >= 0) puts("Found it!");
 */
int list_index(const list* ln, const datacont* dc);


/* -------------------------
 * list_get():
 * Returns a copy of the datacnt contained within a list that is a specified number of nodes down the chain from 'ln'.
 *
 * Inputs:
 * list* ln - the list being operated on.
 * int index - the index used to locate the desired datacont. Negative
 *             values will wrap around.
 *
 * Returns:
 * datacont* dc - (NULL) if the 'index' is OOB, or if either param is NULL.
 *              - a copy of the datacont located at 'index'.
 *
 * Notes:
 * The datacont returned by this function is a COPY of the original from the list. It is the responsibility
 * of the user code to use datacont_delete() on it to avoid memory leaks.
 */
datacont* list_get(const list* ln, int index);


/* ----------------------------
 * list_count():
 * Returns the number of occurrences of a specified datacont value within a list chain.
 *
 * Inputs:
 * list* ln - the list being operated on.
 * datacont* dc - the datacont to look for within the list.
 *
 * Returns:
 * unsigned int num - (-1) when either param is NULL.
 *                  - >= (0) the number of lists that contain the same value as 'dc'.
 */
unsigned int list_count(const list* ln, const datacont* dc);


/* ----------------------------
 * list_length():
 * Returns the length of the list.
 *
 * Inputs:
 * list* ln - the list be operated on.
 *
 * Returns:
 * unsigned int length - >= (0) the length of the list. (0) when 'ln' is NULL.
 */
unsigned int list_length(const list* ln);


#endif

#endif

