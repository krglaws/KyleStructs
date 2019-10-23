
#include <stdlib.h>

#include "include/datacont.h"
#include "include/listnode.h"


listnode* listnode_new(datacont* dc)
{
  if (dc == NULL) return NULL;
  listnode* ln = calloc(1, sizeof(listnode));
  ln->item = dc;
  return ln;
}


void listnode_delete(listnode* ln)
{
  if (ln == NULL) return;
  if (ln->item) datacont_delete(ln->item);
  free(ln);
}


void listnode_delete_all(listnode* ln)
{
  if (ln == NULL) return;
  ln = listnode_seek_beg(ln);

  listnode* next = ln->next;

  listnode_delete(ln);
  listnode_delete_all(next);
}


int listnode_add(listnode* ln, datacont* dc)
{
  if (ln == NULL || dc == NULL) return 1;

  ln = listnode_seek_end(ln);
  
  ln->next = listnode_new(dc);
  ln->next->prev = ln;

  return 0;
}


int listnode_remove(listnode* ln, datacont* dc)
{
  if (dc == NULL) return 1;

  while (ln)
  {
    if (datacont_compare(dc, ln->item) == EQUAL)
    {
      ln->next->prev = ln->prev;
      ln->prev->next = ln->next;
      listnode_delete(ln);
      return 0;
    }
    ln = ln->next;
  }

  return 1;
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


