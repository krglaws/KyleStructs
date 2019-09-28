
#ifndef _LISTNODE_H_
#define _LISTNODE_H_

typedef struct listnode listnode;

struct listnode
{
  datacont* item;
  listnode* prev;
  listnode* next;
};

listnode* listnode_new(datacont* dc);

void listnode_delete(listnode* ln);

listnode* listnode_seek_beg(listnode* ln);

listnode* listnode_seek_end(listnode* ln);

unsigned int listnode_length(listnode* ln);

#endif

