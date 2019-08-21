#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "tree.h"


treenode* new_node(char* word)
{
  treenode* node = (treenode*) malloc(sizeof(treenode));
  node->word = word;
  node->left = node->right = NULL;
  return node;
}


int insert_node(treenode* root, char* word)
{
  if (!root || !word) return -1;
  int compare = strcmp(root->word, word);
  if (compare == 0) return 1;
  else if (compare > 0)
  {
    if (root->left) insert_node(root->left, word);
    else root->left = new_node(word);
  }
  else
  {
    if (root->right) insert_node(root->right, word);
    else root->right = new_node(word);
  }
  return 0;
}


treenode* build_binary_tree(int num_vals, char** words)
{
  if (!words || num_vals < 1) return NULL;
  treenode* root = new_node(words[0]);
  for (int i = 1; i < num_vals; i++)
    insert_node(root, words[i]);
  return root;
}


int tree_height(treenode* root)
{
  if (!root) return 0;
  int left = tree_height(root->left);
  int right = tree_height(root->right);
  printf("node #%d = %s\n", 1 + (left > right ? left : right), root->word);
  return 1 + (left > right ? left : right);
}


int in_tree(treenode* root, char* word)
{
  if (!root) return 0;
  if (!strcmp(root->word, word)) return 1;
  return in_tree(root->right, word) || in_tree(root->left, word);
}


void _generate_dotfile(treenode* root)
{
  if (root->right)
  {
    printf("%s->%s[color=red];\n", root->word, root->right->word);
    _generate_dotfile(root->right);
  }
  if (root->left)
  {
    printf("%s->%s[color=blue];\n", root->word, root->left->word);
    _generate_dotfile(root->left);
  }
}


void generate_dotfile(treenode* root)
{
  if (root)
  {
    printf("%s;\n", root->word);
    if (root->right)
    {
      printf("%s->%s[color=red];\n", root->word, root->right->word);
      _generate_dotfile(root->right);
    }
    if (root->left)
    {
      printf("%s->%s[color=blue];\n", root->word, root->left->word);
      _generate_dotfile(root->left);
    }
  }
  if (!root) printf("NULL;\n");

}
