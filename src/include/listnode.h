
#ifndef _LISTNODE_H_
#define _LISTNODE_H_


typedef struct listnode listnode;


struct listnode
{
  datacont* dc;
  listnode* next;
  listnode* prev;
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
 */
void listnode_delete_all(listnode* ln);


/* ----------------------
 * listnode_contains():
 * Determines whether or not a listnode, or any connected nodes, contains a datacont* with specified value.
 *
 * Inputs:
 * listnode* ln - the list node being operated on.
 * datacont* dc - the datacont to search for within the list.
 *
 * Returns:
 * int result - (0) if the list does not contain the datacont, or when either param is NULL.
 */
int listnode_contains(listnode* ln, datacont* dc);


/* -----------------------
 * listnode_remove():
 * Removes the first occurrence of a datacont found within a chain of listnodes.
 *
 * Inputs:
 * listnode* ln - the listnode being operated on.
 * datacont* dc - the datacont to be removed from the listnode.
 *
 * Returns:
 * int result - (0) if the list does not contain the datacont specified, or if either param is NULL.
 *            - (1) if the datacont was successfully removed.
 */
int listnode_remove(listnode* ln, datacont* dc);


/* -------------------------
 * listnode_get():
 * Returns a copy of the datacont contained within a listnode that is a specified number of nodes down the chain from 'ln' (in the 'ln->next' direction).
 *
 * Inputs:
 * listnode* ln - the listnode being operated on.
 * int index - the index used to locate the desired datacont.
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
 * listnode* ln - the listnode being operated on.
 * datacont* dc - the datacont to search for within the connected listnodes.
 * 
 * Returns:
 * int index - (-1) if the datacont could not be found.
 *           - >= (0) the index of the datacont
 */
int listnode_index(listnode* ln, datacont* dc);


listnode* listnode_seek(listnode* ln, int index);


unsigned int listnode_length(listnode* ln);

#endif

