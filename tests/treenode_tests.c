
#include <stdio.h>

#include "../src/include/datacont.h"
#include "../src/include/treenode.h"


void treenode_new_tests()
{
  int num = 10;
  datacont* dc = datacont_new(&num, INT, 1);
  treenode* tn = treenode_new(dc, NULL, NULL);
  if (dc != tn->dc)
    printf("TEST 1: treenode contains unexpected datacont* value.\n");
  if (! (tn->left == tn->right == NULL))
    printf("TEST 1: treenode should contain NULL left and right treenode* values.\n");
  treenode_delete(tn);
}


void treenode_add_tests()
{
  
}


int main()
{
  printf("\ntreenode tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running treenode_new_tests()...");
  treenode_new_tests();
  printf("done.\n");
  printf("==-----------------------------------==\n");


}

