
#include "include/datacont.h"
#include "include/listnode.h"
#include "include/list.h"


list* list_new()
{
  return calloc(1, sizeof(list));
}


void list_delete(list* l);
{
  listnode_delete_all(l->head);
  free(l);
}


int list_insert(list* l, datacont* dc, int index)
{
  return listnode_insert(l->head, dc, index);
}


int list_remove(list* l, datacont* dc)
{
  return listnode_remove(l->head, dc);
}


datacont* list_index(list* l, int i)
{
  return listnode_index(l->head, i);
}


#endif


