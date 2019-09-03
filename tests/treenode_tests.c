
#include <stdio.h>

#include "../src/include/datacont.h"
#include "../src/include/treenode.h"


static int treenode_new_tests()
{
  int retval = 0;

  /* TEST 1 */
  int num = 10;
  datacont* dc = datacont_new(&num, INT, 1);
  treenode* tn = treenode_new(dc);
  if (dc != tn->dc)
  {
    printf("TEST 1: treenode contains unexpected datacont* value.\n");
    retval = -1;
  }
  if (! (tn->left == NULL && tn->right == NULL))
  {
    printf("TEST 1: treenode should contain NULL left and right treenode* values.\n");
    retval = -1;
  }
  treenode_delete(tn);

  return retval;
}


static int treenode_add_tests()
{
  int retval = 0;

  treenode* root = treenode_new(datacont_new("B\0", CHARP, 2));
  datacont* left = datacont_new("A\0", CHARP, 2);
  datacont* right = datacont_new("C\0", CHARP, 2);

  /* Test 1 */
  if (treenode_add(root, left) != 0)
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
  if (treenode_add(root, right) != 0)
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
  treenode_delete(root);

  return retval;
}


static int treenode_contains_tests()
{
  int retval = 0;
  
  /* Test 1 */
  treenode* root = treenode_new(datacont_new("A", CHAR, 1));
  datacont* dc = datacont_new("B", CHAR, 1);
  if (treenode_contains(root, dc) == 1)
  {
    printf("TEST 1: treenode should not contain char value 'B'.\n");
    retval = -1;
  }

  dc->c = 'A';
  if (treenode_contains(root, dc) == 0)
  {
    printf("TEST 2: treenode should contain char value 'A'.\n");
    retval = -1;
  }
  datacont_delete(dc);
  treenode_delete(root);

  return retval;
}


static int treenode_height_tests()
{
  int retval = 0;

  /* Test 1 */
  treenode* tn = treenode_new(datacont_new("A", CHAR, 1));
  treenode_add(tn, datacont_new("B", CHAR, 1));
  treenode_add(tn, datacont_new("C", CHAR, 1));

  unsigned int height = treenode_height(tn);
  if (height != 3)
  {
    printf("TEST 1: Unexpected treenode height: %d. Expected: %d\n", height, 3);
    retval = -1;
  }

  return retval;
}


int main()
{
  int retval = 0;

  printf("\ntreenode tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treenode_new_tests()...\n");
  if (treenode_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treenode_add_tests()...\n");
  if (treenode_add_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treenode_contains_tests()...\n");
  if (treenode_contains_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treenode_height_tests()...\n");
  if (treenode_height_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

