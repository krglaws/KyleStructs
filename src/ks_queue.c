#include <stdlib.h>

#include <ks_datacont.h>
#include <ks_listnode.h>
#include <ks_queue.h>


ks_queue* ks_queue_new()
{
  return calloc(1, sizeof(ks_queue));
}


void ks_queue_delete(ks_queue* q)
{
  if (q == NULL) return;

  ks_listnode_delete_all(q->head);

  free(q);
}


int ks_queue_enqueue(ks_queue* q, ks_datacont* dc)
{
  if (q == NULL || dc == NULL) return -1;

  if (q->head == NULL) 
  {
    q->head = ks_listnode_new(dc);
    return 0;
  }

  ks_listnode_insert(&(q->head), dc, 0);

  return 0;
}


ks_datacont* ks_queue_dequeue(ks_queue* q)
{
  if (q == NULL) return NULL;
  
  ks_datacont* dc = ks_datacont_copy(ks_listnode_get(q->head, -1));

  ks_listnode_remove_at(&(q->head), -1);

  return dc;
}


unsigned int ks_queue_length(ks_queue* q)
{
  if (q == NULL) return 0;

  return ks_listnode_length(q->head);
}
