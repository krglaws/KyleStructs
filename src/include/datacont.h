
#ifndef _DATACONT_H_
#define _DATACONT_H_


#include <stdlib.h>
#include <stdint.h>
#include <string.h>


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


/* ---------------------------
 * datacont_new():
 * Creates a new datacont* containing the data pointed to by 'data'.
 *
 * Inputs:
 * void* data - THE data being stored within the datacont.
 * enum dataconttype dct - the type of the data being stored. See the enum defined
 *                         above to review supported types.
 * unsigned int count - the number of bytes that 'data' points to.
 * 
 * Returns:
 * datacont* dc - (NULL) if 'data' is NULL or 'count'== 0.
 *              - a datacont* containing the data specified.
 *
 * Notes:
 * The data pointed to by 'data' is COPIED into the new datacont structure. This way,
 * the user code is able to simply allocate whatever data is being used onto the stack.
 */
datacont* datacont_new(const void* data, const enum dataconttype dct, const size_t size);


/* ---------------------------
 * datacont_delete():
 * Deletes a datacont struct along with any data it contains.
 *
 * Inputs:
 * datacont* dc - the datacont being deleted.
 *
 * Returns: 
 * void
 */
void datacont_delete(datacont* dc);


/* ---------------------------
 * datacont_copy():
 * Creates an identical copy of a datacont* struct, including all of the data
 * that the original contains.
 *
 * Inputs:
 * datacont* dc - the datacont being copied.
 *
 * Returns:
 * datacont* copy - (NULL) if 'dc' is NULL.
 *                - a copy of 'dc'.
 *
 * Notes:
 * The copy that is returned by this function contains no references whatsoever to the
 * data contained within the original. This way each copy can be independently deleted
 * or otherwise modified without affecting one another.
 */
datacont* datacont_copy(const datacont* dc);


/* ---------------------------
 * datacont_compare():
 * Compares two datacont structs and returns an enum type that specifies the
 * result of the comparison.
 *
 * Inputs:
 * datacont* dca - one of the datacont structs being compared.
 * datacont* dcb - the other datacont being compared.
 *
 * Returns:
 * enum datacontcomp result - see the enum datacontcomp definition at the top of this
 *                            header for details. 
 */
enum datacontcomp datacont_compare(const datacont* dca, const datacont* dcb);


/* ---------------------------
 * datacont_hash():
 * Hashes the data contained within a datacont and returns the result as an unsigned
 * 32-bit integer.
 * 
 * Inputs:
 * datacont* dc - the datacont being hashed.
 *
 * Returns:
 * uint32_t hash - the hash of the data contained in the datacont.
 */
uint32_t datacont_hash(const datacont* dc);


#endif

