
#include <stdio.h>

#include "../src/include/datacont.h"
#include "../src/include/listnode.h"
#include "../src/include/treemapnode.h"


static int treemapnode_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  int one = 1;
  datacont* key = datacont_new(&one, INT, 1);
  datacont* val = datacont_new("A", CHAR, 1);

  treemapnode* tmn = treemapnode_new(key, val);
  if (tmn->key != key)
  {
    printf("TEST 1: treemapnode key contains unexpected datacont value.\n");
    retval = -1;
  }
  if (tmn->value != val)
  {
    printf("TEST 1: treemapnode value contains unexpected datacont value.\n");
    retval = -1;
  }
  if (tmn->left != NULL)
  {
    printf("TEST 1: treemapnode left should be NULL.\n");
    retval = -1;
  }
  if (tmn->right != NULL)
  {
    printf("TEST 1: treemapnode right should be NULL.\n");
    retval = -1;
  }
  treemapnode_delete(tmn);

  return retval;
}


static int treemapnode_add_tests()
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

  treemapnode* root = treemapnode_new(key2, val2);
  
  if (treemapnode_add(root, key1, val1))
  {
    printf("TEST 1: treemapnode_add() should return zero when adding a new pair.\n");
    retval = -1;
  }
  if (root->left == NULL)
  {
    printf("TEST 1: expected root->left to be non-NULL.\n");
    retval = -1;
  }

  /* TEST 2 */
  if (treemapnode_add(root, key3, val3))
  {
    printf("TEST 2: treemapnode_add() should return zero when adding a new pair.\b");
    retval = -1;
  }
  if (root->right == NULL)
  {
    printf("TEST 2: expected root->right to be non-NULL.\n");
    retval = -1;
  }

  treemapnode_delete(root);

  return retval;
}


static int treemapnode_remove_tests()
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

  treemapnode* root = treemapnode_new(key2, val2);
  key2 = datacont_copy(key2);

  treemapnode_add(root, key1, val1);
  key1 = datacont_copy(key1);

  treemapnode_add(root, key3, val3);
  key3 = datacont_copy(key3);

  if (treemapnode_remove(&root, key2))
  {
    printf("TEST 1: Failed to remove root node from treemapnode.\n");
    retval = -1;
  }
  if (root->key->i != 3)
  {
    printf("TEST 1: Unexpected root key value: %d. Expected: 3.\n", root->key->i);
    retval = -1;
  }
  if (root->right != NULL)
  {
    printf("TEST 1: Expected right node to be NULL.\n");
    retval = -1;
  }

  /* TEST 2 */
  if (treemapnode_remove(&root, key2) != 1)
  {
    printf("TEST 2: treemap_remove() should return 1 when removing not-present node key.\n");
    retval = -1;
  }

  /* TEST 3 */
  if (treemapnode_remove(&root, key1))
  {
    printf("TEST 3: Failed to remove left node from treemapnode.\n");
    retval = -1;
  }
  if (root->left != NULL)
  {
    printf("TEST 3: Expected left node to be NULL.\n");
    retval = -1;
  }

  /* TEST 4 */
  if (treemapnode_remove(&root, key3))
  {
    printf("TEST 4: failed to remove last node in treemapnode.\n");
    retval = -1;
  }
  if (root != NULL)
  {
    printf("TEST 4: Expected root node to be NULL after last treemap_remove().\n");
    retval = -1;
  }

  datacont_delete(key1);
  datacont_delete(key2);
  datacont_delete(key3);

  return retval;
}


static int treemapnode_get_tests()
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

  treemapnode* root = treemapnode_new(key2, val2);
  
  datacont* val = treemapnode_get(root, key2);
  if (val != val2)
  {
    printf("Unexpected datacont value: %c. Expected: %c.\n", val->c, val2->c);
    retval = -1;
  }
  
  treemapnode_delete(root);

  return retval;
}


static int treemapnode_getkeys_tests()
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

  treemapnode* root = treemapnode_new(key2, val2);
  treemapnode_add(root, key1, val1);
  treemapnode_add(root, key3, val3);

  listnode* keys = treemapnode_getkeys(root);
  if (keys == NULL)
  {
    printf("TEST 1: treemapnode_getkeys() should not return NULL on not-empty treemapnode.\n");
    return -1; // can't continue
  }
  if (listnode_length(keys) != 3)
  {
    printf("TEST 1: unexpected listnode length: %d. Expected: 3.\n", listnode_length(keys));
    retval = -1;
  }
  if (keys->item->i != 1)
  {
    printf("TEST 1: unexpected datacont value at 1st listnode: %d. Expected 1.\n", keys->item->i);
    retval = -1;
  }

  keys = keys->next;
  if (keys == NULL)
  {
    printf("TEST 1: listnode missing 2nd item.\n");
    return -1; // can't continue
  }
  if (keys->item->i != 2)
  {
    printf("TEST 1: unexpected datacont value at 2nd listnode: %d. Expected 2.\n", keys->item->i);
    retval = -1;
  }

  keys = keys->next;
  if (keys == NULL)
  {
    printf("TEST 1: listnode missing 3rd item.\n");
    return -1; // can't continue
  }
  if (keys->item->i != 3)
  {
    printf("TEST 1: unexpected datacont value at 3rd listnode: %d. Expected 3.\n", keys->item->i);
    retval = -1;
  }

  treemapnode_delete(root);
  listnode_delete(keys);

  return retval;
}


static int treemapnode_getvalues_tests()
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

  treemapnode* root = treemapnode_new(key2, val2);
  treemapnode_add(root, key1, val1);
  treemapnode_add(root, key3, val3);

  listnode* vals = treemapnode_getvalues(root);
  if (vals == NULL)
  {
    printf("TEST 1: treemapnode_getvalues() should not return NULL on not-empty treemapnode.\n");
    return -1; // can't continue
  }
  if (listnode_length(vals) != 3)
  {
    printf("TEST 1: unexpected listnode length: %d. Expected: 3.\n", listnode_length(vals));
    retval = -1;
  }
  if (vals->item->i != 1)
  {
    printf("TEST 1: unexpected datacont value at 1st listnode: %d. Expected 1.\n", vals->item->i);
    retval = -1;
  }

  vals = vals->next;
  if (vals == NULL)
  {
    printf("TEST 1: listnode missing 2nd item.\n");
    return -1; // can't continue
  }
  if (vals->item->i != 2)
  {
    printf("TEST 1: unexpected datacont value at 2nd listnode: %d. Expected 2.\n", vals->item->i);
    retval = -1;
  }

  vals = vals->next;
  if (vals == NULL)
  {
    printf("TEST 1: listnode missing 3rd item.\n");
    return -1; // can't continue
  }
  if (vals->item->i != 3)
  {
    printf("TEST 1: unexpected datacont value at 3rd listnode: %d. Expected 3.\n", vals->item->i);
    retval = -1;
  }

  treemapnode_delete(root);
  listnode_delete(vals);

  return retval;  
}


static int treemapnode_count_tests()
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

  treemapnode* root = treemapnode_new(key2, val2);
  treemapnode_add(root, key1, val1);
  treemapnode_add(root, key3, val3);
  treemapnode_add(root, key4, val4);

  int count = treemapnode_count(root);
  if (count != 4)
  {
    printf("TEST 1: Unexpected treemapnode_count() return value: %d. Expected: 4.\n", count);
    retval = -1;
  }

  /* TEST 2 */
  count = treemapnode_count(NULL);
  if (count != 0)
  {
    printf("TEST 2: Unexpected treemapnode_count() return value: %d. Expected: 4.\n", count);
    retval = -1;
  }

  treemapnode_delete(root);

  return retval;
}


static int treemapnode_height_tests()
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

  treemapnode* root = treemapnode_new(key2, val2);
  treemapnode_add(root, key1, val1);
  treemapnode_add(root, key3, val3);
  treemapnode_add(root, key4, val4);

  int height = treemapnode_height(root);
  if (height != 3)
  {
    printf("TEST 1: Unexpected treemapnode_height() return value: %d. Expected: 3.\n", height);
    retval = -1;
  }
 
  /* TEST 2 */
  height = treemapnode_height(NULL);
  if (height != 0)
  {
    printf("TEST 2: Unexpected treemapnode_height() return value: %d. Expected: 0.\n", height);
   retval = -1; 
  }

  treemapnode_delete(root);

  return retval;
}


int main()
{
  int retval = 0;

  printf("\ntreemapnode tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemapnode_new_tests()...\n");
  if (treemapnode_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemapnode_add_tests()...\n");
  if (treemapnode_add_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemapnode_remove_tests()...\n");
  if (treemapnode_remove_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemapnode_getkeys_tests()...\n");
  if (treemapnode_getkeys_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemapnode_getvals_tests()...\n");
  if (treemapnode_getvalues_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemapnode_count_tests()...\n");
  if (treemapnode_count_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treemapnode_height_tests()...\n");
  if (treemapnode_height_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

