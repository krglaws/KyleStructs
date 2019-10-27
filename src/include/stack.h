
#ifndef _STACK_H_
#define _STACK_H_


typedef struct stack stack;


struct stack
{
  listnode* top;
};


/* ----------------
 * stack_new():
 * Creates a new empty stack.
 *
 * Inputs:
 * none
 *
 * Returns:
 * stack* s - a new empty stack.
 */
stack* stack_new();


/* ------------------
 * stack_delete():
 * Deletes a stack* and all of its contents.
 *
 * Inputs:
 * stack* s - the stack being deleted.
 *
 * Returns:
 * void
 */
void stack_delete(stack* s);


/* ------------------
 * stack_push():
 * Pushes a datacont* onto a stack.
 *
 * Inputs:
 * stack* s - the stack being operated on.
 * datcont* dc - the datacont* being pushed onto the stack.
 *
 * Returns:
 * int result - (-1) if 's' or 'dc' are NULL.
 *            - (0) on success.
 */
void stack_push(stack* s, datacont* dc);


/* ------------------
 * stack_pop():
 * Pops a datacont* off of a stack.
 *
 * Inputs:
 * stack* s - the stack being operated on.
 *
 * Returns:
 * datacont* dc - (NULL) if stack is empty.
 *              - the datacont* located at the top of the stack.
 *
 * Notes:
 * Elsewhere in this library, returned pointers are COPIES of the original.
 * In this case, the ORIGINAL is returned, and the stack's reference to the 
 * original is disposed of.
 */
datacont* stack_pop(stack* s);


/* ------------------
 * stack_peek():
 * Returns a copy of the top-most datacont* on the stack.
 *
 * Inputs:
 * stack* s - the stack being operated on.
 *
 * Returns:
 * datacont* dc - (NULL) if the stack is empty.
 *              - a copy of the datacont* located at the top of the stack.
 */
datacont* stack_peek(stack* s);


/* -------------------
 * stack_height():
 * Returns the current height of the stack.
 * 
 * Inputs:
 * stack* s - the stack being operated on.
 *
 * Returns:
 * int height - the height of the stack, (0) when NULL or empty.
 */
datacont* stack_height(stack* s);


#endif

