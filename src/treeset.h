#ifndef _TREEH_
#define _TREEH_


typedef struct {
  char* word;
  treesetnode* right;
  treesetnode* left;
} treesetnode;

treesetnode* treesetnode_new(char* word, treesetnode* left, treesetnode* right);

int treesetnode_height(treesetnode* root);


typedef struct {
	int num_nodes;
	treesetnode* root;
} treeset;

treeset* treeset_new(int num_words, char** words);

int treeset_add(treeset* ts, chaddr* word);

int treeset_remove(treeset* ts, char* word);

int treeset_contains(treeset* ts, char* word);

int treeset_height(treeset* ts);

void generate_dotfile(treenode* root);

#endif
