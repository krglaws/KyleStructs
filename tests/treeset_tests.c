
#include <stdio.h>

#include "../src/include/treeset.h"


static int treeset_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  
  treeset* ts = treeset_new();

  if (ts == NULL)
  {
    printf("TEST 1: Unexpected NULL value returned from treeset_new().\n");
    retval = -1;
  }

  if (ts->root)
  {
    printf("TEST 1: treeset should contain NULL 'root' treesetnode* values.\n");
    retval = -1;
  }
  treeset_delete(ts);

  return retval;
}


static int treeset_add_tests()
{
  int retval = 0;

  treeset* ts = treeset_new();
  datacont* dcB = datacont_new("B", CHAR, 2);

  /* Test 1 */
  int result;
  if ((result = treeset_add(ts, datacont_copy(dcB))) != 0)
  {
    printf("TEST 1: Unexpected return value from treeset_add(): %d. Expected: 0.\n", result);
    retval = -1;
  }
  
  /* TEST 2 */
  if ((result = treeset_add(ts, dcB)) != 1)
  {
    printf("TEST 2: Unexpected return value from treeset_add(): %d. Expected 1.\n", result);
    retval = -1;
  }

  /* TEST 3 */
  if ((result = treeset_add(NULL, NULL)) != -1)
  {
    printf("TEST 3: Unexpected return value from treeset_add(): %d. Expected -1.\n", result);
    retval = -1;
  }

  datacont_delete(dcB);
  treeset_delete(ts);

  return retval;
}


static int treeset_remove_by_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* dc = datacont_new("A", CHAR, 1);

  treeset* ts = treeset_new();
  treeset_add(ts, datacont_copy(dc));

  int result;
  if ((result = treeset_remove_by(ts, dc)) != 0)
  {
    printf("TEST 1: Unexpected return value from treeset_remove_by(): %d. Expected: 0.\n", result);
    retval = -1;
  }

  /* TEST 2 */
  if ((result = treeset_remove_by(ts, dc)) != -1)
  {
    printf("TEST 2: Unexpected return value from treeset_remove_by(): %d. Expected: -1.\n", result);
    retval = -1;
  }

  /* TEST 3 */
  if ((result = treeset_remove_by(NULL, NULL)) != -1)
  {
    printf("TEST 3: Unexpected return value from treeset_remove_by(): %d. Expected: -1.\n", result);
    retval = -1;
  }

  datacont_delete(dc);
  treeset_delete(ts);

  return retval;
}


static int treeset_remove_at_tests()
{
  int retval = 0;

  treeset* ts = treeset_new();
  treeset_add(ts, datacont_new("B", CHAR, 1));
  treeset_add(ts, datacont_new("A", CHAR, 1));
  treeset_add(ts, datacont_new("C", CHAR, 1));

  int result;

  /* TEST 1 */
  if ((result = treeset_remove_at(ts, 0)) != 0)
  {
    printf("TEST 1: Unexpected return value from treeset_remove_at(): %d. Expected: 0.\n", result);
    retval = -1;
  } 

  /* TEST 2 */
  if ((result = treeset_remove_at(ts, -6)) != -1)
  {
    printf("TEST 2: Unexpected return value from treeset_remove_at(): %d. Expected: -1.\n", result);
    retval = -1;
  }

  /* TEST 3 */
  if ((result = treeset_remove_at(NULL, 0)) != -1)
  {
    printf("TEST 3: Unexpected return value from treeset_remove_at(): %d. Expected: -1.\n", result);
    retval = -1;
  }

  treeset_delete(ts);

  return retval;
}


static int treeset_index_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  datacont* dcC = datacont_new("C", CHAR, 1);

  treeset* ts = treeset_new();
  treeset_add(ts, datacont_copy(dcB));
  treeset_add(ts, datacont_copy(dcA));
  treeset_add(ts, datacont_copy(dcC));

  int index;

  if ((index = treeset_index(ts, dcA)) != 0)
  {
    printf("TEST 1: Unexpected value returned from treeset_index(): %d. Expected: 0.\n", index);
    retval = -1;
  }

  /* TEST 2 */
  if ((index = treeset_index(ts, dcB)) != 1)
  {
    printf("TEST 2: Unexpected value returned from treeset_index(): %d. Expected: 1.\n", index);
    retval = -1;
  }

  /* TEST 3 */
  if ((index = treeset_index(ts, dcC)) != 2)
  {
    printf("TEST 3: Unexpected value returned from treeset_index(): %d. Expected: 2.\n", index);
    retval = -1;
  }

  if ((index = treeset_index(NULL, NULL)) != -1)
  {
    printf("TEST 4: Unexpected value returned from treeset_index(): %d. Expected: -1.\n", index);
    retval = -1;
  }

  datacont_delete(dcA);
  datacont_delete(dcB);
  datacont_delete(dcC);
  treeset_delete(ts);

  return retval;
}


static int treeset_contains_tests()
{
  int retval = 0;
  
  /* Test 1 */
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  datacont* dcC = datacont_new("C", CHAR, 1);
  datacont* dcZ = datacont_new("Z", CHAR, 1);

  treeset* ts = treeset_new();
  treeset_add(ts, dcB);
  treeset_add(ts, dcC);
  treeset_add(ts, dcA); 
 
  if (treeset_contains(ts, dcZ) == 1)
  {
    printf("TEST 1: treeset should not contain char value 'Z'.\n");
    retval = -1;
  }

  /* TEST 2 */
  if (treeset_contains(ts, dcA) == 0)
  {
    printf("TEST 2: treeset should contain char value 'A'.\n");
    retval = -1;
  }

  /* TEST 3 */
  if (treeset_contains(ts, NULL) != 0)
  {
    printf("TEST 3: treeset_contains() should return 0 on NULL params.\n");
    retval = -1;
  }

  datacont_delete(dcZ);
  treeset_delete(ts);

  return retval;
}


static int treeset_get_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  datacont* dcC = datacont_new("C", CHAR, 1);

  treeset* ts = treeset_new();
  treeset_add(ts, dcB);
  treeset_add(ts, dcC);
  treeset_add(ts, dcA); 
  
  datacont* get_dc = treeset_get(ts, -1);
  if (get_dc->c != 'C')
  {
    printf("TEST 1: Unexpected datacont value after treeset_get(): %c. Expected: C.\n", get_dc->c);
    retval = -1;
  }

  /* TEST 2 */
  get_dc = treeset_get(ts, 1);
  if (get_dc->c != 'B')
  {
    printf("TEST 2: Unexpected datacont value after treeset_get(): %c. Expected: B.\n", get_dc->c);
    retval = -1;
  }

  /* TEST 3 */
  get_dc = treeset_get(ts, 1234);
  if (get_dc != NULL)
  {
    printf("TEST 3: Unexpected datacont value after OOB treeset_get(): %c. Expected: NULL.\n", get_dc->c);
    retval = -1;
  }
  
  treeset_delete(ts);

  return retval;
}


static int treeset_count_tests()
{
  int retval = 0;

  /* Test 1 */
  treeset* ts = treeset_new();
  treeset_add(ts, datacont_new("B", CHAR, 1));
  treeset_add(ts, datacont_new("A", CHAR, 1));
  treeset_add(ts, datacont_new("C", CHAR, 1));

  unsigned int count = treeset_count(ts);
  if (count != 3)
  {
    printf("TEST 1: Unexpected value returned from treeset_count(): %d. Expected: 3.\n", count);
    retval = -1;
  }

  /* TEST 2 */
  treeset_add(ts, datacont_new("Z", CHAR, 1));
  count = treeset_count(ts);
  if (count != 4)
  {
    printf("TEST 2: Unexpected value returned from treeset_count(): %d. Expected 4.\n", count);
    retval = -1;
  }

  /* TEST 3 */
  count = treeset_count(NULL);
  if (count != 0)
  {
    printf("TEST 3: Unexpected value returned from treeset_count(): %d. Expected 0.\n", count);
    retval = -1;
  }

  treeset_delete(ts);

  return retval;
}


static int treeset_height_tests()
{
  int retval = 0;

  /* Test 1 */
  treeset* ts = treeset_new();
  treeset_new(ts, datacont_new("B", CHAR, 1));
  treeset_add(ts, datacont_new("A", CHAR, 1));
  treeset_add(ts, datacont_new("C", CHAR, 1));

  unsigned int height = treeset_height(ts);
  if (height != 2)
  {
    printf("TEST 1: Unexpected treeset height: %d. Expected: 2\n", height);
    retval = -1;
  }

  /* TEST 2 */
  height = treeset_height(NULL);
  if (height != 0)
  {
    printf("TEST 2: Unexpected result from treeset_height() on NULL param: %d. Expected: 0.\n", height);
    retval = -1;
  } 

  treeset_delete(ts);
  return retval;
}


static int treeset_balance_tests()
{
  int retval = 0;

  /* TEST 1 */
  char c = 'A';
  treeset* ts = treeset_new();
  
  for (int i = 0; i < 26; i++, c++)
    treeset_add(ts, datacont_new(&c, CHAR, 1));

  unsigned int height = treeset_height(ts);
  if (height != 26)
  {
    printf("TEST 1: treeset_height() should have returned 26. Can't continue, quitting test...\n");
    treeset_delete(ts);
    return -1;
  }

  treeset_balance(ts);
  height = treeset_height(ts);
  if (height != 5)
  {
    printf("TEST 1: Unexpected tree height after treeset_balance(): %d. Expected: 5.\n", height);
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
  if (treeset_add_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treeset_remove_by_tests()...\n");
  if (treeset_remove_by_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treeset_remove_at_tests()...\n");
  if (treeset_remove_at_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treesetnode_index_tests()...\n");
  if (treeset_index_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treeset_contains_tests()...\n");
  if (treeset_contains_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");
 
  printf("==-----------------------------------==\n");
  printf("Running treeset_get_tests()...\n");
  if (treeset_get_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treeset_count_tests()...\n");
  if (treeset_count_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treeset_height_tests()...\n");
  if (treeset_height_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treeset_balance_tests()...\n");
  if (treeset_balance_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

