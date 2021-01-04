#include <stdio.h>

#include <ks_types.h>
#include <ks_datacont.h>
#include <ks_listnode.h>
#include <ks_list.h>
#include <ks_treemapnode.h>
#include <ks_treemap.h>


static int ks_treemap_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_treemap* tm = ks_treemap_new();

  if (tm->root != NULL)
  {
    printf("TEST 1: ks_treemap->root should be NULL when empty.\n");
    retval = -1;
  }
  ks_treemap_delete(tm);

  return retval;
}


static int ks_treemap_copy_tests()
{
  int retval = 0;

  /* TEST 1 */
  ks_treemap* tm = ks_treemap_new();
  ks_treemap_add(tm, ks_datacont_new("B", KS_CHAR, 1), ks_datacont_new("B", KS_CHAR, 1));
  ks_treemap_add(tm, ks_datacont_new("C", KS_CHAR, 1), ks_datacont_new("C", KS_CHAR, 1));

  ks_treemap* tm_copy = ks_treemap_copy(tm);

  if (tm_copy == NULL)
  {
    printf("TEST 1: Unexpected NULL return from ks_treemap_copy()\n");
    return -1;
  }

  if (tm_copy->root->key->c != 'B')
  {
    printf("TEST 1: Unexpected ks_datacont value in ks_treemap_copy() result\n");
    retval = -1;
  }

  if (tm_copy->root->right->key->c != 'C')
  {
    printf("TEST 1: Unexpected ks_datacont value in ks_treemap_copy() result\n");
    retval = -1;
  }

  ks_treemap_delete(tm);
  ks_treemap_delete(tm_copy);

  return retval;
}


static int ks_treemap_add_tests()
{
  int retval = 0;

  /* TEST 1 */
  int two = 2;
  ks_datacont* key2 = ks_datacont_new(&two, KS_INT, 1);
  ks_datacont* val2 = ks_datacont_new("B", KS_CHAR, 1);

  int three = 3;
  ks_datacont* key3 = ks_datacont_new(&three, KS_INT, 1);
  ks_datacont* val3 = ks_datacont_new("C", KS_CHAR, 1);

  ks_datacont* val4 = ks_datacont_new("D", KS_CHAR, 1);

  ks_treemap* tm = ks_treemap_new();
  
  if (ks_treemap_add(tm, key2, val2))
  {
    printf("TEST 1: ks_treemap_add() should return zero when adding a new pair.\n");
    retval = -1;
  }
  if (tm->root->key->i != 2)
  {
    printf("TEST 1: Unexpected key ks_datacont at root node: %d. Expected: 2.\n", tm->root->key->i);
    retval = -1;
  }
  if (tm->root->value->c != 'B')
  {
    printf("TEST 1: Unexpected value ks_datacont at root node: %d. Expected B.\n", tm->root->value->c);
    retval = -1;
  }

  /* TEST 2 */
  if (ks_treemap_add(tm, key3, val3))
  {
    printf("TEST 2: ks_treemap_add() should return zero when adding a new pair.\n");
    retval = -1;
  }
  if (tm->root->right == NULL)
  {
    printf("TEST 2: expected root->right to be non-NULL.\n");
    retval = -1;
  }

  /* TEST 3 */
  if (ks_treemap_add(tm, ks_datacont_copy(key2), val4) != 1)
  {
    printf("TEST 3: ks_treemap_add() should return 1 when replacing existing pair.\n");
    retval = -1;
  }
  if (tm->root->value->c != 'D')
  {
    printf("TEST 3: Unexpected root node value: %c. Expected: D.\n", tm->root->value->c);
    retval = -1;
  }

  /* TEST 4 */
  if (ks_treemap_add(NULL, NULL, NULL) != -1)
  {
    printf("TEST 4: ks_treemap_add() should return -1 when params are NULL.\n");
    retval = -1;
  }

  ks_treemap_delete(tm);

  return retval;
}


static int ks_treemap_remove_tests()
{
  int retval = 0;

  /* TEST 1 */
  int one = 1;
  ks_datacont* key1 = ks_datacont_new(&one, KS_INT, 1);
  ks_datacont* val1 = ks_datacont_new("A", KS_CHAR, 1);

  int two = 2;
  ks_datacont* key2 = ks_datacont_new(&two, KS_INT, 1);
  ks_datacont* val2 = ks_datacont_new("B", KS_CHAR, 1);

  int three = 3;
  ks_datacont* key3 = ks_datacont_new(&three, KS_INT, 1);
  ks_datacont* val3 = ks_datacont_new("C", KS_CHAR, 1);

  ks_treemap* tm = ks_treemap_new();
  
  ks_treemap_add(tm, key2, val2);
  key2 = ks_datacont_copy(key2);

  ks_treemap_add(tm, key1, val1);
  key1 = ks_datacont_copy(key1);

  ks_treemap_add(tm, key3, val3);
  key3 = ks_datacont_copy(key3);

  if (ks_treemap_remove(tm, key2))
  {
    printf("TEST 1: Failed to remove root node from ks_treemap.\n");
    retval = -1;
  }
  if (tm->root->key->i != 3)
  {
    printf("TEST 1: Unexpected root key value: %d. Expected: 3.\n", tm->root->key->i);
    retval = -1;
  }
  if (tm->root->right != NULL)
  {
    printf("TEST 1: Expected right node to be NULL.\n");
    retval = -1;
  }

  /* TEST 2 */
  if (ks_treemap_remove(tm, key2) != -1)
  {
    printf("TEST 2: ks_treemap_remove() should return -1 when removing not-present node key.\n");
    retval = -1;
  }

  /* TEST 3 */
  if (ks_treemap_remove(tm, key1))
  {
    printf("TEST 3: Failed to remove left node from ks_treemap.\n");
    retval = -1;
  }
  if (tm->root->left != NULL)
  {
    printf("TEST 3: Expected left node to be NULL.\n");
    retval = -1;
  }

  /* TEST 4 */
  if (ks_treemap_remove(tm, key3))
  {
    printf("TEST 4: failed to remove last node in ks_treemap.\n");
    retval = -1;
  }
  if (tm->root != NULL)
  {
    printf("TEST 4: Expected root node to be NULL after last ks_treemap_remove().\n");
    retval = -1;
  }

  ks_datacont_delete(key1);
  ks_datacont_delete(key2);
  ks_datacont_delete(key3);

  ks_treemap_delete(tm);

  return retval;
}


static int ks_treemap_get_tests()
{
  int retval = 0;

  /* TEST 1 */
  int one = 1;
  ks_datacont* key1 = ks_datacont_new(&one, KS_INT, 1);
  ks_datacont* val1 = ks_datacont_new("A", KS_CHAR, 1);

  int two = 2;
  ks_datacont* key2 = ks_datacont_new(&two, KS_INT, 1);
  ks_datacont* val2 = ks_datacont_new("B", KS_CHAR, 1);

  int three = 3;
  ks_datacont* key3 = ks_datacont_new(&three, KS_INT, 1);
  ks_datacont* val3 = ks_datacont_new("C", KS_CHAR, 1);

  int four = 4;
  ks_datacont* not_there = ks_datacont_new(&four, KS_INT, 1);

  ks_treemap* tm = ks_treemap_new();
  ks_treemap_add(tm, key2, val2);
  ks_treemap_add(tm, key1, val1);
  ks_treemap_add(tm, key3, val3);
  
  ks_datacont* val = ks_treemap_get(tm, key2);
  if (val->c != val2->c)
  {
    printf("TEST 1: Unexpected ks_datacont value: %c. Expected: %c.\n", val->c, val2->c);
    retval = -1;
  }

  /* TEST 2 */
  val = ks_treemap_get(tm, key1);
  if (val->c != val1->c)
  {
    printf("TEST 2: Unexpected ks_datacont value: %c. Expected: %c.\n", val->c, val1->c);
    retval = -1;
  }

  /* TEST 3 */
  val = ks_treemap_get(tm, not_there);
  if (val != NULL)
  {
    printf("TEST 3: ks_treemapnode_get() should return NULL on not-present key value.\n");
    retval = -1;
  }

  ks_treemap_delete(tm);
  ks_datacont_delete(not_there);

  return retval;
}


static int ks_treemap_get_key_tests()
{
  int retval = 0;

  /* TEST 1 */
  int one = 1;
  ks_datacont* key1 = ks_datacont_new(&one, KS_INT, 1);
  ks_datacont* val1 = ks_datacont_new("A", KS_CHAR, 1);

  int two = 2;
  ks_datacont* key2 = ks_datacont_new(&two, KS_INT, 1);
  ks_datacont* val2 = ks_datacont_new("B", KS_CHAR, 1);

  int three = 3;
  ks_datacont* key3 = ks_datacont_new(&three, KS_INT, 1);
  ks_datacont* val3 = ks_datacont_new("C", KS_CHAR, 1);

  ks_treemap* tm = ks_treemap_new();
  ks_treemap_add(tm, key2, val2);
  ks_treemap_add(tm, key1, val1);
  ks_treemap_add(tm, key3, val3);
 
  ks_datacont* get_dc = ks_treemap_get_key(tm, 0);
  if (get_dc->i != 1)
  {
    printf("TEST 1: Unexpected ks_datacont value: %d. Expected 1.\n", get_dc->i);
    retval = -1;
  }

  /* TEST 2 */
  get_dc = ks_treemap_get_key(tm, 1);
  if (get_dc->i != 2)
  {
    printf("TEST 2: Unexpected ks_datacont value: %d. Expected 2.\n", get_dc->i);
    retval = -1;
  }

  /* TEST 3 */
  get_dc = ks_treemap_get_key(tm, 2);
  if (get_dc->i != 3)
  {
    printf("TEST 3: Unexpected ks_datacont value: %d. Expected 3.\n", get_dc->i);
    retval = -1;
  }

  /* TEST 4 */
  get_dc = ks_treemap_get_key(tm, 3);
  if (get_dc != NULL)
  {
    printf("TEST 4: Expected OOB call to ks_treemap_get_key() to return NULL.\n");
    retval = -1;
  }

  ks_treemap_delete(tm);

  return retval;
}


static int ks_treemap_count_tests()
{
  int retval = 0;

  /* TEST 1 */
  int one = 1;
  ks_datacont* key1 = ks_datacont_new(&one, KS_INT, 1);
  ks_datacont* val1 = ks_datacont_new("A", KS_CHAR, 1);

  int two = 2;
  ks_datacont* key2 = ks_datacont_new(&two, KS_INT, 1);
  ks_datacont* val2 = ks_datacont_new("B", KS_CHAR, 1);

  int three = 3;
  ks_datacont* key3 = ks_datacont_new(&three, KS_INT, 1);
  ks_datacont* val3 = ks_datacont_new("C", KS_CHAR, 1);

  int four = 4;
  ks_datacont* key4 = ks_datacont_new(&four, KS_INT, 1);
  ks_datacont* val4 = ks_datacont_new("D", KS_CHAR, 1);

  ks_treemap* tm = ks_treemap_new();
  ks_treemap_add(tm, key2, val2);
  ks_treemap_add(tm, key1, val1);
  ks_treemap_add(tm, key3, val3);
  ks_treemap_add(tm, key4, val4);

  int count = ks_treemap_count(tm);
  if (count != 4)
  {
    printf("TEST 1: Unexpected ks_treemap_count() return value: %d. Expected: 4.\n", count);
    retval = -1;
  }

  /* TEST 2 */
  count = ks_treemap_count(NULL);
  if (count != 0)
  {
    printf("TEST 2: Unexpected ks_treemap_count() return value: %d. Expected: 4.\n", count);
    retval = -1;
  }

  ks_treemap_delete(tm);

  return retval;
}


static int ks_treemap_height_tests()
{
  int retval = 0;

  /* TEST 1 */
  int one = 1;
  ks_datacont* key1 = ks_datacont_new(&one, KS_INT, 1);
  ks_datacont* val1 = ks_datacont_new("A", KS_CHAR, 1);

  int two = 2;
  ks_datacont* key2 = ks_datacont_new(&two, KS_INT, 1);
  ks_datacont* val2 = ks_datacont_new("B", KS_CHAR, 1);

  int three = 3;
  ks_datacont* key3 = ks_datacont_new(&three, KS_INT, 1);
  ks_datacont* val3 = ks_datacont_new("C", KS_CHAR, 1);

  int four = 4;
  ks_datacont* key4 = ks_datacont_new(&four, KS_INT, 1);
  ks_datacont* val4 = ks_datacont_new("D", KS_CHAR, 1);

  ks_treemap* tm = ks_treemap_new();
  ks_treemap_add(tm, key2, val2);
  ks_treemap_add(tm, key1, val1);
  ks_treemap_add(tm, key3, val3);
  ks_treemap_add(tm, key4, val4);

  int height = ks_treemap_height(tm);
  if (height != 3)
  {
    printf("TEST 1: Unexpected ks_treemap_height() return value: %d. Expected: 3.\n", height);
    retval = -1;
  }
 
  /* TEST 2 */
  height = ks_treemap_height(NULL);
  if (height != 0)
  {
    printf("TEST 2: Unexpected ks_treemap_height() return value: %d. Expected: 0.\n", height);
    retval = -1; 
  }

  ks_treemap_delete(tm);

  return retval;
}


static int ks_treemap_balance_tests()
{
  int retval = 0;

  /* TEST 1 */
  char c = 'A';
  int i = 0;
  ks_treemap* tm = ks_treemap_new();
  ks_treemap_add(tm, ks_datacont_new(&i, KS_INT, 1), 
                  ks_datacont_new(&c, KS_CHAR, 1));

  for (int i = 0; i < 26; i++, c++)
    ks_treemap_add(tm, ks_datacont_new(&i, KS_INT, 1), 
                     ks_datacont_new(&c, KS_CHAR, 1));

  unsigned int height = ks_treemap_height(tm);
  if (height != 26)
  {
    printf("TEST 1: ks_treemap_height() should have returned 26. Can't continue, quitting test...\n");
    ks_treemap_delete(tm);
    return -1;
  }

  ks_treemap_balance(tm);
  height = ks_treemap_height(tm);
  if (height != 5)
  {
    printf("TEST 1: Unexpected tree height after ks_treemap_balance(): %d. Expected: 5.\n", height);
    retval = -1;
  }

  ks_treemap_delete(tm);

  return retval;
}


int main()
{
  int retval = 0;

  printf("\nks_treemap tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treemap_new_tests()...\n");
  if (ks_treemap_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treemap_copy_tests()...\n");
  if (ks_treemap_copy_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treemap_add_tests()...\n");
  if (ks_treemap_add_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treemap_remove_tests()...\n");
  if (ks_treemap_remove_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treemap_get_tests()...\n");
  if (ks_treemap_get_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treemap_get_key_tests()...\n");
  if (ks_treemap_get_key_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treemap_count_tests()...\n");
  if (ks_treemap_count_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treemap_height_tests()...\n");
  if (ks_treemap_height_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treemap_balance_tests()...\n");
  if (ks_treemap_balance_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

