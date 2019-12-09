
#include <stdio.h>

#include "../src/include/treemap.h"


static int treemap_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  treemap* tm = treemap_new();

  if (tm->root != NULL)
  {
    printf("TEST 1: treemap->root should be NULL when empty.\n");
    retval = -1;
  }
  treemap_delete(tm);

  return retval;
}


static int treemap_add_tests()
{
  int retval = 0;

  /* TEST 1 */
  int two = 2;
  datacont* key2 = datacont_new(&two, INT, 1);
  datacont* val2 = datacont_new("B", CHAR, 1);

  int three = 3;
  datacont* key3 = datacont_new(&three, INT, 1);
  datacont* val3 = datacont_new("C", CHAR, 1);
  datacont* val4 = datacont_new("D", CHAR, 1);

  treemap* tm = treemap_new();
  
  if (treemap_add(tm, key2, val2))
  {
    printf("TEST 1: treemap_add() should return zero when adding a new pair.\n");
    retval = -1;
  }
  if (tm->root->key->i != 2)
  {
    printf("TEST 1: Unexpected key datacont at root node: %d. Expected: 2.\n", tm->root->key->i);
    retval = -1;
  }
  if (tm->root->value->c != 'B')
  {
    printf("TEST 1: Unexpected value datacont at root node: %d. Expected B.\n", tm->root->value->c);
    retval = -1;
  }

  /* TEST 2 */
  if (treemap_add(tm, key3, val3))
  {
    printf("TEST 2: treemap_add() should return zero when adding a new pair.\n");
    retval = -1;
  }
  if (tm->root->right == NULL)
  {
    printf("TEST 2: expected root->right to be non-NULL.\n");
    retval = -1;
  }

  /* TEST 3 */
  if (treemap_add(tm, key2, val4) != 1)
  {
    printf("TEST 3: treemap_add() should return 1 when replacing existing pair.\n");
    retval = -1;
  }
  if (tm->root->value->c != 'D')
  {
    printf("TEST 3: Unexpected root node value: %c. Expected: D.\n", tm->root->value->c);
    retval = -1;
  }

  /* TEST 4 */
  if (treemap_add(NULL, NULL, NULL) != -1)
  {
    printf("TEST 4: treemap_add() should return -1 when params are NULL.\n");
    retval = -1;
  }

  treemap_delete(tm);

  return retval;
}


static int treemap_remove_tests()
{
  int retval = 0;

  /* TEST 1 */
  int one = 1;
  datacont* key1 = datacont_new(&one, INT, 1);
  datacont* val1 = datacont_new("A", CHAR, 1);

  int two = 2;
  datacont* key2 = datacont_new(&two, INT, 1);
  datacont* val2 = datacont_new("B", CHAR, 1);

  int three = 3;
  datacont* key3 = datacont_new(&three, INT, 1);
  datacont* val3 = datacont_new("C", CHAR, 1);

  treemap* tm = treemap_new();
  
  treemap_add(tm, key2, val2);
  key2 = datacont_copy(key2);

  treemap_add(tm, key1, val1);
  key1 = datacont_copy(key1);

  treemap_add(tm, key3, val3);
  key3 = datacont_copy(key3);

  if (treemap_remove(tm, key2))
  {
    printf("TEST 1: Failed to remove root node from treemap.\n");
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
  if (treemap_remove(tm, key2) != -1)
  {
    printf("TEST 2: treemap_remove() should return -1 when removing not-present node key.\n");
    retval = -1;
  }

  /* TEST 3 */
  if (treemap_remove(tm, key1))
  {
    printf("TEST 3: Failed to remove left node from treemap.\n");
    retval = -1;
  }
  if (tm->root->left != NULL)
  {
    printf("TEST 3: Expected left node to be NULL.\n");
    retval = -1;
  }

  /* TEST 4 */
  if (treemap_remove(tm, key3))
  {
    printf("TEST 4: failed to remove last node in treemap.\n");
    retval = -1;
  }
  if (tm->root != NULL)
  {
    printf("TEST 4: Expected root node to be NULL after last treemap_remove().\n");
    retval = -1;
  }

  datacont_delete(key1);
  datacont_delete(key2);
  datacont_delete(key3);

  treemap_delete(tm);

  return retval;
}


static int treemap_get_tests()
{
  int retval = 0;

  /* TEST 1 */
  int one = 1;
  datacont* key1 = datacont_new(&one, INT, 1);
  datacont* val1 = datacont_new("A", CHAR, 1);

  int two = 2;
  datacont* key2 = datacont_new(&two, INT, 1);
  datacont* val2 = datacont_new("B", CHAR, 1);

  int three = 3;
  datacont* key3 = datacont_new(&three, INT, 1);
  datacont* val3 = datacont_new("C", CHAR, 1);

  int four = 4;
  datacont* not_there = datacont_new(&four, INT, 1);

  treemap* tm = treemap_new();
  treemap_add(tm, key2, val2);
  treemap_add(tm, key1, val1);
  treemap_add(tm, key3, val3);
  
  datacont* val = treemap_get(tm, key2);
  if (val->c != val2->c)
  {
    printf("TEST 1: Unexpected datacont value: %c. Expected: %c.\n", val->c, val2->c);
    retval = -1;
  }

  /* TEST 2 */
  val = treemap_get(tm, key1);
  if (val->c != val1->c)
  {
    printf("TEST 2: Unexpected datacont value: %c. Expected: %c.\n", val->c, val1->c);
    retval = -1;
  }

  /* TEST 3 */
  val = treemap_get(tm, not_there);
  if (val != NULL)
  {
    printf("TEST 3: treemapnode_get() should return NULL on not-present key value.\n");
    retval = -1;
  }

  treemap_delete(tm);
  datacont_delete(not_there);

  return retval;
}


static int treemap_get_key_tests()
{
  int retval = 0;

  /* TEST 1 */
  int one = 1;
  datacont* key1 = datacont_new(&one, INT, 1);
  datacont* val1 = datacont_new("A", CHAR, 1);

  int two = 2;
  datacont* key2 = datacont_new(&two, INT, 1);
  datacont* val2 = datacont_new("B", CHAR, 1);

  int three = 3;
  datacont* key3 = datacont_new(&three, INT, 1);
  datacont* val3 = datacont_new("C", CHAR, 1);

  treemap* tm = treemap_new();
  treemap_add(tm, key2, val2);
  treemap_add(tm, key1, val1);
  treemap_add(tm, key3, val3);
 
  datacont* get_dc = treemap_get_key(tm, 0);
  if (get_dc->i != 1)
  {
    printf("TEST 1: Unexpected datacont value: %d. Expected 1.\n", get_dc->i);
    retval = -1;
  }

  /* TEST 2 */
  get_dc = treemap_get_key(tm, 1);
  if (get_dc->i != 2)
  {
    printf("TEST 2: Unexpected datacont value: %d. Expected 2.\n", get_dc->i);
    retval = -1;
  }

  /* TEST 3 */
  get_dc = treemap_get_key(tm, 2);
  if (get_dc->i != 3)
  {
    printf("TEST 3: Unexpected datacont value: %d. Expected 3.\n", get_dc->i);
    retval = -1;
  }

  /* TEST 4 */
  get_dc = treemap_get_key(tm, 3);
  if (get_dc != NULL)
  {
    printf("TEST 4: Expected OOB call to treemap_get_key() to return NULL.\n");
    retval = -1;
  }

  treemap_delete(tm);

  return retval;
}


static int treemap_keys_tests()
{
  int retval = 0;

  /* TEST 1 */
  int one = 1;
  datacont* key1 = datacont_new(&one, INT, 1);
  datacont* val1 = datacont_new("A", CHAR, 1);

  int two = 2;
  datacont* key2 = datacont_new(&two, INT, 1);
  datacont* val2 = datacont_new("B", CHAR, 1);

  int three = 3;
  datacont* key3 = datacont_new(&three, INT, 1);
  datacont* val3 = datacont_new("C", CHAR, 1);

  treemap* tm = treemap_new();
  treemap_add(tm, key2, val2);
  treemap_add(tm, key1, val1);
  treemap_add(tm, key3, val3);

  list* keys = treemap_keys(tm);
  if (keys == NULL)
  {
    printf("TEST 1: treemap_keys() should not return NULL on not-empty treemap.\n");
    return -1; // can't continue
  }
  if (list_length(keys) != 3)
  {
    printf("TEST 1: unexpected list length: %d. Expected: 3.\n", list_length(keys));
    retval = -1;
  }
  if (keys->head->dc->i != 1)
  {
    printf("TEST 1: unexpected datacont value at 1st listnode: %d. Expected 1.\n", keys->head->dc->i);
    retval = -1;
  }

  if (keys->head->next == NULL)
  {
    printf("TEST 1: listnode missing 2nd item.\n");
    return -1; // can't continue
  }
  if (keys->head->next->dc->i != 2)
  {
    printf("TEST 1: unexpected datacont value at 2nd listnode: %d. Expected 2.\n", keys->head->next->dc->i);
    retval = -1;
  }

  if (keys->head->next->next == NULL)
  {
    printf("TEST 1: listnode missing 3rd item.\n");
    return -1; // can't continue
  }
  if (keys->head->next->next->dc->i != 3)
  {
    printf("TEST 1: unexpected datacont value at 3rd listnode: %d. Expected 3.\n", keys->head->next->next->dc->i);
    retval = -1;
  }

  treemap_delete(tm);
  list_delete(keys);

  return retval;
}


static int treemap_values_tests()
{
  int retval = 0;

  /* TEST 1 */
  int one = 1;
  datacont* key1 = datacont_new(&one, INT, 1);
  datacont* val1 = datacont_new("A", CHAR, 1);

  int two = 2;
  datacont* key2 = datacont_new(&two, INT, 1);
  datacont* val2 = datacont_new("B", CHAR, 1);

  int three = 3;
  datacont* key3 = datacont_new(&three, INT, 1);
  datacont* val3 = datacont_new("C", CHAR, 1);

  treemap* tm = treemap_new();
  treemap_add(tm, key2, val2);
  treemap_add(tm, key1, val1);
  treemap_add(tm, key3, val3);

  list* vals = treemap_values(tm);
  if (vals == NULL)
  {
    printf("TEST 1: treemap_values() should not return NULL on non-empty treemap.\n");
    return -1; // can't continue
  }
  if (list_length(vals) != 3)
  {
    printf("TEST 1: unexpected list length: %d. Expected: 3.\n", list_length(vals));
    retval = -1;
  }
  if (vals->head->dc->c != 'A')
  {
    printf("TEST 1: unexpected datacont value at 1st listnode: %c. Expected: A.\n", vals->head->dc->c);
    retval = -1;
  }

  if (vals->head->next == NULL)
  {
    printf("TEST 1: list missing 2nd item.\n");
    return -1; // can't continue
  }
  if (vals->head->next->dc->c != 'B')
  {
    printf("TEST 1: unexpected datacont value at 2nd listnode: %c. Expected B.\n", vals->head->next->dc->c);
    retval = -1;
  }

  if (vals->head->next->next == NULL)
  {
    printf("TEST 1: list missing 3rd item.\n");
    return -1; // can't continue
  }
  if (vals->head->next->next->dc->c != 'C')
  {
    printf("TEST 1: unexpected datacont value at 3rd listnode: %c. Expected C.\n", vals->head->next->next->dc->c);
    retval = -1;
  }

  treemap_delete(tm);
  list_delete(vals);

  return retval;
}


static int treemap_count_tests()
{
  int retval = 0;

  /* TEST 1 */
  int one = 1;
  datacont* key1 = datacont_new(&one, INT, 1);
  datacont* val1 = datacont_new("A", CHAR, 1);

  int two = 2;
  datacont* key2 = datacont_new(&two, INT, 1);
  datacont* val2 = datacont_new("B", CHAR, 1);

  int three = 3;
  datacont* key3 = datacont_new(&three, INT, 1);
  datacont* val3 = datacont_new("C", CHAR, 1);

  int four = 4;
  datacont* key4 = datacont_new(&four, INT, 1);
  datacont* val4 = datacont_new("D", CHAR, 1);

  treemap* tm = treemap_new();
  treemap_add(tm, key2, val2);
  treemap_add(tm, key1, val1);
  treemap_add(tm, key3, val3);
  treemap_add(tm, key4, val4);

  int count = treemap_count(tm);
  if (count != 4)
  {
    printf("TEST 1: Unexpected treemap_count() return value: %d. Expected: 4.\n", count);
    retval = -1;
  }

  /* TEST 2 */
  count = treemap_count(NULL);
  if (count != 0)
  {
    printf("TEST 2: Unexpected treemap_count() return value: %d. Expected: 4.\n", count);
    retval = -1;
  }

  treemap_delete(tm);

  return retval;
}


static int treemap_height_tests()
{
  int retval = 0;

  /* TEST 1 */
  int one = 1;
  datacont* key1 = datacont_new(&one, INT, 1);
  datacont* val1 = datacont_new("A", CHAR, 1);

  int two = 2;
  datacont* key2 = datacont_new(&two, INT, 1);
  datacont* val2 = datacont_new("B", CHAR, 1);

  int three = 3;
  datacont* key3 = datacont_new(&three, INT, 1);
  datacont* val3 = datacont_new("C", CHAR, 1);

  int four = 4;
  datacont* key4 = datacont_new(&four, INT, 1);
  datacont* val4 = datacont_new("D", CHAR, 1);

  treemap* tm = treemap_new();
  treemap_add(tm, key2, val2);
  treemap_add(tm, key1, val1);
  treemap_add(tm, key3, val3);
  treemap_add(tm, key4, val4);

  int height = treemap_height(tm);
  if (height != 3)
  {
    printf("TEST 1: Unexpected treemap_height() return value: %d. Expected: 3.\n", height);
    retval = -1;
  }
 
  /* TEST 2 */
  height = treemap_height(NULL);
  if (height != 0)
  {
    printf("TEST 2: Unexpected treemap_height() return value: %d. Expected: 0.\n", height);
    retval = -1; 
  }

  treemap_delete(tm);

  return retval;
}


static int treemap_balance_tests()
{
  int retval = 0;

  /* TEST 1 */
  char c = 'A';
  int i = 0;
  treemap* tm = treemap_new();
  treemap_add(tm, datacont_new(&i, INT, 1), 
                  datacont_new(&c, CHAR, 1));

  for (int i = 0; i < 26; i++, c++)
    treemap_add(tm, datacont_new(&i, INT, 1), 
                     datacont_new(&c, CHAR, 1));

  unsigned int height = treemap_height(tm);
  if (height != 26)
  {
    printf("TEST 1: treemap_height() should have returned 26. Can't continue, quitting test...\n");
    treemap_delete(tm);
    return -1;
  }

  treemap_balance(tm);
  height = treemap_height(tm);
  if (height != 5)
  {
    printf("TEST 1: Unexpected tree height after treemap_balance(): %d. Expected: 5.\n", height);
    retval = -1;
  }

  treemap_delete(tm);

  return retval;
}


int main()
{
  int retval = 0;

  printf("\ntreemap tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemap_new_tests()...\n");
  if (treemap_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemap_add_tests()...\n");
  if (treemap_add_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemap_remove_tests()...\n");
  if (treemap_remove_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemap_get_tests()...\n");
  if (treemap_get_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemap_get_key_tests()...\n");
  if (treemap_get_key_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemap_keys_tests()...\n");
  if (treemap_keys_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemap_values_tests()...\n");
  if (treemap_values_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemap_count_tests()...\n");
  if (treemap_count_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemap_height_tests()...\n");
  if (treemap_height_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemap_balance_tests()...\n");
  if (treemap_balance_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

