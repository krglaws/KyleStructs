
#ifndef _LIST_H_
#define _LIST_H_

typedef struct list list;

struct list
{
  int length;
  listnode* head;
};

list* list_new();

void list_delete(list* l);

int list_insert(list* l, datacont* dc);

int list_remove(list* l, datacont* dc);

datacont* list_index(list* l, int i);

#endif

