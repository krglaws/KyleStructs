#include <stdio.h>

#include "kylestructs/ks_datacont.h"
#include "kylestructs/ks_listnode.h"
#include "kylestructs/ks_treemapnode.h"
#include "kylestructs/ks_types.h"

static int ks_treemapnode_new_tests() {
    int retval = 0;

    /* TEST 1 */
    int one = 1;
    ks_datacont* key = ks_datacont_new(&one, KS_INT, 1);
    ks_datacont* val = ks_datacont_new("A", KS_CHAR, 1);

    ks_treemapnode* tmn = ks_treemapnode_new(key, val);
    if (tmn->key != key) {
        printf(
            "TEST 1: ks_treemapnode key contains unexpected ks_datacont "
            "value.\n");
        retval = -1;
    }
    if (tmn->value != val) {
        printf(
            "TEST 1: ks_treemapnode value contains unexpected ks_datacont "
            "value.\n");
        retval = -1;
    }
    if (tmn->left != NULL) {
        printf("TEST 1: ks_treemapnode left should be NULL.\n");
        retval = -1;
    }
    if (tmn->right != NULL) {
        printf("TEST 1: ks_treemapnode right should be NULL.\n");
        retval = -1;
    }
    ks_treemapnode_delete_all(tmn);

    return retval;
}

static int ks_treemapnode_copy_tests() {
    int retval = 0;

    /* TEST 1 */
    ks_treemapnode* tmn = ks_treemapnode_new(ks_datacont_new("B", KS_CHAR, 1),
                                             ks_datacont_new("B", KS_CHAR, 1));
    ks_treemapnode_add(tmn, ks_datacont_new("A", KS_CHAR, 1),
                       ks_datacont_new("A", KS_CHAR, 1));

    ks_treemapnode* tmn_copy = ks_treemapnode_copy(tmn);

    if (tmn_copy == NULL) {
        printf("TEST 1: Unexpected NULL return from ks_treemapnode_copy()\n");
        return -1;
    }

    if (tmn_copy->left != NULL || tmn_copy->right != NULL) {
        printf(
            "TEST 1: left and right children of ks_treemapnode_copy() result "
            "should be NULL\n");
        retval = -1;
    }

    if (tmn_copy->key->c != 'B') {
        printf(
            "TEST 1: Unexpected ks_datacont value in ks_treemapnode_copy() "
            "result\n");
        retval = -1;
    }

    ks_treemapnode_delete_all(tmn);
    ks_treemapnode_delete(tmn_copy);

    return retval;
}

static int ks_treemapnode_copy_all_tests() {
    int retval = 0;

    /* TEST 1 */
    ks_treemapnode* tmn = ks_treemapnode_new(ks_datacont_new("B", KS_CHAR, 1),
                                             ks_datacont_new("B", KS_CHAR, 1));
    ks_treemapnode_add(tmn, ks_datacont_new("A", KS_CHAR, 1),
                       ks_datacont_new("A", KS_CHAR, 1));

    ks_treemapnode* tmn_copy = ks_treemapnode_copy_all(tmn);

    if (tmn_copy == NULL) {
        printf("TEST 1: Unexpected NULL return from ks_treemapnode_copy()\n");
        return -1;
    }

    if (tmn_copy->left == NULL) {
        printf(
            "TEST 1: left child of ks_treemapnode_copy_all() result should be "
            "non-NULL\n");
        retval = -1;
    }

    if (tmn_copy->right != NULL) {
        printf(
            "TEST 1: right child of ks_treemapnode_copy_all() result should be "
            "NULL\n");
        retval = -1;
    }

    if (tmn_copy->key->c != 'B' || tmn_copy->left->key->c != 'A') {
        printf(
            "TEST 1: Unexpected ks_datacont value in ks_treemapnode_copy() "
            "result\n");
        retval = -1;
    }

    ks_treemapnode_delete_all(tmn);
    ks_treemapnode_delete_all(tmn_copy);

    return retval;
}

static int ks_treemapnode_add_tests() {
    int retval = 0;

    /* TEST 1 */
    int one = 1;
    ks_datacont* key1 = ks_datacont_new(&one, KS_INT, 1);
    ks_datacont* val1 = ks_datacont_new("A", KS_CHAR, 1);

    int two = 2;
    ks_datacont* key2 = ks_datacont_new(&two, KS_INT, 1);
    ks_datacont* val2 = ks_datacont_new("B", KS_CHAR, 1);

    int three = 3;
    ks_datacont* key3 = ks_datacont_new(&three, KS_INT, 1);
    ks_datacont* val3 = ks_datacont_new("C", KS_CHAR, 1);

    ks_treemapnode* root = ks_treemapnode_new(key2, val2);

    if (ks_treemapnode_add(root, key1, val1)) {
        printf(
            "TEST 1: ks_treemapnode_add() should return zero when adding a new "
            "pair.\n");
        retval = -1;
    }
    if (root->left == NULL) {
        printf("TEST 1: expected root->left to be non-NULL.\n");
        retval = -1;
    }

    /* TEST 2 */
    if (ks_treemapnode_add(root, key3, val3)) {
        printf(
            "TEST 2: ks_treemapnode_add() should return zero when adding a new "
            "pair.\b");
        retval = -1;
    }
    if (root->right == NULL) {
        printf("TEST 2: expected root->right to be non-NULL.\n");
        retval = -1;
    }

    ks_treemapnode_delete_all(root);

    return retval;
}

static int ks_treemapnode_remove_tests() {
    int retval = 0;

    /* TEST 1 */
    int one = 1;
    ks_datacont* key1 = ks_datacont_new(&one, KS_INT, 1);
    ks_datacont* val1 = ks_datacont_new("A", KS_CHAR, 1);

    int two = 2;
    ks_datacont* key2 = ks_datacont_new(&two, KS_INT, 1);
    ks_datacont* val2 = ks_datacont_new("B", KS_CHAR, 1);

    int three = 3;
    ks_datacont* key3 = ks_datacont_new(&three, KS_INT, 1);
    ks_datacont* val3 = ks_datacont_new("C", KS_CHAR, 1);

    ks_treemapnode* root = ks_treemapnode_new(key2, val2);
    key2 = ks_datacont_copy(key2);

    ks_treemapnode_add(root, key1, val1);
    key1 = ks_datacont_copy(key1);

    ks_treemapnode_add(root, key3, val3);
    key3 = ks_datacont_copy(key3);

    if (ks_treemapnode_remove(&root, key2)) {
        printf("TEST 1: Failed to remove root node from ks_treemapnode.\n");
        retval = -1;
    }
    if (root->key->i != 3) {
        printf("TEST 1: Unexpected root key value: %d. Expected: 3.\n",
               root->key->i);
        retval = -1;
    }
    if (root->right != NULL) {
        printf("TEST 1: Expected right node to be NULL.\n");
        retval = -1;
    }

    /* TEST 2 */
    if (ks_treemapnode_remove(&root, key2) != -1) {
        printf(
            "TEST 2: treemap_remove() should return -1 when removing "
            "not-present "
            "node key.\n");
        retval = -1;
    }

    /* TEST 3 */
    if (ks_treemapnode_remove(&root, key1)) {
        printf("TEST 3: Failed to remove left node from ks_treemapnode.\n");
        retval = -1;
    }
    if (root->left != NULL) {
        printf("TEST 3: Expected left node to be NULL.\n");
        retval = -1;
    }

    /* TEST 4 */
    if (ks_treemapnode_remove(&root, key3)) {
        printf("TEST 4: failed to remove last node in ks_treemapnode.\n");
        retval = -1;
    }
    if (root != NULL) {
        printf(
            "TEST 4: Expected root node to be NULL after last "
            "treemap_remove().\n");
        retval = -1;
    }

    ks_datacont_delete(key1);
    ks_datacont_delete(key2);
    ks_datacont_delete(key3);

    return retval;
}

static int ks_treemapnode_get_tests() {
    int retval = 0;

    /* TEST 1 */
    int one = 1;
    ks_datacont* key1 = ks_datacont_new(&one, KS_INT, 1);
    ks_datacont* val1 = ks_datacont_new("A", KS_CHAR, 1);

    int two = 2;
    ks_datacont* key2 = ks_datacont_new(&two, KS_INT, 1);
    ks_datacont* val2 = ks_datacont_new("B", KS_CHAR, 1);

    int three = 3;
    ks_datacont* key3 = ks_datacont_new(&three, KS_INT, 1);
    ks_datacont* val3 = ks_datacont_new("C", KS_CHAR, 1);

    int four = 4;
    ks_datacont* not_there = ks_datacont_new(&four, KS_INT, 1);

    ks_treemapnode* root = ks_treemapnode_new(key2, val2);
    ks_treemapnode_add(root, key1, val1);
    ks_treemapnode_add(root, key3, val3);

    const ks_datacont* val = ks_treemapnode_get(root, key2);
    if (val->c != val2->c) {
        printf("TEST 1: Unexpected ks_datacont value: %c. Expected: %c.\n",
               val->c, val2->c);
        retval = -1;
    }

    /* TEST 2 */
    val = ks_treemapnode_get(root, key1);
    if (val->c != val1->c) {
        printf("TEST 2: Unexpected ks_datacont value: %c. Expected: %c.\n",
               val->c, val1->c);
        retval = -1;
    }

    /* TEST 3 */
    val = ks_treemapnode_get(root, not_there);
    if (val != NULL) {
        printf(
            "TEST 3: ks_treemapnode_get() should return NULL on not-present "
            "key "
            "value.\n");
        retval = -1;
    }

    ks_treemapnode_delete_all(root);
    ks_datacont_delete(not_there);

    return retval;
}

static int ks_treemapnode_get_key_tests() {
    int retval = 0;

    /* TEST 1 */
    int one = 1;
    ks_datacont* key1 = ks_datacont_new(&one, KS_INT, 1);
    ks_datacont* val1 = ks_datacont_new("A", KS_CHAR, 1);

    int two = 2;
    ks_datacont* key2 = ks_datacont_new(&two, KS_INT, 1);
    ks_datacont* val2 = ks_datacont_new("B", KS_CHAR, 1);

    int three = 3;
    ks_datacont* key3 = ks_datacont_new(&three, KS_INT, 1);
    ks_datacont* val3 = ks_datacont_new("C", KS_CHAR, 1);

    ks_treemapnode* root = ks_treemapnode_new(key2, val2);
    ks_treemapnode_add(root, key1, val1);
    ks_treemapnode_add(root, key3, val3);

    const ks_datacont* get_dc = ks_treemapnode_get_key(root, 0);
    if (get_dc->i != 1) {
        printf("TEST 1: Unexpected ks_datacont value: %d. Expected 1.\n",
               get_dc->i);
        retval = -1;
    }

    /* TEST 2 */
    get_dc = ks_treemapnode_get_key(root, 1);
    if (get_dc->i != 2) {
        printf("TEST 2: Unexpected ks_datacont value: %d. Expected 2.\n",
               get_dc->i);
        retval = -1;
    }

    /* TEST 3 */
    get_dc = ks_treemapnode_get_key(root, 2);
    if (get_dc->i != 3) {
        printf("TEST 3: Unexpected ks_datacont value: %d. Expected 3.\n",
               get_dc->i);
        retval = -1;
    }

    /* TEST 4 */
    get_dc = ks_treemapnode_get_key(root, 3);
    if (get_dc != NULL) {
        printf(
            "TEST 4: Expected OOB call to ks_treemapnode_get_key() to return "
            "NULL.\n");
        retval = -1;
    }

    ks_treemapnode_delete_all(root);

    return retval;
}

static int ks_treemapnode_count_tests() {
    int retval = 0;

    /* TEST 1 */
    int one = 1;
    ks_datacont* key1 = ks_datacont_new(&one, KS_INT, 1);
    ks_datacont* val1 = ks_datacont_new("A", KS_CHAR, 1);

    int two = 2;
    ks_datacont* key2 = ks_datacont_new(&two, KS_INT, 1);
    ks_datacont* val2 = ks_datacont_new("B", KS_CHAR, 1);

    int three = 3;
    ks_datacont* key3 = ks_datacont_new(&three, KS_INT, 1);
    ks_datacont* val3 = ks_datacont_new("C", KS_CHAR, 1);

    int four = 4;
    ks_datacont* key4 = ks_datacont_new(&four, KS_INT, 1);
    ks_datacont* val4 = ks_datacont_new("D", KS_CHAR, 1);

    ks_treemapnode* root = ks_treemapnode_new(key2, val2);
    ks_treemapnode_add(root, key1, val1);
    ks_treemapnode_add(root, key3, val3);
    ks_treemapnode_add(root, key4, val4);

    int count = ks_treemapnode_count(root);
    if (count != 4) {
        printf(
            "TEST 1: Unexpected ks_treemapnode_count() return value: %d. "
            "Expected: "
            "4.\n",
            count);
        retval = -1;
    }

    /* TEST 2 */
    count = ks_treemapnode_count(NULL);
    if (count != 0) {
        printf(
            "TEST 2: Unexpected ks_treemapnode_count() return value: %d. "
            "Expected: "
            "4.\n",
            count);
        retval = -1;
    }

    ks_treemapnode_delete_all(root);

    return retval;
}

static int ks_treemapnode_height_tests() {
    int retval = 0;

    /* TEST 1 */
    int one = 1;
    ks_datacont* key1 = ks_datacont_new(&one, KS_INT, 1);
    ks_datacont* val1 = ks_datacont_new("A", KS_CHAR, 1);

    int two = 2;
    ks_datacont* key2 = ks_datacont_new(&two, KS_INT, 1);
    ks_datacont* val2 = ks_datacont_new("B", KS_CHAR, 1);

    int three = 3;
    ks_datacont* key3 = ks_datacont_new(&three, KS_INT, 1);
    ks_datacont* val3 = ks_datacont_new("C", KS_CHAR, 1);

    int four = 4;
    ks_datacont* key4 = ks_datacont_new(&four, KS_INT, 1);
    ks_datacont* val4 = ks_datacont_new("D", KS_CHAR, 1);

    ks_treemapnode* root = ks_treemapnode_new(key2, val2);
    ks_treemapnode_add(root, key1, val1);
    ks_treemapnode_add(root, key3, val3);
    ks_treemapnode_add(root, key4, val4);

    int height = ks_treemapnode_height(root);
    if (height != 3) {
        printf(
            "TEST 1: Unexpected ks_treemapnode_height() return value: %d. "
            "Expected: 3.\n",
            height);
        retval = -1;
    }

    /* TEST 2 */
    height = ks_treemapnode_height(NULL);
    if (height != 0) {
        printf(
            "TEST 2: Unexpected ks_treemapnode_height() return value: %d. "
            "Expected: 0.\n",
            height);
        retval = -1;
    }

    ks_treemapnode_delete_all(root);

    return retval;
}

static int ks_treemapnode_balance_tests() {
    int retval = 0;

    /* TEST 1 */
    char c = 'A';
    int i = 0;
    ks_treemapnode* tmn = ks_treemapnode_new(ks_datacont_new(&i, KS_INT, 1),
                                             ks_datacont_new(&c, KS_CHAR, 1));
    for (int i = 0; i < 26; i++, c++)
        ks_treemapnode_add(tmn, ks_datacont_new(&i, KS_INT, 1),
                           ks_datacont_new(&c, KS_CHAR, 1));

    unsigned int height = ks_treemapnode_height(tmn);
    if (height != 26) {
        printf(
            "TEST 1: ks_treemapnode_height() should have returned 26. Can't "
            "continue, quitting test...\n");
        ks_treemapnode_delete_all(tmn);
        return -1;
    }

    tmn = ks_treemapnode_balance(tmn);
    height = ks_treemapnode_height(tmn);
    if (height != 5) {
        printf(
            "TEST 1: Unexpected tree height after ks_treemapnode_balance(): "
            "%d. "
            "Expected: 5.\n",
            height);
        retval = -1;
    }

    ks_treemapnode_delete_all(tmn);

    return retval;
}

int main() {
    int retval = 0;

    printf("\nks_treemapnode tests:\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treemapnode_new_tests()...\n");
    if (ks_treemapnode_new_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treemapnode_copy_tests()...\n");
    if (ks_treemapnode_copy_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treemapnode_copy_all_tests()...\n");
    if (ks_treemapnode_copy_all_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treemapnode_add_tests()...\n");
    if (ks_treemapnode_add_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treemapnode_remove_tests()...\n");
    if (ks_treemapnode_remove_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treemapnode_get_tests()...\n");
    if (ks_treemapnode_get_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treemapnode_get_key_tests()...\n");
    if (ks_treemapnode_get_key_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treemapnode_count_tests()...\n");
    if (ks_treemapnode_count_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treemapnode_height_tests()...\n");
    if (ks_treemapnode_height_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_treemapnode_balance_tests()...\n");
    if (ks_treemapnode_balance_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    return retval;
}
