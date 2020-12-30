
#include <stdio.h>

#include <treesetnode.h>


static int treesetnode_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  int num = 10;
  datacont* dc = datacont_new(&num, INT, 1);
  treesetnode* tsn = treesetnode_new(dc);
  if (dc != tsn->dc)
  {
    printf("TEST 1: treesetnode contains unexpected datacont* value.\n");
    retval = -1;
  }
  if (! (tsn->left == NULL && tsn->right == NULL))
  {
    printf("TEST 1: treesetnode should contain NULL left and right treesetnode* values.\n");
    retval = -1;
  }
  treesetnode_delete_all(tsn);

  return retval;
}


static int treesetnode_add_tests()
{
  int retval = 0;

  treesetnode* tsn = treesetnode_new(datacont_new("B\0", CHARP, 2));
  datacont* left = datacont_new("A\0", CHARP, 2);
  datacont* right = datacont_new("C\0", CHARP, 2);

  /* Test 1 */
  if (treesetnode_add(tsn, left) != 0)
  {
    printf("TEST 1: Unexpected error on adding (should be) left node to tsn.\n");
    retval = -1;
  }

  if (tsn->left != NULL)
  {
    if (tsn->left->dc->cp[0] != 'A')
    {
      printf("TEST 1: Unexpected container value on left node: %c. Expected: %c.\n", tsn->left->dc->cp[0], 'A');
      retval = -1;
    }
  }
  else
  {
    printf("TEST 1: Unexpected NULL value in left node of tsn.\n");
    retval = -1;
  }  

  /* Test 2 */
  if (treesetnode_add(tsn, right) != 0)
  {
    printf("TEST 2: Unexpected error on adding (should be) left node to tsn.\n");
    retval = -1;
  }
  if (tsn->right != NULL)
  {
    if (tsn->right->dc->cp[0] != 'C')
    {
      printf("TEST 2: Unexpected container value on right node: %c. Expcted: %c.\n", tsn->right->dc->cp[0], 'C');
      retval = -1;
    }
  }
  else
  {
    printf("TEST 2: Unexpected NULL value in right node of tsn.\n");
    retval = -1;
  }
  treesetnode_delete_all(tsn);

  return retval;
}


static int treesetnode_remove_by_tests()
{
  int retval = 0;

  treesetnode* tsn = treesetnode_new(datacont_new("D", CHAR, 1));
  treesetnode_add(tsn, datacont_new("B", CHAR, 1));
  treesetnode_add(tsn, datacont_new("F", CHAR, 1));
  treesetnode_add(tsn, datacont_new("A", CHAR, 1));
  treesetnode_add(tsn, datacont_new("C", CHAR, 1));
  treesetnode_add(tsn, datacont_new("E", CHAR, 1));
  treesetnode_add(tsn, datacont_new("G", CHAR, 1));
 
  datacont* dc_Z = datacont_new("Z", CHAR, 1);
  datacont* dc_D = datacont_new("D", CHAR, 1);
  datacont* dc_B = datacont_new("B", CHAR, 1);
  datacont* dc_A = datacont_new("A", CHAR, 1);

  if (treesetnode_remove_by(&tsn, dc_Z) != -1)
  {
    printf("TEST 1: treesetnode_remove_by() should return -1 when a non-existent datacont value is passed.\n");
    retval = -1;
  }

  if (treesetnode_remove_by(&tsn, dc_D) != 0)
  {
    printf("TEST 2: treesetnode_remove_by() should return 0 on successful removal.\n");
    retval = -1;
  }
  if (treesetnode_contains(tsn, dc_D))
  {
    printf("TEST 2: treesetnode should not contain 'D' datacont value.\n");
    retval = -1;
  }

  if (treesetnode_remove_by(&tsn, dc_B) != 0)
  {
    printf("TEST 3: treesetnode_remove_by() should return 0 on successful removal.\n");
    retval = -1;
  }
  if (treesetnode_contains(tsn, dc_B))
  {
    printf("TEST 3: treesetnode should not contain 'B' datacont value.\n");
    retval = -1;
  }

  if (treesetnode_remove_by(&tsn, dc_A))
  {
    printf("TEST 4: treesetnode_remove_by() should return 0 on successful removal.\n");
    retval = -1;
  }
  if (treesetnode_contains(tsn, dc_A))
  {
    printf("TEST 4: treesetnode should not contain 'A' datacont value.\n");
    retval = -1;
  }
  datacont_delete(dc_Z);
  datacont_delete(dc_D);
  datacont_delete(dc_B);
  datacont_delete(dc_A);
  treesetnode_delete_all(tsn);

  return retval;
}


static int treesetnode_remove_at_tests()
{
  int retval = 0;

  treesetnode* tsn = treesetnode_new(datacont_new("D", CHAR, 1));
  treesetnode_add(tsn, datacont_new("B", CHAR, 1));
  treesetnode_add(tsn, datacont_new("F", CHAR, 1));
  treesetnode_add(tsn, datacont_new("A", CHAR, 1));
  treesetnode_add(tsn, datacont_new("C", CHAR, 1));
  treesetnode_add(tsn, datacont_new("E", CHAR, 1));
  treesetnode_add(tsn, datacont_new("G", CHAR, 1));
 
  datacont* dc_Z = datacont_new("Z", CHAR, 1);
  datacont* dc_D = datacont_new("D", CHAR, 1);
  datacont* dc_B = datacont_new("B", CHAR, 1);
  datacont* dc_A = datacont_new("A", CHAR, 1);
  datacont* dc_G = datacont_new("G", CHAR, 1);

  if (treesetnode_remove_at(&tsn, 10) != -1)
  {
    printf("TEST 1: treesetnode_remove_by() should return 1 when 'index' is OOB.\n");
    retval = -1;
  }

  if (treesetnode_remove_at(&tsn, 0) != 0)
  {
    printf("TEST 2: treesetnode_remove_by() should return 0 on successful removal.\n");
    retval = -1;
  }
  if (treesetnode_contains(tsn, dc_A))
  {
    printf("TEST 2: treesetnode should not contain 'A' datacont value.\n");
    retval = -1;
  }

  if (treesetnode_remove_at(&tsn, 0) != 0)
  {
    printf("TEST 3: treesetnode_remove_by() should return 0 on successful removal.\n");
    retval = -1;
  }
  if (treesetnode_contains(tsn, dc_B))
  {
    printf("TEST 3: treesetnode should not contain 'B' datacont value.\n");
    retval = -1;
  }

  if (treesetnode_remove_at(&tsn, -1))
  {
    printf("TEST 4: treesetnode_remove_by() should return 0 on successful removal.\n");
    retval = -1;
  }
  if (treesetnode_contains(tsn, dc_G))
  {
    printf("TEST 4: treesetnode should not contain 'G' datacont value.\n");
    retval = -1;
  }
  datacont_delete(dc_Z);
  datacont_delete(dc_D);
  datacont_delete(dc_B);
  datacont_delete(dc_A);
  datacont_delete(dc_G);
  treesetnode_delete_all(tsn);

  return retval;
}


static int treesetnode_index_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  datacont* dcC = datacont_new("C", CHAR, 1);

  treesetnode* tsn = treesetnode_new(datacont_copy(dcB));
  treesetnode_add(tsn, datacont_copy(dcA));
  treesetnode_add(tsn, datacont_copy(dcC));

  int index;

  if ((index = treesetnode_index(tsn, dcA)) != 0)
  {
    printf("TEST 1: Unexpected value returned from treesetnode_index(): %d. Expected: 0.\n", index);
    retval = -1;
  }

  /* TEST 2 */
  if ((index = treesetnode_index(tsn, dcB)) != 1)
  {
    printf("TEST 2: Unexpected value returned from treesetnode_index(): %d. Expected: 1.\n", index);
    retval = -1;
  }

  /* TEST 3 */
  if ((index = treesetnode_index(tsn, dcC)) != 2)
  {
    printf("TEST 3: Unexpected value returned from treesetnode_index(): %d. Expected: 2.\n", index);
    retval = -1;
  }

  datacont_delete(dcA);
  datacont_delete(dcB);
  datacont_delete(dcC);
  treesetnode_delete_all(tsn);

  return retval;
}


static int treesetnode_contains_tests()
{
  int retval = 0;
  
  /* Test 1 */
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  datacont* dcC = datacont_new("C", CHAR, 1);
  datacont* dcZ = datacont_new("Z", CHAR, 1);

  treesetnode* tsn = treesetnode_new(dcB);
  treesetnode_add(tsn, dcC);
  treesetnode_add(tsn, dcA); 
 
  if (treesetnode_contains(tsn, dcZ) == 1)
  {
    printf("TEST 1: treesetnode should not contain char value 'Z'.\n");
    retval = -1;
  }

  /* TEST 2 */
  if (treesetnode_contains(tsn, dcA) == 0)
  {
    printf("TEST 2: treesetnode should contain char value 'A'.\n");
    retval = -1;
  }
  datacont_delete(dcZ);
  treesetnode_delete_all(tsn);

  return retval;
}


static int treesetnode_get_tests()
{
  int retval = 0;

  /* TEST 1 */
  datacont* dcA = datacont_new("A", CHAR, 1);
  datacont* dcB = datacont_new("B", CHAR, 1);
  datacont* dcC = datacont_new("C", CHAR, 1);

  treesetnode* tsn = treesetnode_new(dcB);
  treesetnode_add(tsn, dcC);
  treesetnode_add(tsn, dcA); 
  
  datacont* get_dc = treesetnode_get(tsn, -1);
  if (get_dc->c != 'C')
  {
    printf("TEST 1: Unexpected datacont value after treesetnode_get(): %c. Expected: C.\n", get_dc->c);
    retval = -1;
  }

  /* TEST 2 */
  get_dc = treesetnode_get(tsn, 1);
  if (get_dc->c != 'B')
  {
    printf("TEST 2: Unexpected datacont value after treesetnode_get(): %c. Expected: B.\n", get_dc->c);
    retval = -1;
  }

  /* TEST 3 */
  get_dc = treesetnode_get(tsn, 1234);
  if (get_dc != NULL)
  {
    printf("TEST 3: Unexpected datacont value after OOB treesetnode_get(): %c. Expected: NULL.\n", get_dc->c);
    retval = -1;
  }
  
  treesetnode_delete_all(tsn);

  return retval;
}


static int treesetnode_count_tests()
{
  int retval = 0;

  /* Test 1 */
  treesetnode* tsn = treesetnode_new(datacont_new("A", CHAR, 1));
  treesetnode_add(tsn, datacont_new("B", CHAR, 1));
  treesetnode_add(tsn, datacont_new("C", CHAR, 1));

  unsigned int count = treesetnode_count(tsn);
  if (count != 3)
  {
    printf("TEST 1: Unexpected value returned from treesetnode_count(): %d. Expected: 3.\n", count);
    retval = -1;
  }

  /* TEST 2 */
  treesetnode_add(tsn, datacont_new("Z", CHAR, 1));
  count = treesetnode_count(tsn);
  if (count != 4)
  {
    printf("TEST 2: Unexpected value returned from treesetnode_count(): %d. Expected 4.\n", count);
    retval = -1;
  }

  /* TEST 3 */
  count = treesetnode_count(NULL);
  if (count != 0)
  {
    printf("TEST 3: Unexpected value returned from treesetnode_count(): %d. Expected 0.\n", count);
    retval = -1;
  }

  treesetnode_delete_all(tsn);

  return retval;
}


static int treesetnode_height_tests()
{
  int retval = 0;

  /* Test 1 */
  treesetnode* tsn = treesetnode_new(datacont_new("A", CHAR, 1));
  treesetnode_add(tsn, datacont_new("B", CHAR, 1));
  treesetnode_add(tsn, datacont_new("C", CHAR, 1));

  unsigned int height = treesetnode_height(tsn);
  if (height != 3)
  {
    printf("TEST 1: Unexpected treesetnode height: %d. Expected: %d\n", height, 3);
    retval = -1;
  }

  /* TEST 2 */
  height = treesetnode_height(NULL);
  if (height != 0)
  {
    printf("TEST 2: Unexpected result from treesetnode_height() on NULL param: %d. Expected: 0.\n", height);
    retval = -1;
  } 

  treesetnode_delete_all(tsn);
  return retval;
}


static int treesetnode_balance_tests()
{
  int retval = 0;

  /* TEST 1 */
  char c = 'A';
  treesetnode* tsn = treesetnode_new(datacont_new(&c, CHAR, 1));
  for (int i = 1, c = 'B'; i < 26; i++, c++)
    treesetnode_add(tsn, datacont_new(&c, CHAR, 1));

  unsigned int height = treesetnode_height(tsn);
  if (height != 26)
  {
    printf("TEST 1: treesetnode_height() should have returned 16. Returned: %d. Can't continue, quitting test...\n", height);
    treesetnode_delete_all(tsn);
    return -1;
  }

  treesetnode_balance(&tsn);
  height = treesetnode_height(tsn);
  if (height != 5)
  {
    printf("TEST 1: Unexpected tree height after treesetnode_balance(): %d. Expected: 5.\n", height);
    retval = -1;
  }

  treesetnode_delete_all(tsn);

  return retval;
}


int main()
{
  int retval = 0;

  printf("\ntreesetnode tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treesetnode_new_tests()...\n");
  if (treesetnode_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treesetnode_add_tests()...\n");
  if (treesetnode_add_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treesetnode_remove_by_tests()...\n");
  if (treesetnode_remove_by_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treesetnode_remove_at_tests()...\n");
  if (treesetnode_remove_at_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treesetnode_index_tests()...\n");
  if (treesetnode_index_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treesetnode_contains_tests()...\n");
  if (treesetnode_contains_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");
 
  printf("==-----------------------------------==\n");
  printf("Running treesetnode_get_tests()...\n");
  if (treesetnode_get_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treesetnode_count_tests()...\n");
  if (treesetnode_count_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treesetnode_height_tests()...\n");
  if (treesetnode_height_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treesetnode_balance_tests()...\n");
  if (treesetnode_balance_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

