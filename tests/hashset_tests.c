
#include <stdio.h>

#include <hashset.h>


static int hashset_new_tests()
{
  int retval = 0;

  /* Test 1 */
  hashset* hs = hashset_new(CHAR, 20);
  if (hs->type != CHAR)
  {
    printf("TEST 1: hashset contains incorrect datacont type value: %d. Expected: %d.\n", hs->type, CHAR);
    retval = -1;
  }
  if (hs->num_buckets != 20)
  {
    printf("TEST 1: hashset contains incorrect num_buckets value %d. Expected 20.\n", hs->num_buckets);
    retval = -1;
  }
  hashset_delete(hs);

  return retval;
}


static int hashset_add_tests()
{
  int retval = 0;

  /* Test 1 */
  hashset* hs = hashset_new(CHAR, 30);
  datacont* dcA = datacont_new("A", CHAR, 1);
  int num = 1;
  datacont* dc1 = datacont_new(&num, INT, 1);

  if (hashset_add(hs, datacont_copy(dcA)) != 0)
  {
    printf("TEST 1: hashset_add() should return 0 when adding a new item.\n");
    retval = -1;
  }

  /* Test 2 */
  if (hashset_add(hs, dcA) != 1)
  {
    printf("TEST 2: hashset_add() should return 1 when trying to add an already present item.\n");
    retval = -1;
  }

  /* TEST 3 */
  if (hashset_add(hs, dc1) != -1)
  {
    printf("TEST 3: hashset_add() should return -1 when adding datacont that is of a different type.\n");
    retval = -1;
  }

  /* TEST 4 */
  if (hashset_add(NULL, NULL) != -1)
  {
    printf("TEST 4: hashset_add() should return -1 when params are NULL.\n");
    retval = -1;
  }

  hashset_delete(hs);
  datacont_delete(dcA);
  datacont_delete(dc1);

  return retval;
}


static int hashset_remove_tests()
{
  int retval = 0;

  hashset* hs = hashset_new(CHAR, 10);
  datacont* dc = datacont_new("A", CHAR, 1);
  hashset_add(hs, datacont_copy(dc));


  /* TEST 1 */
  if (hashset_remove(hs, dc) != 0)
  {
    printf("TEST 1: hahset_remove() should return 0 when removing present datacont.\n");
    retval = -1;
  }

  /* TEST 2 */
  if (hashset_remove(hs, dc) != -1)
  {
    printf("TEST 2: hashset_remove() should return -1 when removing not-present datacont.\n");
    retval = -1;
  }

  /* TEST 3 */
  if (hashset_remove(hs, NULL) != -1)
  {
    printf("TEST 3: hashset_remove() should return -1 when params are NULL.\n");
    retval = -1;
  }

  datacont_delete(dc);
  hashset_delete(hs); 

  return retval;
}


static int hashset_contains_tests()
{
  int retval = 0;

  /* Test 1 */
  hashset* hs = hashset_new(CHAR, 10);
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  hashset_add(hs, datacont_copy(dcA));
  if (hashset_contains(hs, dcA) != 1)
  {
    printf("TEST 1: hashset_contains() should return 1.\n");
    retval = -1;
  }

  /* TEST 2 */
  if (hashset_contains(hs, dcB) != 0)
  {
    printf("TEST 2: hashset_contains() should return 0 on not present datacont.\n");
    retval = -1;
  } 

  datacont_delete(dcA);
  datacont_delete(dcB);
  hashset_delete(hs);

  return retval;
}


static int hashset_count_tests()
{
  int retval = 0;

  hashset* hs = hashset_new(CHAR, 10);
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  
  int count;

  /* TEST 1 */
  if ((count = hashset_count(hs)) != 0)
  {
    printf("TEST 1: Unexpected return value from hashset_count(): %d. Expected 0.\n", count);
    retval = -1;
  }

  /* TEST 2 */
  hashset_add(hs, dcA);
  if ((count = hashset_count(hs)) != 1)
  {
    printf("TEST 2: Unexpected return value from hashset_count(): %d. Expected 1.\n", count);
    retval = -1;
  }

  /* TEST 3 */
  hashset_add(hs, dcB);
  if ((count = hashset_count(hs)) != 2)
  {
    printf("TEST 3: Unexpected return value from hashset_count(): %d. Expected 2.\n", count);
    retval = -1;
  }  

  /* TEST 4 */
  if ((count = hashset_count(NULL)) != 0)
  {
    printf("TEST 4: Unexpected return value from hashset_count(): %d. Expected 0.\n", count);
    retval = -1;
  }

  hashset_delete(hs);

  return retval;
}


static int hashset_to_list_tests()
{
  int retval = 0;

  hashset* hs = hashset_new(CHAR, 10);
  datacont* dcC = datacont_new("C", CHAR, 1);
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);

  hashset_add(hs, dcC);
  hashset_add(hs, dcA);
  hashset_add(hs, dcB);

  /* TEST 1 */
  list* ls = hashset_to_list(hs);

  int len;
  if ((len = list_length(ls)) != 3)
  {
    printf("TEST 1: Unexpected list length: %d. Expected 3.\n", len);
    retval = -1;
  }

  if (list_index(ls, dcA) == -1)
  {
    printf("TEST 1: list should contain value 'A'.\n");
    retval = -1;
  }

  if (list_index(ls, dcB) == -1)
  {
    printf("TEST 1: list should contain value 'B'.\n");
    retval = -1;
  }

  if (list_index(ls, dcC) == -1)
  {
    printf("TEST 1: list should contains value 'C'.\n");
    retval = -1;
  }

  hashset_delete(hs);
  list_delete(ls);

  return retval;
}


int main()
{
  int retval = 0;

  printf("\nhashset tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running hashset_new_tests()...\n");
  if (hashset_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running hashset_add_tests()...\n");
  if (hashset_add_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n\n");
  printf("Running hashset_remove_tests()...\n");
  if (hashset_add_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running hashset_contains_tests()...\n");
  if (hashset_contains_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running hashset_count_tests()...\n");
  if (hashset_count_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running hashset_to_list_tests()...\n");
  if (hashset_to_list_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

