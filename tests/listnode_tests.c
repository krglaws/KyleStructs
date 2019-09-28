
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
  if (listnode_seek_beg_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running listnode_remove_tests()...\n");
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

