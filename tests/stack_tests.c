
#include <stdio.h>

#include <ks_stack.h>


static int ks_stack_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_stack* s = ks_stack_new();
  if (s == NULL)
  {
    printf("TEST 1: ks_stack_new() should not return a NULL pointer\n");
    retval = -1;
  }

  if (s->top != NULL)
  {
    printf("TEST 1: ks_stack_new() should return a ks_stack* with a NULL ks_stack*\n");
    retval = -1;
  }

  ks_stack_delete(s);
  return retval;
}


static int ks_stack_push_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_stack* s = ks_stack_new();
  
  if (ks_stack_push(s, ks_datacont_new("A", KS_CHAR, 1)) != 0)
  {
    printf("TEST 1: ks_stack_push() should return 0 on success\n");
    retval = -1;
  }

  /* TEST 2 */
  if (ks_stack_push(s, ks_datacont_new("B", KS_CHAR, 1)) != 0)
  {
    printf("TEST 2: ks_stack_push() should return 0 on success\n");
    retval = -1;
  }

  /* TEST 3 */
  if (ks_stack_push(NULL, NULL) != -1)
  {
    printf("TEST 3: ks_stack_push() should return -1 when params are NULL\n");
    retval = -1;
  }

  ks_stack_delete(s);

  return retval;
}


static int ks_stack_pop_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_stack* s = ks_stack_new();
  ks_stack_push(s, ks_datacont_new("A", KS_CHAR, 1));
  ks_stack_push(s, ks_datacont_new("B", KS_CHAR, 1));
  ks_stack_push(s, ks_datacont_new("C", KS_CHAR, 1));

  ks_datacont* dc = ks_stack_pop(s);
  if (dc->c != 'C')
  {
    printf("TEST 1: Unexpected ks_datacont* returned from ks_stack_pop(): %c. Expected: C\n", dc->c);
    retval = -1;
  }
  ks_datacont_delete(dc);

  /* TEST 2 */
  dc = ks_stack_pop(s);
  if (dc->c != 'B')
  {
    printf("TEST 2: Unexpected ks_datacont* returned from ks_stack_pop(): %c. Expected: B\n", dc->c);
    retval = -1;
  }
  ks_datacont_delete(dc);

  /* TEST 3 */
  dc = ks_stack_pop(s);
  if (dc->c != 'A')
  {
    printf("TEST 3: Unexpected ks_datacont* returned from ks_stack_pop(): %c. Expected: A\n", dc->c);
    retval = -1;
  }
  ks_datacont_delete(dc);
 
  /* TEST 4 */
  dc = ks_stack_pop(s);
  if (dc != NULL)
  {
    printf("TEST 4: ks_stack_pop() should return NULL on empty ks_stack*\n");
    retval = -1;
  }

  ks_stack_delete(s);

  return retval;
}


static int ks_stack_height_tests()
{
  int retval = 0;
  
  /* TEST 1 */
  ks_stack* s = ks_stack_new();
  ks_stack_push(s, ks_datacont_new("A", KS_CHAR, 1));
  ks_stack_push(s, ks_datacont_new("B", KS_CHAR, 1));

  int height;
  if ((height = ks_stack_height(s)) != 2)
  {
    printf("TEST 1: Unexpected value returned from ks_stack_height(): %d. Expected: 2\n", height);
    retval = -1;
  }
  ks_datacont_delete(ks_stack_pop(s));

  /* TEST 2 */
  if ((height = ks_stack_height(s)) != 1)
  {
    printf("TEST 2: Unexpected value returned from ks_stack_height(): %d. Expected: 1\n", height);
    retval = -1;
  }
  ks_datacont_delete(ks_stack_pop(s));

  /* TEST 3 */
  if ((height = ks_stack_height(s)) != 0)
  {
    printf("TEST 3: Unexpected value returned from ks_stack_height(): %d. Expected: 0\n", height);
    retval = -1;
  }
  ks_datacont_delete(ks_stack_pop(s));

  /* TEST 4 */
  if ((height = ks_stack_height(NULL)) != 0)
  {
    printf("TEST 4: Unexpected value returned from ks_stack_height() on NULL ks_stack*: %d. Expected: 0\n", height);
    retval = -1;
  }
  ks_stack_delete(s);

  return retval;
}


int main()
{
  int retval = 0;

  printf("\nks_stack tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_stack_new_tests()...\n");
  if (ks_stack_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_stack_push_tests()...\n");
  if (ks_stack_push_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_stack_pop_tests()...\n");
  if (ks_stack_pop_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_stack_height_tests()...\n");
  if (ks_stack_height_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

  

