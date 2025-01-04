#include <stdio.h>

#include "kylestructs/ks_datacont.h"
#include "kylestructs/ks_hashset.h"
#include "kylestructs/ks_treeset.h"
#include "kylestructs/ks_treesetnode.h"
#include "kylestructs/ks_types.h"

static int ks_hashset_new_tests() {
    int retval = 0;

    /* Test 1 */
    ks_hashset* hs = ks_hashset_new(KS_CHAR, 20);
    if (hs->type != KS_CHAR) {
        printf(
            "TEST 1: ks_hashset contains incorrect ks_datacont type value: %d. "
            "Expected: %d.\n",
            hs->type, KS_CHAR);
        retval = -1;
    }
    if (hs->num_buckets != 20) {
        printf(
            "TEST 1: ks_hashset contains incorrect num_buckets value %d. "
            "Expected "
            "20.\n",
            hs->num_buckets);
        retval = -1;
    }
    ks_hashset_delete(hs);

    return retval;
}

static int ks_hashset_copy_tests() {
    int retval = 0;

    /* Test 1 */
    ks_hashset* hs = ks_hashset_new(KS_CHAR, 2);
    ks_hashset_add(hs, ks_datacont_new("B", KS_CHAR, 1));

    ks_hashset* hs_copy = ks_hashset_copy(hs);

    if (hs_copy == NULL) {
        printf("TEST 1: Unexpected NULL return from ks_hashset_copy()\n");
        return -1;
    }

    if (hs_copy->buckets[0] != NULL) {
        if (hs_copy->buckets[0]->root->dc->c != 'B') {
            printf(
                "TEST 1: Unexpected ks_datacont value after "
                "ks_hashset_copy()\n");
            retval = -1;
        }
    } else if (hs_copy->buckets[1] != NULL) {
        if (hs_copy->buckets[1]->root->dc->c != 'B') {
            printf(
                "TEST 1: Unexpected ks_datacont value after "
                "ks_hashset_copy()\n");
            retval = -1;
        }
    } else {
        printf("TEST 1: Unexpected empty ks_hashset after ks_hashset_copy()\n");
        retval = -1;
    }

    ks_hashset_delete(hs);
    ks_hashset_delete(hs_copy);

    return retval;
}

static int ks_hashset_add_tests() {
    int retval = 0;

    /* Test 1 */
    ks_hashset* hs = ks_hashset_new(KS_CHAR, 30);
    ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
    int num = 1;
    ks_datacont* dc1 = ks_datacont_new(&num, KS_INT, 1);

    if (ks_hashset_add(hs, ks_datacont_copy(dcA)) != 0) {
        printf(
            "TEST 1: ks_hashset_add() should return 0 when adding a new "
            "item.\n");
        retval = -1;
    }

    /* Test 2 */
    if (ks_hashset_add(hs, dcA) != 1) {
        printf(
            "TEST 2: ks_hashset_add() should return 1 when trying to add an "
            "already present item.\n");
        retval = -1;
    }

    /* TEST 3 */
    if (ks_hashset_add(hs, dc1) != -1) {
        printf(
            "TEST 3: ks_hashset_add() should return -1 when adding ks_datacont "
            "that is of a different type.\n");
        retval = -1;
    }

    /* TEST 4 */
    if (ks_hashset_add(NULL, NULL) != -1) {
        printf(
            "TEST 4: ks_hashset_add() should return -1 when params are "
            "NULL.\n");
        retval = -1;
    }

    ks_hashset_delete(hs);
    ks_datacont_delete(dcA);
    ks_datacont_delete(dc1);

    return retval;
}

static int ks_hashset_remove_tests() {
    int retval = 0;

    ks_hashset* hs = ks_hashset_new(KS_CHAR, 10);
    ks_datacont* dc = ks_datacont_new("A", KS_CHAR, 1);
    ks_hashset_add(hs, ks_datacont_copy(dc));

    /* TEST 1 */
    if (ks_hashset_remove(hs, dc) != 0) {
        printf(
            "TEST 1: hahset_remove() should return 0 when removing present "
            "ks_datacont.\n");
        retval = -1;
    }

    /* TEST 2 */
    if (ks_hashset_remove(hs, dc) != -1) {
        printf(
            "TEST 2: ks_hashset_remove() should return -1 when removing "
            "not-present ks_datacont.\n");
        retval = -1;
    }

    /* TEST 3 */
    if (ks_hashset_remove(hs, NULL) != -1) {
        printf(
            "TEST 3: ks_hashset_remove() should return -1 when params are "
            "NULL.\n");
        retval = -1;
    }

    ks_datacont_delete(dc);
    ks_hashset_delete(hs);

    return retval;
}

static int ks_hashset_contains_tests() {
    int retval = 0;

    /* Test 1 */
    ks_hashset* hs = ks_hashset_new(KS_CHAR, 10);
    ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
    ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
    ks_hashset_add(hs, ks_datacont_copy(dcA));
    if (ks_hashset_contains(hs, dcA) != 1) {
        printf("TEST 1: ks_hashset_contains() should return 1.\n");
        retval = -1;
    }

    /* TEST 2 */
    if (ks_hashset_contains(hs, dcB) != 0) {
        printf(
            "TEST 2: ks_hashset_contains() should return 0 on not present "
            "ks_datacont.\n");
        retval = -1;
    }

    ks_datacont_delete(dcA);
    ks_datacont_delete(dcB);
    ks_hashset_delete(hs);

    return retval;
}

static int ks_hashset_count_tests() {
    int retval = 0;

    ks_hashset* hs = ks_hashset_new(KS_CHAR, 10);
    ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
    ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);

    int count;

    /* TEST 1 */
    if ((count = ks_hashset_count(hs)) != 0) {
        printf(
            "TEST 1: Unexpected return value from ks_hashset_count(): %d. "
            "Expected "
            "0.\n",
            count);
        retval = -1;
    }

    /* TEST 2 */
    ks_hashset_add(hs, dcA);
    if ((count = ks_hashset_count(hs)) != 1) {
        printf(
            "TEST 2: Unexpected return value from ks_hashset_count(): %d. "
            "Expected "
            "1.\n",
            count);
        retval = -1;
    }

    /* TEST 3 */
    ks_hashset_add(hs, dcB);
    if ((count = ks_hashset_count(hs)) != 2) {
        printf(
            "TEST 3: Unexpected return value from ks_hashset_count(): %d. "
            "Expected "
            "2.\n",
            count);
        retval = -1;
    }

    /* TEST 4 */
    if ((count = ks_hashset_count(NULL)) != 0) {
        printf(
            "TEST 4: Unexpected return value from ks_hashset_count(): %d. "
            "Expected "
            "0.\n",
            count);
        retval = -1;
    }

    ks_hashset_delete(hs);

    return retval;
}

static int ks_hashset_get_tests() {
    int retval = 0;

    /* TEST 1 */
    ks_hashset* hs = ks_hashset_new(KS_CHAR, 2);

    ks_treeset* ts0 = ks_treeset_new();
    ks_treeset_add(ts0, ks_datacont_new("B", KS_CHAR, 1));
    ks_treeset_add(ts0, ks_datacont_new("A", KS_CHAR, 1));
    ks_treeset_add(ts0, ks_datacont_new("C", KS_CHAR, 1));

    ks_treeset* ts1 = ks_treeset_new();
    ks_treeset_add(ts1, ks_datacont_new("E", KS_CHAR, 1));
    ks_treeset_add(ts1, ks_datacont_new("D", KS_CHAR, 1));
    ks_treeset_add(ts1, ks_datacont_new("F", KS_CHAR, 1));

    hs->buckets[0] = ts0;
    hs->buckets[1] = ts1;

    const ks_datacont* dc = ks_hashset_get(hs, -1);
    if (dc->c != 'F') {
        printf(
            "TEST 1: Unexpected ks_datacont value after ks_hashset_get(): %c. "
            "Expected: 'F'\n",
            dc->c);
        retval = -1;
    }

    dc = ks_hashset_get(hs, 5);
    if (dc->c != 'F') {
        printf(
            "TEST 1: Unexpected ks_datacont value after ks_hashset_get(): %c. "
            "Expected: 'F'\n",
            dc->c);
        retval = -1;
    }

    dc = ks_hashset_get(hs, -3);
    if (dc->c != 'D') {
        printf(
            "TEST 1: Unexpected ks_datacont value after ks_hashset_get(): %c. "
            "Expected: 'D'\n",
            dc->c);
        retval = -1;
    }

    dc = ks_hashset_get(hs, 3);
    if (dc->c != 'D') {
        printf(
            "TEST 1: Unexpected ks_datacont value after ks_hashset_get(): %c. "
            "Expected: 'D'\n",
            dc->c);
        retval = -1;
    }

    dc = ks_hashset_get(hs, -4);
    if (dc->c != 'C') {
        printf(
            "TEST 1: Unexpected ks_datacont value after ks_hashset_get(): %c. "
            "Expected: 'C'\n",
            dc->c);
        retval = -1;
    }

    dc = ks_hashset_get(hs, 2);
    if (dc->c != 'C') {
        printf(
            "TEST 1: Unexpected ks_datacont value after ks_hashset_get(): %c. "
            "Expected: 'C'\n",
            dc->c);
        retval = -1;
    }

    dc = ks_hashset_get(hs, -6);
    if (dc->c != 'A') {
        printf(
            "TEST 1: Unexpected ks_datacont value after ks_hashset_get(): %c. "
            "Expected: 'A'\n",
            dc->c);
        retval = -1;
    }

    dc = ks_hashset_get(hs, 0);
    if (dc->c != 'A') {
        printf(
            "TEST 1: Unexpected ks_datacont value after ks_hashset_get(): %c. "
            "Expected: 'A'\n",
            dc->c);
        retval = -1;
    }

    ks_hashset_delete(hs);

    return retval;
}

int main() {
    int retval = 0;

    printf("\nks_hashset tests:\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_hashset_new_tests()...\n");
    if (ks_hashset_new_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_hashset_copy_tests()...\n");
    if (ks_hashset_copy_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_hashset_add_tests()...\n");
    if (ks_hashset_add_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n\n");
    printf("Running ks_hashset_remove_tests()...\n");
    if (ks_hashset_add_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_hashset_contains_tests()...\n");
    if (ks_hashset_contains_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_hashset_count_tests()...\n");
    if (ks_hashset_count_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_hashset_get_tests()...\n");
    if (ks_hashset_get_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    return retval;
}
