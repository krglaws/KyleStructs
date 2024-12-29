#ifndef _KS_TYPES_H_
#define _KS_TYPES_H_

#include <stddef.h>


enum ks_comparison
{
  KS_LESSTHAN,
  KS_EQUAL,
  KS_GREATERTHAN,
  KS_CANTCOMPARE
};


enum ks_datatype
{
  KS_CHAR,
  KS_SHORT,
  KS_INT,
  KS_LL,
  KS_FLOAT,
  KS_DOUBLE,

  KS_UCHAR,
  KS_USHORT,
  KS_UINT,
  KS_ULL,

  KS_VOIDP,
  KS_CHARP,
  KS_SHORTP,
  KS_INTP,
  KS_LLP,
  KS_FLOATP,
  KS_DOUBLEP,

  KS_UCHARP,
  KS_USHORTP,
  KS_UINTP,
  KS_ULLP,

  KS_LIST,
  KS_TREESET,
  KS_HASHSET,
  KS_TREEMAP,
  KS_HASHMAP
};


typedef struct ks_datacont ks_datacont;

typedef struct ks_listnode ks_listnode;
typedef struct ks_list ks_list;

typedef struct ks_treesetnode ks_treesetnode;
typedef struct ks_treeset ks_treeset;
typedef struct ks_hashset ks_hashset;

typedef struct ks_treemapnode ks_treemapnode;
typedef struct ks_treemap ks_treemap;
typedef struct ks_hashmap ks_hashmap;

typedef struct ks_iterator ks_iterator;


struct ks_datacont
{
  enum ks_datatype type;
  size_t size;
  union
  {
    char c;
    short s;
    int i;
    long long ll;
    float f;
    double d;

    unsigned char uc;
    unsigned short us;
    unsigned int ui;
    unsigned long long ull;

    void* vp;
    char* cp;
    short* sp;
    int* ip;
    long long* llp;
    float* fp;
    double* dp;

    unsigned char* ucp;
    unsigned short* usp;
    unsigned int* uip;
    unsigned long long* ullp;

    ks_list* ls;
    ks_treeset* ts;
    ks_hashset* hs;
    ks_treemap* tm;
    ks_hashmap* hm;
  };
};


struct ks_listnode
{
  ks_datacont* dc;
  ks_listnode* next;
};


struct ks_list
{
  ks_listnode* head;
};


struct ks_treesetnode
{
  ks_datacont* dc;
  ks_treesetnode* right;
  ks_treesetnode* left;
};


struct ks_treeset
{
  ks_treesetnode* root;
};


struct ks_hashset
{
  enum ks_datatype type;

  unsigned int num_buckets;

  ks_treeset** buckets;
};


struct ks_treemapnode
{
  ks_datacont* key;
  ks_datacont* value;
  ks_treemapnode* left;
  ks_treemapnode* right;
};


struct ks_treemap
{
  ks_treemapnode* root;
};


struct ks_hashmap
{
  enum ks_datatype type;

  unsigned int num_buckets;
 
  ks_treemap** buckets;
};


struct ks_iterator
{
  enum ks_datatype type;
  int size;
  int index;
  void* parent;
  ks_listnode* curr;
};

#endif
