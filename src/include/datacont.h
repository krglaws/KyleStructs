
#ifndef _DATACONT_H_
#define _DATACONT_H_

enum datacontcomp
{
  LESSER,
  EQUAL,
  GREATER,
  NOCOMP
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
  enum dataconttype;
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

datacont* datacont_new(void* data, const unsigned int num_items);

int datacont_compare(const datacont* dca, const datacont* dcb);

int datacont_delete(datacont* dc);

#endif

