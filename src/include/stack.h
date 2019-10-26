
#ifndef _STACK_H_
#define _STACK_H_

typedef struct stack stack;

struct stack
{
  int len;
  listnode* head;
};

stack* stack_new();

void stack_delete(stack* s);

void stack_push(stack* s, datacont* dc);

datacont* stack_pop(stack* s);

#endif

