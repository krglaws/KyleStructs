
#ifndef _LIST_H_
#define _LIST_H_


typedef struct list list;


struct list
{
  listnode* head;
};


/* ---------------------
 * list_new():
 * Makes a new empty list.
 *
 * Inputs:
 * none
 *
 * Returns:
 * list* l - an empty list.
 */
list* list_new();


/* ---------------------
 * list_delete():
 * Deletes a list and all of its contents.
 * 
 * Inputs:
 * list* l - the list being deleted.
 * 
 * Returns:
 * void
 */
void list_delete(list* l);


/* ---------------------
 * list_insert():
 * Inserts a datacont* at the index specified by 'index'.
 *
 * Inputs:
 * list* l - the list being operated on.
 * datacont* dc - the datacont* being inserted.
 * int index - the index at which the datacont will be placed. 
 * 
 * Returns:
 * int result - (-1) when 'dc' is NULL, 'l' is NULL, or when 'index' is OOB.
 *            - (0) on success.
 *
 * Notes:
 * When the 'index' value negative, it is placed by iterating over the list in reverse 
 * order. For example:
 * 
 * list_insert(myList, myDc, -1) - appends the datacont to the very end of the list.
 * list_insert(myList, myDC, -2) - places the datacont one index before the last
 * datacont in the list.
 * 
 * In cases where the list is empty, a datacont* can only be inserted at index '0' or '-1', 
 * otherwise nothing is changed, and (-1) is returned.
 */
int list_insert(list* l, const datacont* dc);


/* ------------------
 * list_remove():
 * Removes a datacont* matching the datacont* dc parameter.
 *
 * Inputs:
 * list* l - the list being operated on.
 * datacont* dc - the datacont* to be removed from the list.
 * 
 * Returns:
 * int result - (-1) if the 'dc' param could not be found in the list.
 *            - (0) on success
 * 
 */
int list_remove(list* l, const datacont* dc);


/* -----------------
 * list_index():
 * Retrieves a copy of the datacont* contained at the location specified by 'index'.
 *
 * Inputs:
 * list* l - the list being operated on.
 * int index - the index of the desired datacont*.
 * 
 * Returns:
 * datacont* dc - (NULL) if the index is OOB.
 *
 * Notes:
 * The datacont* value that is returned by this function is not a reference to the
 * same datacont* located at 'index', but an identical copy. This is to prevent undefined
 * behavior should the user code delete or otherwise modify the returned value. This way,
 * all modifications to the list and its contents are explicitly performed through this
 * library.
 */
datacont* list_index(const list* l, const int i);


/* -------------------
 * list_contains():
 * Function to determine whether or not a datacont* of a certain value is contained within a list.
 * 
 * Inputs:
 * list* l - the list being operated on.
 * datacont* dc - the datacont* to search for within the list.
 *
 * outputs:
 * int result - (0) if the list does not contain the datacont*, or when either param is NULL.
 *            - (1) if the list does contain the datacont*.
 */
int list_contains(const list* l, const datacont* dc);


/* -----------------
 * list_length():
 * Computes and returns the length of the list.
 *
 * Inputs:
 * list* l - the list being operated on.
 *
 * Returns:
 * int len - the length of the list (0 when 'l' is NULL).
 */
int list_length(const list* l);


#endif

