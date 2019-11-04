
#ifndef _QUEUE_H_
#define _QUEUE_H_


typedef struct queue queue;


struct queue
{
  listnode* head;
};


/* -------------------
 * queue_new():
 * Creates a new empty queue*.
 * 
 * Inputs:
 * void
 *
 * Returns:
 * queue* q - a new empty queue.
 */
queue* queue_new();


/* ---------------------
 * queue_delete():
 * Deletes a queue* and all of its contents.
 *
 * Inputs:
 * queue* q - the queue being deleted.
 *
 * Returns:
 * void
 */
void queue_delete(queue* q);


/* ----------------------
 * queue_enqueue():
 * Enqueues a datacont* onto the tail of the queue.
 *
 * Inputs:
 * queue* q - the queue being added to.
 * datacont* dc - the datacont being added to the queue.
 *
 * Returns:
 * int result - (-1) when either param is NULL.
 *            - (0) on success.
 */
int queue_enqueue(queue* q, datacont* dc);


/* -----------------------
 * queue_dequeue():
 * Dequeues a datacont* off of the head of the queue and returns it.
 *
 * Inputs:
 * queue* q - the queue to dequeue from.
 *
 * Returns:
 * datacont* dc - (NULL) when queue is NULL, or when queue is empty.
 *              - the datacont being dequeued.
 */
datacont* queue_dequeue(queue* q);


/* --------------------------
 * queue_length():
 * Calculates the length of a queue.
 *
 * Inputs:
 * queue* q - the queue being operated on.
 *
 * Returns:
 * unsigned int len - >= (0) the length of the queue.
 */
unsigned int queue_length(queue* q);


#endif

