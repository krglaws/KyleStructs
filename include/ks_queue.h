#ifndef _KS_QUEUE_H_
#define _KS_QUEUE_H_

#include <ks_datacont.h>
#include <ks_listnode.h>


typedef struct ks_queue ks_queue;


struct ks_queue
{
  ks_listnode* head;
};


/* -------------------
 * ks_queue_new():
 * Creates a new empty ks_queue*.
 * 
 * Inputs:
 * void
 *
 * Returns:
 * ks_queue* q - a new empty ks_queue.
 */
ks_queue* ks_queue_new();


/* ---------------------
 * ks_queue_delete():
 * Deletes a ks_queue* and all of its contents.
 *
 * Inputs:
 * ks_queue* q - the ks_queue being deleted.
 *
 * Returns:
 * void
 */
void ks_queue_delete(ks_queue* q);


/* ----------------------
 * ks_queue_enqueue():
 * Enks_queues a ks_datacont* onto the tail of the ks_queue.
 *
 * Inputs:
 * ks_queue* q - the ks_queue being added to.
 * ks_datacont* dc - the ks_datacont being added to the ks_queue.
 *
 * Returns:
 * int result - (-1) when either param is NULL.
 *            - (0) on success.
 */
int ks_queue_enqueue(ks_queue* q, ks_datacont* dc);


/* -----------------------
 * ks_queue_dequeue():
 * Deks_queues a ks_datacont* off of the head of the ks_queue and returns it.
 *
 * Inputs:
 * ks_queue* q - the ks_queue to dequeue from.
 *
 * Returns:
 * ks_datacont* dc - (NULL) when ks_queue is NULL, or when ks_queue is empty.
 *                 - the ks_datacont being dequeued.
 */
ks_datacont* ks_queue_dequeue(ks_queue* q);


/* --------------------------
 * ks_queue_length():
 * Calculates the length of a ks_queue.
 *
 * Inputs:
 * ks_queue* q - the ks_queue being operated on.
 *
 * Returns:
 * unsigned int len - >= (0) the length of the ks_queue.
 */
unsigned int ks_queue_length(ks_queue* q);


#endif
