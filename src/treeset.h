#ifndef _TREEH_
#define _TREEH_

typedef struct treesetnode {
  const char* word;
  treesetnode* right;
  treesetnode* left;
};

treesetnode* treesetnode_new(const char* word, const treesetnode* left, const treesetnode* right);

int treesetnode_add(const treesetnode* tn, const char* word);

int treesetnode_remove(const treesetnode* tn, const char* word);

int treesetnode_contains(const treesetnode* tn, const char* word);

static int _treesetnode_height(const treesetnode* tn, unsigned int accum);

int treesetnode_height(const treesetnode* tn);

typedef struct treeset {
	int num_nodes;
	treesetnode* root;
};

treeset* treeset_new(const int num_words, const char** words);

int treeset_add(const treeset* ts, const char* word);

int treeset_remove(const treeset* ts, const char* word);

int treeset_contains(const treeset* ts, const char* word);

int treeset_height(const treeset* ts);

static void _generate_dotfile(const treesetnode* tn);

void generate_dotfile(const treesetnode* tn);

#endif
