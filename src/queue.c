
#include "include/queue.h"


queue* queue_new()
{
  return calloc(1, sizeof(queue));
}


void queue_delete(queue* q)
{
  if (q == NULL) return;

  listnode_delete_all(q->head);

  free(q);
}


int queue_enqueue(queue* q, datacont* dc)
{
  if (q == NULL || dc == NULL) return -1;

  if (q->head == NULL) 
  {
    q->head = listnode_new(dc);
    return 0;
  }

  listnode_insert(&(q->head), dc, 0);

  return 0;
}


datacont* queue_dequeue(queue* q)
{
  if (q == NULL) return NULL;
  
  datacont* dc = datacont_copy(
		  listnode_get(q->head, -1));

  listnode_remove_at(&(q->head), -1);

  return dc;
}


unsigned int queue_length(queue* q)
{
  if (q == NULL) return 0;

  return listnode_length(q->head);
}

