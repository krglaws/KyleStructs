
#include <stdio.h>

#include "../src/include/datacont.h"
#include "../src/include/listnode.h"


static int listnode_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  listnode* ln = listnode_new(datacont_new("A", CHAR, 1));

  if (ln->prev != NULL)
  {
    printf("TEST 1: ln->prev should be NULL.\n");
    retval = -1;
  }
  if (ln->next != NULL)
  {
    printf("TEST 1: ln->next should be NULL.\n");
    retval = -1;
  }
  if (ln->item->c != 'A')
  {
    printf("TEST 1: Unexpected datacont value: '%c'. Expected: 'A'.\n", ln->item->c);
    retval = -1;
  }

  listnode_delete(ln);

  return retval;
}


static int listnode_add_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* dc = datacont_new("B", CHAR, 1);

  if (listnode_add(NULL, dc) != 1)
  {
    printf("TEST 1: listnode_add() with any NULL parameters should return 1\n");
    retval = -1;
  }

  /* TEST 2 */
  listnode* ln = listnode_new(datacont_new("A", CHAR, 1));
  if (listnode_add(ln, dc) != 0)
  {
    printf("TEST 2: listnode_add() should return 0 when successful");
    retval = -1;
  }

  if (ln->item->c != 'A')
  {
    printf("TEST 2: unexpected datacont value at first listnode: %c. Expected: %c\n", ln->item->c, 'A');
    retval = -1;
  }

  if (ln->next->item->c != 'B')
  {
    printf("TEST 2: unexpected datacont value at second listnode: %c. Expected: %c\n", ln->next->item->c, 'B');
    retval = -1;
  }
  
  listnode_delete_all(ln);

  return retval;
}


static int listnode_remove_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* dc1 = datacont_new("A", CHAR, 1);
  datacont* dc2 = datacont_new("B", CHAR, 1);
  datacont* dc3 = datacont_new("C", CHAR, 1);

  listnode* ln = listnode_new(datacont_copy(dc1));
  listnode_add(ln, datacont_copy(dc2));
  listnode_add(ln, datacont_copy(dc3));

  if (listnode_remove(ln, dc2))
  {
    printf("TEST 1: listnode_remove() should return 0 on successful removal\n");
    retval = -1;
  }

  /* TEST 2 */
  if (listnode_remove(ln, dc1))
  {
    printf("TEST 2: listnode_remove() should return 0 on successful removal\n");
    retval = -1;
  }

  /* TEST 3 */
  if (listnode_remove(ln, dc3))
  {
    printf("TEST 3: listnode_remove() should return 0 on successful removal\n");
    retval = -1;
  }

  datacont_delete(dc1);
  datacont_delete(dc2);
  datacont_delete(dc3);

  return retval;
}


static int listnode_get_nth_tests()
{
  int retval = 0;

  /* TEST 1 */
  listnode* ln = listnode_new(datacont_new("A", CHAR, 1));
  listnode_add(ln, datacont_new("B", CHAR, 1));
  listnode_add(ln, datacont_new("C", CHAR, 1));

  datacont* dcC = listnode_get_nth(ln, 2);
  if (dcC->c != 'C')
  {
    printf("TEST 1: Unexpected return value: %c. Expected: C\n", dcC->c);
    retval = -1;
  }

  /* TEST 2 */
  datacont* dcA = listnode_get_nth(ln, 0);
  if (dcA->c != 'A')
  {
    printf("TEST 2: Unexpected return value: %c. Expected: A\n", dcA->c);
    retval = -1;
  }

  /* TEST 3 */
  datacont* dcB = listnode_get_nth(ln, 1);
  if (dcB->c != 'B')
  {
    printf("TEST 3: Unexpected return value: %c. Expected: B\n", dcB->c);
    retval = -1;
  }

  listnode_delete_all(ln);
  datacont_delete(dcA);
  datacont_delete(dcB);
  datacont_delete(dcC);

  return retval;
}


static int listnode_seek_beg_tests()
{
  int retval = 0;

  /* TEST 1 */
  listnode* head = listnode_new(datacont_new("A", CHAR, 1));

  head->next = listnode_new(datacont_new("B", CHAR, 1));
  head->next->prev = head;

  head->next->next = listnode_new(datacont_new("C", CHAR, 1));
  head->next->next->prev = head->next;

  if (listnode_seek_beg(head->next->next) != head)
  {
    printf("TEST 1: listnode_seek_beg() should return pointer to head.\n");
    retval = -1;
  }
  listnode_delete(head);

  return retval;
}


static int listnode_seek_end_tests()
{
  int retval = 0;

  /* TEST 1 */
  listnode* head = listnode_new(datacont_new("A", CHAR, 1));
  
  head->next = listnode_new(datacont_new("B", CHAR, 1));
  head->next->prev = head;

  head->next->next = listnode_new(datacont_new("C", CHAR, 1));
  head->next->next->prev = head->next;

  if (listnode_seek_end(head) != head->next->next)
  {
    printf("TEST 1: listnode_seek_end() should return pointer to last node.\n");
    retval = -1;
  }
  listnode_delete(head);

  return retval;
}


static int listnode_length_tests()
{
  int retval = 0;

  /* TEST 1 */
  listnode* head = listnode_new(datacont_new("A", CHAR, 1));

  head->next = listnode_new(datacont_new("B", CHAR, 1));
  head->next->prev = head;

  head->next->next = listnode_new(datacont_new("C", CHAR, 1));
  head->next->next->prev = head->next;

  int len = listnode_length(head);
  if (len != 3)
  {
    printf("TEST 1: Unexpected listnode length: %d. Expected: 3.\n", len);
    retval = -1;
  }
  listnode_delete(head);

  return retval;
}


int main()
{
  int retval = 0;

  printf("\nlistnode tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running listnode_new_tests()...\n");
  if (listnode_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running listnode_add_tests()...\n");
  if (listnode_add_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running listnode_remove_tests()...\n");
  if (listnode_remove_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running listnode_get_nth_tests()...\n");
  if (listnode_get_nth_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running listnode_seek_beg_tests()...\n");
  if (listnode_seek_beg_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running listnode_seek_end_tests()...\n");
  if (listnode_seek_end_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running listnode_length_tests()...\n");
  if (listnode_length_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

