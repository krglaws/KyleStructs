
#ifndef _DATACONT_H_
#define _DATACONT_H_

enum datacontcomp
{
  LESSTHAN,
  EQUAL,
  GREATERTHAN,
  CANTCOMPARE
};

enum dataconttype
{
  CHAR,
  SHORT,
  INT,
  LL,
  FLOAT,
  DOUBLE,

  UCHAR,
  USHORT,
  UINT,
  ULL,

  CHARP,
  SHORTP,
  INTP,
  LLP,
  FLOATP,
  DOUBLEP,

  UCHARP,
  USHORTP,
  UINTP,
  ULLP
};

typedef struct datacont datacont;

struct datacont
{
  enum dataconttype type;
  unsigned int count;
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
  };
};

datacont* datacont_new(const void* data, const enum dataconttype dct, const unsigned int count);

void datacont_delete(datacont* dc);

datacont* datacont_copy(const datacont* datacont);

static enum datacontcomp _compare_single_items(const datacont* dca, const datacont* dcb);

static enum datacontcomp _compare_multi_items(const datacont* dca, const datacont* dcb);

enum datacontcomp datacont_compare(const datacont* dca, const datacont* dcb);

unsigned long long datacont_hash(unsigned long long seed, const datacont* dc);

#endif
