#include <stdio.h>

#include "kylestructs/ks_datacont.h"
#include "kylestructs/ks_list.h"
#include "kylestructs/ks_listnode.h"
#include "kylestructs/ks_types.h"

static int ks_list_new_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_list* ls = ks_list_new();

  if (ls->head != NULL) {
    printf("TEST 1: ls->head should be NULL.\n");
    retval = -1;
  }

  ks_list_delete(ls);

  return retval;
}

static int ks_list_copy_tests() {
  int retval = 0;

  /* TEST 1 */
  char c = 'A';
  ks_list* ls = ks_list_new();

  for (int i = 0; i < 3; i++) {
    ks_list_add(ls, ks_datacont_new(&c, KS_CHAR, 1));
    c++;
  }

  ks_list* ls_copy = ks_list_copy(ls);

  if (ls_copy == NULL) {
    printf("TEST 1: Unexpected NULL return from ks_list_copy()\n");
    return -1;
  }

  /* TEST 2 */
  if (ls_copy->head->dc->c != 'A' || ls_copy->head->next->next->dc->c != 'C') {
    printf("TEST 2: Unexpected datacont values in ks_list copy\n");
    retval = -1;
  }

  ks_list_delete(ls);
  ks_list_delete(ls_copy);

  return retval;
}

static int ks_list_add_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dc = ks_datacont_new("B", KS_CHAR, 1);

  if (ks_list_add(NULL, dc) != -1) {
    printf("TEST 1: ks_list_add() with any NULL parameters should return -1\n");
    retval = -1;
  }

  /* TEST 2 */
  ks_list* ls = ks_list_new();
  if (ks_list_add(ls, ks_datacont_new("A", KS_CHAR, 1)) != 0) {
    printf("TEST 2: ks_list_add() should return 0 when successful");
    retval = -1;
  }

  if (ls->head->dc->c != 'A') {
    printf(
        "TEST 2: unexpected ks_datacont value at first ks_list: %c. Expected: "
        "A\n",
        ls->head->dc->c);
    retval = -1;
  }

  ks_list_add(ls, dc);
  if (ls->head->next->dc->c != 'B') {
    printf(
        "TEST 2: unexpected ks_datacont value at second ks_list: %c. Expected: "
        "B\n",
        ls->head->next->dc->c);
    retval = -1;
  }

  ks_list_delete(ls);

  return retval;
}

static int ks_list_merge_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_list* lsa = ks_list_new();
  ks_list_add(lsa, ks_datacont_new("A", KS_CHAR, 1));

  ks_list* lsb = ks_list_new();
  ks_list_add(lsb, ks_datacont_new("B", KS_CHAR, 1));

  lsa = ks_list_merge(lsa, lsb);

  if (ks_list_length(lsa) != 2) {
    printf("TEST 1: Unexpected ks_list length after ks_list_merge()\n");
    retval = -1;
  }

  if (lsa->head->dc->c != 'A' || lsa->head->next->dc->c != 'B') {
    printf("TEST 1: Unexpected ks_datacont values after ks_list_merge()\n");
    retval = -1;
  }

  ks_list_delete(lsa);

  return retval;
}

static int ks_list_remove_by_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_list* ls = ks_list_new();
  ks_list_add(ls, ks_datacont_copy(dcA));
  ks_list_add(ls, ks_datacont_copy(dcB));
  ks_list_add(ls, ks_datacont_copy(dcC));

  if (ks_list_remove_by(ls, dcC) != 1) {
    printf(
        "TEST 1: ks_list_remove_by() should return 1 on successful removal\n");
    retval = -1;
  }

  /* TEST 2 */
  if (ks_list_remove_by(ls, dcC) != 0) {
    printf(
        "TEST 2: ks_list_remove_by() should return 0 when removing not-present "
        "ks_datacont\n");
    retval = -1;
  }

  /* TEST 3 */
  if (ks_list_remove_by(ls, dcB) != 1) {
    printf(
        "TEST 3: ks_list_remove_by() should return 1 on successful removal\n");
    retval = -1;
  }

  /* TEST 4 */
  if (ks_list_remove_by(ls, dcA) != 1) {
    printf(
        "TEST 4: ks_list_remove_by() should return 1 on successful removal\n");
    retval = -1;
  }

  if (ls->head != NULL) {
    printf("TEST 4: ks_list->head should be NULL after final removal\n");
    retval = -1;
  }

  /* TEST 5 */
  if (ks_list_remove_by(NULL, dcA) != -1) {
    printf(
        "TEST 5: ks_list_remove_by() should return -1 when NULL params are "
        "passed\n");
    retval = -1;
  }

  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);
  ks_datacont_delete(dcC);

  ks_list_delete(ls);

  return retval;
}

static int ks_list_remove_at_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_list* ls = ks_list_new();
  ks_list_add(ls, ks_datacont_copy(dcA));
  ks_list_add(ls, ks_datacont_copy(dcB));
  ks_list_add(ls, ks_datacont_copy(dcC));

  if (ks_list_remove_at(ls, -1) != 0) {
    printf(
        "TEST 1: ks_list_remove_at() should return 0 on successful removal\n");
    retval = -1;
  }

  /* TEST 2 */
  if (ks_list_remove_at(ls, 10) != -1) {
    printf("TEST 2: ks_list_remove_at() should return -1 on index OOB\n");
    retval = -1;
  }

  /* TEST 3 */
  if (ks_list_remove_at(ls, 0) != 0) {
    printf(
        "TEST 3: ks_list_remove_at() should return 0 on successful removal\n");
    retval = -1;
  }

  /* TEST 4 */
  if (ks_list_remove_at(ls, -1) != 0) {
    printf(
        "TEST 4: ks_list_remove_at() should return 0 on successful removal\n");
    retval = -1;
  }

  if (ls->head != NULL) {
    printf("TEST 4: ks_list should be NULL after final removal\n");
    retval = -1;
  }

  /* TEST 5 */
  if (ks_list_remove_at(ls, 0) != -1) {
    printf(
        "TEST 5: ks_list_remove_at() should return -1 when params are NULL\n");
    retval = -1;
  }

  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);
  ks_datacont_delete(dcC);

  ks_list_delete(ls);

  return retval;
}

static int ks_list_remove_all_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_list* ls = ks_list_new();
  ks_list_add(ls, ks_datacont_copy(dcA));
  ks_list_add(ls, ks_datacont_copy(dcB));
  ks_list_add(ls, ks_datacont_copy(dcA));
  ks_list_add(ls, ks_datacont_copy(dcC));
  ks_list_add(ls, ks_datacont_copy(dcA));

  int num;

  if ((num = ks_list_remove_all(ls, dcA)) != 3) {
    printf(
        "TEST 1: ks_list_remove_all() should return the number of nodes "
        "removed. Returned: %d. Expected: 3\n",
        num);
    retval = -1;
  }

  /* TEST 2 */
  if ((num = ks_list_remove_all(ls, dcB)) != 1) {
    printf(
        "TEST 2: ks_list_remove_all() should return the number of nodes "
        "removed. Returned: %d. Expected: 1\n",
        num);
    retval = -1;
  }

  /* TEST 3 */
  if ((num = ks_list_remove_all(ls, dcB)) != 0) {
    printf(
        "TEST 3: ks_list_remove_all() should return the number of nodes "
        "removed. Returned: %d. Expected: 0\n",
        num);
    retval = -1;
  }

  /* TEST 4 */
  if ((num = ks_list_remove_all(ls, dcC)) != 1) {
    printf(
        "TEST 4: ks_list_remove_all() should return the number of nodes "
        "removed. Returned: %d. Expected: 1\n",
        num);
    retval = -1;
  }

  if (ls->head != NULL) {
    printf("TEST 4: ks_list should be NULL after final removal\n");
    retval = -1;
  }

  /* TEST 5 */
  if (ks_list_remove_all(ls, dcC) != -1) {
    printf(
        "TEST 5: ks_list_remove_all() should return -1 when either param is "
        "NULL\n");
    retval = -1;
  }

  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);
  ks_datacont_delete(dcC);

  ks_list_delete(ls);

  return retval;
}

static int ks_list_replace_by_tests() {
  int retval = 0;

  /* TEST 1 */
  const ks_datacont* get_dc;
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_list* ls = ks_list_new();
  ks_list_add(ls, ks_datacont_copy(dcA));
  ks_list_add(ls, ks_datacont_copy(dcB));
  ks_list_add(ls, ks_datacont_copy(dcC));

  if (ks_list_replace_by(ls, dcB, ks_datacont_new("Z", KS_CHAR, 1)) != 0) {
    printf(
        "TEST 1: ks_list_replace_by() should return 0 on successful "
        "replacement\n");
    retval = -1;
  }

  get_dc = ks_list_get(ls, 1);
  if (get_dc->c != 'Z') {
    printf(
        "TEST 1: Unexpected ks_datacont value at 2nd ks_list following "
        "ks_list_replace_by(): %c. Expected Z\n",
        get_dc->c);
    retval = -1;
  }

  /* TEST 2 */
  if (ks_list_replace_by(ls, dcB, dcB) != -1) {
    printf(
        "TEST 2: ks_list_replace_by() should return -1 when trying to remove "
        "not-present ks_datacont\n");
    retval = -1;
  }

  /* TEST 3 */
  if (ks_list_replace_by(NULL, NULL, NULL) != -1) {
    printf(
        "TEST 3: ks_list_replace_by() should return -1 when params are NULL\n");
    retval = -1;
  }

  ks_list_delete(ls);
  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);
  ks_datacont_delete(dcC);

  return retval;
}

static int ks_list_replace_at_tests() {
  int retval = 0;

  /* TEST 1 */
  const ks_datacont* get_dc;
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_list* ls = ks_list_new();
  ks_list_add(ls, ks_datacont_copy(dcA));
  ks_list_add(ls, ks_datacont_copy(dcB));
  ks_list_add(ls, ks_datacont_copy(dcC));

  if (ks_list_replace_at(ls, ks_datacont_new("Z", KS_CHAR, 1), 1) != 0) {
    printf(
        "TEST 1: ks_list_replace_at() should return 0 on successful "
        "replacement\n");
    retval = -1;
  }

  get_dc = ks_list_get(ls, 1);
  if (get_dc->c != 'Z') {
    printf(
        "TEST 1: Unexpected ks_datacont value at 2nd ks_list following "
        "ks_list_replace_at(): %c. Expected Z\n",
        get_dc->c);
    retval = -1;
  }

  /* TEST 2 */
  if (ks_list_replace_at(ls, dcB, 10) != -1) {
    printf("TEST 2: ks_list_replace_at() should return -1 when index is OOB\n");
    retval = -1;
  }

  /* TEST 3 */
  if (ks_list_replace_at(NULL, NULL, 0) != -1) {
    printf(
        "TEST 3: ks_list_replace_at() should return -1 when params are NULL\n");
    retval = -1;
  }

  ks_list_delete(ls);
  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);
  ks_datacont_delete(dcC);

  return retval;
}

static int ks_list_replace_all_tests() {
  int retval = 0;

  /* TEST 1 */
  const ks_datacont* get_dc;
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_list* ls = ks_list_new();
  ks_list_add(ls, ks_datacont_copy(dcA));
  ks_list_add(ls, ks_datacont_copy(dcB));
  ks_list_add(ls, ks_datacont_copy(dcA));
  ks_list_add(ls, ks_datacont_copy(dcC));
  ks_list_add(ls, ks_datacont_copy(dcA));

  if (ks_list_replace_all(ls, dcA, ks_datacont_new("Z", KS_CHAR, 1)) != 3) {
    printf(
        "TEST 1: ks_list_replace_all() should return the number of "
        "replacements that occurred\n");
    retval = -1;
  }

  get_dc = ks_list_get(ls, -1);
  if (get_dc->c != 'Z') {
    printf(
        "TEST 1: Unexpected ks_datacont value in last node after "
        "ks_list_replace_all(): %c. Expected: Z\n",
        get_dc->c);
    retval = -1;
  }

  /* TEST 2 */
  if (ks_list_replace_all(ls, dcA, get_dc) != 0) {
    printf(
        "TEST 2: ks_list_replace_all() should return 0 when replacing "
        "not-present ks_datacont value\n");
    retval = -1;
  }

  ks_list_delete(ls);
  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);
  ks_datacont_delete(dcC);

  return retval;
}

static int ks_list_insert_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);
  const ks_datacont* get_dc;
  ks_list* ls = ks_list_new();
  ks_list_add(ls, ks_datacont_copy(dcA));
  ks_list_add(ls, ks_datacont_copy(dcC));

  if (ks_list_insert(ls, ks_datacont_copy(dcB), 0) != 0) {
    printf(
        "TEST 1: ks_list_insert() should return 0 on successful insertion\n");
    retval = -1;
  }

  get_dc = ks_list_get(ls, 0);
  if (get_dc->c != 'B') {
    printf(
        "TEST 1: Unexpected ks_datacont value at first ks_list after "
        "ks_list_insert(): %c. Expected B\n",
        get_dc->c);
    retval = -1;
  }

  /* TEST 2 */
  if (ks_list_insert(ls, ks_datacont_copy(dcB), -1) != 0) {
    printf(
        "TEST 2: ks_list_insert() should return 0 on successful insertion\n");
    retval = -1;
  }

  get_dc = ks_list_get(ls, -2);
  if (get_dc->c != 'B') {
    printf(
        "TEST 2: Unexpected ks_datacont value at 2nd to last ks_list after "
        "ks_list_insert(): %d. Expected: B\n",
        get_dc->c);
    retval = -1;
  }

  /* TEST 3 */
  if (ks_list_insert(ls, NULL, 2) != -1) {
    printf(
        "TEST 3: ks_list_insert() should return -1 when any params are NULL\n");
    retval = -1;
  }

  ks_list_delete(ls);
  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);
  ks_datacont_delete(dcC);

  return retval;
}

static int ks_list_push_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_list* ls = ks_list_new();

  if (ks_list_push(ls, ks_datacont_new("A", KS_CHAR, 1)) != 0) {
    printf("TEST 1: ks_list_push() should return 0 on success\n");
    retval = -1;
  }

  /* TEST 2 */
  if (ks_list_push(ls, ks_datacont_new("B", KS_CHAR, 1)) != 0) {
    printf("TEST 2: ks_list_push() should return 0 on success\n");
    retval = -1;
  }

  /* TEST 3 */
  if (ks_list_push(NULL, NULL) != -1) {
    printf("TEST 3: ks_list_push() should return -1 when params are NULL\n");
    retval = -1;
  }

  ks_list_delete(ls);

  return retval;
}

static int ks_list_pop_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_list* ls = ks_list_new();
  ks_list_push(ls, ks_datacont_new("A", KS_CHAR, 1));
  ks_list_push(ls, ks_datacont_new("B", KS_CHAR, 1));
  ks_list_push(ls, ks_datacont_new("C", KS_CHAR, 1));

  ks_datacont* dc = ks_list_pop(ls);
  if (dc->c != 'C') {
    printf(
        "TEST 1: Unexpected ks_datacont* returned from ks_list_pop(): %c. "
        "Expected: C\n",
        dc->c);
    retval = -1;
  }
  ks_datacont_delete(dc);

  /* TEST 2 */
  dc = ks_list_pop(ls);
  if (dc->c != 'B') {
    printf(
        "TEST 2: Unexpected ks_datacont* returned from ks_list_pop(): %c. "
        "Expected: B\n",
        dc->c);
    retval = -1;
  }
  ks_datacont_delete(dc);

  /* TEST 3 */
  dc = ks_list_pop(ls);
  if (dc->c != 'A') {
    printf(
        "TEST 3: Unexpected ks_datacont* returned from ks_list_pop(): %c. "
        "Expected: A\n",
        dc->c);
    retval = -1;
  }
  ks_datacont_delete(dc);

  /* TEST 4 */
  dc = ks_list_pop(ls);
  if (dc != NULL) {
    printf("TEST 4: ks_list_pop() should return NULL on empty ks_list*\n");
    retval = -1;
  }

  ks_list_delete(ls);

  return retval;
}

static int ks_list_peek_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_list* ls = ks_list_new();
  ks_list_push(ls, ks_datacont_new("A", KS_CHAR, 1));

  const ks_datacont* dc = ks_list_peek(ls);

  if (dc->c != 'A') {
    printf(
        "TEST 1: Unexpected ks_datacont* returned from ks_list_peek(): %c. "
        "Expected: 'A'\n",
        dc->c);
    retval = -1;
  }

  if (ks_list_remove_at(ls, 0) != 0) {
    printf(
        "TEST 1: ks_list_peek() should not remove from ks_list, only return "
        "reference.\n");
    retval = -1;
  }

  /* TEST 2 */
  if (ks_list_peek(ls) != NULL) {
    printf("TEST 2: ks_list_peek() should return NULL on empty list.\n");
    retval = -1;
  }

  ks_list_delete(ls);

  return retval;
}

static int ks_list_enqueue_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_list* ls = ks_list_new();

  if (ks_list_enqueue(ls, ks_datacont_new("A", KS_CHAR, 1)) != 0) {
    printf("TEST 1: ks_list_enqueue() should return 0 on success\n");
    retval = -1;
  }

  /* TEST 2 */
  if (ks_list_enqueue(ls, ks_datacont_new("B", KS_CHAR, 1)) != 0) {
    printf("TEST 2: ks_list_enqueue() should return 0 on success\n");
    retval = -1;
  }

  /* TEST 3 */
  if (ks_list_enqueue(NULL, NULL) != -1) {
    printf("TEST 3: ks_list_enqueue() should return -1 when params are NULL\n");
    retval = -1;
  }

  ks_list_delete(ls);

  return retval;
}

static int ks_list_dequeue_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_list* ls = ks_list_new();
  ks_list_enqueue(ls, ks_datacont_new("A", KS_CHAR, 1));
  ks_list_enqueue(ls, ks_datacont_new("B", KS_CHAR, 1));
  ks_list_enqueue(ls, ks_datacont_new("C", KS_CHAR, 1));

  ks_datacont* dc = ks_list_dequeue(ls);
  if (dc->c != 'A') {
    printf(
        "TEST 1: Unexpected ks_datacont* returned from ks_list_dequeue(): %c. "
        "Expected: A\n",
        dc->c);
    retval = -1;
  }
  ks_datacont_delete(dc);

  /* TEST 2 */
  dc = ks_list_dequeue(ls);
  if (dc->c != 'B') {
    printf(
        "TEST 2: Unexpected ks_datacont* returned from ks_list_dequeue(): %c. "
        "Expected: B\n",
        dc->c);
    retval = -1;
  }
  ks_datacont_delete(dc);

  /* TEST 3 */
  dc = ks_list_dequeue(ls);
  if (dc->c != 'C') {
    printf(
        "TEST 3: Unexpected ks_datacont* returned from ks_list_dequeue(): %c. "
        "Expected: C\n",
        dc->c);
    retval = -1;
  }
  ks_datacont_delete(dc);

  /* TEST 4 */
  dc = ks_list_dequeue(ls);
  if (dc != NULL) {
    printf("TEST 4: ks_list_dequeue() should return NULL on empty ks_list\n");
    retval = -1;
  }

  ks_list_delete(ls);

  return retval;
}

static int ks_list_index_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

  ks_list* ls = ks_list_new();
  ks_list_add(ls, dcA);
  ks_list_add(ls, dcB);
  ks_list_add(ls, dcC);
  ks_list_add(ls, ks_datacont_copy(dcA));

  int index;

  if ((index = ks_list_index(ls, dcA)) != 0) {
    printf(
        "TEST 1: Unexpected index for ks_datacont value 'A': %d. Expected: 0\n",
        index);
    retval = -1;
  }

  /* TEST 2 */
  if ((index = ks_list_index(ls, dcB)) != 1) {
    printf(
        "TEST 2: Unexpected index for ks_datacont value 'B': %d. Expected: 1\n",
        index);
    retval = -1;
  }

  /* TEST 3 */
  if ((index = ks_list_index(ls, dcC)) != 2) {
    printf(
        "TEST 3: Unexpected index for ks_datacont value 'C': %d. Expected: 2\n",
        index);
    retval = -1;
  }

  ks_list_delete(ls);

  return retval;
}

static int ks_list_get_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_list* ls = ks_list_new();
  ks_list_add(ls, ks_datacont_new("A", KS_CHAR, 1));
  ks_list_add(ls, ks_datacont_new("B", KS_CHAR, 1));
  ks_list_add(ls, ks_datacont_new("C", KS_CHAR, 1));

  const ks_datacont* dcC = ks_list_get(ls, 2);
  if (dcC->c != 'C') {
    printf("TEST 1: Unexpected return value: %c. Expected: C\n", dcC->c);
    retval = -1;
  }

  /* TEST 2 */
  const ks_datacont* dcA = ks_list_get(ls, 0);
  if (dcA->c != 'A') {
    printf("TEST 2: Unexpected return value: %c. Expected: A\n", dcA->c);
    retval = -1;
  }

  /* TEST 3 */
  const ks_datacont* dcB = ks_list_get(ls, 1);
  if (dcB->c != 'B') {
    printf("TEST 3: Unexpected return value: %c. Expected: B\n", dcB->c);
    retval = -1;
  }

  ks_list_delete(ls);

  return retval;
}

static int ks_list_count_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
  ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
  ks_list* ls = ks_list_new();
  ks_list_add(ls, ks_datacont_copy(dcA));
  ks_list_add(ls, ks_datacont_copy(dcA));
  ks_list_add(ls, ks_datacont_copy(dcB));
  ks_list_add(ls, ks_datacont_copy(dcA));

  int count;

  if ((count = ks_list_count(ls, dcA)) != 3) {
    printf("TEST 1: Unexpected ks_list_count() result: %d. Expected: 3\n",
           count);
    retval = -1;
  }

  /* TEST 2 */
  if ((count = ks_list_count(ls, dcB)) != 1) {
    printf("TEST 2: Unexpected ks_list_count() result: %d. Expected: 1\n",
           count);
    retval = -1;
  }

  ks_list_delete(ls);
  ks_datacont_delete(dcA);
  ks_datacont_delete(dcB);

  return retval;
}

static int ks_list_length_tests() {
  int retval = 0;

  /* TEST 1 */
  ks_datacont* dc = ks_datacont_new("A", KS_CHAR, 1);
  ks_list* ls = ks_list_new();
  ks_list_add(ls, ks_datacont_copy(dc));
  ks_list_add(ls, ks_datacont_copy(dc));
  ks_list_add(ls, ks_datacont_copy(dc));

  int len;
  if ((len = ks_list_length(ls)) != 3) {
    printf("TEST 1: Unexpected ks_list_length() result: %d. Expected: 3\n",
           len);
    retval = -1;
  }

  ks_list_delete(ls);
  ks_datacont_delete(dc);

  return retval;
}

int main() {
  int retval = 0;

  printf("\nks_list tests:\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_new_tests()...\n");
  if (ks_list_new_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_copy_tests()...\n");
  if (ks_list_copy_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_add_tests()...\n");
  if (ks_list_add_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_merge_tests()...\n");
  if (ks_list_merge_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_remove_by_tests()...\n");
  if (ks_list_remove_by_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_remove_at_tests()...\n");
  if (ks_list_remove_at_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_remove_all_tests()...\n");
  if (ks_list_remove_all_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_replace_by_tests()...\n");
  if (ks_list_replace_by_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_replace_at_tests()...\n");
  if (ks_list_replace_at_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_replace_all_tests()...\n");
  if (ks_list_replace_all_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_insert_tests()...\n");
  if (ks_list_insert_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_push_tests()...\n");
  if (ks_list_push_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_pop_tests()...\n");
  if (ks_list_pop_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_peek_tests()...\n");
  if (ks_list_peek_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_enqueue_tests()...\n");
  if (ks_list_enqueue_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_dequeue_tests()...\n");
  if (ks_list_dequeue_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_index_tests()...\n");
  if (ks_list_index_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_get_tests()...\n");
  if (ks_list_get_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_count_tests()...\n");
  if (ks_list_count_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  printf("==-----------------------------------==\n");
  printf("Running ks_list_length_tests()...\n");
  if (ks_list_length_tests()) retval = -1;
  printf("done.\n");
  printf("==-----------------------------------==\n\n");

  return retval;
}
