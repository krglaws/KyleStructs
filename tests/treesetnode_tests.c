
#include <stdio.h>

#include "../src/include/datacont.h"
#include "../src/include/treesetnode.h"


static int treesetnode_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  int num = 10;
  datacont* dc = datacont_new(&num, INT, 1);
  treesetnode* tn = treesetnode_new(dc);
  if (dc != tn->dc)
  {
    printf("TEST 1: treesetnode contains unexpected datacont* value.\n");
    retval = -1;
  }
  if (! (tn->left == NULL && tn->right == NULL))
  {
    printf("TEST 1: treesetnode should contain NULL left and right treesetnode* values.\n");
    retval = -1;
  }
  treesetnode_delete(tn);

  return retval;
}


static int treesetnode_add_tests()
{
  int retval = 0;

  treesetnode* root = treesetnode_new(datacont_new("B\0", CHARP, 2));
  datacont* left = datacont_new("A\0", CHARP, 2);
  datacont* right = datacont_new("C\0", CHARP, 2);

  /* Test 1 */
  if (treesetnode_add(root, left) != 0)
  {
    printf("TEST 1: Unexpected error on adding (should be) left node to root.\n");
    retval = -1;
  }

  if (root->left != NULL)
  {
    if (root->left->dc->cp[0] != 'A')
    {
      printf("TEST 1: Unexpected container value on left node: %c. Expected: %c.\n", root->left->dc->cp[0], 'A');
      retval = -1;
    }
  }
  else
  {
    printf("TEST 1: Unexpected NULL value in left node of root.\n");
    retval = -1;
  }  

  /* Test 2 */
  if (treesetnode_add(root, right) != 0)
  {
    printf("TEST 2: Unexpected error on adding (should be) left node to root.\n");
    retval = -1;
  }
  if (root->right != NULL)
  {
    if (root->right->dc->cp[0] != 'C')
    {
      printf("TEST 2: Unexpected container value on right node: %c. Expcted: %c.\n", root->right->dc->cp[0], 'C');
      retval = -1;
    }
  }
  else
  {
    printf("TEST 2: Unexpected NULL value in right node of root.\n");
    retval = -1;
  }
  treesetnode_delete(root);

  return retval;
}


static int treesetnode_remove_tests()
{
  int retval = 0;

  treesetnode* root = treesetnode_new(datacont_new("D", CHAR, 1));
  treesetnode_add(root, datacont_new("B", CHAR, 1));
  treesetnode_add(root, datacont_new("F", CHAR, 1));
  treesetnode_add(root, datacont_new("A", CHAR, 1));
  treesetnode_add(root, datacont_new("C", CHAR, 1));
  treesetnode_add(root, datacont_new("E", CHAR, 1));
  treesetnode_add(root, datacont_new("G", CHAR, 1));
 
  datacont* dc_Z = datacont_new("Z", CHAR, 1);
  datacont* dc_D = datacont_new("D", CHAR, 1);
  datacont* dc_B = datacont_new("B", CHAR, 1);
  datacont* dc_A = datacont_new("A", CHAR, 1);

  if (treesetnode_remove(&root, dc_Z) != 1)
  {
    printf("TEST 1: treesetnode_remove() should return 1 when a non-existent datacont value is passed.\n");
    retval = -1;
  }

  if (treesetnode_remove(&root, dc_D) != 0)
  {
    printf("TEST 2: treesetnode_remove() should return 0 on successful removal.\n");
    retval = -1;
  }
  if (treesetnode_contains(root, dc_D))
  {
    printf("TEST 2: treesetnode should not contain 'D' datacont value.\n");
    retval = -1;
  }

  if (treesetnode_remove(&root, dc_B) != 0)
  {
    printf("TEST 3: treesetnode_remove() should return 0 on successful removal.\n");
    retval = -1;
  }
  if (treesetnode_contains(root, dc_B))
  {
    printf("TEST 3: treesetnode should not contain 'B' datacont value.\n");
    retval = -1;
  }

  if (treesetnode_remove(&root, dc_A))
  {
    printf("TEST 4: treesetnode_remove() should return 0 on successful removal.\n");
    retval = -1;
  }
  if (treesetnode_contains(root, dc_A))
  {
    printf("TEST 4: treesetnode should not contain 'A' datacont value.\n");
    retval = -1;
  }
  datacont_delete(dc_Z);
  datacont_delete(dc_D);
  datacont_delete(dc_B);
  datacont_delete(dc_A);
  treesetnode_delete(root);

  return retval;
}


static int treesetnode_contains_tests()
{
  int retval = 0;
  
  /* Test 1 */
  treesetnode* root = treesetnode_new(datacont_new("A", CHAR, 1));
  datacont* dc = datacont_new("B", CHAR, 1);
  if (treesetnode_contains(root, dc) == 1)
  {
    printf("TEST 1: treesetnode should not contain char value 'B'.\n");
    retval = -1;
  }

  dc->c = 'A';
  if (treesetnode_contains(root, dc) == 0)
  {
    printf("TEST 2: treesetnode should contain char value 'A'.\n");
    retval = -1;
  }
  datacont_delete(dc);
  treesetnode_delete(root);

  return retval;
}


static int treesetnode_height_tests()
{
  int retval = 0;

  /* Test 1 */
  treesetnode* tn = treesetnode_new(datacont_new("A", CHAR, 1));
  treesetnode_add(tn, datacont_new("B", CHAR, 1));
  treesetnode_add(tn, datacont_new("C", CHAR, 1));

  unsigned int height = treesetnode_height(tn);
  if (height != 3)
  {
    printf("TEST 1: Unexpected treesetnode height: %d. Expected: %d\n", height, 3);
    retval = -1;
  }

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
  printf("Running treesetnode_remove_tests()...\n");
  if (treesetnode_remove_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treesetnode_contains_tests()...\n");
  if (treesetnode_contains_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treesetnode_height_tests()...\n");
  if (treesetnode_height_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

