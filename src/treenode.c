#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "include/datacont.h"
#include "include/treenode.h"


treenode* treenode_new(const datacont* dc, treenode* left, treenode* right)
{
  if (dc == NULL) return NULL;
  treenode* tn = (treenode*) malloc(sizeof(treenode));
  tn->dc = dc;
  tn->left = left;
  tn->right = right;
  return tn;
}


int treenode_add(treenode* tn, const datacont* dc)
{
  if (tn == NULL || dc == NULL) return -1;
 
  enum datacontcomp result = datacont_compare(dc, tn->dc);
  if (result == EQUAL) return 1;

  else if (result == GREATERTHAN)
  {
    if (tn->left) return treenode_add(tn->left, dc);
    else tn->left = treenode_new(dc, NULL, NULL);
  }
  else
  {
    if (tn->right) return treenode_add(tn->right, dc);
    else tn->right = treenode_new(dc, NULL, NULL);
  }
  return 0;
}


int treenode_remove(treenode* tn, const datacont* dc)
{
  // this is gon' be tricky
  return 0;
}


void treenode_delete(treenode* tn)
{
  if (tn == NULL) return;
  datacont_delete((datacont*) tn->dc);
  free(tn);
}


static int _treenode_height(const treenode* tn, unsigned int accum)
{
  if (tn != NULL)
  {
    accum++;
    int left_height = _treenode_height(tn->left, accum);
    int right_height = _treenode_height(tn->right, accum);
    return left_height > right_height ? left_height : right_height;
  }
  return accum;
}


unsigned int treenode_height(const treenode* tn)
{
  return _treenode_height(tn, 0);
}


int treenode_contains(const treenode* tn, const datacont* dc)
{
  if (tn == NULL || dc == NULL) return 0;
  enum datacontcomp result = datacont_compare(dc, tn->dc);
  if (result == EQUAL) return 1;
  if (result == GREATERTHAN) return treenode_contains(tn->right, dc);
  return treenode_contains(tn->left, dc);
}

/* these will have to be re-written */

/*
static void _generate_dotfile(const treenode* tn)
{
  if (tn->right)
  {
    printf("%s->%s[color=red];\n", tn->dc, tn->right->word);
    _generate_dotfile(tn->right);
  }
  if (tn->left)
  {
    printf("%s->%s[color=blue];\n", tn->dc, tn->left->word);
    _generate_dotfile(tn->left);
  }
}


void generate_dotfile(const treenode* tn)
{
  if (tn)
  {
    printf("%s;\n", tn->dc);
    if (tn->right)
    {
      printf("%s->%s[color=red];\n", tn->dc, tn->right->word);
      _generate_dotfile(tn->right);
    }
    if (tn->left)
    {
      printf("%s->%s[color=blue];\n", tn->dc, tn->left->word);
      _generate_dotfile(tn->left);
    }
  }
  else printf("NULL;\n");
}
*/
