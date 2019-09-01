

#include <stdio.h>

#include "../src/include/datacont.h"
#include "../src/include/treenode.h"
#include "../src/include/treeset.h"
#include "../src/include/hashset.h"


static int hashset_new_tests()
{
  int retval = 0;

  /* Test 1 */
  hashset* hs = hashset_new(100, 0x1234);
  if (hs->seed != 0x1234)
  {
    printf("TEST 1: hashset contains incorrect seed value: %d. Expected: %d.\n", hs->seed, 0x1234);
    retval = -1;
  {
  if (hs->num_buckets != 100)
  {
    printf("TEST 1: hashset contains incorrect num_buckets value %d. Expected %d.\n", hs->num_buckets, 0x1234);
    retval = -1;
  }
  hashset_delete(hs);

  return retval;
}


static int hashset_add_tests()
{


int main()
{
  int retval = -1;

  

  return retval;
}

