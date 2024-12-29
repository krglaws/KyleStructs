#include <stdio.h>

#include "ks_datacont.h"
#include "ks_hashset.h"
#include "ks_treeset.h"
#include "ks_treesetnode.h"
#include "ks_types.h"

static int ks_treeset_new_tests() {
  int retval = 0;

  /* TEST 1 */

  ks_treeset* ts = ks_treeset_new();

  if (ts == NULL) {
    printf("TEST 1: Unexpected NULL value returned from ks_treeset_new().\n");
    retval = -1;
  }

  if (ts->root) {
    printf(
        "TEST 1: ks_treeset should contain NULL 'root' ks_treesetnode* "
        "values.\n");
    retval = -1;
  }
  ks_treeset_delete(ts);

  return retval;
}

static int ks_treeset_copy_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_treeset* ts = ks_treeset_new();
  ks_treeset_add(ts, ks_datacont_new("A", KS_CHAR, 1));
  ks_treeset_add(ts, ks_datacont_new("B", KS_CHAR, 1));

  ks_treeset* ts_copy = ks_treeset_copy(ts);

  if (ts_copy == NULL) {
    printf("TEST 1: Unexpected NULL return from ks_treeset_copy()\n");
    return -1;
  }

  if (ts_copy->root->dc->c != 'A' || ts_copy->root->right->dc->c != 'B') {
    printf("TEST 1: Unexpected ks_datacont values after ts_treeset_copy()\n");
    retval = -1;
  }

  ks_treeset_delete(ts);
  ks_treeset_delete(ts_copy);

  return retval;
}

static int ks_treeset_add_tests() {
  int retval = 0;

  ks_treeset* ts = ks_treeset_new();
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 2);

  /* Test 1 */
  int result;
  if ((result = ks_treeset_add(ts, ks_datacont_copy(dcB))) != 0) {
    printf(
        "TEST 1: Unexpected return value from ks_treeset_add(): %d. Expected: "
        "0.\n",
        result);
    retval = -1;
  }

  /* TEST 2 */
  if ((result = ks_treeset_add(ts, dcB)) != 1) {
    printf(
        "TEST 2: Unexpected return value from ks_treeset_add(): %d. Expected "
        "1.\n",
        result);
    retval = -1;
  }

  /* TEST 3 */
  if ((result = ks_treeset_add(NULL, NULL)) != -1) {
    printf(
        "TEST 3: Unexpected return value from ks_treeset_add(): %d. Expected "
        "-1.\n",
        result);
    retval = -1;
  }

  ks_datacont_delete(dcB);
  ks_treeset_delete(ts);

  return retval;
}

static int ks_treeset_remove_by_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dc = ks_datacont_new("A", KS_CHAR, 1);

  ks_treeset* ts = ks_treeset_new();
  ks_treeset_add(ts, ks_datacont_copy(dc));

  int result;
  if ((result = ks_treeset_remove_by(ts, dc)) != 0) {
    printf(
        "TEST 1: Unexpected return value from ks_treeset_remove_by(): %d. "
        "Expected: 0.\n",
        result);
    retval = -1;
  }

  /* TEST 2 */
  if ((result = ks_treeset_remove_by(ts, dc)) != -1) {
    printf(
        "TEST 2: Unexpected return value from ks_treeset_remove_by(): %d. "
        "Expected: -1.\n",
        result);
    retval = -1;
  }

  /* TEST 3 */
  if ((result = ks_treeset_remove_by(NULL, NULL)) != -1) {
    printf(
        "TEST 3: Unexpected return value from ks_treeset_remove_by(): %d. "
        "Expected: -1.\n",
        result);
    retval = -1;
  }

  ks_datacont_delete(dc);
  ks_treeset_delete(ts);

  return retval;
}

static int ks_treeset_remove_at_tests() {
  int retval = 0;

  ks_treeset* ts = ks_treeset_new();
  ks_treeset_add(ts, ks_datacont_new("B", KS_CHAR, 1));
  ks_treeset_add(ts, ks_datacont_new("A", KS_CHAR, 1));
  ks_treeset_add(ts, ks_datacont_new("C", KS_CHAR, 1));

  int result;

  /* TEST 1 */
  if ((result = ks_treeset_remove_at(ts, 0)) != 0) {
    printf(
        "TEST 1: Unexpected return value from ks_treeset_remove_at(): %d. "
        "Expected: 0.\n",
        result);
    retval = -1;
  }

  /* TEST 2 */
  if ((result = ks_treeset_remove_at(ts, -6)) != -1) {
    printf(
        "TEST 2: Unexpected return value from ks_treeset_remove_at(): %d. "
        "Expected: -1.\n",
        result);
    retval = -1;
  }

  /* TEST 3 */
  if ((result = ks_treeset_remove_at(NULL, 0)) != -1) {
    printf(
        "TEST 3: Unexpected return value from ks_treeset_remove_at(): %d. "
        "Expected: -1.\n",
        result);
    retval = -1;
  }

  ks_treeset_delete(ts);

  return retval;
}

static int ks_treeset_index_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_treeset* ts = ks_treeset_new();
  ks_treeset_add(ts, ks_datacont_copy(dcB));
  ks_treeset_add(ts, ks_datacont_copy(dcA));
  ks_treeset_add(ts, ks_datacont_copy(dcC));

  int index;

  if ((index = ks_treeset_index(ts, dcA)) != 0) {
    printf(
        "TEST 1: Unexpected value returned from ks_treeset_index(): %d. "
        "Expected: 0.\n",
        index);
    retval = -1;
  }

  /* TEST 2 */
  if ((index = ks_treeset_index(ts, dcB)) != 1) {
    printf(
        "TEST 2: Unexpected value returned from ks_treeset_index(): %d. "
        "Expected: 1.\n",
        index);
    retval = -1;
  }

  /* TEST 3 */
  if ((index = ks_treeset_index(ts, dcC)) != 2) {
    printf(
        "TEST 3: Unexpected value returned from ks_treeset_index(): %d. "
        "Expected: 2.\n",
        index);
    retval = -1;
  }

  if ((index = ks_treeset_index(NULL, NULL)) != -1) {
    printf(
        "TEST 4: Unexpected value returned from ks_treeset_index(): %d. "
        "Expected: -1.\n",
        index);
    retval = -1;
  }

  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);
  ks_datacont_delete(dcC);
  ks_treeset_delete(ts);

  return retval;
}

static int ks_treeset_contains_tests() {
  int retval = 0;

  /* Test 1 */
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);
  ks_datacont* dcZ = ks_datacont_new("Z", KS_CHAR, 1);

  ks_treeset* ts = ks_treeset_new();
  ks_treeset_add(ts, dcB);
  ks_treeset_add(ts, dcC);
  ks_treeset_add(ts, dcA);

  if (ks_treeset_contains(ts, dcZ) == 1) {
    printf("TEST 1: ks_treeset should not contain char value 'Z'.\n");
    retval = -1;
  }

  /* TEST 2 */
  if (ks_treeset_contains(ts, dcA) == 0) {
    printf("TEST 2: ks_treeset should contain char value 'A'.\n");
    retval = -1;
  }

  /* TEST 3 */
  if (ks_treeset_contains(ts, NULL) != 0) {
    printf("TEST 3: ks_treeset_contains() should return 0 on NULL params.\n");
    retval = -1;
  }

  ks_datacont_delete(dcZ);
  ks_treeset_delete(ts);

  return retval;
}

static int ks_treeset_get_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_treeset* ts = ks_treeset_new();
  ks_treeset_add(ts, dcB);
  ks_treeset_add(ts, dcC);
  ks_treeset_add(ts, dcA);

  const ks_datacont* get_dc = ks_treeset_get(ts, -1);
  if (get_dc->c != 'C') {
    printf(
        "TEST 1: Unexpected ks_datacont value after ks_treeset_get(): %c. "
        "Expected: C.\n",
        get_dc->c);
    retval = -1;
  }

  /* TEST 2 */
  get_dc = ks_treeset_get(ts, 1);
  if (get_dc->c != 'B') {
    printf(
        "TEST 2: Unexpected ks_datacont value after ks_treeset_get(): %c. "
        "Expected: B.\n",
        get_dc->c);
    retval = -1;
  }

  /* TEST 3 */
  get_dc = ks_treeset_get(ts, 1234);
  if (get_dc != NULL) {
    printf(
        "TEST 3: Unexpected ks_datacont value after OOB ks_treeset_get(): %c. "
        "Expected: NULL.\n",
        get_dc->c);
    retval = -1;
  }

  ks_treeset_delete(ts);

  return retval;
}

static int ks_treeset_count_tests() {
  int retval = 0;

  /* Test 1 */
  ks_treeset* ts = ks_treeset_new();
  ks_treeset_add(ts, ks_datacont_new("B", KS_CHAR, 1));
  ks_treeset_add(ts, ks_datacont_new("A", KS_CHAR, 1));
  ks_treeset_add(ts, ks_datacont_new("C", KS_CHAR, 1));

  unsigned int count = ks_treeset_count(ts);
  if (count != 3) {
    printf(
        "TEST 1: Unexpected value returned from ks_treeset_count(): %d. "
        "Expected: 3.\n",
        count);
    retval = -1;
  }

  /* TEST 2 */
  ks_treeset_add(ts, ks_datacont_new("Z", KS_CHAR, 1));
  count = ks_treeset_count(ts);
  if (count != 4) {
    printf(
        "TEST 2: Unexpected value returned from ks_treeset_count(): %d. "
        "Expected 4.\n",
        count);
    retval = -1;
  }

  /* TEST 3 */
  count = ks_treeset_count(NULL);
  if (count != 0) {
    printf(
        "TEST 3: Unexpected value returned from ks_treeset_count(): %d. "
        "Expected 0.\n",
        count);
    retval = -1;
  }

  ks_treeset_delete(ts);

  return retval;
}

static int ks_treeset_height_tests() {
  int retval = 0;

  /* Test 1 */
  ks_treeset* ts = ks_treeset_new();
  ks_treeset_add(ts, ks_datacont_new("B", KS_CHAR, 1));
  ks_treeset_add(ts, ks_datacont_new("A", KS_CHAR, 1));
  ks_treeset_add(ts, ks_datacont_new("C", KS_CHAR, 1));

  unsigned int height = ks_treeset_height(ts);
  if (height != 2) {
    printf("TEST 1: Unexpected ks_treeset height: %d. Expected: 2\n", height);
    retval = -1;
  }

  /* TEST 2 */
  height = ks_treeset_height(NULL);
  if (height != 0) {
    printf(
        "TEST 2: Unexpected result from ks_treeset_height() on NULL param: %d. "
        "Expected: 0.\n",
        height);
    retval = -1;
  }

  ks_treeset_delete(ts);
  return retval;
}

static int ks_treeset_balance_tests() {
  int retval = 0;

  /* TEST 1 */
  char c = 'A';
  ks_treeset* ts = ks_treeset_new();

  for (int i = 0; i < 26; i++, c++)
    ks_treeset_add(ts, ks_datacont_new(&c, KS_CHAR, 1));

  unsigned int height = ks_treeset_height(ts);
  if (height != 26) {
    printf(
        "TEST 1: ks_treeset_height() should have returned 26. Can't continue, "
        "quitting test...\n");
    ks_treeset_delete(ts);
    return -1;
  }

  ks_treeset_balance(ts);
  height = ks_treeset_height(ts);
  if (height != 5) {
    printf(
        "TEST 1: Unexpected tree height after ks_treeset_balance(): %d. "
        "Expected: 5.\n",
        height);
    retval = -1;
  }

  ks_treeset_delete(ts);

  return retval;
}

int main() {
  int retval = 0;

  printf("\nks_treeset tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treeset_new_tests()...\n");
  if (ks_treeset_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treeset_copy_tests()...\n");
  if (ks_treeset_copy_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treeset_add_tests()...\n");
  if (ks_treeset_add_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treeset_remove_by_tests()...\n");
  if (ks_treeset_remove_by_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treeset_remove_at_tests()...\n");
  if (ks_treeset_remove_at_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treesetnode_index_tests()...\n");
  if (ks_treeset_index_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treeset_contains_tests()...\n");
  if (ks_treeset_contains_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treeset_get_tests()...\n");
  if (ks_treeset_get_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treeset_count_tests()...\n");
  if (ks_treeset_count_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treeset_height_tests()...\n");
  if (ks_treeset_height_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_treeset_balance_tests()...\n");
  if (ks_treeset_balance_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}
