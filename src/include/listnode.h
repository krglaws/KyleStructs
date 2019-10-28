
#ifndef _LISTNODE_H_
#define _LISTNODE_H_


typedef struct listnode listnode;


struct listnode
{
  datacont* dc;
  listnode* next;
};


/* -------------------
 * listnode_new():
 * Creates a new listnode* containing a datacont*.
 *
 * Inputs:
 * datacont* dc - the datacont* to be held by the listnode.
 *
 * Returns:
 * listnode* ln - a listnode*, (NULL) if 'dc' is NULL.
 */
listnode* listnode_new(datacont* dc);


/* --------------------
 * listnode_delete(listnode* ln):
 * Deletes a listnode and its datacont* member.
 *
 * Inputs:
 * listnode* ln - the listnode* being deleted.
 *
 * Returns:
 * void
 * 
 * Notes:
 * This function will not touch the other nodes that 'ln' might be connected to. It is
 * assumed that the user code has or will handle any connected nodes.
 */
void listnode_delete(listnode* ln);


/* -------------------
 * listnode_delete_all():
 * Deletes a listnode and all other connected nodes.
 * 
 * Inputs:
 * listnode* ln - the listnode to be deleted.
 *
 * Returns:
 * void
 *
 * Notes:
 * This function will delete 'ln' and all nodes connected to it. If only part of a
 * list is to be deleted, it will have to be manually isolated, with it's 'next'
 * member set to NULL.
 */
void listnode_delete_all(listnode* ln);


/* --------------------
 * listnode_add():
 * Append a datacont* to a listnode chain.
 *
 * Inputs:
 * listnode* ln - the listnode to be added to.
 * datacont* dc - the datacont being added to the list.
 *
 * Returns:
 * void
 *
 * Notes:
 * If 'ln' or 'dc' is NULL, nothing happens.
 */
void listnode_add(listnode* ln, datacont* dc);


/* -----------------------
 * listnode_remove():
 * Removes the first occurrence of a datacont found within a chain of listnodes.
 *
 * Inputs:
 * listnode* ln - the listnode being operated on.
 * datacont* dc - the datacont to be removed from the listnode.
 *
 * Returns:
 * int result - (-1) if the list does not contain the datacont specified, or if either param is NULL.
 *            - (0) if the datacont was successfully removed.
 */
int listnode_remove(listnode* ln, datacont* dc);


/* ------------------------
 * listnode_remove_all():
 * Removes all occurrences of a specified datacont value within a chain of listnodes.
 *
 * Inputs:
 * listnode* ln - the listnode being operated on.
 * datacont* dc - the datacont being removed from the listnode.
 *
 * Returns:
 * int result - (-1) if either param is NULL.
 *            - >= (0) the number of nodes removed from the listnode chain.
 */
int listnode_remove_all(listnode* ln, datacont* dc);


/* -------------------------
 * listnode_insert():
 * Inserts a datacont* at a location specified in a chain of listnodes.
 *
 * Inputs:
 * listnode* ln - the listnode being operated on.
 * datacont* dc - the datacont being inserted.
 * int index - the location to insert the datacont.
 *
 * Returns:
 * int result - (-1) when either parameter is NULL, or when 'index' is OOB.
 *            - (0) on success.
 */
int listnode_insert(listnode* ln, datacont* dc, int index); 


/* -------------------------
 * listnode_get():
 * Returns a copy of the datacont contained within a listnode that is a specified number of nodes down the chain from 'ln' (in the 'ln->next' direction).
 *
 * Inputs:
 * listnode* ln - the listnode being operated on.
 * int index - the index used to locate the desired datacont. When negative, it will iterate over
 *             the list in REVERSE order.
 *
 * Returns:
 * datacont* dc - (NULL) if the 'index' is OOB, or if either param is NULL.
 *              - a copy of the datacont located at 'index'.
 */
datacont* listnode_get(listnode* ln, int index);


/* ---------------------------
 * listnode_index():
 * Returns the index of the first datacont that matches the datacont 'dc' param located within a group of connected listnodes.
 * 
 * Inputs:
 * listnode* ln - the listnode being searched through.
 * datacont* dc - the datacont to search for within the connected listnodes.
 * 
 * Returns:
 * int index - (-1) if the datacont could not be found.
 *           - >= (0) the index of the datacont
 *
 * Notes:
 * This function can also serve as a 'listnode_contains' function. Example:
 * if (listnode_index(ln, dc) >= 0) puts("Found it!");
 */
int listnode_index(listnode* ln, datacont* dc);



/* -----------------------------
 * listnode_replace_at():
 * Replaces a datacont at a specified location within a listnode chain.
 *
 * Inputs:
 * listnode* ln - the listnode being operated on.
 * datacont* dc - the new datacont being added to the listnode chain.
 * int index - the index at which the replacement will take place.
 *
 * Returns:
 * int result - (-1) when either 'ln' or 'dc' are NULL, or when 'index' is OOB.
 *            - (0) on success.
 */
int listnode_replace_at(listnode* ln, datacont* dc, int index);


/* -----------------------------
 * listnode_replace_by():
 * Replaces the first occurrence of a specified datacont value with a new datacont value.
 *
 * Inputs:
 * listnode* ln - the listnode being operated on.
 * datacont* old_dc - the original datacont to be replaced.
 * datacont* new_dc - the new datacont replacing the original.
 *
 * Returns:
 * int result - (-1) when any param is NULL, or when 'old_dc' could not be found.
 *            - (0) on success.
 */
int listnode_replace_by(listnode* ln, datacont* old_dc, datacont* new_dc);


/* ------------------------------
 * listnode_replace_all():
 * Replaces all occurrences of a specified datacont value with a new datacont value.
 *
 * Inputs:
 * listnode* ln - the listnode being operated on.
 * datacont* old_dc - the original datacont to be replaced.
 * datacont* new_dc - the new datacont replacing the orignal.
 *
 * Returns:
 * int result - >= (0) the number of replacements that occurred. 
 */
int listnode_replace_all(listnode* ln, datacont* old_dc, datacont* new_dc);


/* ----------------------------
 * listnode_length():
 * Returns the length of the list.
 *
 * Inputs:
 * listnode* ln - the listnode be operated on.
 *
 * Returns:
 * int length - the length of the list. (0) when 'ln' is NULL.
 *
 * Notes:
 * This function will only search in the 'ln->next' direction. If the user code is passing in a listnode
 * that is in the middle of the list, 'listnode_seek()' can be used to retrieve the first node in the list,
 * then pass THAT listnode into 'listnode_length()' to get the whole length.
 */
unsigned int listnode_length(listnode* ln);


#endif

