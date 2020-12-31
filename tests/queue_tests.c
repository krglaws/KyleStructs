
#include <stdio.h>

#include <ks_queue.h>


static int ks_queue_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_queue* q = ks_queue_new();
  if (q == NULL)
  {
    printf("TEST 1: ks_queue_new() should not return a NULL pointer\n");
    retval = -1;
  }

  if (q->head != NULL)
  {
    printf("TEST 1: ks_queue_new() should return a ks_queue* with a NULL ks_queue*\n");
    retval = -1;
  }

  ks_queue_delete(q);
  return retval;
}


static int ks_queue_enqueue_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_queue* q = ks_queue_new();
  
  if (ks_queue_enqueue(q, ks_datacont_new("A", KS_CHAR, 1)) != 0)
  {
    printf("TEST 1: ks_queue_enqueue() should return 0 on success\n");
    retval = -1;
  }

  /* TEST 2 */
  if (ks_queue_enqueue(q, ks_datacont_new("B", KS_CHAR, 1)) != 0)
  {
    printf("TEST 2: ks_queue_enqueue() should return 0 on success\n");
    retval = -1;
  }

  /* TEST 3 */
  if (ks_queue_enqueue(NULL, NULL) != -1)
  {
    printf("TEST 3: ks_queue_enqueue() should return -1 when params are NULL\n");
    retval = -1;
  }

  ks_queue_delete(q);

  return retval;
}


static int ks_queue_dequeue_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_queue* q = ks_queue_new();
  ks_queue_enqueue(q, ks_datacont_new("A", KS_CHAR, 1));
  ks_queue_enqueue(q, ks_datacont_new("B", KS_CHAR, 1));
  ks_queue_enqueue(q, ks_datacont_new("C", KS_CHAR, 1));

  ks_datacont* dc = ks_queue_dequeue(q);
  if (dc->c != 'A')
  {
    printf("TEST 1: Unexpected ks_datacont* returned from ks_queue_dequeue(): %c. Expected: A\n", dc->c);
    retval = -1;
  }
  ks_datacont_delete(dc);

  /* TEST 2 */
  dc = ks_queue_dequeue(q);
  if (dc->c != 'B')
  {
    printf("TEST 2: Unexpected ks_datacont* returned from ks_queue_dequeue(): %c. Expected: B\n", dc->c);
    retval = -1;
  }
  ks_datacont_delete(dc);

  /* TEST 3 */
  dc = ks_queue_dequeue(q);
  if (dc->c != 'C')
  {
    printf("TEST 3: Unexpected ks_datacont* returned from ks_queue_dequeue(): %c. Expected: C\n", dc->c);
    retval = -1;
  }
  ks_datacont_delete(dc);
 
  /* TEST 4 */
  dc = ks_queue_dequeue(q);
  if (dc != NULL)
  {
    printf("TEST 4: ks_queue_dequeue() should return NULL on empty ks_queue\n");
    retval = -1;
  }

  ks_queue_delete(q);

  return retval;
}


static int ks_queue_length_tests()
{
  int retval = 0;
  
  /* TEST 1 */
  ks_queue* s = ks_queue_new();
  ks_queue_enqueue(s, ks_datacont_new("A", KS_CHAR, 1));
  ks_queue_enqueue(s, ks_datacont_new("B", KS_CHAR, 1));

  int length;
  if ((length = ks_queue_length(s)) != 2)
  {
    printf("TEST 1: Unexpected value returned from ks_queue_height(): %d. Expected: 2\n", length);
    retval = -1;
  }
  ks_datacont_delete(ks_queue_dequeue(s));

  /* TEST 2 */
  if ((length = ks_queue_length(s)) != 1)
  {
    printf("TEST 2: Unexpected value returned from ks_queue_height(): %d. Expected: 1\n", length);
    retval = -1;
  }
  ks_datacont_delete(ks_queue_dequeue(s));

  /* TEST 3 */
  if ((length = ks_queue_length(s)) != 0)
  {
    printf("TEST 3: Unexpected value returned from ks_queue_height(): %d. Expected: 0\n", length);
    retval = -1;
  }
  ks_datacont_delete(ks_queue_dequeue(s));

  /* TEST 4 */
  if ((length = ks_queue_length(NULL)) != 0)
  {
    printf("TEST 4: Unexpected value returned from ks_queue_height() on NULL ks_queue*: %d. Expected: 0\n", length);
    retval = -1;
  }
  ks_queue_delete(s);

  return retval;
}


int main()
{
  int retval = 0;

  printf("\nks_queue tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_queue_new_tests()...\n");
  if (ks_queue_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_queue_enqueue_tests()...\n");
  if (ks_queue_enqueue_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_queue_dequeue_tests()...\n");
  if (ks_queue_dequeue_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_queue_length_tests()...\n");
  if (ks_queue_length_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

  

