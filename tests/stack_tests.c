
#include <stdio.h>

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

  if (s->top != NULL)
  {
    printf("TEST 1: stack_new() should return a stack* with a NULL stack*\n");
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

  /* TEST 3 */
  if (stack_push(NULL, NULL) != -1)
  {
    printf("TEST 3: stack_push() should return -1 when params are NULL\n");
    retval = -1;
  }

  stack_delete(s);

  return retval;
}


static int stack_pop_tests()
{
  int retval = 0;

  /* TEST 1 */
  stack* s = stack_new();
  stack_push(s, datacont_new("A", CHAR, 1));
  stack_push(s, datacont_new("B", CHAR, 1));
  stack_push(s, datacont_new("C", CHAR, 1));

  datacont* dc = stack_pop(s);
  if (dc->c != 'C')
  {
    printf("TEST 1: Unexpected datacont* returned from stack_pop(): %c. Expected: C\n", dc->c);
    retval = -1;
  }
  datacont_delete(dc);

  /* TEST 2 */
  dc = stack_pop(s);
  if (dc->c != 'B')
  {
    printf("TEST 2: Unexpected datacont* returned from stack_pop(): %c. Expected: B\n", dc->c);
    retval = -1;
  }
  datacont_delete(dc);

  /* TEST 3 */
  dc = stack_pop(s);
  if (dc->c != 'A')
  {
    printf("TEST 3: Unexpected datacont* returned from stack_pop(): %c. Expected: A\n", dc->c);
    retval = -1;
  }
  datacont_delete(dc);
 
  /* TEST 4 */
  dc = stack_pop(s);
  if (dc != NULL)
  {
    printf("TEST 4: stack_pop() should return NULL on empty stack*\n");
    retval = -1;
  }

  stack_delete(s);

  return retval;
}


static int stack_height_tests()
{
  int retval = 0;
  
  /* TEST 1 */
  stack* s = stack_new();
  stack_push(s, datacont_new("A", CHAR, 1));
  stack_push(s, datacont_new("B", CHAR, 1));

  int height;
  if ((height = stack_height(s)) != 2)
  {
    printf("TEST 1: Unexpected value returned from stack_height(): %d. Expected: 2\n", height);
    retval = -1;
  }
  datacont_delete(stack_pop(s));

  /* TEST 2 */
  if ((height = stack_height(s)) != 1)
  {
    printf("TEST 2: Unexpected value returned from stack_height(): %d. Expected: 1\n", height);
    retval = -1;
  }
  datacont_delete(stack_pop(s));

  /* TEST 3 */
  if ((height = stack_height(s)) != 0)
  {
    printf("TEST 3: Unexpected value returned from stack_height(): %d. Expected: 0\n", height);
    retval = -1;
  }
  datacont_delete(stack_pop(s));

  /* TEST 4 */
  if ((height = stack_height(NULL)) != 0)
  {
    printf("TEST 4: Unexpected value returned from stack_height() on NULL stack*: %d. Expected: 0\n", height);
    retval = -1;
  }
  stack_delete(s);

  return retval;
}


int main()
{
  int retval = 0;

  printf("\nstack tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running stack_new_tests()...\n");
  if (stack_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running stack_push_tests()...\n");
  if (stack_push_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running stack_pop_tests()...\n");
  if (stack_pop_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running stack_height_tests()...\n");
  if (stack_height_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

  

