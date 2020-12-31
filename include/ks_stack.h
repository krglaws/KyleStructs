#ifndef _KS_STACK_H_
#define _KS_STACK_H_


#include <ks_datacont.h>
#include "ks_listnode.h"


typedef struct ks_stack ks_stack;


struct ks_stack
{
  ks_listnode* top;
};


/* -------------------
 * ks_stack_new():
 * Creates a new empty ks_stack*.
 *
 * Inputs:
 * void
 *
 * Returns:
 * ks_stack* s - an empty ks_stack
 */
ks_stack* ks_stack_new();


/* -------------------------
 * ks_stack_delete():
 * Deletes a ks_stack and all of its contents.
 *
 * Inputs:
 * ks_stack* s - the ks_stack being deleted.
 *
 * Returns:
 * void
 */
void ks_stack_delete(ks_stack* s);


/* ----------------------------
 * ks_stack_push():
 * Pushes a ks_datacont onto a ks_stack.
 *
 * Inputs:
 * ks_stack* s - the ks_stack being operated on.
 * ks_datacont* dc - the ks_datacont being pushed onto the ks_stack.
 *
 * Returns:
 * int result - (-1) if either parameter is NULL.
 *            - (0) on success
 */
int ks_stack_push(ks_stack* s, const ks_datacont* dc);


/* --------------------------
 * ks_stack_pop():
 * Pops a ks_datacont off of a ks_stack.
 *
 * Inputs:
 * ks_stack* s - the ks_stack being operated on.
 * 
 * Returns:
 * ks_datacont* dc - (NULL) if ks_stack is empty or NULL.
 *              - the ks_datacont at the top of the ks_stack.
 */
ks_datacont* ks_stack_pop(ks_stack* s);


/* ----------------------------
 * ks_stack_height():
 * Calculates the height of a ks_stack.
 *
 * Inputs:
 * ks_stack* s - the ks_stack being operated on.
 *
 * Returns:
 * unsigned int height - >= (0) the height of the ks_stack.
 */
unsigned int ks_stack_height(ks_stack* s);


#endif
