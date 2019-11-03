
#include <stdlib.h>

#include "include/datacont.h"
#include "include/listnode.h"
#include "include/stack.h"


stack* stack_new()
{
  return calloc(1, sizeof(stack));  
}


void stack_delete(stack* s)
{
  listnode_delete_all(s->head);
  free(s);
}


int stack_push(stack* s, const datacont* dc)
{
  if (s->head) return listnode_insert(&(s->head), dc, 0);
  s->head = listnode_new(dc);
  return 0;
}


datacont* stack_pop(stack* s)
{
  datacont* dc = listnode_get(s->head, 0);
  listnode_remove_at(&(s->head), 0);
  return dc;
}


unsigned int stack_height(stack* s)
{
  return listnode_length(s->head);
}

