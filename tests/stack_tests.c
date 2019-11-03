
#include <stdio.h>

#include "../src/include/datacont.h"
#include "../src/include/listnode.h"
#include "../src/include/stack.h"


static int stack_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  stack* s = stack_new();
  if (s == NULL)
  {
    printf("TEST 1: stack_new() should not return a NULL pointer\n");
    retval = -1;
  }

  if (s->head != NULL)
  {
    printf("TEST 1: stack_new() should return a stack* with a NULL listnode*\n");
    retval = -1;
  }

  stack_delete(s);
  return retval;
}


static int stack_push_tests()
{
  int retval = 0;

  /* TEST 1 */
  stack* s = stack_new();
  
  if (stack_push(s, datacont_new("A", CHAR, 1)) != 0)
  {
    printf("TEST 1: stack_push() should return 0 on success\n");
    retval = -1;
  }

  /* TEST 2 */
  if (stack_push(s, datacont_new("B", CHAR, 1)) != 0)
  {
    printf("TEST 2: stack_push() should return 0 on success\n");
    retval = -1;
  }

  if (stack_push(NULL, NULL) != -1)
  {
    printf("TEST 3: stack_push() should return -1 when params are NULL\n");
    retval = -1;
  }

  stack_delete(s);

  return retval;
}

