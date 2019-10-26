
#ifndef _QUEUE_H_
#define _QUEUE_H_

typedef struct queue queue

struct queue
{
  int length;
  listnode* head;
  listnode* tail;
};

queue* queue_new();

void queue_delete(queue* q);

int queue_enqueue(queue* q, datacont* dc);

datacont* queue_dequeue(queue* q);

#endif

