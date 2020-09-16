
#include <stdio.h>

#include "../src/include/hashmap.h"


static int hashmap_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  hashmap* hm = hashmap_new(INT, 10);

  if (hm->type != INT)
  {
    printf("TEST 1: Unexpected type value: %d. Expected %d.\n", hm->type, INT);
    retval = -1;
  }

  if (hm->num_buckets != 10)
  {
    printf("TEST 1: Unexpected num_buckets value: %d. Expected: 10.\n", hm->num_buckets);
    retval = -1;
  }
  hashmap_delete(hm);

  return retval;
}


static int hashmap_add_tests()
{
  int retval = 0;

  /* TEST 1 */
  hashmap* hm = hashmap_new(INT, 10);
  
  int one = 1;
  datacont* key = datacont_new(&one, INT, 1);
  datacont* val = datacont_new("A", CHAR, 1);
  datacont* key_copy = datacont_copy(key);
  datacont* val2 = datacont_new("C", CHAR, 1);

  if (hashmap_add(hm, key, val) != 0)
  {
    printf("TEST 1: hashmap_add() should return 0 when adding a new pair.\n");
    retval = -1;
  }
  
  /* TEST 2 */
  if (hashmap_add(hm, key_copy, val2) != 1)
  {
    printf("TEST 2: hashmap_add() should return 1 when replacing an existing pair.\n");
    retval = -1;
  }

  hashmap_delete(hm);

  return retval;
}


static int hashmap_remove_tests()
{
  int retval = 0;

  /* TEST 1 */
  hashmap* hm = hashmap_new(INT, 20);

  int one = 1;
  datacont* key = datacont_new(&one, INT, 1);
  datacont* key_copy = datacont_copy(key);
  datacont* val = datacont_new("A", CHAR, 1);

  hashmap_add(hm, key, val);

  if (hashmap_remove(hm, key) != 0)
  {
    printf("TEST 1: hashmap_remove() should return 0 on removal of existing pair.\n");
    retval = -1;
  }
  if (hashmap_remove(hm, key_copy) != -1)
  {
    printf("TEST 2: hashmap_remove() should return -1 when removing not-present pair.\n");
    retval = -1;
  }

  datacont_delete(key_copy);
  hashmap_delete(hm);

  return retval;
}


static int hashmap_get_tests()
{
  int retval = 0;

  /* TEST 1 */
  hashmap* hm = hashmap_new(INT, 10);
  
  int one = 1;
  datacont* key = datacont_new(&one, INT, 1);
  datacont* val = datacont_new("A", CHAR, 1);

  hashmap_add(hm, key, val);

  datacont* ret = hashmap_get(hm, key);
  if (datacont_compare(val, ret) != EQUAL)
  {
    printf("TEST 1: unexpected datacont value: %c. Expected: A.\n", ret->c);
    retval = -1;
  }

  hashmap_delete(hm);

  return retval;
}


static int hashmap_keys_tests()
{
  int retval = 0;

  /* TEST 1 */
  hashmap* hm = hashmap_new(INT, 10);

  int one = 1;
  hashmap_add(hm, datacont_new(&one, INT, 1), datacont_new("A", CHAR, 1));

  list* ls = hashmap_keys(hm);
  if (ls->head->dc->i != 1)
  {
    printf("TEST 1: Unexpected listnode item value: %d. Expected 1.\n", ls->head->dc->i);
    retval = -1;
  }

  list_delete(ls);
  hashmap_delete(hm);

  return retval;
}


static int hashmap_values_tests()
{
  int retval = 0;

  /* TEST 1 */
  hashmap* hm = hashmap_new(INT, 10);

  int one = 1;
  hashmap_add(hm, datacont_new(&one, INT, 1), datacont_new("A", CHAR, 1));

  list* ls = hashmap_values(hm);
  if (ls->head->dc->c != 'A')
  {
    printf("TEST 1: Unexpected listnode item value: %c. Expected 'A'.\n", ls->head->dc->c);
    retval = -1;
  }

  list_delete(ls);
  hashmap_delete(hm);

  return retval;
}


static int hashmap_count_tests()
{
  int retval = 0;

  /* TEST 1 */
  hashmap* hm = hashmap_new(INT, 10);

  int one = 1;
  hashmap_add(hm, datacont_new(&one, INT, 1), datacont_new("A", CHAR, 1));

  int count = hashmap_count(hm);
  if (count != 1)
  {
    printf("TEST 1: Unexpected hashmap_count() return value: %d. Expected 1.\n", count);
    retval = -1;
  }

  hashmap_delete(hm);

  return retval;
}


int main()
{
  int retval = 0;

  printf("\nhashmap tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running hashmap_new_tests()...\n");
  if (hashmap_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running hashmap_add_tests()...\n");
  if (hashmap_add_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running hashmap_remove_tests()...\n");
  if (hashmap_remove_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running hashmap_get_tests()...\n");
  if (hashmap_get_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running hashmap_keys_tests()...\n");
  if (hashmap_keys_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running hashmap_getvals_tests()...\n");
  if (hashmap_values_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");
  
  printf("==-----------------------------------==\n");
  printf("Running hashmap_count_tests()...\n");
  if (hashmap_count_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

