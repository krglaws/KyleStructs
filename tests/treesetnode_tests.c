#include <stdio.h>

#include "kylestructs/ks_datacont.h"
#include "kylestructs/ks_treesetnode.h"
#include "kylestructs/ks_types.h"

static int ks_treesetnode_new_tests() {
    int retval = 0;

    /* TEST 1 */
    int num = 10;
    ks_datacont* dc = ks_datacont_new(&num, KS_INT, 1);
    ks_treesetnode* tsn = ks_treesetnode_new(dc);
    if (dc != tsn->dc) {
        printf(
            "TEST 1: ks_treesetnode contains unexpected ks_datacont* value.\n");
        retval = -1;
    }

    if (tsn->left != NULL || tsn->right != NULL) {
        printf(
            "TEST 1: ks_treesetnode should contain NULL left and right "
            "ks_treesetnode* values.\n");
        retval = -1;
    }
    ks_treesetnode_delete_all(tsn);

    return retval;
}

static int ks_treesetnode_copy_tests() {
    int retval = 0;

    /* TEST 1 */
    ks_treesetnode* tsn = ks_treesetnode_new(ks_datacont_new("B", KS_CHAR, 1));

    ks_treesetnode* tsn_copy = ks_treesetnode_copy(tsn);

    if (tsn_copy == NULL) {
        printf("TEST 1: Unexpected NULL return from ks_treesetnode_copy()\n");
        return -1;
    }

    if (tsn_copy->dc->c != 'B') {
        printf(
            "TEST 1: Unexpected ks_datacont value after "
            "ks_treesetnode_copy()\n");
        retval = -1;
    }

    ks_treesetnode_delete(tsn);
    ks_treesetnode_delete(tsn_copy);

    return retval;
}

static int ks_treesetnode_copy_all_tests() {
    int retval = 0;

    /* TEST 1 */
    int num = 1;
    ks_treesetnode* tsn = ks_treesetnode_new(ks_datacont_new(&num, KS_INT, 1));
    num++;
    ks_treesetnode_add(tsn, ks_datacont_new(&num, KS_INT, 1));

    ks_treesetnode* tsn_copy = ks_treesetnode_copy_all(tsn);

    if (tsn_copy == NULL) {
        printf(
            "TEST 1: Unexpected NULL return from ks_treesetnode_copy_all()\n");
        return -1;
    }

    if (tsn_copy->dc->i != 1 || tsn_copy->right->dc->i != 2) {
        printf(
            "TEST 1: Unexpected ks_datacont values after "
            "ks_treesetnode_copy_all()\n");
        retval = -1;
    }

    ks_treesetnode_delete_all(tsn);
    ks_treesetnode_delete_all(tsn_copy);

    return retval;
}

static int ks_treesetnode_add_tests() {
    int retval = 0;

    ks_treesetnode* tsn = ks_treesetnode_new(ks_datacont_new("B", KS_CHAR, 1));
    ks_datacont* left = ks_datacont_new("A", KS_CHAR, 1);
    ks_datacont* right = ks_datacont_new("C", KS_CHAR, 1);

    /* Test 1 */
    if (ks_treesetnode_add(tsn, left) != 0) {
        printf(
            "TEST 1: Unexpected error on adding (should be) left node to "
            "tsn.\n");
        retval = -1;
    }

    if (tsn->left != NULL) {
        if (tsn->left->dc->c != 'A') {
            printf(
                "TEST 1: Unexpected container value on left node: %c. "
                "Expected: "
                "%c.\n",
                tsn->left->dc->c, 'A');
            retval = -1;
        }
    } else {
        printf("TEST 1: Unexpected NULL value in left node of tsn.\n");
        retval = -1;
    }

    /* Test 2 */
    if (ks_treesetnode_add(tsn, right) != 0) {
        printf(
            "TEST 2: Unexpected error on adding (should be) left node to "
            "tsn.\n");
        retval = -1;
    }
    if (tsn->right != NULL) {
        if (tsn->right->dc->c != 'C') {
            printf(
                "TEST 2: Unexpected container value on right node: %c. "
                "Expcted: "
                "%c.\n",
                tsn->right->dc->c, 'C');
            retval = -1;
        }
    } else {
        printf("TEST 2: Unexpected NULL value in right node of tsn.\n");
        retval = -1;
    }
    ks_treesetnode_delete_all(tsn);

    return retval;
}

static int ks_treesetnode_remove_by_tests() {
    int retval = 0;

    ks_treesetnode* tsn = ks_treesetnode_new(ks_datacont_new("D", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("B", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("F", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("A", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("C", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("E", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("G", KS_CHAR, 1));

    ks_datacont* dc_Z = ks_datacont_new("Z", KS_CHAR, 1);
    ks_datacont* dc_D = ks_datacont_new("D", KS_CHAR, 1);
    ks_datacont* dc_B = ks_datacont_new("B", KS_CHAR, 1);
    ks_datacont* dc_A = ks_datacont_new("A", KS_CHAR, 1);

    if (ks_treesetnode_remove_by(&tsn, dc_Z) != -1) {
        printf(
            "TEST 1: ks_treesetnode_remove_by() should return -1 when a "
            "non-existent ks_datacont value is passed.\n");
        retval = -1;
    }

    if (ks_treesetnode_remove_by(&tsn, dc_D) != 0) {
        printf(
            "TEST 2: ks_treesetnode_remove_by() should return 0 on successful "
            "removal.\n");
        retval = -1;
    }
    if (ks_treesetnode_contains(tsn, dc_D)) {
        printf(
            "TEST 2: ks_treesetnode should not contain 'D' ks_datacont "
            "value.\n");
        retval = -1;
    }

    if (ks_treesetnode_remove_by(&tsn, dc_B) != 0) {
        printf(
            "TEST 3: ks_treesetnode_remove_by() should return 0 on successful "
            "removal.\n");
        retval = -1;
    }
    if (ks_treesetnode_contains(tsn, dc_B)) {
        printf(
            "TEST 3: ks_treesetnode should not contain 'B' ks_datacont "
            "value.\n");
        retval = -1;
    }

    if (ks_treesetnode_remove_by(&tsn, dc_A)) {
        printf(
            "TEST 4: ks_treesetnode_remove_by() should return 0 on successful "
            "removal.\n");
        retval = -1;
    }
    if (ks_treesetnode_contains(tsn, dc_A)) {
        printf(
            "TEST 4: ks_treesetnode should not contain 'A' ks_datacont "
            "value.\n");
        retval = -1;
    }
    ks_datacont_delete(dc_Z);
    ks_datacont_delete(dc_D);
    ks_datacont_delete(dc_B);
    ks_datacont_delete(dc_A);
    ks_treesetnode_delete_all(tsn);

    return retval;
}

static int ks_treesetnode_remove_at_tests() {
    int retval = 0;

    ks_treesetnode* tsn = ks_treesetnode_new(ks_datacont_new("D", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("B", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("F", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("A", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("C", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("E", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("G", KS_CHAR, 1));

    ks_datacont* dc_Z = ks_datacont_new("Z", KS_CHAR, 1);
    ks_datacont* dc_D = ks_datacont_new("D", KS_CHAR, 1);
    ks_datacont* dc_B = ks_datacont_new("B", KS_CHAR, 1);
    ks_datacont* dc_A = ks_datacont_new("A", KS_CHAR, 1);
    ks_datacont* dc_G = ks_datacont_new("G", KS_CHAR, 1);

    if (ks_treesetnode_remove_at(&tsn, 10) != -1) {
        printf(
            "TEST 1: ks_treesetnode_remove_by() should return 1 when 'index' "
            "is "
            "OOB.\n");
        retval = -1;
    }

    if (ks_treesetnode_remove_at(&tsn, 0) != 0) {
        printf(
            "TEST 2: ks_treesetnode_remove_by() should return 0 on successful "
            "removal.\n");
        retval = -1;
    }
    if (ks_treesetnode_contains(tsn, dc_A)) {
        printf(
            "TEST 2: ks_treesetnode should not contain 'A' ks_datacont "
            "value.\n");
        retval = -1;
    }

    if (ks_treesetnode_remove_at(&tsn, 0) != 0) {
        printf(
            "TEST 3: ks_treesetnode_remove_by() should return 0 on successful "
            "removal.\n");
        retval = -1;
    }
    if (ks_treesetnode_contains(tsn, dc_B)) {
        printf(
            "TEST 3: ks_treesetnode should not contain 'B' ks_datacont "
            "value.\n");
        retval = -1;
    }

    if (ks_treesetnode_remove_at(&tsn, -1)) {
        printf(
            "TEST 4: ks_treesetnode_remove_by() should return 0 on successful "
            "removal.\n");
        retval = -1;
    }
    if (ks_treesetnode_contains(tsn, dc_G)) {
        printf(
            "TEST 4: ks_treesetnode should not contain 'G' ks_datacont "
            "value.\n");
        retval = -1;
    }
    ks_datacont_delete(dc_Z);
    ks_datacont_delete(dc_D);
    ks_datacont_delete(dc_B);
    ks_datacont_delete(dc_A);
    ks_datacont_delete(dc_G);
    ks_treesetnode_delete_all(tsn);

    return retval;
}

static int ks_treesetnode_index_tests() {
    int retval = 0;

    /* TEST 1 */
    ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
    ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
    ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

    ks_treesetnode* tsn = ks_treesetnode_new(ks_datacont_copy(dcB));
    ks_treesetnode_add(tsn, ks_datacont_copy(dcA));
    ks_treesetnode_add(tsn, ks_datacont_copy(dcC));

    int index;

    if ((index = ks_treesetnode_index(tsn, dcA)) != 0) {
        printf(
            "TEST 1: Unexpected value returned from ks_treesetnode_index(): "
            "%d. "
            "Expected: 0.\n",
            index);
        retval = -1;
    }

    /* TEST 2 */
    if ((index = ks_treesetnode_index(tsn, dcB)) != 1) {
        printf(
            "TEST 2: Unexpected value returned from ks_treesetnode_index(): "
            "%d. "
            "Expected: 1.\n",
            index);
        retval = -1;
    }

    /* TEST 3 */
    if ((index = ks_treesetnode_index(tsn, dcC)) != 2) {
        printf(
            "TEST 3: Unexpected value returned from ks_treesetnode_index(): "
            "%d. "
            "Expected: 2.\n",
            index);
        retval = -1;
    }

    ks_datacont_delete(dcA);
    ks_datacont_delete(dcB);
    ks_datacont_delete(dcC);
    ks_treesetnode_delete_all(tsn);

    return retval;
}

static int ks_treesetnode_contains_tests() {
    int retval = 0;

    /* Test 1 */
    ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
    ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
    ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);
    ks_datacont* dcZ = ks_datacont_new("Z", KS_CHAR, 1);

    ks_treesetnode* tsn = ks_treesetnode_new(dcB);
    ks_treesetnode_add(tsn, dcC);
    ks_treesetnode_add(tsn, dcA);

    if (ks_treesetnode_contains(tsn, dcZ) == 1) {
        printf("TEST 1: ks_treesetnode should not contain char value 'Z'.\n");
        retval = -1;
    }

    /* TEST 2 */
    if (ks_treesetnode_contains(tsn, dcA) == 0) {
        printf("TEST 2: ks_treesetnode should contain char value 'A'.\n");
        retval = -1;
    }
    ks_datacont_delete(dcZ);
    ks_treesetnode_delete_all(tsn);

    return retval;
}

static int ks_treesetnode_get_tests() {
    int retval = 0;

    /* TEST 1 */
    ks_datacont* dcA = ks_datacont_new("A", KS_CHAR, 1);
    ks_datacont* dcB = ks_datacont_new("B", KS_CHAR, 1);
    ks_datacont* dcC = ks_datacont_new("C", KS_CHAR, 1);

    ks_treesetnode* tsn = ks_treesetnode_new(dcB);
    ks_treesetnode_add(tsn, dcC);
    ks_treesetnode_add(tsn, dcA);

    const ks_datacont* get_dc = ks_treesetnode_get(tsn, -1);
    if (get_dc->c != 'C') {
        printf(
            "TEST 1: Unexpected ks_datacont value after ks_treesetnode_get(): "
            "%c. "
            "Expected: C.\n",
            get_dc->c);
        retval = -1;
    }

    /* TEST 2 */
    get_dc = ks_treesetnode_get(tsn, 1);
    if (get_dc->c != 'B') {
        printf(
            "TEST 2: Unexpected ks_datacont value after ks_treesetnode_get(): "
            "%c. "
            "Expected: B.\n",
            get_dc->c);
        retval = -1;
    }

    /* TEST 3 */
    get_dc = ks_treesetnode_get(tsn, 1234);
    if (get_dc != NULL) {
        printf(
            "TEST 3: Unexpected ks_datacont value after OOB "
            "ks_treesetnode_get(): "
            "%c. Expected: NULL.\n",
            get_dc->c);
        retval = -1;
    }

    ks_treesetnode_delete_all(tsn);

    return retval;
}

static int ks_treesetnode_count_tests() {
    int retval = 0;

    /* Test 1 */
    ks_treesetnode* tsn = ks_treesetnode_new(ks_datacont_new("A", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("B", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("C", KS_CHAR, 1));

    unsigned int count = ks_treesetnode_count(tsn);
    if (count != 3) {
        printf(
            "TEST 1: Unexpected value returned from ks_treesetnode_count(): "
            "%d. "
            "Expected: 3.\n",
            count);
        retval = -1;
    }

    /* TEST 2 */
    ks_treesetnode_add(tsn, ks_datacont_new("Z", KS_CHAR, 1));
    count = ks_treesetnode_count(tsn);
    if (count != 4) {
        printf(
            "TEST 2: Unexpected value returned from ks_treesetnode_count(): "
            "%d. "
            "Expected 4.\n",
            count);
        retval = -1;
    }

    /* TEST 3 */
    count = ks_treesetnode_count(NULL);
    if (count != 0) {
        printf(
            "TEST 3: Unexpected value returned from ks_treesetnode_count(): "
            "%d. "
            "Expected 0.\n",
            count);
        retval = -1;
    }

    ks_treesetnode_delete_all(tsn);

    return retval;
}

static int ks_treesetnode_height_tests() {
    int retval = 0;

    /* Test 1 */
    ks_treesetnode* tsn = ks_treesetnode_new(ks_datacont_new("A", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("B", KS_CHAR, 1));
    ks_treesetnode_add(tsn, ks_datacont_new("C", KS_CHAR, 1));

    unsigned int height = ks_treesetnode_height(tsn);
    if (height != 3) {
        printf("TEST 1: Unexpected ks_treesetnode height: %d. Expected: %d\n",
               height, 3);
        retval = -1;
    }

    /* TEST 2 */
    height = ks_treesetnode_height(NULL);
    if (height != 0) {
        printf(
            "TEST 2: Unexpected result from ks_treesetnode_height() on NULL "
            "param: "
            "%d. Expected: 0.\n",
            height);
        retval = -1;
    }

    ks_treesetnode_delete_all(tsn);
    return retval;
}

static int ks_treesetnode_balance_tests() {
    int retval = 0;

    /* TEST 1 */
    char c = 'A';
    ks_treesetnode* tsn = ks_treesetnode_new(ks_datacont_new(&c, KS_CHAR, 1));
    for (int i = 1, c = 'B'; i < 26; i++, c++)
        ks_treesetnode_add(tsn, ks_datacont_new(&c, KS_CHAR, 1));

    unsigned int height = ks_treesetnode_height(tsn);
    if (height != 26) {
        printf(
            "TEST 1: ks_treesetnode_height() should have returned 16. "
            "Returned: "
            "%d. Can't continue, quitting test...\n",
            height);
        ks_treesetnode_delete_all(tsn);
        return -1;
    }

    tsn = ks_treesetnode_balance(tsn);
    height = ks_treesetnode_height(tsn);
    if (height != 5) {
        printf(
            "TEST 1: Unexpected tree height after ks_treesetnode_balance(): "
            "%d. "
            "Expected: 5.\n",
            height);
        retval = -1;
    }

    ks_treesetnode_delete_all(tsn);

    return retval;
}

int main() {
    int retval = 0;

    printf("\nks_treesetnode tests:\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treesetnode_new_tests()...\n");
    if (ks_treesetnode_new_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treesetnode_copy_tests()...\n");
    if (ks_treesetnode_copy_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treesetnode_copy_all_tests()...\n");
    if (ks_treesetnode_copy_all_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treesetnode_add_tests()...\n");
    if (ks_treesetnode_add_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treesetnode_remove_by_tests()...\n");
    if (ks_treesetnode_remove_by_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treesetnode_remove_at_tests()...\n");
    if (ks_treesetnode_remove_at_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treesetnode_index_tests()...\n");
    if (ks_treesetnode_index_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treesetnode_contains_tests()...\n");
    if (ks_treesetnode_contains_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treesetnode_get_tests()...\n");
    if (ks_treesetnode_get_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treesetnode_count_tests()...\n");
    if (ks_treesetnode_count_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treesetnode_height_tests()...\n");
    if (ks_treesetnode_height_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treesetnode_balance_tests()...\n");
    if (ks_treesetnode_balance_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    return retval;
}
