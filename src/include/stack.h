
#ifndef _STACK_H_
#define _STACK_H_


typedef struct stack stack;


struct stack
{
  listnode* head;
};


/* -------------------
 * stack_new():
 * Creates a new empty stack*.
 *
 * Inputs:
 * void
 *
 * Returns:
 * stack* s - an empty stack
 */
stack* stack_new();


/* -------------------------
 * stack_delete():
 * Deletes a stack and all of its contents.
 *
 * Inputs:
 * stack* s - the stack being deleted.
 *
 * Returns:
 * void
 */
void stack_delete(stack* s);


/* ----------------------------
 * stack_push():
 * Pushes a datacont onto a stack.
 *
 * Inputs:
 * stack* s - the stack being operated on.
 * datacont* dc - the datacont being pushed onto the stack.
 *
 * Returns:
 * int result - (-1) if either parameter is NULL.
 *            - (0) on success
 */
int stack_push(stack* s, const datacont* dc);


/* --------------------------
 * stack_pop():
 * Pops a datacont off of a stack.
 *
 * Inputs:
 * stack* s - the stack being operated on.
 * 
 * Returns:
 * datacont* dc - (NULL) if stack is empty or NULL.
 *              - the datacont at the top of the stack.
 */
datacont* stack_pop(stack* s);


/* ----------------------------
 * stack_height():
 * Calculates the height of a stack.
 *
 * Inputs:
 * stack* s - the stack being operated on.
 *
 * Returns:
 * unsigned int height - >= (0) the height of the stack.
 */
unsigned int stack_height(stack* s);


#endif

