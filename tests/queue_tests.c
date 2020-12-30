
#include <stdio.h>

#include <queue.h>


static int queue_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  queue* q = queue_new();
  if (q == NULL)
  {
    printf("TEST 1: queue_new() should not return a NULL pointer\n");
    retval = -1;
  }

  if (q->head != NULL)
  {
    printf("TEST 1: queue_new() should return a queue* with a NULL queue*\n");
    retval = -1;
  }

  queue_delete(q);
  return retval;
}


static int queue_enqueue_tests()
{
  int retval = 0;

  /* TEST 1 */
  queue* q = queue_new();
  
  if (queue_enqueue(q, datacont_new("A", CHAR, 1)) != 0)
  {
    printf("TEST 1: queue_enqueue() should return 0 on success\n");
    retval = -1;
  }

  /* TEST 2 */
  if (queue_enqueue(q, datacont_new("B", CHAR, 1)) != 0)
  {
    printf("TEST 2: queue_enqueue() should return 0 on success\n");
    retval = -1;
  }

  /* TEST 3 */
  if (queue_enqueue(NULL, NULL) != -1)
  {
    printf("TEST 3: queue_enqueue() should return -1 when params are NULL\n");
    retval = -1;
  }

  queue_delete(q);

  return retval;
}


static int queue_dequeue_tests()
{
  int retval = 0;

  /* TEST 1 */
  queue* q = queue_new();
  queue_enqueue(q, datacont_new("A", CHAR, 1));
  queue_enqueue(q, datacont_new("B", CHAR, 1));
  queue_enqueue(q, datacont_new("C", CHAR, 1));

  datacont* dc = queue_dequeue(q);
  if (dc->c != 'A')
  {
    printf("TEST 1: Unexpected datacont* returned from queue_dequeue(): %c. Expected: A\n", dc->c);
    retval = -1;
  }
  datacont_delete(dc);

  /* TEST 2 */
  dc = queue_dequeue(q);
  if (dc->c != 'B')
  {
    printf("TEST 2: Unexpected datacont* returned from queue_dequeue(): %c. Expected: B\n", dc->c);
    retval = -1;
  }
  datacont_delete(dc);

  /* TEST 3 */
  dc = queue_dequeue(q);
  if (dc->c != 'C')
  {
    printf("TEST 3: Unexpected datacont* returned from queue_dequeue(): %c. Expected: C\n", dc->c);
    retval = -1;
  }
  datacont_delete(dc);
 
  /* TEST 4 */
  dc = queue_dequeue(q);
  if (dc != NULL)
  {
    printf("TEST 4: queue_dequeue() should return NULL on empty queue\n");
    retval = -1;
  }

  queue_delete(q);

  return retval;
}


static int queue_length_tests()
{
  int retval = 0;
  
  /* TEST 1 */
  queue* s = queue_new();
  queue_enqueue(s, datacont_new("A", CHAR, 1));
  queue_enqueue(s, datacont_new("B", CHAR, 1));

  int length;
  if ((length = queue_length(s)) != 2)
  {
    printf("TEST 1: Unexpected value returned from queue_height(): %d. Expected: 2\n", length);
    retval = -1;
  }
  datacont_delete(queue_dequeue(s));

  /* TEST 2 */
  if ((length = queue_length(s)) != 1)
  {
    printf("TEST 2: Unexpected value returned from queue_height(): %d. Expected: 1\n", length);
    retval = -1;
  }
  datacont_delete(queue_dequeue(s));

  /* TEST 3 */
  if ((length = queue_length(s)) != 0)
  {
    printf("TEST 3: Unexpected value returned from queue_height(): %d. Expected: 0\n", length);
    retval = -1;
  }
  datacont_delete(queue_dequeue(s));

  /* TEST 4 */
  if ((length = queue_length(NULL)) != 0)
  {
    printf("TEST 4: Unexpected value returned from queue_height() on NULL queue*: %d. Expected: 0\n", length);
    retval = -1;
  }
  queue_delete(s);

  return retval;
}


int main()
{
  int retval = 0;

  printf("\nqueue tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running queue_new_tests()...\n");
  if (queue_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running queue_enqueue_tests()...\n");
  if (queue_enqueue_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running queue_dequeue_tests()...\n");
  if (queue_dequeue_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running queue_length_tests()...\n");
  if (queue_length_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

  

