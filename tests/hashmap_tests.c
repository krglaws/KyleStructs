#include <stdio.h>

#include <ks_types.h>
#include <ks_datacont.h>
#include <ks_listnode.h>
#include <ks_list.h>
#include <ks_treemapnode.h>
#include <ks_treemap.h>
#include <ks_hashmap.h>


static int ks_hashmap_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_hashmap* hm = ks_hashmap_new(KS_INT, 10);

  if (hm->type != KS_INT)
  {
    printf("TEST 1: Unexpected type value: %d. Expected %d.\n", hm->type, KS_INT);
    retval = -1;
  }

  if (hm->num_buckets != 10)
  {
    printf("TEST 1: Unexpected num_buckets value: %d. Expected: 10.\n", hm->num_buckets);
    retval = -1;
  }
  ks_hashmap_delete(hm);

  return retval;
}


static int ks_hashmap_copy_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_hashmap* hm = ks_hashmap_new(KS_CHAR, 2);
  ks_hashmap_add(hm, ks_datacont_new("B", KS_CHAR, 1), ks_datacont_new("B", KS_CHAR, 1));

  ks_hashmap* hm_copy = ks_hashmap_copy(hm);

  if (hm_copy == NULL)
  {
    printf("TEST 1: Unexpected NULL return from ks_hashmap_copy() result\n");
    return -1;
  }

  if (hm_copy->buckets[0] != NULL)
  {
    if (hm_copy->buckets[0]->root->key->c != 'B')
    {
      printf("TEST 1: Unexpected ks_datacont value in ks_hashmap_copy() result\n");
      retval = -1;
    }
  }
  else if (hm_copy->buckets[1] != NULL)
  {
    if (hm_copy->buckets[1]->root->key->c != 'B')
    {
      printf("TEST 1: Unexpected ks_datacont value in ks_hashmap_copy() result\n");
      retval = -1;
    }
  }
  else
  {
    printf("TEST 1: Unexpected empty ks_hashmap after ks_hashmap_copy()\n");
    retval = -1;
  }

  ks_hashmap_delete(hm);
  ks_hashmap_delete(hm_copy);

  return retval;
}


static int ks_hashmap_add_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_hashmap* hm = ks_hashmap_new(KS_INT, 10);
  
  int one = 1;
  ks_datacont* key = ks_datacont_new(&one, KS_INT, 1);
  ks_datacont* val = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* key_copy = ks_datacont_copy(key);
  ks_datacont* val2 = ks_datacont_new("C", KS_CHAR, 1);

  if (ks_hashmap_add(hm, key, val) != 0)
  {
    printf("TEST 1: ks_hashmap_add() should return 0 when adding a new pair.\n");
    retval = -1;
  }
  
  /* TEST 2 */
  if (ks_hashmap_add(hm, key_copy, val2) != 1)
  {
    printf("TEST 2: ks_hashmap_add() should return 1 when replacing an existing pair.\n");
    retval = -1;
  }

  ks_hashmap_delete(hm);

  return retval;
}


static int ks_hashmap_remove_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_hashmap* hm = ks_hashmap_new(KS_INT, 20);

  int one = 1;
  ks_datacont* key = ks_datacont_new(&one, KS_INT, 1);
  ks_datacont* key_copy = ks_datacont_copy(key);
  ks_datacont* val = ks_datacont_new("A", KS_CHAR, 1);

  ks_hashmap_add(hm, key, val);

  if (ks_hashmap_remove(hm, key) != 0)
  {
    printf("TEST 1: ks_hashmap_remove() should return 0 on removal of existing pair.\n");
    retval = -1;
  }
  if (ks_hashmap_remove(hm, key_copy) != -1)
  {
    printf("TEST 2: ks_hashmap_remove() should return -1 when removing not-present pair.\n");
    retval = -1;
  }

  ks_datacont_delete(key_copy);
  ks_hashmap_delete(hm);

  return retval;
}


static int ks_hashmap_get_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_hashmap* hm = ks_hashmap_new(KS_INT, 10);
  
  int one = 1;
  ks_datacont* key = ks_datacont_new(&one, KS_INT, 1);
  ks_datacont* val = ks_datacont_new("A", KS_CHAR, 1);

  ks_hashmap_add(hm, key, val);

  const ks_datacont* ret = ks_hashmap_get(hm, key);
  if (ks_datacont_compare(val, ret) != KS_EQUAL)
  {
    printf("TEST 1: unexpected ks_datacont value: %c. Expected: A.\n", ret->c);
    retval = -1;
  }

  ks_hashmap_delete(hm);

  return retval;
}


static int ks_hashmap_get_key_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_hashmap* hm = ks_hashmap_new(KS_CHAR, 2);

  ks_treemap* tm0 = ks_treemap_new();
  ks_treemap_add(tm0, ks_datacont_new("B", KS_CHAR, 1), ks_datacont_new("B", KS_CHAR, 1));
  ks_treemap_add(tm0, ks_datacont_new("A", KS_CHAR, 1), ks_datacont_new("A", KS_CHAR, 1));
  ks_treemap_add(tm0, ks_datacont_new("C", KS_CHAR, 1), ks_datacont_new("C", KS_CHAR, 1));

  ks_treemap* tm1 = ks_treemap_new();
  ks_treemap_add(tm1, ks_datacont_new("E", KS_CHAR, 1), ks_datacont_new("E", KS_CHAR, 1));
  ks_treemap_add(tm1, ks_datacont_new("D", KS_CHAR, 1), ks_datacont_new("D", KS_CHAR, 1));
  ks_treemap_add(tm1, ks_datacont_new("F", KS_CHAR, 1), ks_datacont_new("F", KS_CHAR, 1));

  hm->buckets[0] = tm0;
  hm->buckets[1] = tm1;

  const ks_datacont* dc = ks_hashmap_get_key(hm, -1);
  if (dc->c != 'F')
  {
    printf("TEST 1: Unexpected ks_datacont value after ks_hashmap_get_key(): %c. Expected: 'F'\n", dc->c);
    retval = -1;
  }

  dc = ks_hashmap_get_key(hm, 5);
  if (dc->c != 'F')
  {
    printf("TEST 1: Unexpected ks_datacont value after ks_hashmap_get_key(): %c. Expected: 'F'\n", dc->c);
    retval = -1;
  }

  dc = ks_hashmap_get_key(hm, -3);
  if (dc->c != 'D')
  {
    printf("TEST 1: Unexpected ks_datacont value after ks_hashmap_get_key(): %c. Expected: 'D'\n", dc->c);
    retval = -1;
  }

  dc = ks_hashmap_get_key(hm, 3);
  if (dc->c != 'D')
  {
    printf("TEST 1: Unexpected ks_datacont value after ks_hashmap_get_key(): %c. Expected: 'D'\n", dc->c);
    retval = -1;
  }

  dc = ks_hashmap_get_key(hm, -4);
  if (dc->c != 'C')
  {
    printf("TEST 1: Unexpected ks_datacont value after ks_hashmap_get_key(): %c. Expected: 'C'\n", dc->c);
    retval = -1;
  }

  dc = ks_hashmap_get_key(hm, 2);
  if (dc->c != 'C')
  {
    printf("TEST 1: Unexpected ks_datacont value after ks_hashmap_get_key(): %c. Expected: 'C'\n", dc->c);
    retval = -1;
  }

  dc = ks_hashmap_get_key(hm, -6);
  if (dc->c != 'A')
  {
    printf("TEST 1: Unexpected ks_datacont value after ks_hashmap_get_key(): %c. Expected: 'A'\n", dc->c);
    retval = -1;
  }

  dc = ks_hashmap_get_key(hm, 0);
  if (dc->c != 'A')
  {
    printf("TEST 1: Unexpected ks_datacont value after ks_hashmap_get_key(): %c. Expected: 'A'\n", dc->c);
    retval = -1;
  }

  ks_hashmap_delete(hm);

  return retval;
}


static int ks_hashmap_count_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_hashmap* hm = ks_hashmap_new(KS_INT, 10);

  int one = 1;
  ks_hashmap_add(hm, ks_datacont_new(&one, KS_INT, 1), ks_datacont_new("A", KS_CHAR, 1));

  int count = ks_hashmap_count(hm);
  if (count != 1)
  {
    printf("TEST 1: Unexpected ks_hashmap_count() return value: %d. Expected 1.\n", count);
    retval = -1;
  }

  ks_hashmap_delete(hm);

  return retval;
}


int main()
{
  int retval = 0;

  printf("\nks_hashmap tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_hashmap_new_tests()...\n");
  if (ks_hashmap_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_hashmap_copy_tests()...\n");
  if (ks_hashmap_copy_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_hashmap_add_tests()...\n");
  if (ks_hashmap_add_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_hashmap_remove_tests()...\n");
  if (ks_hashmap_remove_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_hashmap_get_tests()...\n");
  if (ks_hashmap_get_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_hashmap_get_key_tests()...\n");
  if (ks_hashmap_get_key_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_hashmap_count_tests()...\n");
  if (ks_hashmap_count_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

