
#include <stdio.h>

#include "../src/include/hashset.h"


static int hashset_new_tests()
{
  int retval = 0;

  /* Test 1 */
  hashset* hs = hashset_new(100, 0x1234);
  if (hs->seed != 0x1234)
  {
    printf("TEST 1: hashset contains incorrect seed value: %llu. Expected: %llu.\n", hs->seed, (unsigned long long) 0x1234);
    retval = -1;
  }
  if (hs->num_buckets != 100)
  {
    printf("TEST 1: hashset contains incorrect num_buckets value %d. Expected %d.\n", hs->num_buckets, 0x1234);
    retval = -1;
  }
  hashset_delete(hs);

  return retval;
}


static int hashset_add_tests()
{
  int retval = 0;

  /* Test 1 */
  hashset* hs = hashset_new(100, 0x1234);
  if (hashset_add(hs, datacont_new("A", CHAR, 1)) != 0)
  {
    printf("TEST 1: hashset_add() should return 0 when adding a new item.\n");
    retval = -1;
  }

  /* Test 2 */
  if (hashset_add(hs, datacont_new("A", CHAR, 1)) != 1)
  {
    printf("TEST 2: hashset_add() should return 1 when trying to add an already present item.\n");
    retval = -1;
  }
  hashset_delete(hs);

  return retval;
}


static int hashset_remove_tests()
{
  int retval = 0;

  hashset* hs = hashset_new(10, 0x1234);
  datacont* dc = datacont_new("A", CHAR, 1);
  hashset_add(hs, dc);

  if (hashset_remove(hs, dc) != 0)
  {
    printf("TEST 1: hahset_remove() should return 0 when removing present datacont.\n");
    retval = -1;
  }
  hashset_delete(hs); 

  return retval;
}


static int hashset_contains_tests()
{
  int retval = 0;

  /* Test 1 */
  hashset* hs = hashset_new(100, 0x1234);
  datacont* dc = datacont_new("A", CHAR, 1);
  hashset_add(hs, dc);
  if (hashset_contains(hs, dc) == 0)
  {
    printf("TEST 1: hashset_contains() should return 1.\n");
    retval = -1;
  }
  hashset_delete(hs);

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

  printf("==-----------------------------------==\n");
  printf("Running hashset_contains_tests()...\n");
  if (hashset_contains_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

