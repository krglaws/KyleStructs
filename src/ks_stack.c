#include <stdlib.h>

#include <ks_datacont.h>
#include <ks_listnode.h>
#include <ks_stack.h>


ks_stack* ks_stack_new()
{
  return calloc(1, sizeof(ks_stack));  
}


void ks_stack_delete(ks_stack* s)
{
  if (s == NULL) return;

  ks_listnode_delete_all(s->top);

  free(s);
}


int ks_stack_push(ks_stack* s, const ks_datacont* dc)
{
  if (s == NULL) return -1;

  if (s->top) return ks_listnode_insert(&(s->top), dc, 0);

  s->top = ks_listnode_new(dc);

  return 0;
}


ks_datacont* ks_stack_pop(ks_stack* s)
{
  if (s == NULL) return NULL;

  ks_datacont* dc = ks_datacont_copy(
		  ks_listnode_get(s->top, 0));

  ks_listnode_remove_at(&(s->top), 0);

  return dc;
}


unsigned int ks_stack_height(ks_stack* s)
{
  if (s == NULL) return 0;

  return ks_listnode_length(s->top);
}
