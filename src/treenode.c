#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "datacont.h"
#include "treenode.h"


treenode* treenode_new(const char* word, treenode* left, treenode* right)
{
  treenode* tn = (treenode*) malloc(sizeof(treenode));
  tn->word = word;
  tn->left = left;
  tn->right = right;
  return tn;
}


int treenode_add(treenode* tn, const char* word)
{
  if (tn == NULL) return -1;
  int compare = strcmp(tn->word, word);
  if (compare == 0) return 1;

  else if (compare > 0)
  {
    if (tn->left) return treenode_add(tn->left, word);
    else tn->left = treenode_new(word, NULL, NULL);
  }
  else
  {
    if (tn->right) return treenode_add(tn->right, word);
    else tn->right = treenode_new(word, NULL, NULL);
  }
  return 0;
}


int treenode_remove(treenode* tn, const char* word)
{
  // this is gon' be tricky
  return 0;
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


int treenode_contains(const treenode* tn, const char* word)
{
  if (tn == NULL || word == NULL) return 0;
  int compare = strcmp(word, tn->word);
  if (compare == 0) return 1;
  if (compare > 0) return treenode_contains(tn->right, word);
  return treenode_contains(tn->left, word);
}


int treenode_height(const treenode* tn)
{
  return _treenode_height(tn, 0);
}


static void _generate_dotfile(const treenode* tn)
{
  if (tn->right)
  {
    printf("%s->%s[color=red];\n", tn->word, tn->right->word);
    _generate_dotfile(tn->right);
  }
  if (tn->left)
  {
    printf("%s->%s[color=blue];\n", tn->word, tn->left->word);
    _generate_dotfile(tn->left);
  }
}


void generate_dotfile(const treenode* tn)
{
  if (tn)
  {
    printf("%s;\n", tn->word);
    if (tn->right)
    {
      printf("%s->%s[color=red];\n", tn->word, tn->right->word);
      _generate_dotfile(tn->right);
    }
    if (tn->left)
    {
      printf("%s->%s[color=blue];\n", tn->word, tn->left->word);
      _generate_dotfile(tn->left);
    }
  }
  else printf("NULL;\n");
}

