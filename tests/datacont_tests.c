#include <stdio.h>

#include "../src/include/datacont.h"

static void datacont_new_tests()
{
  datacont* char_cont = datacont_new("A", CHAR, 1);
  if (char_cont->type != CHAR) 
    printf("TEST 1: Unexpected container type: %d. Expected: %d\n", char_cont->type, CHAR);
  if (char_cont->count != 1) 
    printf("TEST 1: Unexpected count value: %d. Expected: %d\n", char_cont->count, 1);
  if (char_cont->c != 'A')
    printf("TEST 1: Unexpected container value: %c. Expected: %c\n", char_cont->c, 'A');
  datacont_delete(char_cont);

  unsigned int num = 0x12345678;
  datacont* uint_cont = datacont_new(&num, UINT, 1);
  if (uint_cont->type != UINT)
      printf("TEST 2: Unexpected container type: %d. Expected: %d\n", uint_cont->type, UINT);
  if (uint_cont->count != 1) 
    printf("TEST 2: Unexpected count value: %d. Expected: %d\n", uint_cont->count, 1);
  if (uint_cont->ui != num)
    printf("TEST 2: Unexpected container value: %d. Expected: %d\n", uint_cont->ui, num);
  datacont_delete(uint_cont);
}


static void datacont_compare_tests()
{
  int num;
  char* str;
  enum datacontcomp result;
  datacont* dca;
  datacont* dcb;

  num = 10;
  dca = datacont_new(&num, INT, 1);
  num = 11;
  dcb = datacont_new(&num, INT, 1);
  result = datacont_compare(dca, dcb);
  if (result != LESSTHAN)
    printf("TEST 1: Unexpected comparison result: %d. Expected: %d\n", result, LESSTHAN);
  datacont_delete(dca);
  datacont_delete(dcb);

  str = "TESTSTRING";
  dca = datacont_new(str, CHARP, 11);
  dcb = datacont_new(str, CHARP, 11);
  result = datacont_compare(dca, dcb);
  if (result != EQUAL)
    printf("TEST 2: Unexpected comparison result: %d. Expected: %d\n", result, EQUAL);
  datacont_delete(dca);
  datacont_delete(dcb);

  dca = datacont_new(str, CHARP, 11);
  dcb = datacont_new(&num, INT, 1);
  result = datacont_compare(dca, dcb);
  if (result != CANTCOMPARE)
    printf("TEST 3: Unexpected comparison result: %d. Expected: %d\n", result, CANTCOMPARE);
  datacont_delete(dca);
  datacont_delete(dcb);
}


static void datacont_hash_tests()
{
  /* tough to test hashes...
   * probably just make sure hashes of the 
   * same value are equal.
   */
  datacont* dca = datacont_new("abcd", CHARP, 5);
  unsigned long long seed = 1234;
  unsigned long long hash1 = datacont_hash(seed, dca);
  unsigned long long hash2 = datacont_hash(seed, dca);
  if (hash1 != hash2)
    printf("TEST 1: Unexpected hash result: %llX. Expected: %llX\n", hash2, hash1);
  datacont_delete(dca);
}


void main()
{
  printf("\ndatacont tests:\n\n");
  
  printf("==-----------------------------------==\n");
  printf("Running datacont_new_tests()...\n");
  datacont_new_tests();
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running datacont_compare_tests()...\n");
  datacont_compare_tests();
  printf("done.\n");
  printf("==-----------------------------------==\n\n");


  printf("==-----------------------------------==\n");
  printf("Running datacont_hash_tests()...\n");
  datacont_hash_tests();
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

}
