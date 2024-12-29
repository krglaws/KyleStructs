#include <stdio.h>

#include "ks_datacont.h"
#include "ks_hashmap.h"
#include "ks_hashset.h"
#include "ks_iterator.h"
#include "ks_list.h"
#include "ks_listnode.h"
#include "ks_treemap.h"
#include "ks_treemapnode.h"
#include "ks_treeset.h"
#include "ks_treesetnode.h"
#include "ks_types.h"

static int ks_iterator_new_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_list* ls = ks_list_new();
  ks_list_add(ls, ks_datacont_new("A", KS_CHAR, 1));
  ks_list_add(ls, ks_datacont_new("B", KS_CHAR, 1));
  ks_list_add(ls, ks_datacont_new("C", KS_CHAR, 1));

  ks_iterator* iter = ks_iterator_new(ls, KS_LIST);

  if (iter->type != KS_LIST) {
    printf("TEST 1: Unexpected iterator->type value: %d. Expected: %d\n",
           iter->type, KS_LIST);
    retval = -1;
  }

  if (iter->size != 3) {
    printf("TEST 1: Unexpected iterator->size value: %d. Expected: 3\n",
           iter->size);
    retval = -1;
  }

  if (iter->index != 0) {
    printf("TEST 1: Unexpected iterator->index value: %d. Expected: 0\n",
           iter->index);
    retval = -1;
  }

  if (iter->curr->dc->c != 'A') {
    printf("TEST 1: Unexpected iterator->curr value: %c. Expected: A\n",
           iter->curr->dc->c);
    retval = -1;
  }

  ks_iterator_delete(iter);
  ks_list_delete(ls);

  return retval;
}

static int ks_iterator_next_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_list* ls = ks_list_new();
  ks_list_add(ls, ks_datacont_new("A", KS_CHAR, 1));
  ks_list_add(ls, ks_datacont_new("B", KS_CHAR, 1));
  ks_list_add(ls, ks_datacont_new("C", KS_CHAR, 1));

  ks_iterator* iter = ks_iterator_new(ls, KS_LIST);

  const ks_datacont* dc = ks_iterator_next(iter);
  if (dc->c != 'A') {
    printf("TEST 1: Unexpected ks_iterator_next() value: %c. Expected: A\n",
           iter->curr->dc->c);
    retval = -1;
  }

  dc = ks_iterator_next(iter);
  if (dc->c != 'B') {
    printf("TEST 1: Unexpected ks_iterator_next() value: %c. Expected: B\n",
           iter->curr->dc->c);
    retval = -1;
  }

  dc = ks_iterator_next(iter);
  if (dc->c != 'C') {
    printf("TEST 1: Unexpected ks_iterator_next() value: %c. Expected: C\n",
           iter->curr->dc->c);
    retval = -1;
  }

  ks_iterator_delete(iter);
  ks_list_delete(ls);

  return retval;
}

int main() {
  int retval = 0;

  printf("\nks_iterator tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_iterator_new_tests()...\n");
  if (ks_iterator_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_iterator_next_tests()...\n");
  if (ks_iterator_next_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}
