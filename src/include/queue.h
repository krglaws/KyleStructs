
#ifndef _QUEUE_H_
#define _QUEUE_H_


typedef struct queue queue


struct queue
{
  listnode* head;
  listnode* tail;
};


/* ------------------
 * queue_new():
 * Creates a new empty queue.
 *
 * Inputs:
 * none
 * 
 * Returns:
 * queue* q - an empty queue.
 */
queue* queue_new();


/* ---------------------
 * queue_delete():
 * Deletes a queue and all of its contents.
 *
 * Inputs:
 * queue* q - the queue to be deleted.
 * 
 * Returns:
 * void
 */
void queue_delete(queue* q);


/* -----------------------
 * queue_enqueue():
 * Enqueues a datacont* onto a queue.
 *
 * Inputs:
 * queue* q - the queue being operated on.
 * datacont* dc - the datacont* to be enqueued.
 *
 * Returns:
 * int result - (-1) if 'q' or 'dc' are NULL.
 *            - (0) on success.
 */
int queue_enqueue(queue* q, datacont* dc);


/* ------------------------
 * queue_dequeue():
 * Dequeues a datacont* from a queue.
 * 
 * Inputs:
 * queue* q - the queue being operated on.
 * 
 * Returns:
 * datacont* dc - (NULL) if queue is empty,
 *              - the datacont* that has been dequeued.
 */
datacont* queue_dequeue(queue* q);


/* ------------------------
 * queue_length():
 * Calculates the length of a queue.
 *
 * Inputs:
 * queue* q - the queue being operated on.
 *
 * Returns:
 * int length - the length of the queue, (0) when NULL or empty.
 */
int queue_length(queue* q);


#endif

