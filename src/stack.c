#include <stack.h>


stack* stack_new()
{
  return calloc(1, sizeof(stack));  
}


void stack_delete(stack* s)
{
  if (s == NULL) return;

  listnode_delete_all(s->top);

  free(s);
}


int stack_push(stack* s, const datacont* dc)
{
  if (s == NULL) return -1;

  if (s->top) return listnode_insert(&(s->top), dc, 0);

  s->top = listnode_new(dc);

  return 0;
}


datacont* stack_pop(stack* s)
{
  if (s == NULL) return NULL;

  datacont* dc = datacont_copy(
		  listnode_get(s->top, 0));

  listnode_remove_at(&(s->top), 0);

  return dc;
}


unsigned int stack_height(stack* s)
{
  if (s == NULL) return 0;

  return listnode_length(s->top);
}
