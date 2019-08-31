#include <stdio.h>

#include "../src/include/datacont.h"

static int datacont_new_tests()
{
  int retval = 0;

  /* Test 1 */
  datacont* char_cont = datacont_new("A", CHAR, 1);
  if (char_cont->type != CHAR) 
  {
    printf("TEST 1: Unexpected container type: %d. Expected: %d\n", char_cont->type, CHAR);
    retval = -1;
  }
  if (char_cont->count != 1)
  {
    printf("TEST 1: Unexpected count value: %d. Expected: %d\n", char_cont->count, 1);
    retval = -1;
  }
  if (char_cont->c != 'A')
  {
    printf("TEST 1: Unexpected container value: %c. Expected: %c\n", char_cont->c, 'A');
    retval = -1;
  }
  datacont_delete(char_cont);

  /* Test 2 */
  unsigned int num = 0x12345678;
  datacont* uint_cont = datacont_new(&num, UINT, 1);
  if (uint_cont->type != UINT)
  {
    printf("TEST 2: Unexpected container type: %d. Expected: %d\n", uint_cont->type, UINT);
    retval = -1;
  }
  if (uint_cont->count != 1)
  {
    printf("TEST 2: Unexpected count value: %d. Expected: %d\n", uint_cont->count, 1);
    retval = -1;
  }
  if (uint_cont->ui != num)
  {
    printf("TEST 2: Unexpected container value: %d. Expected: %d\n", uint_cont->ui, num);
    retval = -1;
  }
  datacont_delete(uint_cont);

  return retval;
}


static int datacont_compare_tests()
{
  int retval = 0;
  int num;
  char* str;
  enum datacontcomp result;
  datacont* dca;
  datacont* dcb;

  /* Test 1 */
  num = 10;
  dca = datacont_new(&num, INT, 1);
  num = 11;
  dcb = datacont_new(&num, INT, 1);
  result = datacont_compare(dca, dcb);
  if (result != LESSTHAN)
  {
    printf("TEST 1: Unexpected comparison result: %d. Expected: %d\n", result, LESSTHAN);
    retval = -1;
  }
  datacont_delete(dca);
  datacont_delete(dcb);

  /* Test 2 */
  str = "TESTSTRING";
  dca = datacont_new(str, CHARP, 11);
  dcb = datacont_new(str, CHARP, 11);
  result = datacont_compare(dca, dcb);
  if (result != EQUAL)
  {
    printf("TEST 2: Unexpected comparison result: %d. Expected: %d\n", result, EQUAL);
    retval = -1;
  }
  datacont_delete(dca);
  datacont_delete(dcb);

  /* Test 3 */
  dca = datacont_new(str, CHARP, 11);
  dcb = datacont_new(&num, INT, 1);
  result = datacont_compare(dca, dcb);
  if (result != CANTCOMPARE)
  {
    printf("TEST 3: Unexpected comparison result: %d. Expected: %d\n", result, CANTCOMPARE);
    retval = -1;
  }
  datacont_delete(dca);
  datacont_delete(dcb);

  return retval;
}


static int datacont_hash_tests()
{
  /* tough to test hashes...
   * probably just make sure hashes of the 
   * same value are equal.
   */
  int retval = 0;
  datacont* dca = datacont_new("abcd", CHARP, 5);
  unsigned long long seed = 1234;
  unsigned long long hash1 = datacont_hash(seed, dca);
  unsigned long long hash2 = datacont_hash(seed, dca);
  if (hash1 != hash2)
  {
    printf("TEST 1: Unexpected hash result: %llX. Expected: %llX\n", hash2, hash1);
    retval = -1;
  }
  datacont_delete(dca);
  return retval;
}


int main()
{
  int retval = 0;

  printf("\ndatacont tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running datacont_new_tests()...\n");
  if (datacont_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running datacont_compare_tests()...\n");
  if (datacont_compare_tests()) retval - 1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running datacont_hash_tests()...\n");
  if (datacont_hash_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}

