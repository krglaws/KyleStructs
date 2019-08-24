#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "treeset.h"


treesetnode* treesetnode_new(const char* word, const treesetnode* left, const treesetnode* right)
{
  treesetnode* tn = (treesetnode*) malloc(sizeof(treesetnode));
  tn->word = word;
  tn->left = left;
  tn->right = right;
  return tn;
}


int treesetnode_add(const treesetnode* tn, const char* word)
{
  if (tn == NULL) return -1;
  int compare = strcmp(tn->word, word);
  if (compare == 0) return 1;

  else if (compare > 0)
  {
    if (tn->left) return treesetnode_add(tn->left, word);
    else tn->left = treesetnode_new(word, NULL, NULL);
  }
  else
  {
    if (tn->right) return treesetnode_add(tn->right, word);
    else tn->right = treesetnode_new(word, NULL, NULL);
  }
  return 0;
}


int treesetnode_remove(treesetnode* tn, char* word)
{
  // this is gon' be tricky
  return 0;
}


static int _treesetnode_height(const treesetnode* tn, unsigned int accum)
{
  if (tn != NULL)
  {
    accum++;
    int left_height = _treesetnode_height(tn->left, accum);
    int right_height = _treesetnode_height(tn->right, accum);
    return left_height > right_height ? left_height : right_height;
  }
  return accum;
}


int treesetnode_contains(const treesetnode* tn, const char* word)
{
  if (tn == NULL || word == NULL) return 0;
  int compare = strcmp(word, tn->word);
  if (compare == 0) return 1;
  if (compare > 0) return treesetnode_contains(tn->right, word);
  return treesetnode_contains(tn->left, word);
}


int treesetnode_height(const treesetnode* tn)
{
  return _treesetnode_height(tn, 0);
}


treeset* treeset_new(const int num_words, const char** words)
{
  treeset* ts = (treeset*) malloc(sizeof(treesetnode));
  
  int find = 0;
  while (find < num_words && !words[find]) find++;
  if (find == num_words) return NULL;

  ts->root = treesetnode_new(words[find], NULL, NULL);
  ts->num_nodes = 1;

  for (int i = 0; i < num_words; i++)
    if (treeset_add(ts, words[i]) == 0) ts->num_nodes++;
  
  return ts;
}


int treeset_add(const treeset* ts, const char* word)
{
  if (!ts || !word) return -1;
  int retval = treesetnode_add(ts->root, word);
  if (retval == 0) ts->num_nodes++;
  return retval;
}


int treeset_remove(const treeset* ts, const char* word)
{
  if (ts == NULL || word == NULL) return 1;
  return treesetnode_remove(ts->root, word);
}


int treeset_contains(const treeset* ts, char* word)
{
  if (ts == NULL || word == NULL) return 0;
  return treesetnode_contains(ts->root, word);
}


int treeset_height(const treeset* ts)
{
  if (ts == NULL) return 0;
  return treesetnode_height(ts->root);
}


static void _generate_dotfile(const treesetnode* tn)
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


void generate_dotfile(const treesetnode* tn)
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
