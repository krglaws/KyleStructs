#ifndef _TREEH_
#define _TREEH_

typedef struct treenode_t {
  char* word;
  struct treenode_t* right;
  struct treenode_t* left;
} treenode;

treenode* new_node(char* word);

int insert_node(treenode* root, char* word);

treenode* build_binary_tree(int num_vals, char** words);

int tree_height(treenode* root);

int in_tree(treenode* root, char* word);

void generate_dotfile(treenode* root);

#endif
