
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

void listnode_delete_all(listnode* ln);

int listnode_add(listnode* ln, datacont* dc);

int listnode_contains(listnode* ln, datacont* dc);

int listnode_remove(listnode* ln, datacont* dc);

datacont* listnode_get_nth(listnode* ln, int n);

listnode* listnode_seek_beg(listnode* ln);

listnode* listnode_seek_end(listnode* ln);

unsigned int listnode_length(listnode* ln);

#endif

