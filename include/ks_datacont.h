#ifndef _KS_DATACONT_H_
#define _KS_DATACONT_H_


#include <stdlib.h>
#include <stdint.h>


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

  KS_CHARP,
  KS_SHORTP,
  KS_INTP,
  KS_LLP,
  KS_FLOATP,
  KS_DOUBLEP,

  KS_UCHARP,
  KS_USHORTP,
  KS_UINTP,
  KS_ULLP
};


typedef struct ks_datacont ks_datacont;


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
 * ks_datacont_new():
 * Creates a new ks_datacont* containing the data pointed to by 'data'.
 *
 * Inputs:
 * void* data - THE data being stored within the ks_datacont.
 * enum ks_datatype dct - the type of the data being stored. See the enum defined
 *                         above to review supported types.
 * unsigned int count - the number of bytes that 'data' points to.
 * 
 * Returns:
 * ks_datacont* dc - (NULL) if 'data' is NULL or 'count'== 0.
 *              - a ks_datacont* containing the data specified.
 *
 * Notes:
 * The data pointed to by 'data' is COPIED into the new ks_datacont structure. This way,
 * the user code is able to simply allocate whatever data is being used onto the stack.
 *
 * When the new ks_datacont is to be of type CHARP, a null terminating character '\0' is
 * appended to the end of the string so that calls like strlen(dc->cp) won't cause a seg fault.
 */
ks_datacont* ks_datacont_new(const void* data, const enum ks_datatype type, const size_t size);


/* ---------------------------
 * ks_datacont_delete():
 * Deletes a ks_datacont struct along with any data it contains.
 *
 * Inputs:
 * ks_datacont* dc - the ks_datacont being deleted.
 *
 * Returns: 
 * void
 */
void ks_datacont_delete(ks_datacont* dc);


/* ---------------------------
 * ks_datacont_copy():
 * Creates an identical copy of a ks_datacont* struct, including all of the data
 * that the original contains.
 *
 * Inputs:
 * ks_datacont* dc - the ks_datacont being copied.
 *
 * Returns:
 * ks_datacont* copy - (NULL) if 'dc' is NULL.
 *                - a copy of 'dc'.
 *
 * Notes:
 * The copy that is returned by this function contains no references whatsoever to the
 * data contained within the original. This way each copy can be independently deleted
 * or otherwise modified without affecting one another.
 */
ks_datacont* ks_datacont_copy(const ks_datacont* dc);


/* ---------------------------
 * ks_datacont_compare():
 * Compares two ks_datacont structs and returns an enum type that specifies the
 * result of the comparison.
 *
 * Inputs:
 * ks_datacont* dca - one of the ks_datacont structs being compared.
 * ks_datacont* dcb - the other ks_datacont being compared.
 *
 * Returns:
 * enum ks_comparison result - see the enum ks_comparison definition at the top of this
 *                            header for details. 
 */
enum ks_comparison ks_datacont_compare(const ks_datacont* dca, const ks_datacont* dcb);


/* ---------------------------
 * ks_datacont_hash():
 * Hashes the data contained within a ks_datacont and returns the result as an unsigned
 * 32-bit integer.
 * 
 * Inputs:
 * ks_datacont* dc - the ks_datacont being hashed.
 *
 * Returns:
 * uint32_t hash - the hash of the data contained in the ks_datacont.
 */
uint32_t ks_datacont_hash(const ks_datacont* dc);


#endif
