
#include <stdlib.h>

#include "include/datacont.h"
#include "include/listnode.h"


listnode* listnode_new(datacont* dc)
{
  listnode* ln = calloc(1, sizeof(listnode));
  ln->item = dc;
  return ln;
}


void listnode_delete(listnode* ln)
{
  if (ln == NULL) return;
  
  ln = listnode_seek_beg(ln);

  if (ln->item) datacont_delete(ln->item);
  free(ln);
}


listnode* listnode_seek_beg(listnode* ln)
{
  if (ln == NULL) return NULL;
  while (ln->prev) ln = ln->prev;
  return ln;
}


listnode* listnode_seek_end(listnode* ln)
{
  if (ln == NULL) return NULL;
  while (ln->next) ln = ln->next;
  return ln;
}


unsigned int listnode_length(listnode* ln)
{
  if (ln == NULL) return 0;
  unsigned int length = 0;
  ln = listnode_seek_beg(ln);
  while (ln)
  {
    length++;
    ln = ln->next;
  }
  return length;
}


