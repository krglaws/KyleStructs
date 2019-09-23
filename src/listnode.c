
#include <stdlib.h>


struct listnode
{
  datacont* item;
  listnode* prev;
  listnode* next;
}


listnode* listnode_new(datacont* dc)
{
  listnode* ln = calloc(1, sizeof(listnode));
  ln->item = dc;
  return ln;
}


void listnode_delete(listnode* ln)
{
  if (listnode->item) datacont_delete(listnode->item);
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
  while (ln)
  {
    length++;
    ln = ln->next;
  }
  return length;
}


