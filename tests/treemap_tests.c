

#include <stdio.h>

#include "../src/include/datacont.h"
#include "../src/include/listnode.h"
#include "../src/include/treemapnode.h"
#include "../src/include/treemap.h"


static int treemap_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  int one = 1;
  datacont* key = datacont_new(&one, INT, 1);
  datacont* val = datacont_new("A", CHAR, 1);

  treemap* tm = treemap_new();
  treemap_add(tm, key, val);

  if (tm->root->key != key)
  {
    printf("TEST 1: treemap root key contains unexpected datacont value.\n");
    retval = -1;
  }
  if (tm->root->value != val)
  {
    printf("TEST 1: treemap root value contains unexpected datacont value.\n");
    retval = -1;
  }
  if (tm->root->left != NULL)
  {
    printf("TEST 1: treemap root left should be NULL.\n");
    retval = -1;
  }
  if (tm->root->right != NULL)
  {
    printf("TEST 1: treemap root right should be NULL.\n");
    retval = -1;
  }
  treemap_delete(tm);

  return retval;
}


static int treemap_add_tests()
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
  
  if (treemap_add(tm, key1, val1))
  {
    printf("TEST 1: treemap_add() should return zero when adding a new pair.\n");
    retval = -1;
  }
  if (tm->root->left == NULL)
  {
    printf("TEST 1: expected treemap root left to be non-NULL.\n");
    retval = -1;
  }

  /* TEST 2 */
  if (treemap_add(tm, key3, val3))
  {
    printf("TEST 2: treemap_add() should return zero when adding a new pair.\b");
    retval = -1;
  }
  if (tm->root->right == NULL)
  {
    printf("TEST 2: expected treemap root->right to be non-NULL.\n");
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
    printf("TEST 1: Expected root->right node to be NULL.\n");
    retval = -1;
  }

  /* TEST 2 */
  if (treemap_remove(tm, key2) != 1)
  {
    printf("TEST 2: treemap_remove() should return 1 when removing not-present node key.\n");
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
    printf("TEST 3: Expected root->left node to be NULL.\n");
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

  treemap* tm = treemap_new();
  treemap_add(tm, key2, val2);
 
  datacont* val = treemap_get(tm, key2);
  if (datacont_compare(val, val2) != EQUAL)
  {
    printf("Unexpected datacont value: %c. Expected: %c.\n", val->c, val2->c);
    retval = -1;
  }
  
  datacont_delete(val);
  treemap_delete(tm);

  return retval;
}


static int treemap_getkeys_tests()
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

  listnode* keys = treemap_getkeys(tm);
  if (keys == NULL)
  {
    printf("TEST 1: treemap_getkeys() should not return NULL on not-empty treemap.\n");
    return -1; // can't continue
  }
  if (listnode_length(keys) != 3)
  {
    printf("TEST 1: unexpected listnode length: %d. Expected: 3.\n", listnode_length(keys));
    retval = -1;
  }
  if (keys->dc->i != 1)
  {
    printf("TEST 1: unexpected datacont value at 1st listnode: %d. Expected 1.\n", keys->dc->i);
    retval = -1;
  }

  keys = keys->next;
  if (keys == NULL)
  {
    printf("TEST 1: listnode missing 2nd item.\n");
    return -1; // can't continue
  }
  if (keys->dc->i != 2)
  {
    printf("TEST 1: unexpected datacont value at 2nd listnode: %d. Expected 2.\n", keys->dc->i);
    retval = -1;
  }

  keys = keys->next;
  if (keys == NULL)
  {
    printf("TEST 1: listnode missing 3rd item.\n");
    return -1; // can't continue
  }
  if (keys->dc->i != 3)
  {
    printf("TEST 1: unexpected datacont value at 3rd listnode: %d. Expected 3.\n", keys->dc->i);
    retval = -1;
  }

  treemap_delete(tm);
  listnode_delete(keys);

  return retval;
}


static int treemap_getvalues_tests()
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

  listnode* vals = treemap_getvalues(tm);
  if (vals == NULL)
  {
    printf("TEST 1: treemap_getvalues() should not return NULL on not-empty treemap.\n");
    return -1; // can't continue
  }
  if (listnode_length(vals) != 3)
  {
    printf("TEST 1: unexpected listnode length: %d. Expected: 3.\n", listnode_length(vals));
    retval = -1;
  }
  if (vals->dc->c != 'A')
  {
    printf("TEST 1: unexpected datacont value at 1st listnode: %c. Expected: A.\n", vals->dc->c);
    retval = -1;
  }

  vals = vals->next;
  if (vals == NULL)
  {
    printf("TEST 1: listnode missing 2nd item.\n");
    return -1; // can't continue
  }
  if (vals->dc->c != 'B')
  {
    printf("TEST 1: unexpected datacont value at 2nd listnode: %c. Expected B.\n", vals->dc->c);
    retval = -1;
  }

  vals = vals->next;
  if (vals == NULL)
  {
    printf("TEST 1: listnode missing 3rd item.\n");
    return -1; // can't continue
  }
  if (vals->dc->c != 'C')
  {
    printf("TEST 1: unexpected datacont value at 3rd listnode: %c. Expected C.\n", vals->dc->c);
    retval = -1;
  }

  treemap_delete(tm);
  listnode_delete(vals);

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
    printf("TEST 2: Unexpected treemap_count() return value: %d. Expected: 0.\n", count);
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
  printf("Running treemap_getkeys_tests()...\n");
  if (treemap_getkeys_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemap_getvalues_tests()...\n");
  if (treemap_getvalues_tests()) retval = -1;
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

  return retval;
}

