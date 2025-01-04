#include <stdio.h>

#include "kylestructs/ks_datacont.h"
#include "kylestructs/ks_hashmap.h"
#include "kylestructs/ks_hashset.h"
#include "kylestructs/ks_list.h"
#include "kylestructs/ks_listnode.h"
#include "kylestructs/ks_treemap.h"
#include "kylestructs/ks_treemapnode.h"
#include "kylestructs/ks_treeset.h"
#include "kylestructs/ks_treesetnode.h"
#include "kylestructs/ks_types.h"

static int ks_datacont_new_tests() {
    int retval = 0;

    /* Test 1 */
    ks_datacont* char_cont = ks_datacont_new("A", KS_CHAR, 1);
    if (char_cont->type != KS_CHAR) {
        printf("TEST 1: Unexpected container type: %d. Expected: %d\n",
               char_cont->type, KS_CHAR);
        retval = -1;
    }
    if (char_cont->size != 1) {
        printf("TEST 1: Unexpected size value: %ld. Expected: %d\n",
               char_cont->size, 1);
        retval = -1;
    }
    if (char_cont->c != 'A') {
        printf("TEST 1: Unexpected container value: %c. Expected: %c\n",
               char_cont->c, 'A');
        retval = -1;
    }
    ks_datacont_delete(char_cont);

    /* Test 2 */
    unsigned int num = 0x12345678;
    ks_datacont* uint_cont = ks_datacont_new(&num, KS_UINT, 1);
    if (uint_cont->type != KS_UINT) {
        printf("TEST 2: Unexpected container type: %d. Expected: %d\n",
               uint_cont->type, KS_UINT);
        retval = -1;
    }
    if (uint_cont->size != 1) {
        printf("TEST 2: Unexpected size value: %ld. Expected: %d\n",
               uint_cont->size, 1);
        retval = -1;
    }
    if (uint_cont->ui != num) {
        printf("TEST 2: Unexpected container value: %d. Expected: %d\n",
               uint_cont->ui, num);
        retval = -1;
    }
    ks_datacont_delete(uint_cont);

    return retval;
}

static int ks_datacont_copy_tests() {
    int retval = 0;

    int num = 1234;
    ks_datacont* dc1 = ks_datacont_new(&num, KS_INT, 1);
    ks_datacont* dc2 = ks_datacont_copy(dc1);

    /* TEST 1 */
    if (dc1 == dc2) {
        printf(
            "TEST 1: ks_datacont_copy() should return different reference.\n");
        retval = -1;
    }

    /* TEST 2 */
    enum ks_comparison result = ks_datacont_compare(dc1, dc2);
    if (result != KS_EQUAL) {
        printf(
            "TEST 2: dc1 and dc2 should be equal. ks_datacont_compare() "
            "returned: "
            "%d.\n",
            result);
        printf("\ndc1->type = %d\n", dc1->type);
        printf("dc2->type = %d\n", dc2->type);
        printf("\ndc1->size = %ld\n", dc1->size);
        printf("dc2->size = %ld\n", dc2->size);
        printf("\ndc1->cp = %s\n", dc1->cp);
        printf("dc2->cp = %s\n", dc2->cp);
        retval = -1;
    }

    ks_datacont_delete(dc1);
    ks_datacont_delete(dc2);

    return retval;
}

static int ks_datacont_compare_tests() {
    int retval = 0;
    int num;
    enum ks_comparison result;
    ks_datacont* dca;
    ks_datacont* dcb;

    /* Test 1 */
    num = 10;
    dca = ks_datacont_new(&num, KS_INT, 1);
    num = 11;
    dcb = ks_datacont_new(&num, KS_INT, 1);
    result = ks_datacont_compare(dca, dcb);
    if (result != KS_LESSTHAN) {
        printf("TEST 1: Unexpected comparison result: %d. Expected: %d\n",
               result, KS_LESSTHAN);
        retval = -1;
    }
    ks_datacont_delete(dca);
    ks_datacont_delete(dcb);

    /* Test 2 */
    dca = ks_datacont_new("A", KS_CHAR, 1);
    dcb = ks_datacont_new("A", KS_CHAR, 1);
    result = ks_datacont_compare(dca, dcb);
    if (result != KS_EQUAL) {
        printf("TEST 2: Unexpected comparison result: %d. Expected: %d\n",
               result, KS_EQUAL);
        retval = -1;
    }
    ks_datacont_delete(dca);
    ks_datacont_delete(dcb);

    /* Test 3 */
    char* str = "TESTSTRING";
    dca = ks_datacont_new(str, KS_CHARP, 10);
    dcb = ks_datacont_new(&num, KS_INT, 1);
    result = ks_datacont_compare(dca, dcb);
    if (result != KS_CANTCOMPARE) {
        printf("TEST 3: Unexpected comparison result: %d. Expected: %d\n",
               result, KS_CANTCOMPARE);
        retval = -1;
    }
    ks_datacont_delete(dca);
    ks_datacont_delete(dcb);

    /* TEST 4 */
    short arr1[3] = {0xfff0, 0xffff, 0xffff};
    short arr2[2] = {0xffff, 0xffff};

    ks_datacont* dcc = ks_datacont_new(arr1, KS_SHORTP, 3);
    ks_datacont* dcd = ks_datacont_new(arr2, KS_SHORTP, 2);

    result = ks_datacont_compare(dcc, dcd);

    if (result != KS_LESSTHAN) {
        printf("TEST 3: Unexpected comparison result: %d. Expected: %d\n",
               result, KS_CANTCOMPARE);
        retval = -1;
    }

    ks_datacont_delete(dcc);
    ks_datacont_delete(dcd);

    return retval;
}

static int ks_datacont_hash_tests() {
    /* tough to test hashes...
   * probably just make sure hashes of the 
   * same value are equal.
   */
    int retval = 0;
    ks_datacont* dc1 = ks_datacont_new("abcd", KS_CHARP, 5);
    ks_datacont* dc2 = ks_datacont_new("abcd", KS_CHARP, 5);
    unsigned int hash1 = ks_datacont_hash(dc1);
    unsigned int hash2 = ks_datacont_hash(dc2);
    if (hash1 != hash2) {
        printf("TEST 1: Unexpected hash result: %X. Expected: %X\n", hash2,
               hash1);
        retval = -1;
    }
    ks_datacont_delete(dc1);
    ks_datacont_delete(dc2);
    return retval;
}

int main() {
    int retval = 0;

    printf("\nks_datacont tests:\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_datacont_new_tests()...\n");
    if (ks_datacont_new_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_datacont_copy_tests()...\n");
    if (ks_datacont_copy_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_datacont_compare_tests()...\n");
    if (ks_datacont_compare_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    printf("==-----------------------------------==\n");
    printf("Running ks_datacont_hash_tests()...\n");
    if (ks_datacont_hash_tests()) retval = -1;
    printf("done.\n");
    printf("==-----------------------------------==\n\n");

    return retval;
}
