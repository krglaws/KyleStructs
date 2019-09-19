
#include <stdio.h>

#include "../src/include/datacont.h"
#include "../src/include/treenode.h"
#include "../src/include/treeset.h"


static int treeset_new_tests()
{
  int retval = 0;

  /* Test 1 */
  treeset* ts = treeset_new();
  if (ts->root != NULL | ts->num_nodes != 0)
  {
    printf("TEST 1: new treenode should be empty.\n");
    retval = -1;
  }
  treeset_delete(ts);
  
  return retval;
}


static int treeset_add_tests()
{
  int retval = 0;

  /* Test 1 */
  treeset* ts = treeset_new();
  if (treeset_add(ts, datacont_new("A", CHAR, 1)) != 0)
  {
    printf("TEST 1: treeset_add() should return 0 if treeset does not already contain item.\n");
    retval = -1;
  }

  /* Test 2 */
  if (treeset_add(ts, datacont_new("A", CHAR, 1)) != 1)
  {
    printf("TEST 2: treeset_add() should return 1 if treeset already contains item.\n");
    retval = -1;
  }

  if (treeset_height(ts) > 1)
  {
    printf("TEST 2: treeset height should not be affected when adding an already present item.\n");
    retval = -1;
  }
  treeset_delete(ts);

  return retval;
}


static int treeset_remove_tests()
{
  int retval = 0;
  treeset* ts = treeset_new();
  treeset_add(ts, datacont_new("D", CHAR, 1));
  treeset_add(ts, datacont_new("B", CHAR, 1));
  treeset_add(ts, datacont_new("F", CHAR, 1));
  treeset_add(ts, datacont_new("A", CHAR, 1));
  treeset_add(ts, datacont_new("C", CHAR, 1));
  treeset_add(ts, datacont_new("E", CHAR, 1));
  treeset_add(ts, datacont_new("G", CHAR, 1));

  datacont* dc_D = datacont_new("D", CHAR, 1);

  int num_nodes = ts->num_nodes;
  if (treeset_remove(ts, dc_D) != 0)
  {
    printf("TEST 1: treeset_remove() should return 0 when removing a present node.\n");
    retval = -1;
  }
  if (num_nodes - ts->num_nodes != 1)
  {
    printf("TEST 1: unexpected ts->num_nodes value after call to treeset_remove(). Expected: %d. Received: %d.\n",
		    num_nodes-1, ts->num_nodes);
    retval = -1;
  }
  
  datacont_delete(dc_D);
  treeset_delete(ts);

  return retval;
}


static int treeset_contains_tests()
{
  int retval = 0;

  datacont* dca = datacont_new("A", CHAR, 1);
  datacont* dcb = datacont_new("B", CHAR, 1);

  treeset* ts = treeset_new();
  treeset_add(ts, dca);

  /* TEST 1 */
  if (treeset_contains(ts, dcb) == 1)
  {
    printf("TEST 1: treeset should not contain datacont 'B'.\n");
    retval = -1;
  }

  if (treeset_contains(ts, dca) == 0)
  {
    printf("TEST 2: treeset should contain datacont 'A'.\n");
    retval = -1;
  }
  treeset_delete(ts);
  datacont_delete(dcb);

  return retval;
}


static int treeset_height_tests()
{
  int retval = 0;

  treeset* ts = treeset_new();
  treeset_add(ts, datacont_new("A", CHAR, 1));
  treeset_add(ts, datacont_new("B", CHAR, 1));
  treeset_add(ts, datacont_new("C", CHAR, 1));

  /* TEST 1 */
  if (treeset_height(ts) != 3)
  {
    printf("TEST 1: treeset height should be 3.\n");
    retval = -1;
  }
  treeset_delete(ts);

  return retval;
}


int main()
{
  int retval = 0;

  printf("\ntreeset tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treeset_new_tests()...\n");
  if (treeset_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treeset_add_tests()...\n");
  if (treeset_add_tests()) retval - 1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treeset_remove_tests()...\n");
  if (treeset_remove_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treeset_contains_tests()...\n");
  if (treeset_contains_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");\

  printf("==-----------------------------------==\n");
  printf("Running treeset_height_tests()...\n");
  if (treeset_height_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");


  return retval;
}

