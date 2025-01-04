#include "kylestructs/ks_treesetnode.h"

#include <stdlib.h>

#include "kylestructs/ks_datacont.h"
#include "kylestructs/ks_types.h"

ks_treesetnode* ks_treesetnode_new(const ks_datacont* dc) {
    if (dc == NULL) return NULL;

    ks_treesetnode* tsn = calloc(1, sizeof(ks_treesetnode));

    tsn->dc = (ks_datacont*)dc;

    return tsn;
}

void ks_treesetnode_delete(ks_treesetnode* tsn) {
    if (tsn == NULL) return;

    ks_datacont_delete(tsn->dc);

    free(tsn);
}

ks_treesetnode* ks_treesetnode_copy(const ks_treesetnode* tsn) {
    if (tsn == NULL) return NULL;

    ks_datacont* dc = ks_datacont_copy(tsn->dc);

    return ks_treesetnode_new(dc);
}

void ks_treesetnode_delete_all(ks_treesetnode* tsn) {
    if (tsn == NULL) return;

    ks_treesetnode_delete_all(tsn->left);

    ks_treesetnode_delete_all(tsn->right);

    ks_treesetnode_delete(tsn);
}

ks_treesetnode* ks_treesetnode_copy_all(const ks_treesetnode* tsn) {
    if (tsn == NULL) return NULL;

    ks_treesetnode* tsn_copy = ks_treesetnode_copy(tsn);

    tsn_copy->left = ks_treesetnode_copy_all(tsn->left);
    tsn_copy->right = ks_treesetnode_copy_all(tsn->right);

    return tsn_copy;
}

int ks_treesetnode_add(ks_treesetnode* tsn, const ks_datacont* dc) {
    if (tsn == NULL || dc == NULL) return -1;

    enum ks_comparison result = ks_datacont_compare(dc, tsn->dc);

    if (result == KS_EQUAL) return 1;
    if (result == KS_CANTCOMPARE)
        return -1;

    else if (result == KS_LESSTHAN) {
        if (tsn->left)
            return ks_treesetnode_add(tsn->left, dc);
        else
            tsn->left = ks_treesetnode_new(dc);
    } else {
        if (tsn->right)
            return ks_treesetnode_add(tsn->right, dc);
        else
            tsn->right = ks_treesetnode_new(dc);
    }
    return 0;
}

int ks_treesetnode_remove_by(ks_treesetnode** tsn, const ks_datacont* dc) {
    if (tsn == NULL || *tsn == NULL || dc == NULL) return -1;

    enum ks_comparison result = ks_datacont_compare(dc, (*tsn)->dc);

    if (result == KS_EQUAL) {
        if ((*tsn)->left != NULL && (*tsn)->right != NULL) {
            ks_treesetnode** leftmost = &(*tsn)->right;
            while ((*leftmost)->left) leftmost = &(*leftmost)->left;
            ks_datacont_delete((*tsn)->dc);
            (*tsn)->dc = ks_datacont_copy((*leftmost)->dc);
            return ks_treesetnode_remove_by(leftmost, (*leftmost)->dc);
        } else if ((*tsn)->left) {
            ks_datacont_delete((*tsn)->dc);
            (*tsn)->dc = ks_datacont_copy((*tsn)->left->dc);
            return ks_treesetnode_remove_by(&(*tsn)->left, (*tsn)->left->dc);
        } else if ((*tsn)->right) {
            ks_datacont_delete((*tsn)->dc);
            (*tsn)->dc = ks_datacont_copy((*tsn)->right->dc);
            return ks_treesetnode_remove_by(&(*tsn)->right, (*tsn)->right->dc);
        } else {
            ks_treesetnode_delete(*tsn);
            *tsn = NULL;
            return 0;
        }
    } else if (result == KS_LESSTHAN)
        return ks_treesetnode_remove_by(&(*tsn)->left, dc);
    else if (result == KS_GREATERTHAN)
        return ks_treesetnode_remove_by(&(*tsn)->right, dc);
    return -1;
}

static int __ks_treesetnode_remove_at(ks_treesetnode** tsn, int index,
                                      int* curr_index) {
    if (tsn == NULL || *tsn == NULL) return -1;

    if (index < 0 &&
        (__ks_treesetnode_remove_at(&(*tsn)->right, index, curr_index) == 0))
        return 0;

    else if (__ks_treesetnode_remove_at(&(*tsn)->left, index, curr_index) == 0)
        return 0;

    if (*curr_index == index) return ks_treesetnode_remove_by(tsn, (*tsn)->dc);

    index < 0 ? (*curr_index)-- : (*curr_index)++;

    if (index < 0)
        return __ks_treesetnode_remove_at(&(*tsn)->left, index, curr_index);

    return __ks_treesetnode_remove_at(&(*tsn)->right, index, curr_index);
}

int ks_treesetnode_remove_at(ks_treesetnode** tsn, int index) {
    int curr_index;

    if (index < 0)
        curr_index = -1;
    else
        curr_index = 0;

    return __ks_treesetnode_remove_at(tsn, index, &curr_index);
}

static int __ks_treesetnode_index(const ks_treesetnode* tsn,
                                  const ks_datacont* dc, int* curr_index) {
    if (tsn == NULL) return -1;

    int index;
    if ((index = __ks_treesetnode_index(tsn->left, dc, curr_index)) > -1)
        return index;

    if (ks_datacont_compare(dc, tsn->dc) == KS_EQUAL) return *curr_index;

    (*curr_index)++;

    return __ks_treesetnode_index(tsn->right, dc, curr_index);
}

int ks_treesetnode_index(const ks_treesetnode* tsn, const ks_datacont* dc) {
    int curr_index = 0;

    return __ks_treesetnode_index(tsn, dc, &curr_index);
}

unsigned int ks_treesetnode_contains(const ks_treesetnode* tsn,
                                     const ks_datacont* dc) {
    if (tsn == NULL || dc == NULL) return 0;

    enum ks_comparison result = ks_datacont_compare(dc, tsn->dc);

    if (result == KS_EQUAL) return 1;

    if (result == KS_GREATERTHAN)
        return ks_treesetnode_contains(tsn->right, dc);

    return ks_treesetnode_contains(tsn->left, dc);
}

static ks_datacont* __ks_treesetnode_get(const ks_treesetnode* tsn, int index,
                                         int* curr_index) {
    if (tsn == NULL) return NULL;

    ks_treesetnode* first = index < 0 ? tsn->right : tsn->left;
    ks_treesetnode* second = index < 0 ? tsn->left : tsn->right;

    ks_datacont* dc;

    if ((dc = __ks_treesetnode_get(first, index, curr_index)) != NULL)
        return dc;

    index < 0 ? (*curr_index)-- : (*curr_index)++;

    if (*curr_index == index) return tsn->dc;

    return __ks_treesetnode_get(second, index, curr_index);
}

const ks_datacont* ks_treesetnode_get(const ks_treesetnode* tsn, int index) {
    int curr_index = index < 0 ? 0 : -1;

    return __ks_treesetnode_get(tsn, index, &curr_index);
}

unsigned int ks_treesetnode_count(const ks_treesetnode* tsn) {
    if (tsn == NULL) return 0;

    return 1 + ks_treesetnode_count(tsn->left) +
           ks_treesetnode_count(tsn->right);
}

unsigned int ks_treesetnode_height(const ks_treesetnode* tsn) {
    if (tsn == NULL) return 0;

    unsigned int left_height = ks_treesetnode_height(tsn->left);

    unsigned int right_height = ks_treesetnode_height(tsn->right);

    return 1 + (left_height > right_height ? left_height : right_height);
}

static ks_treesetnode* __ks_treesetnode_balance(ks_treesetnode* tsn, int start,
                                                int end) {
    if (start > end) return NULL;

    int mid = (start + end) / 2;

    ks_datacont* dc = ks_datacont_copy(ks_treesetnode_get(tsn, mid));
    ks_treesetnode* root = ks_treesetnode_new(dc);

    root->left = __ks_treesetnode_balance(tsn, start, mid - 1);
    root->right = __ks_treesetnode_balance(tsn, mid + 1, end);

    return root;
}

ks_treesetnode* ks_treesetnode_balance(ks_treesetnode* root) {
    if (root == NULL) return NULL;

    int count = ks_treesetnode_count(root);

    ks_treesetnode* balanced = __ks_treesetnode_balance(root, 0, count - 1);

    ks_treesetnode_delete_all(root);

    return balanced;
}
